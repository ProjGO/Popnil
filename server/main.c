//
// Created by yuhaorong on 2019/8/31.
//

#include "../common/include/socket_utils.h"
#include "../common/include/rio.h"
#include "login_reg_server.h"
#include "friend_group_server.h"
pool pool_log;
pool pool_chat;
pool pool_file;

int FD_log[100];
int FD_chat[100];
int FD_file[100];

void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
int check_clients(pool *p);

int check_clients(pool *p);
int check_id_log(int fd);

int byte_cnt = 0;

int main(int argc, char **argv)
{
    memset(FD_log,0, sizeof(FD_log));
    memset(FD_chat,0, sizeof(FD_chat));
    memset(FD_file,0,sizeof(FD_file));

    int listenfd, fd_log, port, fd_chat, fd_file;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;

    port=DEFAULT_PORT;
    listenfd = open_listenfd_old(port);
    init_pool(listenfd, &pool_log);
    init_pool(-1, &pool_chat);
    init_pool(-1, &pool_file);
    while(1)
    {
        pool_log.ready_set = pool_log.read_set;
        //select在检查ready_set中为1的那些fd，并将ready_set中可以读取的fd对应的位的值设为1，返回可以读取的fd的数量
        //也因此每次都要将ready_set恢复为标记所有要检查的fd的read_set的值（也就是上面那句）
        pool_log.nready = select(pool_log.maxfd+1, &pool_log.ready_set, NULL, NULL, NULL);
        int op;
        if(FD_ISSET(listenfd, &pool_log.ready_set))
        {
            fd_log = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            rio_t newclient;
            rio_readinitb(&newclient,fd_log);
            rio_readnb(&newclient,&op,sizeof(OP_TYPE));
//            read(fd_log,&op, sizeof(OP_TYPE));
            switch(op)
            {
                case LOGIN: //登录功能
                {
                    login_info *s=(login_info*)malloc(sizeof(login_info));
                    rio_readlineb(&newclient,s,sizeof(login_info));
                    response_s2c *flag=check_login(s);//标识登录是否成功
                    if(flag->return_val)
                    {
                        rio_writen(fd_log,flag,sizeof(response_s2c));
                        FD_log[s->id]=fd_log;
                        //新建两个套接字用于聊天与发文件
                        fd_chat = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
                        fd_file = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
                        FD_chat[s->id]=fd_chat;
                        FD_file[s->id]=fd_file;
                        add_client(fd_log, &pool_log);
//                        add_client(fd_chat,&pool_chat);
//                        add_client(fd_file,&pool_file);
                    }
                    else
                    {
                        rio_writen(fd_log,flag,sizeof(response_s2c));
                        close(fd_log);
                    }
                    free(s);
                    free(flag);
                    break;
                }
                case REGISTER: //注册功能
                {
                    reg_info_c2s *s=(reg_info_c2s*)malloc(sizeof(reg_info_c2s));
                    rio_readnb(&newclient, s, sizeof(reg_info_c2s));
//                    read(fd_log,s,sizeof(reg_info_c2s));
                    response_s2c *flag=reg(s);
                    rio_writen(fd_log,flag, sizeof(response_s2c));
                    free(s);
                    free(flag);
                    close(fd_log);
                    break;
                }
                default:printf("参数传递错误\n");break;
            }
        }
        else
        {
            fd_log=check_clients(&pool_log);
            rio_t newclient;
            rio_readinitb(&newclient,fd_log);
            rio_readnb(&newclient,&op,sizeof(OP_TYPE));
            switch (op)
            {
                case TEXT_trans: { // 如果是文字信息
                    char buf[1024]; // 接收消息用的buf
                    if (rio_readnb(&newclient, buf, sizeof(text_pack_t))>=0) // 如果成功将消息包接收到buf指向的内存中
                    {
                        text_pack_t *text_pack_c2s = (text_pack_t *)buf; // 类型转换
                        text_pack_t text_pack_s2c;
                        int source_id = check_id_log(fd_log);

                        general_array target_ids_array;
                        int *target_ids = (int *) target_ids_array.data;
                        if(text_pack_c2s->id < 10000) {
                            target_ids = (int*)malloc(sizeof(int));
                            target_ids_array.num = 1;
                            target_ids[0] = text_pack_c2s->id;
                        } else
                            target_ids_array = listmembership(text_pack_c2s->id - 10000);

                        for (int j = 0; j < target_ids_array.num; j++) {
                            int target_fd = FD_chat[target_ids[j]]; // 获取目标fd
                            int cur_target_id = target_ids[j];
                            if(cur_target_id != source_id) {
                                rio_writen(target_fd, &op, sizeof(OP_TYPE));
                                text_pack_s2c.id = source_id; // 获取发送者id并填写消息包字段
                                strcpy(text_pack_s2c.text, text_pack_c2s->text); // 将要转发的消息内容填写到要发送出去的消息包中
                                rio_writen(target_fd, &text_pack_s2c, sizeof(text_pack_s2c)); // 发送消息包
                                printf("%d: %s\n", text_pack_s2c.id, text_pack_s2c.text);
                            }
                        }
                        free(target_ids_array.data);
                        target_ids_array.data = NULL;
                    }
                    break;
                };
                case FILE_trans:
                {
                    size_t *file_buf;
                    int filesize, target_id;
                    int source_id = check_id_log(fd_log);
                    file_buf = (size_t*)malloc(MAX_FILE_SIZE*sizeof(size_t));
                    rio_readnb(&newclient, &target_id, sizeof(int));
                    rio_readnb(&newclient, &filesize, sizeof(int)); // 接收文件大小
                    rio_readnb(&newclient, &file_buf, filesize); // 接收文件

                    general_array target_ids_array;
                    int *target_ids = (int *) target_ids_array.data;
                    if(target_id < 10000) {
                        target_ids_array.num = 1;
                        target_ids[0] = target_id;
                    } else
                        target_ids_array = listmembership(target_id-10000);

                    for(int j = 0; j < target_ids_array.num; j++)
                    {
                        int target_fd = FD_chat[target_ids[j]];
                        int cur_target_id = target_ids[j];
                        if(cur_target_id != source_id) {
                            rio_writen(target_fd, &op, sizeof(OP_TYPE));
                            rio_writen(target_fd, &source_id, sizeof(int)); // 发送者id
                            rio_writen(target_fd, &filesize, sizeof(int)); // 发送文件大小
                            rio_writen(target_fd, file_buf, filesize); // 发送文件
                        }
                    }
                    free(target_ids_array.data);
                    target_ids_array.data = NULL;
                    break;
                }
                case SEARCH_FRIEND://查找好友
                {
                    oper_friend_info * s=(oper_friend_info*)malloc(sizeof(oper_friend_info));
                    rio_readnb(&newclient,s,sizeof(oper_friend_info));
                    s->type=SEARCH_FRIEND;
                    s->id_app=check_id_log(fd_log);
                    s->fd_app=fd_log;
                    s->fd_re=FD_log[s->id_re];
                    if(operate_friend(s))
                    {
                        printf("id%d查找id%d成功\n",s->id_app,s->id_re);
                    }
                    else
                    {
                        printf("查找好友失败\n");
                    }
                    free(s);
                    break;
                }
                case ADD_FRIEND: //添加好友
                {
                    oper_friend_info * s=(oper_friend_info*)malloc(sizeof(oper_friend_info));
                    rio_readnb(&newclient,s,sizeof(oper_friend_info));
                    s->type=ADD_FRIEND;
                    s->id_app=check_id_log(fd_log);
                    s->fd_app=fd_log;
                    s->fd_re=FD_log[s->id_re];
                    if(operate_friend(s))
                    {
                        printf("id%d与id%d添加好友成功\n",s->id_app,s->id_re);
                    }
                    else
                    {
                        printf("添加好友失败\n");
                    }
                    free(s);
                    break;
                }
                case DELETE_FRIEND://删除好友
                {
                    oper_friend_info * s=(oper_friend_info*)malloc(sizeof(oper_friend_info));
                    rio_readnb(&newclient,s,sizeof(oper_friend_info));
                    s->type=DELETE_FRIEND;
                    s->id_app=check_id_log(fd_log);
                    if(operate_friend(s))
                    {
                        printf("id%d与id%d删除好友成功\n",s->id_app,s->id_re);
                    }
                    else
                    {
                        printf("删除好友失败\n");
                    }
                    free(s);
                    break;
                }
                case ADD_GROUP://创建群组
                {
                    oper_group_info * s=(oper_group_info*)malloc(sizeof(oper_group_info));
                    rio_readnb(&newclient,s,sizeof(oper_friend_info));
                    s->type=ADD_GROUP;
                    s->owner_id=check_id_log(fd_log);
                    if(operate_group(s))
                    {
                        printf("id%d创建群%d\n",s->owner_id,s->group_id);
                    }
                    else
                    {
                        printf("创建群失败\n");
                    }
                    free(s);
                    break;
                }
//                case DELETE_GROUP
                case JOIN_GROUP://加入群组
                {
                    oper_group_info * s=(oper_group_info*)malloc(sizeof(oper_group_info));
                    rio_readnb(&newclient,s,sizeof(oper_friend_info));
                    s->type=JOIN_GROUP;
                    s->client_id=check_id_log(fd_log);
                    if(operate_group(s))
                    {
                        printf("id%d加入群%d\n",s->client_id,s->group_id);
                    }
                    else
                    {
                        printf("加入群失败\n");
                    }
                    free(s);
                    break;
                }
                case QUIT_GROUP://退出群组
                {
                    oper_group_info * s=(oper_group_info*)malloc(sizeof(oper_group_info));
                    rio_readnb(&newclient,s,sizeof(oper_friend_info));
                    s->type=QUIT_GROUP;
                    s->client_id=check_id_log(fd_log);
                    if(operate_group(s))
                    {
                        printf("id%d退出群%d\n",s->client_id,s->group_id);
                    }
                    else
                    {
                        printf("退出群失败\n");
                    }
                    free(s);
                    break;
                }
                case UPDATE: // 拉取好友信息
                {
                    int user_id;
                    client_info cur_friend_info;
                    rio_readnb(&newclient, &user_id, sizeof(int)); // 从客户端接收用户id
                    client_info user_info = getuser(user_id); // 获取用户本人的信息
                    write(fd_log, &user_info, sizeof(client_info)); // 发送用户本人信息
                    
                    general_array related_ids_array = listfriendship(user_id); // 获取用户好友及群的信息
                    int related_ids_num = related_ids_array.num;
                    int *related_ids = (int*)related_ids_array.data;
                    write(fd_log, &related_ids_num, sizeof(int)); // 告诉客户端有几个要传
                    for(int i = 0; i < related_ids_num; i++)
                    {
                        ///zzk changed
                        cur_friend_info.id = related_ids[i];
                        client_info tem;
                        tem = getuser(cur_friend_info.id);
                        write(fd_log,&tem, sizeof(client_info));
                        //向客户端逐条发好友信息
                    }
                }
            }
        }
    }
}

