#include<gtk/gtk.h>
#include<string.h>
#include<stdlib.h>

const char * friend_name = "friend_a";

GtkWidget *FileSelection;

typedef gboolean (*SunGtkSelectRow)(GtkWidget *widget, GdkEventButton *event, gpointer data);
#define SUNGTK_CLIST(x) (SunGtkCList *)x
typedef struct _clist_link
{
    GtkWidget *box;
    GtkWidget *head_box;
    GtkWidget *name_box;
    GtkWidget *event_box;	//每一行都有一个事件盒子，用于支持点击
    GtkWidget *label;		//将label放置在事件盒子中，用于显示文字
    GtkWidget *image;
    GtkWidget *name;
    GtkWidget *table;
    struct _clist_link *next;
}CListLink;
typedef struct _sungtk_clist
{
    GtkWidget *fixed;		//整个列表是一个固定布局
    GtkWidget *vbox;		//利用垂直布局，可以动态追加行
    gint select_row;		//当前选中行
    gint font_size;			//字体大小
    gchar font_color[30];	//字体颜色
    gint row_height;		//每行的高度
    gint col_width;			//每行宽度
    gint total_num;			//行总数
    gchar sig_str[30];		//信号
    SunGtkSelectRow callback;//行点击回调函数
    CListLink *head;
}SunGtkCList;
static void sungtk_clist_set_label_color(GtkWidget *label, const char *color_buf)
{
    GdkColor color;
    gdk_color_parse(color_buf, &color);
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color);
}
static void sungtk_clist_set_label_size(GtkWidget *label, const gint size)
{
    PangoFontDescription *font;
    font = pango_font_description_from_string("Sans");          //"Sans"字体名
    pango_font_description_set_size(font, size*PANGO_SCALE);//设置字体大小
    gtk_widget_modify_font(GTK_WIDGET(label), font);
    pango_font_description_free(font);
}
int sungtk_clist_set_foreground(SunGtkCList *clist, const gchar *color_buf)
{
    if(clist == NULL)
        return -1;
    int i = 0;
    CListLink *temp_head = clist->head;
    memset(clist->font_color, 0, sizeof(clist->font_color));
    strncpy(clist->font_color, color_buf, sizeof(clist->font_color));
    while(temp_head)
    {
        sungtk_clist_set_label_color(temp_head->label, color_buf);
        temp_head = temp_head->next;
        ++i;
    }
    return i;
}
int sungtk_clist_set_row_color(SunGtkCList *clist, gint row, const gchar *color_buf)
{
    if(clist == NULL)
        return -1;
    int i = 0;
    CListLink *temp_head = clist->head;
    while(temp_head)
    {
        if(i==row){
            sungtk_clist_set_label_color(temp_head->label, color_buf);
            break;
        }
        temp_head = temp_head->next;
        ++i;
    }
    return i;
}
int sungtk_clist_select_row(SunGtkCList *clist, gint row, const gchar *color_buf)
{
    if(clist == NULL)
        return -1;
    int i = 0;
    CListLink *temp_head = clist->head;
    while(temp_head)
    {
        sungtk_clist_set_label_color(temp_head->label, clist->font_color);
        if(i==row){
            clist->select_row = i;
            sungtk_clist_set_label_color(temp_head->label, color_buf);
        }
        temp_head = temp_head->next;
        ++i;
    }
    return i;
}
int sungtk_clist_set_row_height(SunGtkCList *clist, gint height)
{
    if(clist == NULL)
        return -1;
    int i = 0;
    CListLink *temp_head = clist->head;
    clist->row_height = height;
    while(temp_head)
    {
        gtk_widget_set_size_request(temp_head->event_box, clist->col_width, clist->row_height);
        temp_head = temp_head->next;
        ++i;
    }
    return i;
}
int sungtk_clist_set_col_width(SunGtkCList *clist, gint width)
{
    if(clist == NULL)
        return -1;
    int i = 0;
    CListLink *temp_head = clist->head;
    clist->col_width = width;
    while(temp_head)
    {
        gtk_widget_set_size_request(temp_head->event_box, clist->col_width, clist->row_height);
        temp_head = temp_head->next;
        ++i;
    }
    return i;
}
int sungtk_clist_set_text_size(SunGtkCList *clist, int size)
{
    if(clist == NULL)
        return -1;
    int i = 0;
    CListLink *temp_head = clist->head;
    clist->font_size = size;
    while(temp_head)
    {
        sungtk_clist_set_label_size(temp_head->label, size);
        temp_head = temp_head->next;
        ++i;
    }
    return i;
}
const gchar *sungtk_clist_get_row_data(SunGtkCList *clist, gint row)
{
    if(clist == NULL)
        return NULL;
    int i = 0;
    CListLink *temp_head = clist->head;
    while(temp_head)
    {
        if(row == i)
            return gtk_label_get_text(GTK_LABEL(temp_head->label));
        temp_head = temp_head->next;
        ++i;
    }
    return NULL;
}
int sungtk_clist_set_row_data(SunGtkCList *clist, gint row, const gchar *text)
{
    if(clist == NULL || text==NULL)
        return -1;
    int i = 0;
    CListLink *temp_head = clist->head;
    while(temp_head)
    {
        if(row == i){
            gtk_label_set_text(GTK_LABEL(temp_head->label), text);
            break;
        }
        temp_head = temp_head->next;
        ++i;
    }
    return -1;
}
int sungtk_clist_set_select_row_signal(SunGtkCList *clist, const gchar *detailed_signal, SunGtkSelectRow callback)
{
    if(clist == NULL)
        return -1;

    clist->callback = callback;
    strncpy(clist->sig_str, detailed_signal, sizeof(clist->sig_str));
    return 0;
}
void sungtk_clist_set_position_in_fixed(SunGtkCList *clist, gint x, gint y)
{
    gtk_fixed_move(GTK_FIXED(clist->fixed), clist->vbox, x, y);
}
int sungtk_clist_append(SunGtkCList *clist, const gchar *text, const gchar *image, const gchar* name)
{
    if(clist==NULL || text==NULL)
        return -1;
    CListLink *temp = (CListLink *)malloc(sizeof(CListLink));
    if(temp==NULL)
        return -1;

    GtkWidget *img;
    img = gtk_image_new_from_file(image);
    temp->image = img;
    temp->table = gtk_table_new(3,20,TRUE);

    temp->box = gtk_hbox_new(FALSE,0);
    temp->name_box = gtk_hbox_new(FALSE,0);
    temp->head_box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(clist->vbox), temp->box);
    //gtk_widget_set_size_request(temp->box,20,20);

    temp->event_box = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(temp->event_box), FALSE);
    gtk_widget_set_size_request(temp->event_box, clist->col_width, clist->row_height);
    gtk_container_add(GTK_CONTAINER(temp->head_box), temp->image);

    gtk_container_add(GTK_CONTAINER(temp->box),temp->table);
    //gtk_container_add(GTK_CONTAINER(temp->vbox),temp->name_box);
    //gtk_container_add(GTK_CONTAINER(clist->vbox), temp->event_box);


    temp->label = gtk_label_new(text);
    temp->name = gtk_label_new(name);
    gtk_misc_set_alignment(GTK_MISC(temp->label), 0, 0.5);//居中
    sungtk_clist_set_label_size(temp->label, clist->font_size);
    sungtk_clist_set_label_color(temp->label, clist->font_color);
    //gtk_container_add(GTK_CONTAINER(temp->event_box), temp->image);
    gtk_container_add(GTK_CONTAINER(temp->event_box), temp->label);
    gtk_container_add(GTK_CONTAINER(temp->name_box),temp->name);
    gtk_table_attach_defaults(GTK_TABLE(temp->table),temp->head_box,0,3,0,3);
    gtk_table_attach_defaults(GTK_TABLE(temp->table),temp->name_box,2,10,0,2);
    gtk_table_attach_defaults(GTK_TABLE(temp->table),temp->event_box,3,20,1,3);
    //gtk_container_add(GTK_CONTAINER(temp->vbox),temp->event_box);

    temp->next = NULL;

    if(clist->callback != NULL){
        g_signal_connect(temp->event_box, clist->sig_str, G_CALLBACK(clist->callback), (void *)clist->total_num);
    }
    clist->total_num++;

    if(clist->head == NULL){
        clist->head = temp;
        return 0;
    }
    CListLink *temp_head = clist->head;
    CListLink *pf = NULL;
    while(temp_head)
    {
        pf = temp_head;
        temp_head = temp_head->next;
    }
    pf->next = temp;


    return 0;
}
SunGtkCList *sungtk_clist_new()
{
    SunGtkCList *clist = (SunGtkCList *)malloc(sizeof(SunGtkCList));
    if(clist==NULL)
        return NULL;
    memset(clist, 0, sizeof(SunGtkCList));
    clist->fixed = gtk_fixed_new();
    clist->vbox = gtk_vbox_new(TRUE, 5);
    gtk_fixed_put(GTK_FIXED(clist->fixed), clist->vbox, 0, 0);

    clist->font_size = 8;
    strncpy(clist->font_color, "black", sizeof(clist->font_color));
    clist->row_height = 30;
    clist->col_width = 100;
    clist->select_row = 0;
    clist->total_num = 0;
    return clist;
}
int sungtk_clist_unref(SunGtkCList *clist)
{
    if(clist == NULL)
        return-1;
    int i = 0;
    CListLink *temp_head = clist->head;
    CListLink *pf = NULL;
    while(temp_head)
    {
        pf = temp_head;
        temp_head = temp_head->next;
        gtk_widget_destroy(pf->label);
        gtk_widget_destroy(pf->event_box);
        free(pf);
        ++i;
    }
    gtk_widget_destroy(clist->fixed);
    free(clist);
    return 0;
}
SunGtkCList* llist = NULL;
/*void on_font_select_ok (GtkWidget *button,GtkFontSelectionDialog *fs)
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

    g_signal_connect_object(GTK_OBJECT(GTK_FONT_SELECTION_DIALOG(dialog)->cancel_button),
                              "clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy),
                              GTK_OBJECT(dialog));


    gtk_widget_show(dialog);
}

void OpenFile(GtkWidget *widget,gpointer *data)

{
    g_print("%s/n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(FileSelection)));

}

void doc_button_clicked(GtkWidget *widget,gpointer *data)

{

    FileSelection=gtk_file_selection_new("选择文件");

    gtk_file_selection_set_filename(GTK_FILE_SELECTION(FileSelection),"*.txt");

    gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(FileSelection)->ok_button),
            "clicked",GTK_SIGNAL_FUNC(OpenFile),NULL);

    gtk_signal_connect_object(GTK_OBJECT(GTK_FILE_SELECTION(FileSelection)->cancel_button),
                              "clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy),
                              GTK_OBJECT(FileSelection));


    gtk_widget_show(FileSelection);

}*/





