//
// Created by yuhaorong on 2019/8/30.
//

#ifndef LINPOP_RIO_H
#define LINPOP_RIO_H

#define RIO_BUFSIZE 8192
typedef struct rio_t {
    int rio_fd;                /* descriptor for this internal buf */
    int rio_cnt;               /* unread bytes in internal buf */
    char *rio_bufptr;          /* next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE]; /* internal buffer */
} rio_t;

/*以下两个均为unbuffered*/
/*从fd中读取n字节信息到usrbuf中*/
ssize_t Rio_readn(int fd, void *ptr, size_t nbytes);

/*向fd中写usrbuf指向的n个字节*/
void Rio_writen(int fd, void *usrbuf, size_t n);
void rio_writen(int fd, void *usrbuf, size_t n);

/*以下均为buffered*/
/*初始化一个rio_t*/
void rio_readinitb(struct rio_t *rp, int fd);

/*从一个已经被初始化的rio_t中读取n个字节到usrbuf指向的空间中*/
ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n);

/*从一个已经被初始化的rio_t中读取一行字符到usrbuf中*/
ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);



#endif //LINPOP_RIO_H
