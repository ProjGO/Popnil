#include <gtk/gtk.h>
#include <string.h>
#include "../common/include/define.h"

//extern local_user_info;
extern GtkWidget *add_friends();
extern GtkWidget *add_groups();
extern GtkWidget *chat(char *target_name, int *target_id);
extern GtkWidget *group_chat();
extern GtkWidget *setting();
extern int usr_id;
extern int fd_log,fd_chat,fd_file;
extern rio_t rio_log, rio_chat, rio_file;
extern void update_widget_bg(GtkWidget *widget, int w,int h, const gchar *img_file);
GtkWidget *image_usericon;
GtkWidget *window_list;
GtkWidget *page_friend_vbox;
GtkWidget *search_entry_friend_list;
////好友(群组)列表的个数max & 每个列表中好友(群组)的个数max
#define MAX_LIST_NUM 100
#define MAX_LIST_FRIEND_GROUP_NUM 100


general_array update_friend_info_c(rio_t *rio_log, int fd_log)
{
    OP_TYPE type = UPDATE;
    int friend_num = 0;
    client_info my_info;
    general_array friend_info_array;
    rio_writen(fd_log, &type, sizeof(OP_TYPE)); // 向服务器发送请求同步的op
    rio_writen(fd_log, &usr_id, sizeof(int)); // 发送自己的id

    read(fd_log, &my_info, sizeof(client_info));
    //----------------------------------------------------------
    //在客户端中更新显示本人头像、昵称等
    //----------------------------------------------------------

    read(fd_log, &friend_num, sizeof(int)); // 从服务器接收有几个好友
    friend_info_array.num = friend_num;
    friend_info_array.data = malloc(friend_num * sizeof(client_info)); // 申请内存
    for(int i = 0; i < friend_num; i++)
    {
        //read(fd_log, &((client_info *)friend_info_array.data)[i], sizeof(client_info)); // 填进去
        rio_readnb(rio_log, &((client_info *)friend_info_array.data)[i], sizeof(client_info));
        printf("%d : %d\n",i,((client_info *)friend_info_array.data)[i].id);
    }

    return friend_info_array;
}


//记录每个好友和群组的信息
struct  friend_and_group
{
    GtkWidget* vbox; //vbox代表在哪一个列表中
    GtkWidget* button; //button代表在列表中哪一个控件中
    char *number_name[25];
    char *list_name[25];
    gboolean is_empty; //判断该位置是否可以存储好友信息
    int friend_group_num; //记录每列中好友的个数
};
//好友列表 & 群组列表
struct friend_and_group friend[MAX_LIST_NUM][MAX_LIST_FRIEND_GROUP_NUM];
struct friend_and_group group[MAX_LIST_NUM][MAX_LIST_FRIEND_GROUP_NUM];


//GtkWidget* add_list(GtkWidget *page, GtkWidget* vbox, const char *str)
GtkWidget* add_list(GtkWidget *page, const char *str)
{
    //创建滑动窗口
    // GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL,NULL);
    //设置自动滑动条
    // gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    GtkWidget* expander = gtk_expander_new_with_mnemonic(str);
    GtkWidget* vbox = gtk_vbox_new(TRUE, 5);
    //添加到page中
    gtk_box_pack_start(GTK_BOX(page), expander, FALSE, FALSE, 10);
//    gtk_container_add(GTK_CONTAINER(expander), scrolled_window);
    gtk_container_add(GTK_CONTAINER(expander), vbox);
    gtk_expander_get_spacing(expander);
//    gtk_scrolled_window_add_with_viewport(scrolled_window, vbox);
    return vbox;
}
/**添加好友或群组
 * str好友或群组名字
 *
 */
//弹出菜单回调函数
static gint my_popup_handler (GtkWidget *widget, GdkEvent *event)
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

