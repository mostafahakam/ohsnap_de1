#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

GtkBuilder	*builder;
GtkWindow	*window;
GtkNotebook 	*notebook;
GtkImage	*image;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "glade/test_glade.glade", NULL);
    window = GTK_WINDOW(gtk_builder_get_object(builder, "main"));
    image = GTK_IMAGE(gtk_builder_get_object(builder, "splash_image"));
    notebook = GTK_NOTEBOOK(gtk_builder_get_object(builder, "notebook_main"));
    gtk_image_set_from_file(image, "img/photobooth.jpg");

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(GTK_WIDGET(window));
    gtk_widget_show(GTK_WIDGET(image));
    gtk_main();

    return 0;
}

// called when window is closed
void on_main_window_destroy() {
    gtk_main_quit();
}


void on_take_clicked() {
    printf("take image\n");
}

void on_register_clicked() {
    printf("register\n");
    gtk_notebook_set_current_page(notebook, 1);
}

void on_back_register_clicked() {
    printf("register back\n");
    gtk_notebook_set_current_page(notebook, 0);
}


void on_browse_click() {
    printf("browse\n");

}

void on_button_submit_clicked() {
    GtkEntry *name;
//    GtkEntry *email;
//    GtkEntry *instagram;
//    GtkEntry *twitter;
    gchar *name_text;
    name = GTK_ENTRY(gtk_builder_get_object(builder, "name_field"));
    name_text = gtk_entry_get_text(name);

    printf("Name: '%s'\n", name_text);
}
