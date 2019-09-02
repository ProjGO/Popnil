//
// Created by yuhaorong on 2019/8/31.
//

#ifndef LINPOP_INCLUDE_H
#define LINPOP_INCLUDE_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../include/rio.h"
#include "../include/socket_utils.h"
#include "../include/define.h"

#endif //LINPOP_INCLUDE_H

extern int FD_log[100];
extern int FD_chat[100];
extern int FD_file[100];