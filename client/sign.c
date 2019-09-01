//
// Created by hsx on 2019/8/31.
//
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

extern GtkWidget * sign_success();

int sign_clicked (GtkWidget *window, gpointer data)
{
    const char *password_text = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) data));
    unsigned long len = strlen(password_text);
//    printf("hahah\n");
    if(len >= 3 && len <=12)
    {
        printf("sign up successfully!\n");
        sign_success();
    }
    else
    {
        printf("密码必长度必须大于三小于12!");
    }
    return 0;
}

GtkWidget * sign()
{
    GtkWidget *window;
    GtkWidget *nickname_label, *password_label;
    GtkWidget *nickname_entry, *password_entry;
    GtkWidget *sign_ok_button;
    GtkWidget *hbox1, *hbox2;
    GtkWidget *vbox, *hbox;

    //   gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	//创建窗口
    gtk_window_set_title(GTK_WINDOW(window), "Sign up");	//设置标题
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	//设置位置
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);		//设置默认大小
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    nickname_label = gtk_label_new("Nikname:");
    gtk_label_set_markup(
            GTK_LABEL(nickname_label),
            "<span foreground='white'  font_desc='20'>Nickname:</span>");

    password_label = gtk_label_new("Password:");
    gtk_label_set_markup(
            GTK_LABEL(password_label),
            "<span foreground='white'  font_desc='20'>Password:</span>");

    nickname_entry = gtk_entry_new();
    password_entry = gtk_entry_new();

    gtk_entry_set_visibility(GTK_ENTRY (password_entry), FALSE);

    sign_ok_button = gtk_button_new_with_label("注册");

    g_signal_connect (sign_ok_button, "clicked",
                      G_CALLBACK(sign_clicked), password_entry);	//为ok_button链接“单击事件”


    hbox1 = gtk_hbox_new(TRUE, 1);
    hbox2 = gtk_hbox_new(TRUE, 1);
    vbox = gtk_vbox_new(TRUE, 1);
    hbox = gtk_hbox_new(TRUE, 1);

    GtkWidget * sign_image=gtk_image_new_from_file("../client/images/sign1.jpg");
    gtk_container_add(GTK_CONTAINER(hbox), sign_image);

    gtk_box_pack_start(GTK_BOX(hbox1), nickname_label, TRUE, FALSE, 1);	//将nickname编辑框添加到hbox1中
    gtk_box_pack_start(GTK_BOX(hbox1), nickname_entry, TRUE, FALSE, 1);	//将nickname标签添加到hbox1中

    gtk_box_pack_start(GTK_BOX(hbox2), password_label, TRUE, FALSE, 1);	//将password编辑框添加到hbox2中
    gtk_box_pack_start(GTK_BOX(hbox2), password_entry, TRUE, FALSE, 1);	//将password标签添加到hbox2中

    gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), sign_ok_button, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, FALSE, 1);

    gtk_container_add(GTK_CONTAINER(window), hbox);

    gtk_widget_show_all(window);	//show窗口
    gtk_main ();

    return window;

}