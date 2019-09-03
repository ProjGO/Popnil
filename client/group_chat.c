#include <gtk/gtk.h>
#include <stdlib.h>
#include "tools.h"

const char * group_name = "group_a";
extern GtkWidget *create_bbox(GtkTextBuffer *input_buffer1 );
SunGtkCList* glist = NULL;
SunGtkCList* new_list = NULL;
SunGtkCList* log_group_list = NULL;
SunGtkCList* friend_list = NULL;
GtkWidget *window;
GtkWidget *table_chat;

GtkWidget *FileSelection;
GtkTextBuffer *buffer;
GtkWidget *icon;



void on_font_group_select_ok (GtkWidget *button,GtkFontSelectionDialog *fs)
{
    GtkWidget *dialog;
    gchar message[1024];
    gchar *s = gtk_font_selection_dialog_get_font_name(fs);
    sprintf(message,"你选择的字体是：%s \n",s);
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    message,
                                    NULL);
    g_free(s);
    gtk_widget_destroy(GTK_WIDGET(fs));
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
void font_button_group_clicked (GtkWidget *button,gpointer userdata)
{
    GtkWidget* dialog ;

    dialog = gtk_font_selection_dialog_new("请选择一种字体：");
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_signal_connect(GTK_OBJECT(dialog),"destroy",
                       GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog);
    gtk_signal_connect(GTK_OBJECT(GTK_FONT_SELECTION_DIALOG(dialog)->ok_button),
                       "clicked",GTK_SIGNAL_FUNC(on_font_group_select_ok),
                       GTK_FONT_SELECTION_DIALOG(dialog));

    gtk_signal_connect_object(GTK_OBJECT(GTK_FONT_SELECTION_DIALOG(dialog)->cancel_button),
                              "clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy),
                              GTK_OBJECT(dialog));


    gtk_widget_show(dialog);
}
void emoji_button_group_clicked(GtkWidget *button,gpointer userdata)
{
    GtkWidget *vbox;
    //filename_textView *filetrans;
    //filetrans->buffer1 = input_buffer1;
    //filetrans->buffer2 = output_buffer2;

    icon = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW (icon),GTK_WIN_POS_CENTER);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW (icon),TRUE);
    gtk_window_set_title (GTK_WINDOW (icon), "表情");

    g_signal_connect (G_OBJECT (icon), "destroy",G_CALLBACK (gtk_widget_destroy),icon);

    vbox = create_bbox(buffer);
    gtk_container_add (GTK_CONTAINER (icon), vbox);
    gtk_widget_show_all (icon);
}
void OpengroupFile(GtkWidget *widget,gpointer *data)

{
    g_print("%s/n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(FileSelection)));

}
void doc_button_group_clicked(GtkWidget *widget,gpointer *data)

{

    FileSelection=gtk_file_selection_new("选择文件");/*创建文件选择构件*/

    gtk_file_selection_set_filename(GTK_FILE_SELECTION(FileSelection),"*.txt");

    gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(FileSelection)->ok_button),
                       "clicked",GTK_SIGNAL_FUNC(OpengroupFile),NULL);/*捕捉打开按纽的”clicked”信号*/

    gtk_signal_connect_object(GTK_OBJECT(GTK_FILE_SELECTION(FileSelection)->cancel_button),
                              "clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy),
                              GTK_OBJECT(FileSelection));


    gtk_widget_show(FileSelection);

}
void update_chat(gchar *message, gchar *name, gint icon, gint id)
{

    sungtk_clist_append(glist, message, "../client/images/head_48.png", name,id);
    gtk_widget_show_all(window);
}
void update_friend_list(gchar *role, gchar* name, gint icon, gint id)
{
    sungtk_clist_append(friend_list, role, "../client/images/head_48.png", name,id);
    gtk_widget_show_all(window);
}
void delete_friend_list(gint id)
{
    id = friend_list->head->id+id*160;
    CListLink *target = friend_list->head;
    while(target!=NULL)
    {
        if(target->id==id)
        {
            break;
        }
        target=target->next;
    }
    if(target==NULL)
    {
        //error solution
    }
    CListLink *pointer = friend_list->head;
    while(pointer!=NULL)
    {
        if(pointer->next==target)
        {
            break;
        }
        pointer=pointer->next;
    }
    pointer->next=target->next;
    free(target);
    friend_list->total_num--;
    gtk_widget_show_all(window);
}
void log_button_group_clicked(GtkWidget *widget)
{
    delete_friend_list(3);
    //update_friend_list("mmdzb","mmdzb",3,4);
    sungtk_clist_unref(log_group_list);
    GtkWidget* log_window;
    GtkWidget* frame;
    GtkWidget* table;
    GtkWidget* table_list;
    GtkWidget* scroll_window;
    SunGtkCList *pointer = glist;
    SunGtkCList *pointer_to_log = log_group_list;

    log_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(log_window),"聊天记录");
    gtk_window_set_default_size(GTK_WINDOW(log_window),500,700);
    gtk_window_set_position(GTK_WINDOW(log_window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(log_window),20);

    table = gtk_table_new(1,1,TRUE);
    table_list = gtk_table_new(1,1,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(log_window),table);

    frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_IN);
    gtk_table_attach_defaults(GTK_TABLE(table),frame,0,1,0,1);

    scroll_window = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_window),
                                   GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(frame),scroll_window);

    /*sungtk_clist_set_row_height(llist,50);
    sungtk_clist_set_col_width(llist,200);
    sungtk_clist_set_text_size(llist,15);
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb")
    sungtk_clist_set_foreground(llist, "red");
    sungtk_clist_set_row_data(llist, 2, ": ***********");*/

   /*gtk_table_attach_defaults(GTK_TABLE(table_list),log_list->fixed,0,1,0,1);
   gtk_scrolled_window_add_with_viewport(scroll_window,table_list);*/
   gtk_widget_show_all(log_window);
}