int main(int argc,char *argv[])
{
    GtkWidget *window;
    GtkWidget *table, *table1, *table3, *table5;
    GtkWidget *frame1, *frame2, *frame3, *frame4, *frame5;
    GtkWidget *hbox1;
    GtkWidget *friend_name_label;
    GtkWidget *friend_portrait, *emoji, *doc, *font;
    GtkWidget *send_button, *font_button, *emoji_button, *doc_button, *history_button;
    GtkWidget *input;
    GtkWidget *scrlled_window;
    GtkTextBuffer *buffer;
    GtkWidget *table_chat;



    gtk_init(&argc,&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),700,700);
    gtk_window_set_title(GTK_WINDOW(window),"Chat");

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

    scrlled_window = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrlled_window),
                                   GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(frame2),scrlled_window);


    gtk_table_attach_defaults(GTK_TABLE(table),frame1,0,1,0,2);
    gtk_table_attach_defaults(GTK_TABLE(table),frame2,0,1,2,14);
    gtk_table_attach_defaults(GTK_TABLE(table),frame3,0,1,14,15);
    gtk_table_attach_defaults(GTK_TABLE(table),frame4,0,1,15,19);
    gtk_table_attach_defaults(GTK_TABLE(table),frame5,0,1,19,20);




    hbox1 = gtk_hbox_new(TRUE, 1);
    send_button = gtk_button_new_with_label("发送");

    friend_portrait=gtk_image_new_from_file("../client/images/friend_portrait.png");
    gtk_container_add(GTK_CONTAINER(hbox1), friend_portrait);

    friend_name_label = gtk_label_new(friend_name);
    gtk_container_add(GTK_CONTAINER(hbox1), friend_name_label);



    table1 = gtk_table_new(1, 10, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table1),0);
    gtk_table_set_col_spacings(GTK_TABLE(table1),0);
    gtk_table_attach_defaults(GTK_TABLE(table1),hbox1,0,3,0,1);
    gtk_container_add(GTK_CONTAINER(frame1),table1);

    table_chat = gtk_table_new(2,1,TRUE);
    llist = sungtk_clist_new();
    sungtk_clist_set_row_height(llist,50);
    sungtk_clist_set_col_width(llist,200);
    sungtk_clist_set_text_size(llist,15);
    gtk_table_attach_defaults(GTK_TABLE(table_chat),llist->fixed,0,1,0,1);
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
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_append(llist, ": aaaaaaaaaaaaaa","../client/images/head_48.png","mmdzb");
    sungtk_clist_set_foreground(llist, "red");
    sungtk_clist_set_row_data(llist, 2, ": ***********");
    gtk_scrolled_window_add_with_viewport(scrlled_window,table_chat);

    font = gtk_image_new_from_file("../client/images/font.png");
    emoji = gtk_image_new_from_file("../client/images/emoji.png");
    doc = gtk_image_new_from_file("../client/images/doc.png");

    font_button = gtk_button_new();
    emoji_button = gtk_button_new();
    doc_button = gtk_button_new();


    history_button = gtk_button_new_with_label("消息记录");

   /* g_signal_connect(G_OBJECT(font_button),"clicked",
                     G_CALLBACK(font_button_clicked),NULL);

    g_signal_connect(G_OBJECT(doc_button),"clicked",G_CALLBACK(doc_button_clicked),NULL);*/




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


    gtk_main();
    return 0;
}