//void remove_friend_group(struct  remove_friend_from_list* data)
//{
//    gtk_container_remove(GTK_CONTAINER(data->vbox), data->button);
//}
//chang shi
GtkWidget* add_friend_group(GtkWidget* vbox, const char *str, const char *image_path)
{
    GtkWidget* button = gtk_button_new();
    GtkWidget* hbox = gtk_hbox_new(TRUE, 0);
    GtkWidget* name_label = gtk_label_new(str);
    GtkWidget* image = gtk_image_new_from_file(image_path);
    GtkWidget* filemenu;
    GtkWidget* menuitem;
    GtkAccelGroup* accel_group;

    accel_group = gtk_accel_group_new();
    filemenu = gtk_menu_new();
    menuitem = gtk_image_menu_item_new_from_stock("删除好友", accel_group);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), menuitem);
    gtk_widget_show(menuitem);

//    gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),filemenu);
//    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),rootmenu);
    //设置button背景透
    gtk_button_set_relief(button, GTK_RELIEF_NONE);
    //点击信号
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(group_chat), NULL);
    g_signal_connect_swapped(GTK_OBJECT(button),"button_press_event",G_CALLBACK(my_popup_handler), GTK_OBJECT(filemenu));
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(button), hbox);
    gtk_box_pack_start(GTK_BOX(hbox), image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), name_label, TRUE, TRUE, 0);

//    struct remove_friend_from_list remove_button;
//    remove_button.vbox = vbox;
//    remove_button.button = button;
//    struct remove_friend_from_list* data = &remove_button;
//    g_signal_connect_swapped(G_OBJECT(menuitem), "activate", G_CALLBACK(remove_friend_group), data);

    return button;
}


/*
 * 初始化好友/群组列表
 */
void init_friend_group_list()
{
    int i, j;
    for (i = 0; i < MAX_LIST_NUM; i++)
    {
        for (j = 0; j < MAX_LIST_FRIEND_GROUP_NUM; j++)
        {
            friend[i][j].is_empty = TRUE;
            friend[i][j].friend_group_num = 0;
            group[i][j].is_empty = TRUE;
            group[i][j].friend_group_num = 0;
        }
    }
}

/**添加一个好友, 并放入指定列表名字中
 *
 */
void add_list_friends(GtkWidget* page, const char* list_name, const char* friend_name, const char* image)
{
    int i, j;
    //先找有无该列表
    int flag = 0;
    for(i = 1; i < MAX_LIST_NUM; i++)
    {
        if (friend[i][0].friend_group_num > 0 && strcmp(friend[i][0].list_name, list_name) == 0) {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        //有 群组加1
        friend[i][0].friend_group_num += 1;
        int j;
        for (j = 1; j < MAX_LIST_FRIEND_GROUP_NUM; j++)
        {
            if (friend[i][j].is_empty) {
                strcpy(friend[i][0].list_name, list_name);
                strcpy(friend[i][j].number_name, friend_name);
                //将好友添加到界面中
//                GtkWidget* friend_group = add_friend_group(friend[i][0].vbox, friend_name, image);
                friend[i][j].button = add_friend_group(friend[i][0].vbox, friend_name, image);

                friend[i][j].is_empty = FALSE;
                break;
            }
        }
    }
    else
    {
        //需要新建列表
        for (i = 1; i < MAX_LIST_NUM; i++) {
            if (friend[i][0].friend_group_num == 0)
            {
                break;
            }
        }
        friend[i][0].friend_group_num = 1;
        strcpy(friend[i][0].list_name, list_name);
        strcpy(friend[i][1].number_name, friend_name);
        friend[i][1].is_empty = FALSE;
        //将好友添加到界面中
//        GtkWidget* vbox = add_list(page, list_name);
        friend[i][0].vbox = add_list(page, list_name);
//        GtkWidget* friend_group = add_friend_group(vbox, friend_name, image);
        friend[i][1].button = add_friend_group(friend[i][0].vbox, friend_name, image);
    }

}
/**添加一个群组, 并放入指定列表名字中
 *
 * str 列表的名字
 */
void add_list_groups(GtkWidget* page, const char* list_name, const char* group_name, const char* image)
{
    int i, j;
    //先找有无该列表
    int flag = 0;
    for(i = 1; i < MAX_LIST_NUM; i++)
    {
        if (group[i][0].friend_group_num > 0 && strcmp(group[i][0].list_name, list_name) == 0) {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        //有 成员加1
        group[i][0].friend_group_num += 1;
        int j;
        for (j = 1; j < MAX_LIST_FRIEND_GROUP_NUM; j++)
        {
            if (group[i][j].is_empty) {
                strcpy(group[i][0].list_name, list_name);
                strcpy(group[i][j].number_name, group_name);
                //将好友添加到界面中
//                GtkWidget* friend_group = add_friend_group(friend[i][0].vbox, friend_name, image);
                group[i][j].button = add_friend_group(group[i][0].vbox, group_name, image);

                group[i][j].is_empty = FALSE;
                break;
            }
        }
    }
    else
    {
        //需要新建列表
        for (i = 1; i < MAX_LIST_NUM; i++) {
            if (group[i][0].friend_group_num == 0)
            {
                break;
            }
        }
        group[i][0].friend_group_num = 1;
        strcpy(group[i][0].list_name, list_name);
        strcpy(group[i][1].number_name, group_name);
        group[i][1].is_empty = FALSE;
        //将好友添加到界面中
//        GtkWidget* vbox = add_list(page, list_name);
        group[i][0].vbox = add_list(page, list_name);
//        GtkWidget* friend_group = add_friend_group(vbox, friend_name, image);
        group[i][1].button = add_friend_group(group[i][0].vbox, group_name, image);
    }
}



GtkWidget* create_button(char *image_path, char *button_label)
{
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *label;
    GtkWidget *button;
    //char *title = "红苹果";
    image = gtk_image_new_from_file(image_path);

    label = gtk_label_new(button_label);//(title);
    //不均匀排放，间隔为2个像素
    box = gtk_vbox_new(FALSE,0);
    //设定容器边框的宽度
    gtk_container_set_border_width(GTK_CONTAINER(box),0);
    gtk_box_pack_start(GTK_BOX(box),image,TRUE,TRUE,0);
//    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
    gtk_widget_show(image);
//    gtk_widget_show(label);

    button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button),box);
    gtk_widget_show(box);
    return button;
}

