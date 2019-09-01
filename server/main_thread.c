//
// Created by yuhaorong on 2019/8/30.
//

/*-----------------------------------------------------假的----------------------------------------------------*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../common/include/rio.h"
#include "../common/include/socket_utils.h"
#include "../common/include/define.h"

#define MAXCLIENT 1024

int fd2ip[MAXCLIENT];
int fd2port[MAXCLIENT];
int client_cnt = 0;

int findFdByIp(int ip)
{
    for(int i = 0; i < client_cnt; i++)
        if(ip == fd2ip[i])
            return i;
    return -1;
}

int findFdByPort(int port)
{
    for(int i = 0; i < client_cnt; i++)
        if(port == fd2port[i])
            return i;
    return -1;
}

/*用于传给负责这个新client的线程，其中包含了分配给这个连接的fd和这个client的地址信息*/
struct client_fd_and_ip
{
    int connfd;
    struct sockaddr *addr;
};

void *thread_for_one_client(void* vargp);

int main(int argc, char **argv)
{
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int listenfd, *connfdp;
    struct sockaddr clientaddr;
    pthread_t tid;

    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    char *port = argv[1];
    listenfd = open_listenfd_old(atoi(port));

    printf("server started successfully, running on port %d\n", atoi(port));

    while(1)
    {
        struct client_fd_and_ip *new_client;
        new_client = malloc(sizeof(struct client_fd_and_ip));
        // 新建连接，并将fd和client的addr写入new_client传给负责这个client的线程
        new_client->connfd = Accept(listenfd, new_client->addr, &addrlen);
        pthread_create(&tid, NULL, thread_for_one_client, (void*)new_client);

    }
}

void* thread_for_one_client(void *vargp)
{
    struct client_fd_and_ip* client_info = (struct client_fd_and_ip*)vargp;
    pthread_detach(pthread_self());
    printf("new thread created, pid: %lu, connfd: %d\n", pthread_self(), client_info->connfd);

    char* buf = malloc(MAX_MSG_LEN*sizeof(char));
    rio_t rio;
    rio_readinitb(&rio, client_info->connfd);
    while(1) {
        Rio_readlineb(&rio, buf, MAX_MSG_LEN);

        MSG_TYPE msg_type;
        sscanf(buf, "%d", &msg_type);

        int n_byte;
        switch (msg_type) {
            case TEXT:
                n_byte = Rio_readnb(&rio, buf, sizeof(text_pack_t));
                printf("received %d bytes from %d\n", n_byte, client_info->connfd);
                text_pack_t *textpack_p = (text_pack_t*)buf;
                // int target_connfd = findFdByIp(textpack_p->target);
                // int target_connfd = findFdByPort(textpack_p->port);
                int target_connfd = 5;
                Rio_writen(target_connfd, textpack_p->text, MAXLEN);

            case PIC:
                break;

            default:
                ;
        }
    }




}

//void* thread(void *vargp)
//{
//    int fd;
//    vargp = (struct text_pack_t*)vargp;
//    pthread_detach(pthread_self());
//    free(vargp);
//    if((fd = findFd(ntohl(tp.target.s_addr))) < 0) {
//        printf("fd not found\n");
//        pthread_exit(NULL);
//    }
//    Rio_writen(fd, (void*)&(vargp->text), sizeof(vargp->text));
//    free(vargp);
//}
