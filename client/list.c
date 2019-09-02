#include <gtk/gtk.h>

extern GtkWidget *add_friends();
extern GtkWidget *chat();
extern GtkWidget *setting();
/**添加一个好友列表或其群组列表
 * page 好友界面&群组界面
 * str 列表的名字
 * 返回vbox来添加好友或群组
 */
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
void add_friend_group(GtkWidget* vbox, const char *str, const char *image_path)
{
    GtkWidget* button = gtk_button_new();
    GtkWidget* hbox = gtk_hbox_new(TRUE, 0);
    GtkWidget* name_label = gtk_label_new(str);
    GtkWidget* image = gtk_image_new_from_file(image_path);
    //设置button背景透
    gtk_button_set_relief(button, GTK_RELIEF_NONE);
    //点击信号
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(chat), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(button), hbox);
    gtk_box_pack_start(GTK_BOX(hbox), image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), name_label, TRUE, TRUE, 0);

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
void list()
{
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *image_usericon;
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
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),200,500);
    gtk_window_set_title(GTK_WINDOW(window),"Chat");
    gtk_container_set_border_width(GTK_CONTAINER(window),0);
//    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_widget_destroy),window);
    table = gtk_table_new(40, 16, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(window),table);
    g_signal_connect ( window, "destroy",
                       G_CALLBACK (gtk_main_quit), NULL);	//为窗口连接“退出事件”
//  g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);




    image_usericon = gtk_image_new_from_file("../client/images/friend_portrait.png");
    gtk_table_attach_defaults(GTK_TABLE(table), image_usericon, 1, 5, 1, 5);

    label_username = gtk_label_new("XDX");
    gtk_table_attach_defaults(GTK_TABLE(table),label_username, 5, 13, 1, 5);

    button_setting = create_button("../client/images/set.png", NULL);
    gtk_table_attach_defaults(GTK_TABLE(table),button_setting, 11, 16, 0, 4);
    g_signal_connect(GTK_BUTTON(button_setting),"clicked", G_CALLBACK(setting), NULL);

    GdkPixbuf * pixbuf= gdk_pixbuf_new_from_file("../client/images/search.png", FALSE);

    search_entry = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),search_entry, 0, 16, 6, 8);
    gtk_entry_set_has_frame(search_entry, FALSE);
    gtk_entry_set_icon_from_pixbuf(search_entry, GTK_ENTRY_ICON_PRIMARY, pixbuf);
    gtk_entry_set_text(search_entry, "Search...");


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
    button_add_friends = create_button("../client/images/add_friends.png", NULL);
    //把事件盒放到横向的盒子里
    gtk_table_attach_defaults(GTK_TABLE(table), button_add_friends, 0, 16, 37, 40);
    g_signal_connect(button_add_friends, "clicked", G_CALLBACK(add_friends), NULL);

    GtkWidget* my_friend_vbox =add_list(page_friend_vbox, "我的好友");
    add_friend_group(my_friend_vbox, "lalalala", "../client/images/emoji.png");



    gtk_widget_show_all(window);
    gtk_main();

}