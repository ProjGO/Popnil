//
// Created by xdx on 19-8-31.
//


#include <gtk/gtk.h>
void update_widget_bg(GtkWidget *widget, const gchar *img_file)
{
    GtkStyle *style;
    GdkPixbuf *pixbuf;
    GdkPixmap *pixmap;
    gint width, height;

    pixbuf = gdk_pixbuf_new_from_file(img_file, NULL);
    width = gdk_pixbuf_get_width(pixbuf);
    height = gdk_pixbuf_get_height(pixbuf);
    pixmap = gdk_pixmap_new(NULL, width, height, 24);
    gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);
    style = gtk_style_copy(GTK_WIDGET (widget)->style);

    if (style->bg_pixmap[GTK_STATE_NORMAL])
        g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);

    style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);
    style->bg_pixmap[GTK_STATE_ACTIVE] = g_object_ref(pixmap);
    style->bg_pixmap[GTK_STATE_PRELIGHT] = g_object_ref(pixmap);
    style->bg_pixmap[GTK_STATE_SELECTED] = g_object_ref(pixmap);
    style->bg_pixmap[GTK_STATE_INSENSITIVE] = g_object_ref(pixmap);
    gtk_widget_set_style(GTK_WIDGET (widget), style);
    g_object_unref(style);

}
GtkWidget* set_background()
{
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"设置");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    update_widget_bg(window, "../images/sign_success.jpg");
//    GtkWidget *button;
//    button = gtk_button_new();
//
//    gtk_container_add(GTK_WINDOW(window), button);
    gtk_widget_show_all(window);
    return window;
}