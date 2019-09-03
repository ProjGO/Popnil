//
// Created by hsx on 2019/8/31.
//
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/include/include.h"
#include "../common/include/define.h"

extern GtkWidget * sign_success(char * userid);
GtkWidget *nickname_entry, *password_entry;
int sign_clicked (GtkWidget *window, gpointer data)
{
    reg_info_c2s *reg_text=(reg_info_c2s*)malloc(sizeof(reg_info_c2s));
    strcpy(reg_text->name,gtk_entry_get_text(GTK_ENTRY((GtkWidget *) nickname_entry)));
    strcpy(reg_text->pwd,gtk_entry_get_text(GTK_ENTRY((GtkWidget *) password_entry)));
    unsigned long len = strlen(reg_text->pwd);
//    printf("hahah\n");
    if(len >= 3 && len <=12)
    {
        printf("sign up successfully!\n");
        /*///////////////////////////////////////////////*/
        int socketfd;
        int myport=8088;
        struct sockaddr_in pin_addr;
        bzero(&pin_addr, sizeof(pin_addr));
        pin_addr.sin_family = AF_INET;
        pin_addr.sin_addr.s_addr = inet_addr(DEFAULT_IP);
        pin_addr.sin_port = htons(myport);
        if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            printf("can’t create socket\n");
            exit(1);
        }
        if (connect(socketfd, (void*) &pin_addr,sizeof(pin_addr)) == -1)
        {
            printf ("Error connecting to socket\n");
            exit(1);
        }
        int flag=1; //表示注册功能
        if (write(socketfd, &flag, sizeof(int)) == -1 )
        {
            printf ("Error in send\n");
            exit(1);
        }
        if (write(socketfd, reg_text, sizeof(reg_info_c2s)) == -1 )
        {
            printf ("Error in send\n");
            exit(1);
        }
        response_s2c *msg=(response_s2c*)malloc(sizeof(response_s2c));
        read(socketfd,msg,sizeof(response_s2c));
        close(socketfd);
        char str[10];
        sprintf(str, "%d", msg->return_val);
        sign_success(str);
        free(msg);
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
    GtkWidget *sign_ok_button;
    GtkWidget *hbox1, *hbox2;
    GtkWidget *vbox, *hbox;

    //   gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	//创建窗口
    gtk_window_set_title(GTK_WINDOW(window), "Sign up");	//设置标题
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	//设置位置
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);		//设置默认大小
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
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
                      G_CALLBACK(sign_clicked), NULL);	//为ok_button链接“单击事件”


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