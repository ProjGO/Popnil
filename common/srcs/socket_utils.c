//
// Created by yuhaorong on 2019/8/30.
//

#include "../include/socket_utils.h"

int Socket(int domain, int type, int protocol)
{
    int rc;

    if ((rc = socket(domain, type, protocol)) < 0)
        unix_error("Socket error");
    return rc;
}

void Setsockopt(int s, int level, int optname, const void *optval, int optlen)
{
    int rc;

    if ((rc = setsockopt(s, level, optname, optval, optlen)) < 0)
        unix_error("Setsockopt error");
}

void Bind(int sockfd, struct sockaddr *my_addr, int addrlen)
{
    int rc;

    if ((rc = bind(sockfd, my_addr, addrlen)) < 0)
        unix_error("Bind error");
}

void Listen(int s, int backlog)
{
    int rc;

    if ((rc = listen(s,  backlog)) < 0)
        unix_error("Listen error");
}

int Accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    int rc;

    if ((rc = accept(s, addr, addrlen)) < 0)
        unix_error("Accept error");
    return rc;
}

void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen)
{
    int rc;

    if ((rc = connect(sockfd, serv_addr, addrlen)) < 0)
        unix_error("Connect error");
}

int open_clientfd(char *hostname, char *port)
{
    int clientfd;
    struct addrinfo hints, *listp, *p;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
    getaddrinfo(hostname, port, &hints, &listp);

    for(p = listp; p; p = p->ai_next) {
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue; // 若socket建立失败直接尝试下一个
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break; // 连接成功，不用继续尝试
        close(clientfd); // 这次尝试失败，关闭这个clientfd
    }

    freeaddrinfo(listp);
    if(!p)
        return -1;
    else
        return clientfd;
}

int open_listenfd(char *port)
{
    struct addrinfo hints, *listp, *p;
    int listenfd, optval = 1;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // 被动接受来自任意ip的连接
    hints.ai_flags |= AI_NUMERICSERV; // 将port解释为端口号
    getaddrinfo(NULL, port, &hints, &listp); // 因为是服务器，并不需要hostname

    for(p = listp; p; p = p->ai_next)
    {
        if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;
        Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));

        if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break;
        close(listenfd);
    }

    freeaddrinfo(listp);
    if(!p)
        return -1;

    if(listen(listenfd, 1024) < 0)
    {
        close(listenfd);
        return -1;
    }

    return listenfd;
}

int open_clientfd_old(char *hostname, int port)
{
    int clientfd;
    struct hostent* hp;
    struct sockaddr_in serveraddr;

    if((clientfd = Socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    if((hp = gethostbyname(hostname)) == NULL)
        return -2;

    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char*)hp->h_addr_list[0],
          (char*)&serveraddr.sin_addr.s_addr, hp->h_length);
    serveraddr.sin_port = htons(port);

    if(connect(clientfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
        return -1;

    return clientfd;
}

int open_listenfd_old(int port)
{
    int listenfd, optval=1;
    struct sockaddr_in serveraddr;

    if((listenfd = Socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int)) < 0)
        return -1;

    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // 接受来自任意IP的连接
    serveraddr.sin_port = htons((unsigned short) port);

    if(bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
        return -1;

    if(listen(listenfd, 1024) < 0)
        return -1;

    return listenfd;
}