void init_pool(int listenfd, pool *p)
{
    int i;
    p->maxi = -1;
    for(i = 0; i < FD_SETSIZE; i++)
        p->clientfd[i] = -1;

    //开始时只有listenfd是select要检查的fd(也就是read_set)
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    if(listenfd >= 0)
        FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p)
{
    int i;
    p->nready--;
    for(i = 0; i < FD_SETSIZE; i++)
        if(p->clientfd[i] < 0)
        {
            p->clientfd[i] = connfd;
            rio_readinitb(&p->clientrio[i], connfd);

            //将新客户端的connfd加入到read_set中
            FD_SET(connfd, &p->read_set);

            if(connfd > p->maxfd)
                p->maxfd = connfd;
            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    if(i == FD_SETSIZE)
        fprintf(stderr, "add_client error: too many clients\n");
}

int check_clients(pool *p)
{
    int i, connfd, n;
    char buf[1024];
    rio_t rio;

    for(i = 0; (i <= p->maxi) && (p->nready > 0); i++)
    {
        connfd = p->clientfd[i];
        if((connfd > 0) && (FD_ISSET(connfd, &p->ready_set)))
            return connfd;
    }
}

int check_id_log(int fd)
{
    int i;
    for(i=0;i<100;i++)
    {
        if(FD_log[i]==fd)
        {
            return i;
        }
    }
}
