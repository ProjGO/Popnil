//
// Created by hsx on 2019/9/2.
//

#include <gtk/gtk.h>

GtkWidget *select_portrait()
{
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *portrait1, *portrait2, *portrait3, *portrait4, *portrait5, *portrait6, *portrait7, *portrait8, *portrait9;
    GtkWidget *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9;

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


    button1 = gtk_button_new_with_label("选择");
    button2 = gtk_button_new_with_label("选择");
    button3 = gtk_button_new_with_label("选择");
    button4 = gtk_button_new_with_label("选择");
    button5 = gtk_button_new_with_label("选择");
    button6 = gtk_button_new_with_label("选择");
    button7 = gtk_button_new_with_label("选择");
    button8 = gtk_button_new_with_label("选择");
    button9 = gtk_button_new_with_label("选择");


    table = gtk_table_new(21,20,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),10);
    gtk_table_set_col_spacings(GTK_TABLE(table),10);


    gtk_table_attach_defaults(GTK_TABLE(table),portrait1,0,6,0,5);
      gtk_table_attach_defaults(GTK_TABLE(table),button1,2,4,5,7);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait2,7,13,0,5);
      gtk_table_attach_defaults(GTK_TABLE(table),button2,9,11,5,7);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait3,14,20,0,5);
      gtk_table_attach_defaults(GTK_TABLE(table),button3,16,18,5,7);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait4,0,6,7,12);
      gtk_table_attach_defaults(GTK_TABLE(table),button4,2,4,12,14);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait5,7,13,7,12);
      gtk_table_attach_defaults(GTK_TABLE(table),button5,9,11,12,14);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait6,14,20,7,12);
      gtk_table_attach_defaults(GTK_TABLE(table),button6,16,18,12,14);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait7,0,6,14,19);
      gtk_table_attach_defaults(GTK_TABLE(table),button7,2,4,19,21);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait8,7,13,14,19);
      gtk_table_attach_defaults(GTK_TABLE(table),button8,9,11,19,21);
    gtk_table_attach_defaults(GTK_TABLE(table),portrait9,14,20,14,19);
      gtk_table_attach_defaults(GTK_TABLE(table),button9,16,18,19,21);

    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_widget_show_all(window);


    gtk_main();

      return window;

}