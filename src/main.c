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
GtkImage	*image_login;
bool fullscreen;
char username[256];

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    fullscreen = false;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "glade/test_glade.glade", NULL);
    window = GTK_WINDOW(gtk_builder_get_object(builder, "main"));
    image = GTK_IMAGE(gtk_builder_get_object(builder, "splash_image"));
    image_login = GTK_IMAGE(gtk_builder_get_object(builder, "login_photo_display"));
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

void on_take_login_photo_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;


    printf("snap!!");

    system("python scripts/login_snap.py");

    gtk_image_set_from_file(image_login, "img/login.jpg");
    pixBuf = gtk_image_get_pixbuf(image_login);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 640, 480, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(image_login, pixScaled);
}

void on_submit_login_photo_clicked(){
    printf("submit!!");
    system("python scripts/login_verify.py");
    FILE * fp = fopen("/home/pi/Desktop/ohsnap/test.txt","r");
    if(fgets(username,sizeof(username),fp)){
    }
    fclose(fp);
    if(strcmp(username,"unrecognized")){
      gtk_notebook_set_current_page(notebook, 2);
    }
    else if(strcmp(username,"f")){}
    else{
      gtk_notebook_set_current_page(notebook, 2);
    }
    printf("%s",username);
}

void on_back_login_clicked(){
    gtk_notebook_set_current_page(notebook, 0);
}


void on_snap_clicked() {
    GtkImage	*image_taken;
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;
    char charbuf[256];

    image_taken = GTK_IMAGE(gtk_builder_get_object(builder, "taken_photo_display"));
    printf("take image\n");
    gtk_notebook_set_current_page(notebook, 3);

    sprintf(charbuf,"python scripts/snap.py %s","saywaht");
    system(charbuf);

    gtk_image_set_from_file(image_taken, "img/TRY.jpg");
    pixBuf = gtk_image_get_pixbuf(image_taken);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 640, 480, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(image_taken, pixScaled);
    gtk_widget_show(GTK_WIDGET(image_taken));
}

void on_browse_clicked(){
    

}

void on_login_clicked() {
    printf("login\n");
    gtk_notebook_set_current_page(notebook, 1);
    gtk_image_set_from_file(image_login, "img/flower.png");
}

void on_back_register_clicked() {
    printf("register back\n");
    gtk_notebook_set_current_page(notebook, 0);
}

void on_back_take_photo_clicked() {
    printf("take photo back\n");
    gtk_notebook_set_current_page(notebook, 1);
}

void on_signup_clicked() {
    printf("signup\n");
    gtk_notebook_set_current_page(notebook, 2);

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
