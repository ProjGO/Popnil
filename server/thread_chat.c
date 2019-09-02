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
    int connfd;

    size_t *buf = malloc(sizeof(pic_pack_t)); // 接收消息用的buf,既用来接收消息内容，又作数据包的缓存,最大也就可能装图片包了
    general_array target_ids_array;
    text_pack_t text_pack_s2c; // 服务器要转发出去的消息包
    pic_pack_t pic_pack_s2c; // 服务器要转发出去的图片包

    rio_t *rio; // ==========================
    while(1) {
        pool_chat.ready_set = pool_chat.ready_set;
        pool_chat.nready = select(pool_chat.maxfd + 1, &pool_chat.ready_set, NULL, NULL, NULL);
        for (int i = 0; (i <= pool_chat.maxi && i <= pool_chat.nready); i++) {
            connfd = pool_chat.clientfd[i]; // 现在在检查的这个connfd
            rio = &pool_chat.clientrio[i]; // 现在在检查的这个connfd对应的rio_t
            MSG_TYPE msg_type; // 接收到的消息的类型
            int target_fd; // 要转发的目标的fd

            if ((connfd > 0) && (FD_ISSET(connfd, &pool_chat.ready_set))) // 如果正在检查的这个connfd确实可以读取
            {
                pool_chat.nready--; //
                rio_readlineb(rio, buf, MAX_MSG_LEN); // 先从这个connfd读取消息类型
                sscanf(buf, "%d", &msg_type); // 字符串->数字
                printf("received msg_type %d from user %d\n", msg_type, get_id_by_fd(connfd));
                switch (msg_type) {
                    case TEXT: { // 如果是文字信息
                        if (rio_readnb(rio, buf, sizeof(text_pack_t))>=0) // 如果成功将消息包接收到buf指向的内存中
                        {
                            text_pack_t *text_pack_c2s = (text_pack_t *) buf; // 类型转换
                            int *target_ids = (int *) target_ids_array.data; // 类型转换以读取array中的内容
                            // 调试用-------------------------------
                            target_ids_array.num  = 1;
                            target_ids[0] = text_pack_c2s->id;
                            // ------------------------------------
                            for (int j = 0; j < target_ids_array.num; j++) {
                                target_fd = get_fd_by_id(target_ids[j]); // 获取目标fd
                                text_pack_s2c.id = get_id_by_fd(connfd); // 获取发送者id并填写消息包字段
                                strcpy(text_pack_s2c.text, text_pack_c2s->text); // 将要转发的消息内容填写到要发送出去的消息包中
                                rio_writen(target_fd, &text_pack_s2c, sizeof(text_pack_s2c)); // 发送消息包
                                printf("%d: %s\n", text_pack_s2c.id, text_pack_s2c.text);
                            }
                        }
                        break;
                    }
                    case PIC: {
//                        int pic_size; // 照片的大小
//                        rio_readnb(rio, &pic_size, sizeof(int)); // 得到图片大小
                        rio_readnb(rio, &buf, sizeof(pic_pack_t)); // 接收图片包到buf
                        pic_pack_t *pic_pack_c2s = (pic_pack_t*)buf;
                        memcpy(pic_pack_s2c.data, pic_pack_c2s->data, pic_pack_c2s->size); // 将图片填如待发出的数据包
                        int *target_ids = (int *) target_ids_array.data; // 类型转换以读取array中的内容
                        // 调试用-------------------------------
                        target_ids_array.num  = 1;
                        target_ids[0] = pic_pack_c2s->id;
                        // ------------------------------------
                        for (int j = 0; j < target_ids_array.num; j++) {
                            target_fd = get_fd_by_id(target_ids[j]); // 获取目标fd
                            pic_pack_s2c.id = get_id_by_fd(connfd); // 获取发送者id并填写消息包字段
                            rio_writen(target_fd, &pic_pack_s2c, sizeof(pic_pack_s2c)); // 发送消息包
                            printf("%d: send a picture\n", text_pack_s2c.id);
                        }
                    }
                    default:;
                }

            }
        }
    }
}

int get_id_by_fd(int fd)
{
    for(int i=0; i < 100; i++)
        if(FD_chat[i] == fd)
            return i;
    return -1;
}

int get_fd_by_id(int id)
{
    return FD_chat[id];
}