#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

GtkBuilder	*builder;
GtkWindow	*window;
GtkNotebook 	*notebook;
GtkImage	*image;
GtkImage	*snap_image;
GtkImage	*filtered_snap_image;
GtkImage	*filter_dynamic_snap_image;
GtkImage	*d0;
GtkImage	*d1;
GtkImage	*d2;
GtkImage	*d3;
GtkImage	*d4;
GtkImage	*d5;
bool fullscreen;
bool logged;
bool filtered;
char username[256];
char filter_file_name[256];
int count;
GtkStatusbar *upload_status;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    fullscreen = true;
    count = 0;
    logged = false;
    filtered = false;
    strcpy(filter_file_name,"img/snap.jpg");

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "glade/working.glade", NULL);
    window = GTK_WINDOW(gtk_builder_get_object(builder, "main"));
    image = GTK_IMAGE(gtk_builder_get_object(builder, "splash_image"));
    snap_image = GTK_IMAGE(gtk_builder_get_object(builder, "taken_photo_display"));
    filtered_snap_image = GTK_IMAGE(gtk_builder_get_object(builder, "taken_photo_display1"));
    filter_dynamic_snap_image = GTK_IMAGE(gtk_builder_get_object(builder, "taken_photo_display2"));
    gtk_window_fullscreen(window);
    d0 = GTK_IMAGE(gtk_builder_get_object(builder, "fimg0"));
    d1 = GTK_IMAGE(gtk_builder_get_object(builder, "fimg1"));
    d2 = GTK_IMAGE(gtk_builder_get_object(builder, "fimg2"));
    d3 = GTK_IMAGE(gtk_builder_get_object(builder, "fimg3"));
    d4 = GTK_IMAGE(gtk_builder_get_object(builder, "fimg4"));
    d5 = GTK_IMAGE(gtk_builder_get_object(builder, "fimg5"));
    upload_status = GTK_STATUSBAR(gtk_builder_get_object(builder, "upload_status"));
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

void on_login_clicked(){
    gtk_notebook_set_current_page(notebook, 5);
}

void on_button_submit_login_clicked(){
}


void on_snap_photo_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    printf("snap!!");
    system("python scripts/state1.py");
    system("python scripts/login_snap.py");

    gtk_image_set_from_file(snap_image, "img/snap.jpg");
    pixBuf = gtk_image_get_pixbuf(snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(snap_image, pixScaled);
    gtk_notebook_set_current_page(notebook, 1);

    GtkStatusbar *reg_status;
    reg_status = GTK_STATUSBAR(gtk_builder_get_object(builder, "users_detected_status"));

    system("python scripts/login_verify.py");
    FILE * fp = fopen("/home/pi/Desktop/ohsnap/output.txt","r");
    fgets(username,sizeof(username),fp);
    puts(username);
    fclose(fp);

    if(strcmp(username,"Unrecognized")==0){
      gtk_statusbar_push(reg_status, 0, "You are not recognized, do you still want to proceed?");
    }
    else if(strcmp(username,"f")==0){
      gtk_statusbar_push(reg_status, 0, "Server Offline");
    }
    else{
      char a[256] = "Welcome, ";
      strcat(a,username);
      char c[] = ". Do you like this photo?";
      strcat(a,c);
      gtk_statusbar_push(reg_status, 0, a);
      logged = true;
    }

}

void on_back_take_photo_clicked(){
    gtk_notebook_set_current_page(notebook, 0);
    logged = false;
}

void on_do_you_like_yes_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;
    gtk_image_set_from_file(filtered_snap_image, "img/snap.jpg");
    pixBuf = gtk_image_get_pixbuf(filtered_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filtered_snap_image, pixScaled);
    gtk_notebook_set_current_page(notebook, 2);
}

void on_do_you_like_no_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    system("python scripts/login_snap.py");

    gtk_image_set_from_file(snap_image, "img/snap.jpg");
    pixBuf = gtk_image_get_pixbuf(snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(snap_image, pixScaled);
    gtk_notebook_set_current_page(notebook, 1); 
    if(!logged){
	GtkStatusbar *reg_status;
    	reg_status = GTK_STATUSBAR(gtk_builder_get_object(builder, "users_detected_status"));

    	system("python scripts/login_verify.py");
   	FILE * fp = fopen("/home/pi/Desktop/ohsnap/output.txt","rw");
    	fgets(username,sizeof(username),fp);
    	fclose(fp);
	printf(username);
    	if(strcmp(username,"Unrecognized")==0){
     	  gtk_statusbar_push(reg_status, 0, "You are not recognized, do you still want to proceed?");
          
    	}
    	else if(strcmp(username,"f")==0){
      	  gtk_statusbar_push(reg_status, 0, "Server Offline");
    	}
    	else{
          char a[256] = "Welcome, ";
          strcat(a,username);
          char c[] = ". Do you like this photo?";
          strcat(a,c);
      	  gtk_statusbar_push(reg_status, 0, a);
      	  logged = true;
    	}
    }
}

void on_back_login_clicked(){
    gtk_notebook_set_current_page(notebook, 0);
}

