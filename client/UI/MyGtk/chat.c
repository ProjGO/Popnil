//
// Created by hsx on 2019/9/1.
//

#include <gtk/gtk.h>


GtkWidget * chat()
{
    GtkWidget *window;
    GtkWidget *hbox1, *hbox2, *hbox3, *hbox4, *hbox1_1, *hbox1_2, *hbox4_1, *hbox4_2, *hbox4_3;
    GtkWidget *vbox;
    GtkWidget *friend_name_label;
    GtkWidget *friend_portrait;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	//创建窗口
    gtk_window_set_title(GTK_WINDOW(window), "Chat");	//设置标题
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	//设置位置
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 900);		//设置默认大小
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    hbox1 = gtk_hbox_new(TRUE, 1);
    hbox1_1 = gtk_hbox_new(TRUE, 1);
    hbox1_2 = gtk_hbox_new(TRUE, 1);
    hbox2 = gtk_hbox_new(TRUE, 1);
    hbox3 = gtk_hbox_new(TRUE, 1);
    hbox4 = gtk_hbox_new(TRUE, 1);
    hbox4_1 = gtk_hbox_new(TRUE, 1);
    hbox4_2 = gtk_hbox_new(TRUE, 1);
    hbox4_3 = gtk_hbox_new(TRUE, 1);
    vbox = gtk_vbox_new(TRUE, 1);

    gtk_box_pack_start(GTK_BOX(hbox1), hbox1_1, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), hbox1_2, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox4), hbox4_1, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox4), hbox4_2, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox4), hbox4_3, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox3, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox4, TRUE, FALSE, 1);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);	//show窗口
    gtk_main ();

    return window;

}