//
// Created by hsx on 2019/9/2.
//

#include <gtk/gtk.h>

extern GtkWidget *select_portrait();
extern GtkWidget *add_friend_window;
extern GtkWidget *window_list;

extern void update_widget_bg(GtkWidget *widget, int w,int h, const gchar *img_file);

GtkWidget *portrait;


void addLabel(GtkWidget *info_table, const char *str, int columnl, int columnr, int rowu, int rowd)
{
    GtkWidget *label = gtk_label_new(str);
    gtk_table_attach(GTK_TABLE(info_table), label, columnl, columnr, rowu, rowd, GTK_FILL, GTK_FILL, 2, 6);
}
void addEntry(GtkWidget *info_table, int columnl, int columnr, int rowu, int rowd)
{
    GtkWidget *entry = gtk_entry_new();

    gtk_table_attach(GTK_TABLE(info_table), entry, columnl, columnr, rowu, rowd, GTK_FILL, GTK_FILL, 2, 6);
}

void changeBackGround(GtkWidget *widget, int w, int h, const gchar *path)
{
    gtk_widget_set_app_paintable(widget, TRUE);		//允许窗口可以绘图
    gtk_widget_realize(widget);

    /* 更改背景图时，图片会重叠
     * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。
     */
    gtk_widget_queue_draw(widget);

    GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);	// 创建图片资源对象
    // w, h是指定图片的宽度和高度
    GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);

    GdkPixmap *pixmap = NULL;

    /* 创建pixmap图像;
     * NULL：不需要蒙版;
     * 123： 0~255，透明到不透明
     */
    gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);
    // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE
    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);

    // 释放资源
    g_object_unref(src_pixbuf);
    g_object_unref(dst_pixbuf);
    g_object_unref(pixmap);
}


void deal_switch_page(GtkNotebook *notebook, gpointer page, guint page_num, gpointer data)
{
    printf("我是第%d个页面\n", page_num+1);
    return;
}

void button1_clicked()
{
    update_widget_bg(window_list,300, 500, "../client/images/bg/1.jpg");
}

void button2_clicked()
{
    update_widget_bg(window_list,300, 500, "../client/images/bg/2.jpg");
}

void button3_clicked()
{
    update_widget_bg(window_list,300, 500, "../client/images/bg/3.jpg");
}

void button4_clicked()
{
    update_widget_bg(window_list,300, 500, "../client/images/bg/4.jpg");
}

void button5_clicked()
{
    update_widget_bg(window_list,300, 500, "../client/images/bg/5.jpg");
}

void button6_clicked()
{
    update_widget_bg(window_list,300, 500, "../client/images/bg/6.jpg");
}
GtkWidget* setting()
{

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 1000, 750);
    GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);
    GtkWidget *per_info_window;
    //主框架
    GtkWidget *main_frame;
    //左边框架
    GtkWidget *person_vbox;
    GtkWidget *person_table;
    //右边具体信息框架
    GtkWidget *info_vbox;
    GtkWidget *info_frame;
    GtkWidget *info_table;

    //个人背景图片
    GtkWidget *person_background_image;
    //个人头像
    GtkWidget *person_profile_photo;

    GtkWidget *table;
    GtkWidget *bg1, *bg2, *bg3, *bg4, *bg5, *bg6;

    GtkWidget *button1, *button2, *button3, *button4, *button5, *button6;

    GtkWidget *select_portrait_button;




//    //用户账号
//    GtkWidget *user_id;
//    //昵称
//    GtkWidget *nickname;
//    //个性签名
//    GtkWidget *signature;
//    //性别
//    GtkWidget *gender;
//    //年龄
//    GtkWidget *age;
//    //生日
//    GtkWidget *birthday;
//    //星座
//    GtkWidget *constellation;
//    //所在地
//    GtkWidget *location;
//    //故乡
//    GtkWidget *hometown;
//    //职业
//    GtkWidget *profession;
//    //手机
//    GtkWidget *mobilephone;
//    //学校
//    GtkWidget *school;
//    //邮箱
//    GtkWidget *email;

    GtkWidget *background;
    //初始化GTK

    //创建最上层主窗口

    //去边框
    //gtk_window_set_decorated(GTK_WINDOW(per_info_window),FALSE);
    //设定窗口默认宽高
    //gtk_window_set_default_size(GTK_WINDOW(per_info_window), 740, 520);
    //让窗口大小不可改变
