//
// Created by xdx on 19-9-2.
//

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>   //键盘头文件，GDK_Up在这声明
#include "../common/include/include.h"
#include "../common/include/define.h"
GtkWidget* id;
GtkWidget* user_name;
GtkWidget *search_entry;
GtkWidget* frame;
extern int fd_log,fd_chat,fd_file;
char* default_image_path = "../client/images/friend_portrait.png";
char* default_id = "1120173454";
char* default_name = "xdx";
extern GtkWidget *create_button(char *image_path, char *button_label);

void search(GtkWidget *window, gpointer data)
{
    oper_friend_info *id_text=(oper_friend_info*)malloc(sizeof(oper_friend_info));
    id_text->id_re=atoi(gtk_entry_get_text(GTK_ENTRY((GtkWidget *) search_entry)));
    int flag;
    flag=2;
//    write(fd_log,&flag,sizeof(int));
//    write(fd_log,id_text,sizeof(oper_friend_info));
    if (write(fd_log, &flag, sizeof(int)) == -1 )
    {
        printf ("Error in send\n");
        exit(1);
    }
    if (write(fd_log, id_text, sizeof(oper_friend_info)) == -1 )
    {
        printf ("Error in send\n");
        exit(1);
    }
    client_info *msg=(client_info*)malloc(sizeof(client_info));
    read(fd_log,msg, sizeof(client_info));
    if(msg->id==-1)
    {

    }
    else
    {
        gtk_label_set_text(user_name, msg->nickname);
        printf("%s\n", user_name);
        char str_id[24];
        sprintf(str_id, "%d", msg->id);
        gtk_label_set_text(id, str_id);
        free(msg);
    }
//    gtk_widget_show_all(window);
}

GtkWidget *information_frame()
{
    GtkWidget* table;
    GtkWidget* image;

    GtkWidget* button;
    frame = gtk_frame_new("Information");
    table = gtk_table_new(16, 12, TRUE);
    gtk_container_add(frame, table);
    gtk_frame_set_label(frame, "Information");

    image = gtk_image_new_from_file(default_image_path);
    gtk_table_attach_defaults(GTK_TABLE(table),image, 0, 5, 0, 5);
    id = gtk_label_new(default_id);
    user_name = gtk_label_new(default_name);

    gtk_table_attach_defaults(GTK_TABLE(table), id, 5, 10, 0, 3);

    gtk_table_attach_defaults(GTK_TABLE(table), user_name, 5, 10, 3, 5);

    button = create_button("../client/images/add.png", "添加");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 5, 7, 9, 12);

    return frame;
}

GtkWidget *add_friends()
{
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *frame;
    GtkWidget *button_search;
    client_info* msgback=(client_info*)malloc(sizeof(client_info));

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),400,400);
    gtk_window_set_title(GTK_WINDOW(window),"Add friends");
    gtk_container_set_border_width(GTK_CONTAINER(window),0);
    g_signal_connect ( window, "destroy",
                       G_CALLBACK (gtk_main_quit), NULL);	//为窗口连接“退出事件”
    table = gtk_table_new(20, 20, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(window),table);

    search_entry = gtk_search_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),search_entry, 2, 16, 2, 4);
//    search_friends();
    button_search = create_button("../client/images/search.png", NULL);
    gtk_table_attach_defaults(GTK_TABLE(table),button_search, 17, 19, 2, 4);
    g_signal_connect ( button_search, "clicked",
                       G_CALLBACK (search), msgback);
    frame=information_frame();
    gtk_table_attach_defaults(GTK_TABLE(table),frame, 2, 18, 6, 18);


    gtk_widget_show_all(window);
    gtk_main();
    free(msgback);
    return window;
}