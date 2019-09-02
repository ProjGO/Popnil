#include <gtk/gtk.h>


void list()
{
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *table_user;
    GtkWidget *image_usericon;
    GtkWidget *label_username;
    GtkWidget *search_entry;
    GtkWidget *notebook;
    GtkWidget *page1;
    GtkWidget *notebook_image_friend;
    GtkWidget *page2;
    GtkWidget *notebook_image_group;

//    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),200,500);
    gtk_window_set_title(GTK_WINDOW(window),"Chat");
    gtk_container_set_border_width(GTK_CONTAINER(window),0);

    table = gtk_table_new(40, 16, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table),0);
    gtk_table_set_col_spacings(GTK_TABLE(table),1);
    gtk_container_add(GTK_CONTAINER(window),table);
//  g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);




    image_usericon = gtk_image_new_from_file("../client/images/friend_portrait.png");
    gtk_table_attach_defaults(GTK_TABLE(table), image_usericon, 1, 5, 1, 5);

    label_username = gtk_label_new("XDX");
    gtk_table_attach_defaults(GTK_TABLE(table),label_username, 5, 13, 1, 5);

    search_entry = gtk_search_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),search_entry, 0, 16, 6, 8);

    gtk_entry_set_text(search_entry, "Search...");


    notebook = gtk_notebook_new();
    gtk_table_attach_defaults(GTK_TABLE(table), notebook, 0, 16, 9, 37);
    notebook_image_friend = gtk_image_new_from_file("../client/images/friends_list.png");
    notebook_image_group = gtk_image_new_from_file("../client/images/group_list.png");

    page1 = gtk_hbox_new(FALSE, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, notebook_image_friend);

    page2 = gtk_hbox_new(FALSE, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, notebook_image_group);

    gtk_notebook_set_tab_reorderable(notebook, page1, TRUE);
    gtk_notebook_set_tab_reorderable(notebook, page2, TRUE);

    gtk_widget_show_all(window);
    gtk_main();

}