void on_back_take_photo1_clicked(){
    gtk_statusbar_push(upload_status, 0, "");
    fullscreen = false;
    count = 0;
    logged = false;
    filtered = false;
    strcpy(filter_file_name,"img/snap.jpg");
    gtk_notebook_set_current_page(notebook, 0);
}

void on_do_upload_clicked(){
    if(!filtered){
    	char command[256] = "python scripts/upload.py ";
    	strcat(command,filter_file_name);
    	system(command);
    }
    char command[256] = "python scripts/uploadins.py ";
    strcat(command,filter_file_name);
    system(command);

    gtk_statusbar_push(upload_status, 0, "uploaded successfully!");
}

void on_do_filter_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    gtk_image_set_from_file(filter_dynamic_snap_image, filter_file_name);
    pixBuf = gtk_image_get_pixbuf(filter_dynamic_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filter_dynamic_snap_image, pixScaled);

    gtk_image_set_from_file(d0, "img/d0.jpg");
    pixBuf = gtk_image_get_pixbuf(d0);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 100, 75, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(d0, pixScaled);

    gtk_image_set_from_file(d1, "img/d1.jpg");
    pixBuf = gtk_image_get_pixbuf(d1);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 100, 75, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(d1, pixScaled);

    gtk_image_set_from_file(d2, "img/d2.jpg");
    pixBuf = gtk_image_get_pixbuf(d2);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 100, 75, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(d2, pixScaled);

    gtk_image_set_from_file(d3, "img/d3.jpg");
    pixBuf = gtk_image_get_pixbuf(d3);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 100, 75, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(d3, pixScaled);

    gtk_image_set_from_file(d4, "img/d4.jpg");
    pixBuf = gtk_image_get_pixbuf(d4);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 100, 75, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(d4, pixScaled);

    gtk_image_set_from_file(d5, "img/d5.jpg");
    pixBuf = gtk_image_get_pixbuf(d5);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 100, 75, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(d5, pixScaled);
    filtered = true;
    system("python scripts/state2.py");
    gtk_notebook_set_current_page(notebook, 3);
}

void on_filter0_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    gtk_image_set_from_file(filter_dynamic_snap_image, "img/snap.jpg");
    pixBuf = gtk_image_get_pixbuf(filter_dynamic_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filter_dynamic_snap_image, pixScaled);
    strcpy(filter_file_name,"img/snap.jpg");
}
void on_filter1_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    system("python scripts/apply_filter.py 1");

    gtk_image_set_from_file(filter_dynamic_snap_image, "img/snap1.jpg");
    pixBuf = gtk_image_get_pixbuf(filter_dynamic_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filter_dynamic_snap_image, pixScaled);
    strcpy(filter_file_name,"img/snap1.jpg");
}
void on_filter2_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    system("python scripts/apply_filter.py 2");

    gtk_image_set_from_file(filter_dynamic_snap_image, "img/snap2.jpg");
    pixBuf = gtk_image_get_pixbuf(filter_dynamic_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filter_dynamic_snap_image, pixScaled);
    strcpy(filter_file_name,"img/snap2.jpg");
}
void on_filter3_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    system("python scripts/apply_filter.py 3");

    gtk_image_set_from_file(filter_dynamic_snap_image, "img/snap3.jpg");
    pixBuf = gtk_image_get_pixbuf(filter_dynamic_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filter_dynamic_snap_image, pixScaled);
    strcpy(filter_file_name,"img/snap3.jpg");
}
void on_filter4_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    system("python scripts/apply_filter.py 4");

    gtk_image_set_from_file(filter_dynamic_snap_image, "img/snap4.jpg");
    pixBuf = gtk_image_get_pixbuf(filter_dynamic_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filter_dynamic_snap_image, pixScaled);
    strcpy(filter_file_name,"img/snap4.jpg");
}
void on_filter5_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    system("python scripts/apply_filter.py 5");

    gtk_image_set_from_file(filter_dynamic_snap_image, "img/snap5.jpg");
    pixBuf = gtk_image_get_pixbuf(filter_dynamic_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filter_dynamic_snap_image, pixScaled);
    strcpy(filter_file_name,"img/snap5.jpg");
}

void on_done_clicked(){
    GdkPixbuf 	*pixBuf;
    GdkPixbuf	*pixScaled;

    gtk_image_set_from_file(filtered_snap_image, filter_file_name);
    pixBuf = gtk_image_get_pixbuf(filtered_snap_image);
    pixScaled = gdk_pixbuf_scale_simple(pixBuf, 480, 320, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(filtered_snap_image, pixScaled);

    char command[256] = "python scripts/upload.py ";
    strcat(command,filter_file_name);
    system(command);
    gtk_statusbar_push(upload_status, 0, "");
    gtk_notebook_set_current_page(notebook, 2);
}

void on_back_register_clicked() {
    printf("register back\n");
    gtk_notebook_set_current_page(notebook, 0);
}


void on_signup_clicked() {
    printf("signup\n");
    gtk_notebook_set_current_page(notebook, 4);

}

void on_fullscreen_clicked() {
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
