//
// Created by yuhaorong on 2019/9/1.
//

#include "../common/include/define.h"
#include "../common/include/include.h"
#include "../common/include/communication.h"

extern pool pool_chat;
extern int FD_chat[100]; // 用户id -> fd

int get_id_by_fd(int fd);
int get_fd_by_id(int id);

void *thread_chat(void *vargp)
{
    int connfd, n;
    char buf[1024]; // 接收消息用的buf
    char pic_buf[MAX_PIC_SIZE]; // 接收图片用的buf
    rio_t *rio; // ==========================
    while(1) {
        pool_chat.ready_set = pool_chat.ready_set;
        pool_chat.nready = select(pool_chat.maxfd + 1, &pool_chat.ready_set, NULL, NULL, NULL);
        for (int i = 0; (i <= pool_chat.maxi && i <= pool_chat.nready); i++) {
            connfd = pool_chat.clientfd[i]; // 现在在检查的这个connfd
            rio = &pool_chat.clientrio[i]; // 现在在检查的这个connfd对应的rio_t
            MSG_TYPE msg_type; // 接收到的消息的类型
            text_pack_t_s2c text_pack_s2c; // 服务器要转发出去的消息包
            int target_fd; // 要转发的目标的fd

            if ((connfd > 0) && (FD_ISSET(connfd, pool_chat.ready_set))) // 如果正在检查的这个connfd确实可以读取
            {
                pool_chat.nready--; //
                n = Rio_readlineb(rio, buf, sizeof(MSG_TYPE)); // 先从这个connfd读取消息类型
                sscanf(buf, "%d", &msg_type); // 字符串->数字
                printf("received msg_type %d from user %d\n", msg_type, get_id_by_fd(connfd));
                switch (msg_type) {
                    case TEXT: // 如果是文字信息
                        if (recv_text_message(connfd, buf, rio) == 0) // 如果成功将消息包接收到buf指向的内存中
                        {
                            text_pack_t_c2s *text_pack_c2s = (text_pack_t_c2s *) buf; // 类型转换
                            target_fd = get_fd_by_id(text_pack_c2s->target_id); // 获取目标fd
                            text_pack_s2c.source_id = get_id_by_fd(connfd); // 获取发送者id并填写消息包字段
                            strcpy(text_pack_s2c.text, text_pack_c2s->text); // 将要转发的消息内容填写到要发送出去的消息包中
                            Rio_writen(target_fd, &text_pack_s2c, sizeof(text_pack_s2c)); // 发送消息包
                            printf("%d: %s\n", text_pack_s2c.source_id, text_pack_s2c.text);
                        }
                    case PIC:
                        int pic_size; // 照片的大小
                        Rio_readn(rio, pic_buf, pic_size);
                        // 将图片保存在本地
                        // 将图片显示在聊天框中
                    default:;
                }

            }
        }
    }
}

int get_id_by_fd(int fd)
{
    for(int i=0; i < MAX_USR_NUM; i++)
        if(FD_chat[i] == fd)
            return i;
    return -1;
}

int get_fd_by_id(int id)
{
    return FD_chat[id];
}