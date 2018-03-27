#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

GtkBuilder	*builder;
GtkWindow	*window;
GtkNotebook 	*notebook;
GtkImage	*image;
bool fullscreen;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    fullscreen = false;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "glade/test_glade.glade", NULL);
    window = GTK_WINDOW(gtk_builder_get_object(builder, "main"));
    image = GTK_IMAGE(gtk_builder_get_object(builder, "splash_image"));
    notebook = GTK_NOTEBOOK(gtk_builder_get_object(builder, "notebook_main"));
    gtk_image_set_from_file(image, "img/photobooth.jpg");

    gtk_builder_connect_signals(builder, NULL);

//    g_object_unref(builder); //DON'T DISABLE

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
    gtk_notebook_set_current_page(notebook, 1);
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

void on_fullscreen_clicked() {
    printf("fullscreen\n");
    if(!fullscreen) {
    	gtk_window_fullscreen(window);
	fullscreen = true;
	return;
    } else {
	gtk_window_unfullscreen(window);
	fullscreen = false;
	return;
    }
}

void on_button_submit_clicked() {
    GtkEntry *name;
    const gchar *name_text;
    name = GTK_ENTRY(gtk_builder_get_object(builder, "name_field"));
    name_text = gtk_entry_get_text(name);
    printf("Name: '%s'\n", name_text);

    GtkEntry *email;
    const gchar *email_text;
    email = GTK_ENTRY(gtk_builder_get_object(builder, "email_field"));
    email_text = gtk_entry_get_text(email);
    printf("email: '%s'\n", email_text);

    GtkEntry *instagram;
    const gchar *instagram_text;
    instagram = GTK_ENTRY(gtk_builder_get_object(builder, "instagram_field"));
    instagram_text = gtk_entry_get_text(instagram);
    printf("instagram: '%s'\n", instagram_text);

    GtkEntry *twitter;
    const gchar *twitter_text;
    twitter = GTK_ENTRY(gtk_builder_get_object(builder, "twitter_field"));
    twitter_text = gtk_entry_get_text(twitter);
    printf("twitter: '%s'\n", twitter_text);

    GtkStatusbar *reg_status;
    reg_status = GTK_STATUSBAR(gtk_builder_get_object(builder, "register_status"));


// Put code for sending to server here
    gtk_statusbar_push(reg_status, 0, "Successfully Registered!");
}
