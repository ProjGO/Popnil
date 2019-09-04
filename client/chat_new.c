#include <gtk/gtk.h>
#include "tools.h"
#include "../common/include/include.h"
#include "../common/include/define.h"
#include "../common/include/client_utils.h"

//const char * friend_name = "friend_a";
extern GtkWidget *create_bbox(GtkTextBuffer *input_buffer1 );
SunGtkCList* llist = NULL;
SunGtkCList* log_list = NULL;

GtkWidget *FileSelection;
GtkTextBuffer *buffer;
GtkWidget *icon;
GtkWidget *input;
GtkWidget *window;

extern int fd_log, fd_chat, fd_file;
extern int all_ids[100]; // 所有与这个人有关系的id,在登陆时由服务器告知,并在加好友/群时更新
extern int all_ids_cnt; // 字面意思
extern client_info target;
extern GtkWidget * id2window[100];
extern int usr_id;
extern client_info my_info;

extern SunGtkCList* idx2list[100];
extern GtkWidget* idx2window[100];
extern int opend_list_idx2id[100];
extern int max_chat_window_idx;

text_pack_t recved_messages[100];
int recved_messages_cnt = 0;

void update_chat(gchar *massage,gchar *name,gint icon,gint id)
{
    char *portrait_filename = get_portrait_filename_by_idx(icon);
    sungtk_clist_append(llist, massage, portrait_filename, name, id);
    free(portrait_filename);
    gtk_widget_show_all(window);
}

void send_button_clicked(GtkWidget *window)
{
    char *text;

    char temp[2000] = ": ";
    GtkTextIter start,end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);

    const GtkTextIter s=start, e=end;
    text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&s,&e,FALSE);
    strcat(temp,text);
    update_chat(temp, my_info.nickname,my_info.portrait_idx,4);
    gtk_text_buffer_delete(buffer,&s,&e);

    OP_TYPE op = TEXT_trans;
    rio_writen(fd_log, &op, sizeof(OP_TYPE));
    text_pack_t text_pack;
    memset(&text_pack, 0, sizeof(text_pack));
    //strcpy(text_pack.text, gtk_entry_get_text(GTK_ENTRY((GtkWidget *)input)));
    strcpy(text_pack.text,temp);
    //text_pack.id = target.id;//////////////////////////////
    text_pack.id = opend_list_idx2id[max_chat_window_idx-1];
    if(write(fd_log, &text_pack, sizeof(text_pack_t))<0)
        printf("f**k you\n");
}

void on_font_select_ok (GtkWidget *button,GtkFontSelectionDialog *fs)
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
void font_button_clicked (GtkWidget *button,gpointer userdata)
{
    GtkWidget* dialog ;

    dialog = gtk_font_selection_dialog_new("请选择一种字体：");
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    g_signal_connect(GTK_OBJECT(dialog),"destroy",
                       GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog);
    g_signal_connect(GTK_OBJECT(GTK_FONT_SELECTION_DIALOG(dialog)->ok_button),
                       "clicked",GTK_SIGNAL_FUNC(on_font_select_ok),
                       GTK_FONT_SELECTION_DIALOG(dialog));

    gtk_signal_connect_object(GTK_OBJECT(GTK_FONT_SELECTION_DIALOG(dialog)->cancel_button),
                              "clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy),
                              GTK_OBJECT(dialog));


    gtk_widget_show(dialog);
}
void emoji_button_clicked(GtkWidget *button,gpointer userdata)
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
void OpenFile(GtkWidget *widget,gpointer *data)
{

    // g_print("%s/n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(FileSelection)));
    OP_TYPE op = FILE_trans;
    rio_writen(fd_log, &op, sizeof(OP_TYPE)); // 发送op类型
    size_t *buf;
    buf = (size_t*)malloc(MAX_FILE_SIZE*sizeof(size_t)); // 20Mb buf
    char filename[256];
    sprintf(filename, "%s", gtk_file_selection_get_filename(GTK_FILE_SELECTION(FileSelection)));
    struct stat statbuf;
    stat(filename, &statbuf);
    int filesize = statbuf.st_size;
    rio_writen(fd_log, &target.id, sizeof(int)); // 发送目标id
    rio_writen(fd_log, &filesize, sizeof(int)); // 发送文件大小
    FILE *file = fopen(filename, "rb");
    if(!file){
        printf("文件打开失败\n");
        exit(-1);
    }
    if(fseek(file, 0, SEEK_SET)!=0)
    {
        printf("fseed failed\n");
        exit(-1);
    }
    if(fread(buf, filesize, 1, file)) // 将文件完全读取到buf中
    {
        printf("文件读取失败\n");
        exit(-1);
    }
    rio_writen(fd_log, buf, filesize); // 发送文件
}
void doc_button_clicked(GtkWidget *widget,gpointer *data)

