//
// Created by yuhaorong on 2019/8/30.
//

#ifndef LINPOP_DEFINE_H
#define LINPOP_DEFINE_H

#define TIME_INFO_LEN 20 // YYYY_MM_DD_HH_MM_SS
#define MAX_NAME_LEN 32
#define MAX_PWD_LEN 512
#define MAX_MSG_LEN 512

typedef enum OP_TYPE {LOGIN, LOGON,ADD_FRIEND,ADD_GROUP,QUIT_GROUP} OP_TYPE;

typedef struct login_info_c2s
{
    int id;
    char pwd[MAX_PWD_LEN];
} login_info;

typedef struct logon_info_c2s
{
    char name[MAX_NAME_LEN];
    char pwd[MAX_PWD_LEN];
} logon_info_c2s;

typedef struct new_friend_info_c2s
{
    int friend_id;
} new_friend_info;

typedef struct new_friend_request_s2c
{
    int friend_id;
} new_friend_request_s2c;

typedef struct new_group_c2s
{
    char group_name[MAX_NAME_LEN];
} new_group_s2c;

typedef struct add_group_c2s
{
    int group_id;
} add_group_c2s;

typedef struct quit_group_c2s
{
    int group_id;
} quit_group_c2s;

typedef struct response_s2c
{
    int return_val;
    char err_msg[MAX_MSG_LEN];
} response_s2c;



typedef enum MSG_TYPE {TEXT, PIC} MSG_TYPE;

typedef struct text_pack_t_c2s
{
    int target_id;
    char time;
    char text[MAX_MSG_LEN];
} text_pack_t;

typedef struct text_pack_t_s2c
{
    int source_id;

    char text[MAX_MSG_LEN];
} text_pack_t_s2c;

typedef struct file_request_s2c
{
    int source_id;

} file_requese_s2c;

typedef struct pool{
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} pool;
#endif //LINPOP_DEFINE_H
