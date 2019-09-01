//
// Created by yuhaorong on 2019/8/30.
//

#ifndef LINPOP_SOCKET_UILS_H
#define LINPOP_SOCKET_UILS_H

#include "include.h"

/*简单的包装，出错时打印所无信息*/
int Socket(int domin, int type, int protocol);
void Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
void Listen(int s, int backlog);
/*等待建立连接
 * s:用于监听的file descriptor
 * addr：建立成功后将客户端的socket填入到addr指向的sockaddr中
 * addrlen：将得到的sockaddr(也就是第二个参数addr)的大小填入addrlen指向的int
 * */
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
void Setsockopt(int s, int level, int optname, const void *optval, int optlen);

/*建立客户端socket并完成connect，即已经与服务器建立连接，可以读写数据
 * hostname：ip地址（xxx.xxx.xxx.xxx）或域名，字符串
 * port：要连接的端口
 * 返回：连接后的file descriptor
 * */
int open_clientfd(char *hostname, char *port);
int open_clientfd_old(char *hostname, int port);
/*建立服务器端的socket并完成bind与listen，之后可以直接用于accept
 * port：要连接的端口
 * 返回：可以用于listen的file descriptor
 * */
int open_listenfd(char *port);
int open_listenfd_old(int port);

#endif //LINPOP_SOCKET_UILS_H
