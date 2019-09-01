//
// Created by hsx on 2019/8/31.
//

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

const char* userid = "12345678";

GtkWidget * sign_success()
{
    GtkWidget *window;
    GtkWidget * vbox;
    GtkWidget *success_label, *inform_label, *userid_label;

    //   gtk_init(&argc, &argv);


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	//创建窗口
    gtk_window_set_title(GTK_WINDOW(window), "注册成功！");	//设置标题
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	//设置位置
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);		//设置默认大小
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    success_label = gtk_label_new("注册成功！");
    inform_label = gtk_label_new("您的ID是：");
    userid_label = gtk_label_new(userid);
    vbox = gtk_vbox_new(TRUE, 1);

    gtk_label_set_markup(
            GTK_LABEL(success_label),
            "<span foreground='white'  font_desc='20'>注册成功!</span>");

    gtk_label_set_markup(
            GTK_LABEL(inform_label),
            "<span foreground='white'  font_desc='20'>  您的ID是：</span>");

    userid_label = gtk_label_new(userid);
    gtk_label_set_markup(
            GTK_LABEL(userid_label),
            "<span foreground='white'  font_desc='20'></span>");

    gtk_label_set_text(userid_label, userid);

    PangoFontDescription *font_desc = pango_font_description_from_string ("Serif 15");
    pango_font_description_set_size (font_desc, 20 * PANGO_SCALE);

    gtk_widget_modify_font (userid_label, font_desc);
    pango_font_description_free (font_desc);

    gtk_box_pack_start(GTK_BOX(vbox), success_label, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), inform_label, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), userid_label, TRUE, FALSE, 1);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);	//show窗口
    gtk_main ();

    return window;
}