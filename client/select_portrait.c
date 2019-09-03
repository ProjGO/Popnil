//
// Created by hsx on 2019/9/2.
//

#include <gtk/gtk.h>

extern GtkWidget *window_list;

extern void update_widget_bg(GtkWidget *widget, int w,int h, const gchar *img_file);

extern GtkWidget *image_usericon;

//void buttons1_clicked()
//{
//    update_widget_bg(window_list,300, 500, "../client/images/bg/1.jpg");
//}

void buttons1_clicked(){

    printf("buttons1 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/1.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
    printf("buttons1 end");
}

void buttons2_clicked(){
    printf("buttons2 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/2.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
}

void buttons3_clicked(){
    printf("buttons3 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/3.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
}

void buttons4_clicked(){
    printf("buttons4 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/4.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
}

void buttons5_clicked(){
    printf("buttons5 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/5.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
}

void buttons6_clicked(){
    printf("buttons6 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/6.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
}

void buttons7_clicked(){
    printf("buttons7 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/7.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
}

void buttons8_clicked(){
    printf("buttons8 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/8.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
}

void buttons9_clicked(){
    printf("buttons9 begin");
    GdkPixbuf *src = gdk_pixbuf_new_from_file("../client/images/list_portrait/9.png", NULL);
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_usericon), src);
    gtk_widget_show_all(window_list);
}


GtkWidget *select_portrait()
{

    printf("select portrait begin");
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *portrait1, *portrait2, *portrait3, *portrait4, *portrait5, *portrait6, *portrait7, *portrait8, *portrait9;
    GtkWidget *buttons1, *buttons2, *buttons3, *buttons4, *buttons5, *buttons6, *buttons7, *buttons8, *buttons9;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),700,700);
    gtk_window_set_title(GTK_WINDOW(window),"更换头像");

    portrait1 = gtk_image_new_from_file("../client/images/portrait/1.png");
    portrait2 = gtk_image_new_from_file("../client/images/portrait/2.png");
    portrait3 = gtk_image_new_from_file("../client/images/portrait/3.png");
    portrait4 = gtk_image_new_from_file("../client/images/portrait/4.png");
    portrait5 = gtk_image_new_from_file("../client/images/portrait/5.png");
    portrait6 = gtk_image_new_from_file("../client/images/portrait/6.png");
    portrait7 = gtk_image_new_from_file("../client/images/portrait/7.png");
    portrait8 = gtk_image_new_from_file("../client/images/portrait/8.png");
    portrait9 = gtk_image_new_from_file("../client/images/portrait/9.png");


    buttons1 = gtk_button_new_with_label("选择");
    buttons2 = gtk_button_new_with_label("选择");
    buttons3 = gtk_button_new_with_label("选择");
    buttons4 = gtk_button_new_with_label("选择");
    buttons5 = gtk_button_new_with_label("选择");
    buttons6 = gtk_button_new_with_label("选择");
    buttons7 = gtk_button_new_with_label("选择");
    buttons8 = gtk_button_new_with_label("选择");
    buttons9 = gtk_button_new_with_label("选择");


    table = gtk_table_new(21,20,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),10);
    gtk_table_set_col_spacings(GTK_TABLE(table),10);


    gtk_table_attach_defaults(GTK_TABLE(table),portrait1,0,6,0,5);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons1,2,4,5,7);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait2,7,13,0,5);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons2,9,11,5,7);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait3,14,20,0,5);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons3,16,18,5,7);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait4,0,6,7,12);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons4,2,4,12,14);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait5,7,13,7,12);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons5,9,11,12,14);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait6,14,20,7,12);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons6,16,18,12,14);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait7,0,6,14,19);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons7,2,4,19,21);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait8,7,13,14,19);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons8,9,11,19,21);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait9,14,20,14,19);
    gtk_table_attach_defaults(GTK_TABLE(table),buttons9,16,18,19,21);

    g_signal_connect(G_OBJECT(buttons1),"clicked",
                     G_CALLBACK(buttons1_clicked),NULL);

    g_signal_connect(G_OBJECT(buttons2),"clicked",
                     G_CALLBACK(buttons2_clicked),NULL);

    g_signal_connect(G_OBJECT(buttons3),"clicked",
                     G_CALLBACK(buttons3_clicked),NULL);

    g_signal_connect(G_OBJECT(buttons4),"clicked",
                     G_CALLBACK(buttons4_clicked),NULL);

    g_signal_connect(G_OBJECT(buttons5),"clicked",
                     G_CALLBACK(buttons5_clicked),NULL);

    g_signal_connect(G_OBJECT(buttons6),"clicked",
                     G_CALLBACK(buttons6_clicked),NULL);

    g_signal_connect(G_OBJECT(buttons7),"clicked",
                     G_CALLBACK(buttons7_clicked),NULL);

    g_signal_connect(G_OBJECT(buttons8),"clicked",
                     G_CALLBACK(buttons8_clicked),NULL);

    g_signal_connect(G_OBJECT(buttons9),"clicked",
                     G_CALLBACK(buttons9_clicked),NULL);



    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_widget_show_all(window);


    gtk_main();
    printf("select portrait end");

    return window;

}