//
// Created by yuhaorong on 2019/8/31.
//

#ifndef LINPOP_COMMUNICATION_H
#define LINPOP_COMMUNICATION_H

#include "rio.h"

/*向target_id发送text中的信息，成功返回0，失败返回-1*/
int send_text_message(int target_id, char *text, int connfd, void *buf);

/*从connfd中接受text_pack, 并储存到buf中,读取时用rp指向的rio作为buf*/
int recv_text_message(int connfd, void *buf, rio_t *rp);

#endif //LINPOP_COMMUNICATION_H
