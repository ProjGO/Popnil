//
// Created by hsx on 2019/8/30.
//

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "../common/include/include.h"
#include "../common/include/rio.h"
#include "../common/include/define.h"
#include "tools.h"

extern int login (int argc, char *argv[]);
//extern GtkWidget* window();

int fd_log, fd_chat, fd_file;
rio_t rio_log, rio_chat, rio_file;

int all_ids[100]; // 所有与这个人有关系的id,在登陆时由服务器告知,并在加好友/群时更新
int all_ids_cnt; // 字面意思
int usr_id; // 这个用户本人的id
client_info my_info;
client_info target;

int max_chat_window_idx = 0; // opened_lists中最大可用下标值
GtkWidget* idx2window[100]; // id->window的指针
GtkWidget* id2button[100]; //
SunGtkCList* idx2list[100]; // id->list的指针
int opend_list_idx2id[100]; // 已经打开的list->它们对应的id

general_array friendlist;

int main(int argc, char *argv[]){
    rio_readinitb(&rio_log, fd_log);

//    GtkWidget *w = window();
//    gtk_widget_show_all(w);
    login(argc, argv);

    //sign(argc, argv);
    //sign_success(argc, argv);
    return 0;
}

client_info get_info_by_id(int id)
{
    client_info result;
    client_info *client_info_list = (client_info*)friendlist.data;
    for(int i = 0; i < MAX_USR_NUM; i++)
        if(client_info_list[i].id == id)
            return client_info_list[i];
    printf("info not found by id\n");
    exit(-1);
}
