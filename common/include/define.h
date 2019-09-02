//
// Created by yuhaorong on 2019/8/30.
//

#ifndef LINPOP_DEFINE_H
#define LINPOP_DEFINE_H

#include "rio.h"


#define TIME_INFO_LEN 20 // YYYY_MM_DD_HH_MM_SS
#define MAX_NAME_LEN 32
#define MAX_PWD_LEN 512
#define MAX_MSG_LEN 512
#define MAX_PIC_SIZE (1024*1024*3) // 1Mb
#define DEFAULT_PORT 8088

typedef enum OP_TYPE {LOGIN, REGISTER, ADD_FRIEND, ADD_GROUP, QUIT_GROUP, UPDATE} OP_TYPE;

typedef struct login_info_c2s
{
    int id;
    char pwd[MAX_PWD_LEN];
} login_info;

typedef struct reg_info_c2s
{
    char name[MAX_NAME_LEN];
    char pwd[MAX_PWD_LEN];
} reg_info_c2s;

typedef struct new_friend_info
{
    int type;//定义信息类型，1：申请加好友c2s 2:申请加好友s2c 3:回应加好友c2s 4:回应加好友s2c;
    int id_app;//申请方id
    int id_re;//被申请方id
    int response;//回应：1：同意 2：拒绝
    char msg[100];//提示信息
} new_friend_info;

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
    int return_val; //0表示操作失败，1表示操作成功
    char err_msg[MAX_MSG_LEN];
} response_s2c;

typedef struct friend_info_s2c // 同步过程中服务器传给客户端的每个用户的信息
{
    int id;
    char name[MAX_NAME_LEN]; // 昵称
    char group_name[MAX_NAME_LEN]; // 所属分组名称
    int pic;  // 头像编号
} friend_info_s2c;

typedef struct friend_info_array_c // 客户端收到的好友信息会保存在这个里面
{
    int friend_num; // 好友数量
    // 使用后记得free
    struct friend_info_s2c *data; // 指向实际的数据,大小为friend_num*sizeof(friend_info_s2c)
} friend_info_array_c;



typedef enum MSG_TYPE {TEXT, PIC} MSG_TYPE;

typedef struct text_pack_t_c2s
{
    int target_id;
    char time;
    char text[MAX_MSG_LEN];
} text_pack_t_c2s;

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

typedef struct general_array{
    int num; // 数量
    int size; // 每项的大小
    void *data; // 实际数据
} general_array;