{

    FileSelection=gtk_file_selection_new("选择文件");/*创建文件选择构件*/

    gtk_file_selection_set_filename(GTK_FILE_SELECTION(FileSelection),"*.txt");

    g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(FileSelection)->ok_button),
            "clicked",GTK_SIGNAL_FUNC(OpenFile),NULL);/*捕捉打开按纽的”clicked”信号*/

    gtk_signal_connect_object(GTK_OBJECT(GTK_FILE_SELECTION(FileSelection)->cancel_button),
                              "clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy),
                              GTK_OBJECT(FileSelection));


    gtk_widget_show(FileSelection);

}
void log_button_clicked(GtkWidget *widget)
{
    GtkWidget* log_window;
    GtkWidget* frame;
    GtkWidget* table;
    GtkWidget* table_list;
    GtkWidget* scroll_window;

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

    gtk_table_attach_defaults(GTK_TABLE(table_list),llist->fixed,0,1,0,1);
    gtk_scrolled_window_add_with_viewport(scroll_window,table_list);

    gtk_widget_show_all(log_window);

}

GtkWidget* chat(GtkWidget *button)
{


    GtkWidget *table, *table1, *table3, *table5;
    GtkWidget *frame1, *frame2, *frame3, *frame4, *frame5;
    GtkWidget *hbox1;
    GtkWidget *friend_name_label;
    GtkWidget *friend_portrait, *emoji, *doc, *font;
    GtkWidget *send_button, *font_button, *emoji_button, *doc_button, *history_button;
//     GtkWidget *input;
    GtkWidget *scrolled_window;
    GtkWidget *table_chat;

//    gtk_init(&argc,&argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);////////////////////////////
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),700,700);
    gtk_window_set_title(GTK_WINDOW(window),target.nickname);

    gtk_container_set_border_width(GTK_CONTAINER(window),0);


    table = gtk_table_new(20,1,TRUE);
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

    scrolled_window = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(frame2),scrolled_window);

    gtk_table_attach_defaults(GTK_TABLE(table),frame1,0,1,0,2);
    gtk_table_attach_defaults(GTK_TABLE(table),frame2,0,1,2,14);
    gtk_table_attach_defaults(GTK_TABLE(table),frame3,0,1,14,15);
    gtk_table_attach_defaults(GTK_TABLE(table),frame4,0,1,15,19);
    gtk_table_attach_defaults(GTK_TABLE(table),frame5,0,1,19,20);




    hbox1 = gtk_hbox_new(TRUE, 1);
    send_button = gtk_button_new_with_label("发送");
    g_signal_connect(send_button,"clicked",G_CALLBACK(send_button_clicked), NULL);

    friend_portrait=gtk_image_new_from_file("../client/images/friend_p.ortrait.png");
    gtk_container_add(GTK_CONTAINER(hbox1), friend_portrait);

    friend_name_label = gtk_label_new(target.nickname);
    gtk_container_add(GTK_CONTAINER(hbox1), friend_name_label);

    table_chat = gtk_table_new(1,1,TRUE);
    llist = sungtk_clist_new();/////////////////////////////////////////
    sungtk_clist_set_row_height(llist,50);
    sungtk_clist_set_col_width(llist,200);
    sungtk_clist_set_text_size(llist,15);
//    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb",233);
//    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");

    sungtk_clist_set_foreground(llist, "red");
    sungtk_clist_set_row_data(llist, 2, ": ***********");
    gtk_table_attach_defaults(GTK_TABLE(table_chat),llist->fixed,0,1,0,1);
    gtk_scrolled_window_add_with_viewport(scrolled_window,table_chat);

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
                     G_CALLBACK(font_button_clicked),NULL);


    g_signal_connect(G_OBJECT(emoji_button),"clicked",
                     G_CALLBACK(emoji_button_clicked),NULL);

    gtk_signal_connect(GTK_OBJECT(doc_button),"clicked",
            G_CALLBACK(doc_button_clicked),NULL);
    gtk_signal_connect(GTK_OBJECT(history_button),"clicked",
                       G_CALLBACK(log_button_clicked),NULL);



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
    opend_list_idx2id[max_chat_window_idx]=target.id;
    idx2list [max_chat_window_idx]=llist;
    idx2window[max_chat_window_idx]=window;
    max_chat_window_idx++;

    gtk_main();

    return window;
}
