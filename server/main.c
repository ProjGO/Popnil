//
// Created by yuhaorong on 2019/8/31.
//

#include "../common/include/socket_utils.h"
#include "../common/include/rio.h"
#include "login_on_server.h"

pool pool_log;
pool pool_chat;
pool pool_file;

int FD_log[100];
int FD_chat[100];
int FD_file[100];

void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);

int byte_cnt = 0;

int main(int argc, char **argv)
{
    memset(FD_log,0, sizeof(FD_log));
    memset(FD_chat,0, sizeof(FD_chat));
    memset(FD_file,0,sizeof(FD_file));

    int listenfd, fd_log, port,fd_chat,fd_file;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;

    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);

    listenfd = open_listenfd_old(port);
    init_pool(listenfd, &pool_log);
    while(1)
    {
        pool_log.ready_set = pool_log.read_set;
        //select在检查ready_set中为1的那些fd，并将ready_set中可以读取的fd对应的位的值设为1，返回可以读取的fd的数量
        //也因此每次都要将ready_set恢复为标记所有要检查的fd的read_set的值（也就是上面那句）
        pool_log.nready = select(pool_log.maxfd+1, &pool_log.ready_set, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &pool_log.ready_set))
        {
            enum OP_TYPE op;
            fd_log = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            rio_t newclient;
            rio_readinitb(&newclient,fd_log);
            Rio_readlineb(&newclient,op,sizeof(OP_TYPE));
            switch(op)
            {
                case LOGIN: //登录功能
                {
                    login_info *s;
                    Rio_readlineb(&newclient,s,sizeof(s));
                    response_s2c *flag=check_login(s);//标识登录是否成功
                    if(flag->return_val)
                    {
                        Rio_writen(fd_log,flag,sizeof(response_s2c));
                        FD_log[s->id]=fd_log;
                        fd_chat = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
                        fd_file = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
                        FD_chat[s->id]=fd_chat;
                        FD_file[s->id]=fd_file;
                        add_client(fd_log, &pool_log);
                        add_client(fd_chat,&pool_chat);
                        add_client(fd_file,&pool_file);
                    }
                    else
                    {
                        Rio_writen(fd_log,&flag,sizeof(int));
                    }
                }
            }
        }

        check_clients(&pool_log);
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

void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[1024];
    rio_t rio;

    for(i = 0; (i <= p->maxi) && (p->nready > 0); i++)
    {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if((connfd > 0) && (FD_ISSET(connfd, &p->ready_set)))
        {
            p->nready--;
            if((n=Rio_readlineb(&rio, buf, 1024)) != 0)
            {
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
                Rio_writen(connfd, buf, n);
            }
        }
        else
        {
            close(connfd);
            FD_CLR(connfd, &p->read_set);
            p->clientfd[i] = -1;
        }
    }
}