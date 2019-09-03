//
// Created by hsx on 2019/9/3.
//

#include <gtk/gtk.h>
//#include <gtk-3.0>
#include <gdk/gdkkeysyms.h>   //键盘头文件，GDK_Up在这声明
#include "../common/include/include.h"
GtkWidget *search_group_entry;
char* default_group_image_path = "../client/images/group_list.png";
char* default_group_id = "1120173454";
char* default_group_name = "xdx";
extern GtkWidget *create_button(char *image_path, char *button_label);
extern void update_widget_bg(GtkWidget *widget, int w,int h, const gchar *img_file);


GtkWidget *add_group_window;

void search_group(GtkWidget *window, gpointer data)
{
//    new_friend_info *id_text=(new_friend_info*)malloc(sizeof(new_friend_info));
//    id_text->id_re=atoi(gtk_entry_get_text(GTK_ENTRY((GtkWidget *) search_entry)));


}

GtkWidget *group_information_frame()
{
    GtkWidget* frame;
    GtkWidget* table;
    GtkWidget* image;
    GtkWidget* id;
    GtkWidget* user_name;
    GtkWidget* button;


    frame = gtk_frame_new("Information");
    table = gtk_table_new(16, 12, TRUE);
    gtk_container_add(frame, table);
    gtk_frame_set_label(frame, "Information");
    image = gtk_image_new_from_file(default_group_image_path);
    gtk_table_attach_defaults(GTK_TABLE(table),image, 0, 5, 0, 5);
    id = gtk_label_new(default_group_id);
    user_name = gtk_label_new(default_group_name);
    gtk_table_attach_defaults(GTK_TABLE(table), id, 5, 10, 0, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), user_name, 5, 10, 3, 5);

    button = create_button("../client/images/add.png", "添加");
    gtk_table_attach_defaults(GTK_TABLE(table), button, 5, 7, 9, 12);

    return frame;
}

GtkWidget *add_groups()
{
//    GtkWidget *add_friend_window;
    GtkWidget *table;
    GtkWidget *frame;
    GtkWidget *button_search;


    add_group_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(add_group_window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(add_group_window),400,400);
    gtk_window_set_title(GTK_WINDOW(add_group_window),"Add groups");
    gtk_container_set_border_width(GTK_CONTAINER(add_group_window),0);
    g_signal_connect ( add_group_window, "destroy",
                       G_CALLBACK (gtk_main_quit), NULL);	//为窗口连接“退出事件”
    table = gtk_table_new(20, 20, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(add_group_window),table);

//    search_entry = gtk_search_entry_new();
    GdkPixbuf * pixbuf= gdk_pixbuf_new_from_file("../client/images/search.png", FALSE);
    search_group_entry = gtk_entry_new();
    gtk_entry_set_has_frame(search_group_entry, FALSE);
    gtk_entry_set_icon_from_pixbuf(search_group_entry, GTK_ENTRY_ICON_PRIMARY, pixbuf);
    gtk_entry_set_text(search_group_entry, "Search...");
    gtk_table_attach_defaults(GTK_TABLE(table),search_group_entry, 2, 16, 2, 4);
//    search_friends();
    button_search = create_button("../client/images/search.png", NULL);
    gtk_table_attach_defaults(GTK_TABLE(table),button_search, 17, 19, 2, 4);
    g_signal_connect ( button_search, "clicked",
                       G_CALLBACK (search_group), NULL);

    frame = group_information_frame();
    gtk_table_attach_defaults(GTK_TABLE(table),frame, 2, 18, 6, 18);

    update_widget_bg(add_group_window,400, 400, "../client/images/bg/7.jpg");

    gtk_widget_show_all(add_group_window);
    gtk_main();
    return add_group_window;
}