/*static gint my_popup_handler (GtkWidget *widget, GdkEvent *event)
{
    GtkMenu *menu;
    //要弹出菜单的对象
    GdkEventButton *event_button;

    g_return_val_if_fail (widget != NULL, FALSE);
    g_return_val_if_fail (GTK_IS_MENU (widget), FALSE);
    g_return_val_if_fail (event != NULL, FALSE);

    //转换为菜单

    menu = GTK_MENU (widget);
    //判断是否是此事件
    if (event->type == GDK_BUTTON_PRESS)
    {
        event_button = (GdkEventButton *) event;
        //判断是否为左右键
        if (event_button->button == 3)
        {      //右键执行操作，第2～5个参数为NULL时表示在鼠标当前位置弹出菜单，
            //第6个参数表示被按下的按钮，最后一个参数是鼠标按下的时间。

            gtk_menu_popup (menu, NULL, NULL, NULL, NULL,event_button->button, event_button->time);
            return TRUE;
        }
    }
    return FALSE;
}

void set_menu()
{

    gtk_widget_set_events (llist->head->event_box, GDK_BUTTON_PRESS_MASK);
    g_signal_connect (G_OBJECT (llist->head->event_box), "button_press_event",
                      G_CALLBACK (my_popup_handler), NULL);



    gtk_widget_realize (llist->head->event_box);
}*/
//预计用来实现右键菜单，但还没实现

