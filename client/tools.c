#include<gtk/gtk.h>
#include<string.h>
#include<stdlib.h>
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
    gint id;
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
int sungtk_clist_append(SunGtkCList *clist, const gchar *text, const gchar *image, const gchar* name,const gint id)
{

    if(clist==NULL || text==NULL)
        return -1;
    CListLink *temp = (CListLink *)malloc(sizeof(CListLink));
    if(temp==NULL)
        return -1;

    temp->id = id;

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