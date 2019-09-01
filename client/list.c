#include <gtk/gtk.h>


void list()
{
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *image_usericon;
    GtkWidget *label_username;

//    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),200,500);
    gtk_window_set_title(GTK_WINDOW(window),"Chat");
    gtk_container_set_border_width(GTK_CONTAINER(window),0);

    table = gtk_table_new(10, 4, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(window),table);
    g_signal_connect(GTK_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    image_usericon = gtk_image_new_from_file("../client/images/friend_portrait.png");
    gtk_table_attach_defaults(GTK_TABLE(table), image_usericon, 0, 1, 0, 1);

    label_username = gtk_label_new("XDX");
    gtk_table_attach_defaults(GTK_TABLE(table),label_username, 1, 3, 0, 1);


    gtk_widget_show_all(window);
    gtk_main();

}