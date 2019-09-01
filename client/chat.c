//
// Created by xdx on 19-9-1.
//
#include <gtk/gtk.h>
const char * friend_name = "friend_a";
GtkWidget *window()
{
    GtkWidget *window;
    GtkWidget *table, *table1, *table3;
    GtkWidget *frame1, *frame2, *frame3, *frame4, *frame5;
    GtkWidget *hbox1;
    GtkWidget *friend_name_label;
    GtkWidget *friend_portrait, *emoji, *doc, *font;
    GtkWidget *send_button, *font_button, *emoji_button, *doc_button, *history_button;
    GtkWidget *input;
    GtkTextBuffer *buffer;



    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),700,700);
    gtk_window_set_title(GTK_WINDOW(window),"Chat");

    gtk_container_set_border_width(GTK_CONTAINER(window),0);


    table = gtk_table_new(5,20,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(window),table);

    frame1 = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame1),GTK_SHADOW_IN);

    frame2 = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame2),GTK_SHADOW_IN);

    frame3 = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame3),GTK_SHADOW_IN);

    frame4 = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame4),GTK_SHADOW_IN);

    frame5 = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame5),GTK_SHADOW_IN);


    gtk_table_attach_defaults(GTK_TABLE(table),frame1,0,20,0,2);
    gtk_table_attach_defaults(GTK_TABLE(table),frame2,0,20,2,14);
    gtk_table_attach_defaults(GTK_TABLE(table),frame3,0,20,14,15);
    gtk_table_attach_defaults(GTK_TABLE(table),frame4,0,20,15,19);
    gtk_table_attach_defaults(GTK_TABLE(table),frame5,17,20,19,20);




    hbox1 = gtk_hbox_new(TRUE, 1);
    send_button = gtk_button_new_with_label("发送");

    friend_portrait=gtk_image_new_from_file("../images/friend_portrait.png");
    gtk_container_add(GTK_CONTAINER(hbox1), friend_portrait);

    friend_name_label = gtk_label_new(friend_name);
    gtk_container_add(GTK_CONTAINER(hbox1), friend_name_label);



    table1 = gtk_table_new(1, 10, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table1),0);
    gtk_table_set_col_spacings(GTK_TABLE(table1),0);
    gtk_table_attach_defaults(GTK_TABLE(table1),hbox1,0,3,0,1);
    gtk_container_add(GTK_CONTAINER(frame1),table1);


    font = gtk_image_new_from_file("../images/font.png");
    emoji = gtk_image_new_from_file("../images/emoji.png");
    doc = gtk_image_new_from_file("../images/doc.png");

    font_button = gtk_button_new();
    emoji_button = gtk_button_new();
    doc_button = gtk_button_new();

    history_button = gtk_button_new_with_label("消息记录");

    gtk_container_add(GTK_CONTAINER(font_button),font);
    gtk_container_add(GTK_CONTAINER(emoji_button),emoji);
    gtk_container_add(GTK_CONTAINER(doc_button),doc);

    table3 = gtk_table_new(1, 15, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table3),0);
    gtk_table_set_col_spacings(GTK_TABLE(table3),2);
    gtk_table_attach_defaults(GTK_TABLE(table3),font_button,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table3),emoji_button,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table3),doc_button,2,3,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table3),history_button,13,15,0,1);
    gtk_container_add(GTK_CONTAINER(frame3),table3);


    input = gtk_text_view_new ();
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (input));
    gtk_text_buffer_set_text (buffer, "", -1);

    gtk_container_add(GTK_CONTAINER(frame4),input);


    gtk_container_add(GTK_CONTAINER(frame5),send_button);

    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),G_OBJECT(window));

    gtk_widget_show_all(window);

    gtk_main();
}