//    gtk_window_set_resizable(GTK_WINDOW(per_info_window),FALSE);
    //temp..尝试
    //background = gtk_image_new_from_file("../background.jpeg");
    //改变窗口背景颜色 750 570
    //changeBackGround(per_info_window, 958, 553, "../background4.jpg");
    //创建盒子
    main_frame = gtk_hbox_new(TRUE, 0);
    person_vbox = gtk_vbox_new(TRUE, 0);
    person_table = gtk_table_new(10, 10, FALSE);

    info_vbox = gtk_vbox_new(TRUE, 0);
    info_frame = gtk_frame_new("Personal Information");

    //尝试去掉info_frame边框
    gtk_window_set_decorated(GTK_FRAME(info_frame),FALSE);

    info_table = gtk_table_new(14, 7, FALSE);

    //试图改变frame的颜色
    //static GdkColor green = {0, 0, 0xffff, 0};
    //gtk_widget_modify_fg(frame, GTK_STATE_PRELIGHT, &green);

    //添加主盒子
    //gtk_container_add(GTK_CONTAINER(per_info_window), background);
//    gtk_container_add(GTK_CONTAINER(per_info_window), main_frame);

    //person头像名字在左边 具体info在右边
    gtk_box_pack_start(GTK_BOX(main_frame), person_vbox, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(person_vbox), person_table);
    gtk_box_pack_start(GTK_BOX(main_frame), info_vbox, TRUE, TRUE, 0);
    //改变info_vbox背景 不成功
    //changeBackGround(info_vbox, 750, 570, "../background2.jpeg");
    gtk_container_add(GTK_CONTAINER(info_vbox), info_frame);
    gtk_container_add(GTK_CONTAINER(info_frame), info_table);

    //个人背景图片
    person_background_image = gtk_image_new_from_file("../client/images/tupian2.jpg"); //CLion
    gtk_table_attach(GTK_TABLE(person_table), person_background_image, 0, 10, 0, 5, GTK_FILL, GTK_FILL, 0, 0);
    //person_background_image = gtk_image_new_from_file("person_background.jpg"); //终端
    //gtk_box_pack_start(GTK_BOX(person_vbox), person_background_image, TRUE, TRUE, 0);
    //用户头像
    //person_profile_photo = gtk_label_new("头像待定");


    //person_profile_photo = gtk_image_new_from_file("../images/profile_photo.png");
    //gtk_table_attach(GTK_TABLE(person_table), person_profile_photo, 0, 1, 3, 4, GTK_FILL, GTK_FILL, 0, 0);


    //gtk_box_pack_start(GTK_BOX(person_vbox), person_profile_photo, TRUE, TRUE, 0);

    portrait = gtk_image_new_from_file("../client/images/d_portrait.PNG");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/d_portrait.PNG", NULL);
    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src,
                                             150, 150, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf( GTK_IMAGE(portrait), dst);


    gtk_table_attach(GTK_TABLE(person_table), portrait, 0, 10, 5, 9, GTK_FILL, GTK_FILL, 0, 50);

    select_portrait_button = gtk_button_new_with_label("更换头像");
    gtk_table_attach(GTK_TABLE(person_table), select_portrait_button, 4, 6, 9, 10, GTK_FILL, GTK_FILL, 0, 5);

    g_signal_connect(G_OBJECT(select_portrait_button),"clicked",
                     G_CALLBACK(select_portrait),NULL);



//    //用户账号id
//    singleInfo(info_frame, "账号");
    addLabel(info_table, "账号", 0, 1, 0, 1);
    addEntry(info_table, 1, 7, 0, 1);
//    //用户昵称
//    singleInfo(info_frame, "昵称");
    addLabel(info_table, "昵称", 0, 1, 1, 2);
    addEntry(info_table, 1, 7, 1, 2);
//    //性别 年龄
//    doubleInfo(info_frame, "性别", "年龄");
    addLabel(info_table, "性别", 0, 1, 2, 3);
    addEntry(info_table, 1, 3, 2, 3);
    addLabel(info_table, "年龄", 4, 5, 2, 3);
    addEntry(info_table, 5, 7, 2, 3);
//    //生日 星座
//    doubleInfo(info_frame, "生日", "星座");
    addLabel(info_table, "生日", 0, 1, 3, 4);
    addEntry(info_table, 1, 3, 3, 4);
    addLabel(info_table, "星座", 4, 5, 3, 4);
    addEntry(info_table, 5, 7, 3, 4);
