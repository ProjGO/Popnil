//
// Created by yuhaorong on 2019/8/31.
//

#ifndef LINPOP_COMMUNICATION_H
#define LINPOP_COMMUNICATION_H

#include "include.h"

/*向target_id发送text中的信息，成功返回0，失败返回-1*/
int send_text_message(int target_id, char *text, int connfd, void *buf);

#endif //LINPOP_COMMUNICATION_H
