//
// Created by hsx on 2019/8/30.
//

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "../common/include/include.h"
#include "../common/include/rio.h"

extern int login (int argc, char *argv[]);
//extern GtkWidget* window();

int fd_log, fd_chat, fd_file;
rio_t rio_log, rio_char, rio_file;

int all_ids[100]; // 所有与这个人有关系的id,在登陆时由服务器告知,并在加好友/群时更新
int all_ids_cnt; // 字面意思

GtkWidget* id2window[100];

int main(int argc, char *argv[]){
    rio_readinitb(&rio_log, fd_log);
    rio_readinitb(&rio_char, fd_chat);
    rio_readinitb(&rio_file, fd_file);

//    GtkWidget *w = window();
//    gtk_widget_show_all(w);
    login(argc, argv);

    //sign(argc, argv);
    //sign_success(argc, argv);
    return 0;
}
