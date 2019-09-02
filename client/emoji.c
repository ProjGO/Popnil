//
// Created by hsx on 2019/9/2.
//

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>

extern GtkTextBuffer *buffer;



typedef struct _filename_textView
{
    char *filename;
    GtkTextBuffer *buffer1;  //input
    GtkTextBuffer *buffer2;

}filename_textView;

//extern GtkTextBuffer *input_buffer;
//extern GtkTextBuffer *buffer;
//gchar buf[MAX_LEN];




GtkWidget *icon;

void picButton_callback( GtkWidget *button,filename_textView *filename_textViewAll )
{
    GtkTextIter end;
    GdkPixbuf *pixbuf;
    //filename_textViewAll->textViewAll->message = filename_textViewAll->filename;
    gtk_text_buffer_get_end_iter(buffer,&end);
    pixbuf = gdk_pixbuf_new_from_file(filename_textViewAll->filename,NULL);
    g_print ("%s was pressed\n", (char *)filename_textViewAll->filename);
    gtk_text_buffer_insert_pixbuf(buffer,&end,pixbuf);
    gtk_widget_destroy(icon);
}



GtkWidget *face_button( gchar *filename,GtkTextBuffer *input_buffer1)
//GtkWidget *face_button( gchar *filename,filename_textView *filename_textViewAll)
{
    GtkWidget *image;
    GtkWidget *button;

    filename_textView *filename_textViewAll= (filename_textView *)malloc(sizeof(filename_textView));

    filename_textViewAll->buffer1 = input_buffer1;
    filename_textViewAll->filename = filename;
    button = gtk_button_new ();
    image = gtk_image_new_from_file (filename);

    g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK (picButton_callback), filename_textViewAll);

    gtk_container_add (GTK_CONTAINER (button), image);
    gtk_container_set_border_width (GTK_CONTAINER (button), 0);
    return button;

}


GtkWidget *create_bbox(GtkTextBuffer *input_buffer1 )
{
    GtkWidget *vbox;
    GtkWidget *bbox;
    GtkWidget *button;
    vbox = gtk_vbox_new (FALSE, 0);
/////////
    bbox = gtk_hbox_new (FALSE, 0);

    button = face_button("../client/emoji/1.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/2.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/3.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/4.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/5.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/6.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/7.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/8.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/9.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/10.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    gtk_container_add (GTK_CONTAINER (vbox), bbox);
/////////

    bbox = gtk_hbox_new (FALSE, 0);
    button = face_button("../client/emoji/11.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/12.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/13.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/14.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/15.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/16.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/17.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/18.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/19.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/20.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    gtk_container_add (GTK_CONTAINER (vbox), bbox);
////////
    bbox = gtk_hbox_new (FALSE, 0);
    button = face_button("../client/emoji/21.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/22.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/23.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/24.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/25.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/26.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/27.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/28.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/29.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/30.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    gtk_container_add (GTK_CONTAINER (vbox), bbox);
////////
    bbox = gtk_hbox_new (FALSE, 0);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/31.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/32.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/33.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/34.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/35.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/36.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/37.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/38.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/39.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/40.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    gtk_container_add (GTK_CONTAINER (vbox), bbox);
////////
    bbox = gtk_hbox_new (FALSE, 0);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/41.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/42.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/43.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/44.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/45.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/46.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/47.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/48.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/49.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
    button = face_button("../client/emoji/50.gif",input_buffer1);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);


    gtk_container_add (GTK_CONTAINER (vbox), bbox);
    return vbox;
}