//    //所在地
//    singleInfo(info_frame, "所在地");
    addLabel(info_table, "所在地", 0, 1, 4, 5);
    addEntry(info_table, 1, 7, 4, 5);
//    //故乡
//    singleInfo(info_frame, "故乡");
    addLabel(info_table, "故乡", 0, 1, 5, 6);
    addEntry(info_table, 1, 7, 5, 6);
//    //学校
//    singleInfo(info_frame, "学校");
    addLabel(info_table, "学校", 0, 1, 6, 7);
    addEntry(info_table, 1, 7, 6, 7);
//    //职业
//    singleInfo(info_frame, "职业");
    addLabel(info_table, "职业", 0, 1, 7, 8);
    addEntry(info_table, 1, 7, 7, 8);
//    //手机
//    singleInfo(info_frame, "手机");
    addLabel(info_table, "手机", 0, 1, 8, 9);
    addEntry(info_table, 1, 7, 8, 9);
//    //邮箱
//    singleInfo(info_frame, "邮箱");
    addLabel(info_table, "邮箱", 0, 1, 9, 10);
    addEntry(info_table, 1, 7, 9, 10);
//    //个性签名
//    singleInfo(info_frame, "个性签名");
    addLabel(info_table, "个性签名", 0, 1, 10, 14);
    addEntry(info_table, 1, 7, 10, 14);


    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);


    GtkWidget *hbox = gtk_hbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(window), hbox);


    GtkWidget *label = gtk_label_new("个人信息");


    gtk_container_add(GTK_CONTAINER(hbox), main_frame);


    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hbox, label);



    table = gtk_table_new(10,20,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),10);
    gtk_table_set_col_spacings(GTK_TABLE(table),10);

    label = gtk_label_new("个性化");
    gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), table, label, 2);

    bg1 = gtk_image_new_from_file("../client/images/bg/1.jpg");
    bg2 = gtk_image_new_from_file("../client/images/bg/2.jpg");
    bg3 = gtk_image_new_from_file("../client/images/bg/3.jpg");
    bg4 = gtk_image_new_from_file("../client/images/bg/4.jpg");
    bg5 = gtk_image_new_from_file("../client/images/bg/5.jpg");
    bg6 = gtk_image_new_from_file("../client/images/bg/6.jpg");

    button1 = gtk_button_new_with_label("选择");
    button2 = gtk_button_new_with_label("选择");
    button3 = gtk_button_new_with_label("选择");
    button4 = gtk_button_new_with_label("选择");
    button5 = gtk_button_new_with_label("选择");
    button6 = gtk_button_new_with_label("选择");


    gtk_table_attach_defaults(GTK_TABLE(table),bg1,0,6,0,4);
    gtk_table_attach_defaults(GTK_TABLE(table),button1,2,4,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),bg2,7,13,0,4);
    gtk_table_attach_defaults(GTK_TABLE(table),button2,9,11,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),bg3,14,20,0,4);
    gtk_table_attach_defaults(GTK_TABLE(table),button3,16,18,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),bg4,0,6,5,9);
    gtk_table_attach_defaults(GTK_TABLE(table),button4,2,4,9,10);
    gtk_table_attach_defaults(GTK_TABLE(table),bg5,7,13,5,9);
    gtk_table_attach_defaults(GTK_TABLE(table),button5,9,11,9,10);
    gtk_table_attach_defaults(GTK_TABLE(table),bg6,14,20,5,9);
    gtk_table_attach_defaults(GTK_TABLE(table),button6,16,18,9,10);

    g_signal_connect(G_OBJECT(button1),"clicked",
                     G_CALLBACK(button1_clicked),NULL);

    g_signal_connect(G_OBJECT(button2),"clicked",
                     G_CALLBACK(button2_clicked),NULL);

    g_signal_connect(G_OBJECT(button3),"clicked",
                     G_CALLBACK(button3_clicked),NULL);

    g_signal_connect(G_OBJECT(button4),"clicked",
                     G_CALLBACK(button4_clicked),NULL);

    g_signal_connect(G_OBJECT(button5),"clicked",
                     G_CALLBACK(button5_clicked),NULL);

    g_signal_connect(G_OBJECT(button6),"clicked",
                     G_CALLBACK(button6_clicked),NULL);



    g_signal_connect(notebook, "switch-page", G_CALLBACK(deal_switch_page), NULL);


    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook),1);

    //   update_widget_bg(notebook,400, 400, "../client/images/bg/8.jpg");



    gtk_widget_show_all(window);


    gtk_main();

    return 0;
}