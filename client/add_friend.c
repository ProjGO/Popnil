//
// Created by xdx on 19-9-2.
//

#include <gtk/gtk.h>
//#include <gtk-3.0>
#include <gdk/gdkkeysyms.h>   //键盘头文件，GDK_Up在这声明
#include "../common/include/include.h"
#include "../common/include/define.h"
GtkWidget *search_entry;
char* default_image_path = "../client/images/friend_portrait.png";
char* default_id = "1120173454";
char* default_name = "xdx";
extern GtkWidget *create_button(char *image_path, char *button_label);
extern void update_widget_bg(GtkWidget *widget, int w,int h, const gchar *img_file);

GtkWidget *add_friend_window;
void search(GtkWidget *window, gpointer data)
{
    oper_friend_info *id_text=(oper_friend_info*)malloc(sizeof(oper_friend_info));
    id_text->id_re=atoi(gtk_entry_get_text(GTK_ENTRY((GtkWidget *) search_entry)));


}

GtkWidget *information_frame()
{
    GtkWidget* frame;
    GtkWidget* table;
    GtkWidget* image;
    GtkWidget* id;
    GtkWidget* user_name;
    GtkWidget* button;

    frame = gtk_frame_new("Information");
    table = gtk_table_new(16, 12, TRUE);
    gtk_container_add(frame, table);
    gtk_frame_set_label(frame, "Information");
    image = gtk_image_new_from_file(default_image_path);
    gtk_table_attach_defaults(GTK_TABLE(table),image, 0, 3, 0, 5);
    id = gtk_label_new(default_id);
    user_name = gtk_label_new(default_name);

    PangoFontDescription *font_desc = pango_font_description_from_string ("Serif 15");
    pango_font_description_set_size (font_desc, 20 * PANGO_SCALE);
    gtk_widget_modify_font (id, font_desc);
    gtk_widget_modify_font (user_name, font_desc);
    pango_font_description_free (font_desc);

    gtk_table_attach_defaults(GTK_TABLE(table), id, 3, 10, 0, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), user_name, 3, 10, 3, 6);

    button = create_button("../client/images/add.png", "添加");
    gtk_button_set_relief(button, GTK_RELIEF_NONE);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 4, 8, 7, 13);

    return frame;
}

GtkWidget *add_friends()
{

    GtkWidget *table;
    GtkWidget *frame;
    GtkWidget *button_search;

    add_friend_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(add_friend_window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(add_friend_window),400,400);
    gtk_window_set_title(GTK_WINDOW(add_friend_window),"Add friends");
    gtk_container_set_border_width(GTK_CONTAINER(add_friend_window),0);
    g_signal_connect ( add_friend_window, "destroy",
                       G_CALLBACK (gtk_main_quit), NULL);	//为窗口连接“退出事件”
    table = gtk_table_new(20, 20, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(add_friend_window),table);

//    search_entry = gtk_search_entry_new();
    GdkPixbuf * pixbuf= gdk_pixbuf_new_from_file("../client/images/search.png", FALSE);
    search_entry = gtk_entry_new();
    gtk_entry_set_has_frame(search_entry, FALSE);
    gtk_entry_set_icon_from_pixbuf(search_entry, GTK_ENTRY_ICON_PRIMARY, pixbuf);
    gtk_entry_set_text(search_entry, "Search...");
    gtk_table_attach_defaults(GTK_TABLE(table),search_entry, 2, 16, 2, 4);
//    search_friends();
    button_search = create_button("../client/images/search.png", NULL);
    gtk_table_attach_defaults(GTK_TABLE(table),button_search, 17, 19, 2, 4);
    g_signal_connect ( button_search, "clicked",
                       G_CALLBACK (search), NULL);
    gtk_button_set_relief(button_search, GTK_RELIEF_NONE);
    frame = information_frame();
    gtk_table_attach_defaults(GTK_TABLE(table),frame, 2, 18, 6, 18);
    update_widget_bg(add_friend_window,400, 400, "../client/images/bg/7.jpg");


    gtk_widget_show_all(add_friend_window);
    gtk_main();
    return add_friend_window;
}