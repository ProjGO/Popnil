//
// Created by hsx on 2019/8/31.
//
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "../common/include/socket_utils.h"
#include "../common/include/include.h"
#include "../common/include/define.h"


extern GtkWidget * sign();
extern void list();
//const char password[MAX_PWD_LEN] = "secret";
extern int fd_log,fd_chat,fd_file;

GtkWidget *username_entry, *password_entry;
void button_clicked (GtkWidget *window, gpointer data)
{
    login_info *info = (login_info *) malloc(sizeof(login_info));
    memset(&info->id,0, sizeof(info->id));
    memset(info->pwd,0,sizeof(info->pwd));
    info->id=atoi(gtk_entry_get_text(GTK_ENTRY((GtkWidget *) username_entry)));
    strcpy(info->pwd,gtk_entry_get_text(GTK_ENTRY((GtkWidget *) password_entry)));
    fd_log = open_clientfd_old(DEFAULT_IP,DEFAULT_PORT);
    if(fd_log>0)
    {
        printf("connect scs.\n");
        //向数据库中信息核查
        //建立三个extern线程
        int flag=0;
        if(write(fd_log,&flag,sizeof(int))==-1)
        {
            printf("ord send err.\n");
            exit(1);
        }
        if(write(fd_log,info, sizeof(login_info))==-1)
        {
            printf("msg send err.\n");
            exit(1);
        }
        response_s2c *msg = (response_s2c*)malloc(sizeof(response_s2c));
       read(fd_log,msg, sizeof(response_s2c));
        if(msg->return_val)
        {
            fd_chat = open_clientfd_old(DEFAULT_IP,DEFAULT_PORT);
            fd_file = open_clientfd_old(DEFAULT_IP,DEFAULT_PORT);
            list();

        }
        else
            printf("%s\n",msg->err_msg);
    }
}

int login (int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *sign_button, *retrieve_button;
//
    GtkWidget *ok_button;
    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *hbox, *vbox, *vbox1, *vbox2;
    GtkWidget *frame;


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	//创建窗口
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntryBox");	//设置标题
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	//设置位置
    gtk_window_set_default_size(GTK_WINDOW(window), 550, 350);		//设置默认大小
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    g_signal_connect ( window, "destroy",
                       G_CALLBACK (gtk_main_quit), NULL);	//为窗口连接“退出事件”

    sign_button = gtk_button_new_with_label("注册账号");
    retrieve_button = gtk_button_new_with_label("找回密码");



    username_entry = gtk_entry_new();	//设置id编辑框
    password_entry = gtk_entry_new();	//设置密码编辑框

    gtk_entry_set_visibility(GTK_ENTRY (password_entry), FALSE);	//密码设置为不可见

    ok_button = gtk_button_new_with_label("登录");		//设置“OK”按钮

    g_signal_connect (ok_button, "clicked",
                      G_CALLBACK(button_clicked), password_entry);	//为ok_button链接“单击事件”


    hbox0 = gtk_hbox_new ( TRUE, 1 );
    hbox1 = gtk_hbox_new ( TRUE, 1 );		//创建hbox1
    hbox2 = gtk_hbox_new ( TRUE, 1 );		//创建hbox2
    hbox3 = gtk_hbox_new ( TRUE, 1 );
    hbox4 = gtk_hbox_new ( TRUE, 1 );

    g_signal_connect ( sign_button, "clicked",
                       G_CALLBACK (sign), NULL);



    hbox = gtk_hbox_new ( TRUE, 1 );
    vbox = gtk_vbox_new ( FALSE, 1);		//创建vbox
    vbox1 = gtk_vbox_new ( FALSE, 1);
    vbox2 = gtk_vbox_new ( FALSE, 1);

    frame=gtk_frame_new(NULL);
    GtkWidget* image=gtk_image_new_from_file("../client/images/login2.png");
    gtk_container_add(GTK_CONTAINER(frame),image);
    gtk_container_add(GTK_CONTAINER(vbox), frame);

    GtkWidget * portrait=gtk_image_new_from_file("../client/images/d_portrait.PNG");
    gtk_container_add(GTK_CONTAINER(hbox0), portrait);

    gtk_box_pack_start(GTK_BOX(hbox1), username_entry, TRUE, FALSE, 1);	//将username编辑框添加到hbox1中
    gtk_box_pack_start(GTK_BOX(hbox3), sign_button, TRUE, FALSE, 1);	//将username标签添加到hbox1中

    gtk_box_pack_start(GTK_BOX(hbox2), password_entry, TRUE, FALSE, 1);	//将密码编辑框添加到hbox2中
    gtk_box_pack_start(GTK_BOX(hbox4), retrieve_button, TRUE, FALSE, 1);		//将密码标签添加到hbox2中


    gtk_box_pack_start(GTK_BOX(vbox1), hbox1, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox1), hbox2, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox2), hbox3, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox2), hbox4, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), hbox0, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), vbox1, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), vbox2, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), ok_button, FALSE, FALSE, 1);


    gtk_container_add(GTK_CONTAINER(window), vbox);


    gtk_widget_show_all(window);	//show窗口
    gtk_main ();

    return 0;
}