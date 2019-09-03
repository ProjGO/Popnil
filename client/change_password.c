//
// Created by hsx on 2019/9/3.
//

#include <gtk/gtk.h>
extern void update_widget_bg(GtkWidget *widget, int w,int h, const gchar *img_file);

GtkWidget *id_entry, *password_entry, *new_password_entry;

GtkWidget * change_clicked()
{
    GtkWidget *window;
    GtkWidget * label;

    //   gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	//创建窗口
    gtk_window_set_title(GTK_WINDOW(window), "注册成功！");	//设置标题
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	//设置位置
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);		//设置默认大小
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    label = gtk_label_new("成功修改密码！");
    gtk_label_set_markup(
            GTK_LABEL(label),
            "<span foreground='white'  font_desc='20'>成功修改密码!</span>");
    gtk_container_add(GTK_CONTAINER(window), label);

    gtk_widget_show_all(window);	//show窗口
    gtk_main ();
    return window;
}

GtkWidget * change_password()
{
    GtkWidget *window;
    GtkWidget *id_label, *password_label, *new_password_label;
    GtkWidget *change_password_button;
    GtkWidget *hbox1, *hbox2, *hbox3;
    GtkWidget *table;

    //   gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	//创建窗口
    gtk_window_set_title(GTK_WINDOW(window), "修改密码");	//设置标题
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	//设置位置
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);		//设置默认大小
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    table = gtk_table_new(10,10,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),10);
    gtk_table_set_col_spacings(GTK_TABLE(table),0);

    id_label = gtk_label_new("ID:");
    gtk_label_set_markup(
            GTK_LABEL(id_label),
            "<span foreground='white'  font_desc='20'>ID:</span>");

    password_label = gtk_label_new("Password:");
    gtk_label_set_markup(
            GTK_LABEL(password_label),
            "<span foreground='white'  font_desc='20'>Password:</span>");

    new_password_label = gtk_label_new("New Password:");
    gtk_label_set_markup(
            GTK_LABEL(new_password_label),
            "<span foreground='white'  font_desc='20'>New Password:</span>");

    id_entry = gtk_entry_new();
    password_entry = gtk_entry_new();
    new_password_entry = gtk_entry_new();

    gtk_entry_set_visibility(GTK_ENTRY (password_entry), FALSE);

    gtk_entry_set_visibility(GTK_ENTRY (new_password_entry), FALSE);

    change_password_button = gtk_button_new_with_label("保存修改");

    g_signal_connect (change_password_button, "clicked",
                      G_CALLBACK(change_clicked), NULL);	//为ok_button链接“单击事件”


    hbox1 = gtk_hbox_new(TRUE, 1);
    hbox2 = gtk_hbox_new(TRUE, 1);
    hbox3 = gtk_hbox_new(TRUE, 1);

//    GtkWidget * sign_image=gtk_image_new_from_file("../client/images/sign1.jpg");
//    gtk_container_add(GTK_CONTAINER(hbox), sign_image);

    gtk_box_pack_start(GTK_BOX(hbox1), id_label, TRUE, FALSE, 1);	//将nickname编辑框添加到hbox1中
    gtk_box_pack_start(GTK_BOX(hbox1), id_entry, TRUE, FALSE, 1);	//将nickname标签添加到hbox1中

    gtk_box_pack_start(GTK_BOX(hbox2), password_label, TRUE, FALSE, 1);	//将password编辑框添加到hbox2中
    gtk_box_pack_start(GTK_BOX(hbox2), password_entry, TRUE, FALSE, 1);	//将password标签添加到hbox2中

    gtk_box_pack_start(GTK_BOX(hbox3), new_password_label, TRUE, FALSE, 1);	//将new_password编辑框添加到hbox2中
    gtk_box_pack_start(GTK_BOX(hbox3), new_password_entry, TRUE, FALSE, 1);	//将new_password标签添加到hbox2中

    gtk_table_attach_defaults(GTK_TABLE(table),hbox1,0,10,0,2);
    gtk_table_attach_defaults(GTK_TABLE(table),hbox2,0,10,2,4);
    gtk_table_attach_defaults(GTK_TABLE(table),hbox3,0,10,4,6);
    gtk_table_attach_defaults(GTK_TABLE(table),change_password_button,0,10,9,10);

    gtk_container_add(GTK_CONTAINER(window), table);

    update_widget_bg(window,1000, 1000, "../client/images/change_password.jpg");

    // update_widget_bg(window,1000, 600, "../client/images/bg/8.jpg");

    gtk_widget_show_all(window);	//show窗口
    gtk_main ();

    return window;

}