/*
 * 搜索好友功能
 */
void search_friend()
{
    char* text = gtk_entry_get_text(search_entry_friend_list);
    int i, j;
    int a = 1;
    for (i = 1; i < MAX_LIST_NUM; i++)
    {
        for (j = 1; j < MAX_LIST_FRIEND_GROUP_NUM; j++)
        {

//            if (!friend[i][j].is_empty)
//              printf("%s\n", friend[i][j].number_name);
            if (!friend[i][j].is_empty && strcmp(friend[i][j].number_name, text) == 0)
            {
                chat(friend[i][j].number_name, &a);
                break;
            }

        }
    }
}

void call_add_friends()
{
    add_friends();
    while(gtk_events_pending()){

        gtk_main_iteration();

    }

    sleep(1);

}

void list()
{

    GtkWidget *table;
    GtkWidget *label_username;
    GtkWidget *button_setting;
    GtkWidget *search_entry;
    GtkWidget *notebook;
    GtkWidget *page_friend_vbox;
    GtkWidget *notebook_image_friend;
    GtkWidget *page_group_vbox;
    GtkWidget *notebook_image_group;
    GtkWidget *scrolled_window_page_friend;
    GtkWidget *scrolled_window_page_group;



//    gtk_init(&argc, &argv);

    
    window_list = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window_list),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window_list),200,500);
    gtk_window_set_title(GTK_WINDOW(window_list),"Chat");
    gtk_container_set_border_width(GTK_CONTAINER(window_list),0);
//    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_widget_destroy),window);
    table = gtk_table_new(40, 16, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(window_list),table);
    g_signal_connect ( window_list, "destroy",
                       G_CALLBACK (gtk_main_quit), NULL);	//为窗口连接“退出事件”
