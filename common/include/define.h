//
// Created by yuhaorong on 2019/8/30.
//

#ifndef LINPOP_DEFINE_H
#define LINPOP_DEFINE_H

#include "rio.h"
#include <gtk/gtk.h>

#define TIME_INFO_LEN 20 // YYYY_MM_DD_HH_MM_SS
#define MAX_NAME_LEN 32
#define MAX_PWD_LEN 512
#define MAX_MSG_LEN 512
#define MAX_USR_NUM 100
#define MAX_FILE_SIZE (1024*1024*20)
#define MAX_FILENAME_LENGTH 256
#define DEFAULT_PORT 8088
#define DEFAULT_IP "127.0.0.1"

/*-----------------------------------用户登陆注册等相关------------------------------------*/
typedef enum OP_TYPE {LOGIN, REGISTER,SEARCH_FRIEND,ADD_FRIEND,DELETE_FRIEND,ADD_GROUP,DELETE_GROUP,
                      JOIN_GROUP,QUIT_GROUP,UPDATE, TEXT_trans, FILE_trans} OP_TYPE;

typedef struct client_info
{
    int id;
    char passwd[32];
    char nickname[32];
    char bio[1024];
    char birthday[20];
    int portrait_idx;
}client_info;

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

typedef struct oper_friend_info
{
    int type;//定义信息类型 与optype一致
    int id_app;//申请方id
    int fd_app;//申请方fd
    int id_re;//被申请方id
    int fd_re;//被申请方fd
    int response;//回应：1：同意 2：拒绝
    char msg[100];//提示信息
} oper_friend_info;

typedef struct oper_group_info
{
    int type;//定义信息类型 与optype一致
    char group_name[MAX_NAME_LEN];
    int group_id;
    int owner_id;//创建者id
    int client_id;//进行操作者id
} oper_group_info;

//typedef struct add_group_c2s
//{
//    int group_id;
//} add_group_c2s;
//
//typedef struct quit_group_c2s
//{
//    int group_id;
//} quit_group_c2s;

typedef struct friend_info_s2c
{
    int id;
    char name[MAX_NAME_LEN];
    int pic;
} friend_info;

typedef struct response_s2c
{
    int return_val; //0表示操作失败，1表示操作成功
    char err_msg[MAX_MSG_LEN];
} response_s2c;


/*-----------------------------------聊天相关------------------------------------*/
typedef enum MSG_TYPE {TEeXT, PIC} MSG_TYPE;

typedef struct text_pack_t
{
    int id;
    char time[TIME_INFO_LEN];
    char text[MAX_MSG_LEN];
} text_pack_t;

typedef struct file_request_s2c
{
    int source_id;
} file_requese_s2c;


/*-----------------------------------其它------------------------------------*/
typedef struct pool{
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} pool;

typedef struct general_array
{
    int num;
    int size;
    void *data;
} general_array;

typedef enum Permission
{
    owner,
    admin,
    none
} Permission;



//记录每个好友和群组的信息
struct  friend_and_group
{
    GtkWidget* vbox; //vbox代表在哪一个列表中
    GtkWidget* button; //button代表在列表中哪一个控件中
    int id;
    char *number_name[25];
    char *list_name[25];
    gboolean is_empty; //判断该位置是否可以存储好友信息
    int friend_group_num; //记录每列中好友的个数
};

#endif //LINPOP_DEFINE_H
