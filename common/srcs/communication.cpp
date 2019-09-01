//
// Created by yuhaorong on 2019/8/31.
//

#include "../include/communication.h"

int send_text_message(int target_id, char *text, int connfd, void *buf)
{
    int n;
    text_pack_t *text_pack_buf = (text_pack_t*)buf;
    text_pack_buf->target_id = target_id;
    strcpy(text_pack_buf->text, text);
    if((n = rio_writen(connfd, buf, sizeof(text_pack_t))) != sizeof(text_pack_t))
        return -1;
    return 0;
}

int recv_text_message(int connfd, void *buf, rio_t *rp)
{
    int n;
    if((n = rio_readnb(rp, buf, sizeof(text_pack_t))) != sizeof(text_pack_t))
        return -1;
    return 0;
}