//  g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);



    image_usericon = gtk_image_new_from_file("../client/images/d_portrait.PNG");
    gtk_table_attach_defaults(GTK_TABLE(table), image_usericon, 1, 5, 1, 5);

    label_username = gtk_label_new("XDX");
    gtk_table_attach_defaults(GTK_TABLE(table),label_username, 5, 13, 1, 5);

    button_setting = create_button("../client/images/set.png", NULL);
    gtk_table_attach_defaults(GTK_TABLE(table),button_setting, 14, 16, 37, 40);
    g_signal_connect(GTK_BUTTON(button_setting),"clicked", G_CALLBACK(setting), NULL);

    GdkPixbuf * pixbuf= gdk_pixbuf_new_from_file("../client/images/search.png", FALSE);

    search_entry_friend_list = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),search_entry_friend_list, 0, 16, 6, 8);
    gtk_entry_set_has_frame(search_entry_friend_list, FALSE);
    gtk_entry_set_icon_from_pixbuf(search_entry_friend_list, GTK_ENTRY_ICON_PRIMARY, pixbuf);
    gtk_entry_set_text(search_entry_friend_list, "Search...");
    g_signal_connect(GTK_OBJECT(search_entry_friend_list), "activate", G_CALLBACK(search_friend), NULL);


    notebook = gtk_notebook_new();
    gtk_table_attach_defaults(GTK_TABLE(table), notebook, 0, 16, 9, 37);
    notebook_image_friend = gtk_image_new_from_file("../client/images/friends_list.png");
    notebook_image_group = gtk_image_new_from_file("../client/images/group_list.png");

    page_friend_vbox = gtk_vbox_new(FALSE, 0);
    scrolled_window_page_friend = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window_page_friend),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window_page_friend), page_friend_vbox);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scrolled_window_page_friend, notebook_image_friend);

    page_group_vbox = gtk_vbox_new(FALSE, 0);
    scrolled_window_page_group = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window_page_group),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window_page_group), page_group_vbox);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scrolled_window_page_group, notebook_image_group);

    gtk_notebook_set_tab_reorderable(notebook, scrolled_window_page_friend, TRUE);
    gtk_notebook_set_tab_reorderable(notebook, scrolled_window_page_group, TRUE);

//
    GtkWidget *button_add_friends;
    GtkWidget *button_add_groups;
    button_add_friends = create_button("../client/images/add_friends.png", NULL);
    button_add_groups = create_button("../client/images/add_groups.png", NULL);
    //把事件盒放到横向的盒子里
    gtk_table_attach_defaults(GTK_TABLE(table), button_add_friends, 0, 4, 37, 40);
    g_signal_connect(button_add_friends, "clicked", G_CALLBACK(call_add_friends), NULL);
    gtk_widget_show(window_list);

    gtk_table_attach_defaults(GTK_TABLE(table), button_add_groups, 4, 8, 37, 40);
    g_signal_connect(button_add_groups, "clicked", G_CALLBACK(add_groups), NULL);

//    GtkWidget* my_friend_vbox =add_list(page_friend_vbox, "我的好友");
//    add_friend_group(my_friend_vbox, "lalalala", "../client/images/emoji.png");
    init_friend_group_list();
//    add_list_friends(page_friend_vbox, "my friend", "liuzhen", "../client/images/emoji.png");
//    add_list_friends(page_friend_vbox, "my friend", "lalalal", "../client/images/emoji.png");
//    add_list_friends(page_friend_vbox, "我的同学", "xdx", "../client/images/emoji.png");
//    add_list_friends(page_friend_vbox, "我的同学", "666", "../client/images/emoji.png");
//
//    add_list_groups(page_group_vbox, "my friend", "liuzhen", "../client/images/emoji.png");
//    add_list_groups(page_group_vbox, "my friend", "lalalal", "../client/images/emoji.png");
//    add_list_groups(page_group_vbox, "我的同学", "xdx", "../client/images/emoji.png");
//    add_list_groups(page_group_vbox, "我的同学", "666", "../client/images/emoji.png");

    //////zzk
    general_array friendlist;
    friendlist = update_friend_info_c(&rio_log,fd_log);
//    GtkWidget* my_friend_vbox =add_list(page_friend_vbox, "我的好友");
    client_info * tem = (client_info*) friendlist.data;
    for(int i=0;i<friendlist.num;i++)
    {//zzk change
        add_list_friends(page_friend_vbox, "my friend", tem[i].nickname ,"../client/images/emoji.png");
//        add_friend_group(my_friend_vbox,tem[i].nickname , "../client/images/emoji.png");
    }
    //add_list_groups("我的群组", "hahahqun", "../image.png");
//    while(gtk_events_pending()){
//
//        gtk_main_iteration();
//
//    }
//
//    sleep(1);
   

    gtk_widget_show_all(window_list);

    gtk_main();




}