void group_chat()
{

    GtkWidget *table, *table1, *table3, *table5;
    GtkWidget *frame1, *frame2, *frame3, *frame4, *frame5, *frame6;
    GtkWidget *hbox1;
    GtkWidget *friend_name_label;
    GtkWidget *friend_portrait, *emoji, *doc, *font;
    GtkWidget *send_button, *font_button, *emoji_button, *doc_button, *history_button;
    GtkWidget *input;
    GtkWidget *scrolled_window;
    GtkWidget *scrolled_friend;
    //GtkWidget *table_chat;
    GtkWidget *table_friend;
    GtkWidget *friend_label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),1000,700);
    gtk_window_set_title(GTK_WINDOW(window),"Chat");

    gtk_container_set_border_width(GTK_CONTAINER(window),0);


    table = gtk_table_new(20,4,TRUE);
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

    frame6 = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame6),GTK_SHADOW_IN);

    scrolled_window = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(frame2),scrolled_window);

    scrolled_friend = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_friend),
                                   GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    friend_label = gtk_label_new("群成员");
    gtk_label_set_markup(
            GTK_LABEL(friend_label),
            "<span font_desc='22'>群成员列表</span>");
    gtk_container_add(GTK_CONTAINER(frame6),scrolled_friend);

    gtk_table_attach_defaults(GTK_TABLE(table),frame1,0,3,0,2);
    gtk_table_attach_defaults(GTK_TABLE(table),frame2,0,3,2,14);
    gtk_table_attach_defaults(GTK_TABLE(table),frame3,0,3,14,15);
    gtk_table_attach_defaults(GTK_TABLE(table),frame4,0,3,15,19);
    gtk_table_attach_defaults(GTK_TABLE(table),frame5,0,3,19,20);
    gtk_table_attach_defaults(GTK_TABLE(table),frame6,3,4,0,20);



    hbox1 = gtk_hbox_new(TRUE, 1);
    send_button = gtk_button_new_with_label("发送");

    friend_portrait=gtk_image_new_from_file("../client/images/friend_portrait.png");
    gtk_container_add(GTK_CONTAINER(hbox1), friend_portrait);

    friend_name_label = gtk_label_new(group_name);
    gtk_container_add(GTK_CONTAINER(hbox1), friend_name_label);

    table_chat = gtk_table_new(1,1,TRUE);
    gtk_scrolled_window_add_with_viewport(scrolled_window,table_chat);
    sungtk_clist_unref(glist);
    glist = sungtk_clist_new();
    sungtk_clist_set_row_height(glist, 50);
    sungtk_clist_set_col_width(glist, 200);
    sungtk_clist_set_text_size(glist, 15);
    sungtk_clist_append(glist, ": aaaaaaaaaaaaaa", "../client/images/head_48.png", "mmdzb",1);
    sungtk_clist_append(glist, ": aaaaaaaaaaaaaa", "../client/images/head_48.png", "mmdzb",2);
    sungtk_clist_append(glist, ": aaaaaaaaaaaaaa", "../client/images/head_48.png", "mmdzb",3);
    sungtk_clist_set_foreground(glist, "red");
    sungtk_clist_set_row_data(glist, 2, ": ***********");
    gtk_table_attach_defaults(GTK_TABLE(table_chat), glist->fixed, 0, 1, 0, 1);


    //gtk_table_attach_defaults(GTK_TABLE(table_chat), llist->fixed, 0, 1, 0, 1);

    table_friend = gtk_table_new(10,1,TRUE);
    friend_list = sungtk_clist_new();
    sungtk_clist_set_row_height(friend_list,50);
    sungtk_clist_set_col_width(friend_list,200);
    sungtk_clist_set_text_size(friend_list,15);
    sungtk_clist_append(friend_list, "  群成员","../client/images/head_48.png","mmdzb",1);
    sungtk_clist_append(friend_list, "  管理员","../client/images/head_48.png","mmdzb",2);
    sungtk_clist_append(friend_list, "  管理员","../client/images/head_48.png","mmdzb",3);
    sungtk_clist_append(friend_list, "  管理员","../client/images/head_48.png","mmdzb",4);
    sungtk_clist_append(friend_list, "  管理员","../client/images/head_48.png","mmdzb",5);
    sungtk_clist_append(friend_list, "  管理员","../client/images/head_48.png","mmdzb",6);
    sungtk_clist_set_foreground(friend_list, "gray");
    //sungtk_clist_set_row_data(friend_list, 2, ": ***********");
    gtk_table_attach_defaults(GTK_TABLE(table_friend),friend_label,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table_friend),friend_list->fixed,0,1,1,10);
    gtk_scrolled_window_add_with_viewport(scrolled_friend,table_friend);




    table1 = gtk_table_new(1, 10, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table1),0);
    gtk_table_set_col_spacings(GTK_TABLE(table1),0);
    gtk_table_attach_defaults(GTK_TABLE(table1),hbox1,0,3,0,1);
    gtk_container_add(GTK_CONTAINER(frame1),table1);

    font = gtk_image_new_from_file("../client/images/font.png");
    emoji = gtk_image_new_from_file("../client/images/emoji.png");
    doc = gtk_image_new_from_file("../client/images/doc.png");

    font_button = gtk_button_new();
    emoji_button = gtk_button_new();
    doc_button = gtk_button_new();


    history_button = gtk_button_new_with_label("消息记录");

    g_signal_connect(G_OBJECT(font_button),"clicked",
                     G_CALLBACK(font_button_group_clicked),NULL);


    g_signal_connect(G_OBJECT(emoji_button),"clicked",
                     G_CALLBACK(emoji_button_group_clicked),NULL);

    gtk_signal_connect(GTK_OBJECT(doc_button),"clicked",
                       G_CALLBACK(doc_button_group_clicked),NULL);
    gtk_signal_connect(GTK_OBJECT(history_button),"clicked",
                       G_CALLBACK(log_button_group_clicked),NULL);



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


    table5 = gtk_table_new(1, 15, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table5),0);
    gtk_table_set_col_spacings(GTK_TABLE(table5),0);
    gtk_table_attach_defaults(GTK_TABLE(table5),send_button,13,15,0,1);
    gtk_container_add(GTK_CONTAINER(frame5),table5);


    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),G_OBJECT(window));



    gtk_widget_show_all(window);

    //set_menu();

    gtk_main();

}