//
// Created by yuhaorong on 2019/8/30.
//
/*---------------------------------------------假的----------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../common/include/socket_utils.h"
#include "../common/include/rio.h"
#include "../common/include/define.h"

int main(int argc, char **argv)
{
    int clientfd;
    char *hostname, *port;
    rio_t rio;

    if(argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    hostname = argv[1];
    port = argv[2];

    int targetport = 0;
//    printf("input target host port:\n");
//    getchar();
//    scanf("%d\n", &targetport);

    if((clientfd = open_clientfd_old(hostname, atoi(port))) >= 0)
        printf("connection established, clientfd: %d\n", clientfd);
    else
        printf("connection establish failed\n");
    rio_readinitb(&rio, clientfd);
    text_pack_t text_pack;
    char type_buf[MAX_MSG_LEN];
    memset(type_buf, 0, sizeof(type_buf));
    while(1)
    {
        fflush(stdin);
        scanf("%s", text_pack.text);
        strcpy(type_buf, "0");
        Rio_writen(clientfd, type_buf, sizeof(type_buf));
        memset(&text_pack, 0, sizeof(text_pack));
        text_pack.target = htonl(0x7F000001);
        text_pack.port = targetport;
        Rio_writen(clientfd, text_pack.text, sizeof(text_pack.text));
    }
}

void* thread_for_receiving_msg(void *argp)
{
    int connfd = *(int*)argp;
    pthread_detach(pthread_self());
    rio_t rio;

}