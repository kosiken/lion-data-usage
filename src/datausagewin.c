#include <stdio.h>
#include <gtk/gtk.h>
#include "datausageapp.h"
#include "datausagewin.h"

struct _DataUsageAppWindow
{
    GtkApplicationWindow parent;
};

typedef struct _DataUsageAppWindowPrivate DataUsageAppWindowPrivate;
struct _DataUsageAppWindowPrivate
{
    GtkWidget *content_box;
    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *sent, *recieved;
    GtkWidget *grid;
    
};

DataUsageAppWindow *data_usage_app_window_new(DataUsageApp *app)
{
    return g_object_new(DATA_USAGE_APP_WINDOW_TYPE, "application", app, NULL);
};
G_DEFINE_TYPE_WITH_PRIVATE(DataUsageAppWindow, data_usage_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void data_usage_app_window_init(DataUsageAppWindow *win)
{

    gtk_widget_init_template(GTK_WIDGET(win));
    DataUsageAppWindowPrivate *priv;
    gchar *basename;
    GtkWidget *sent, *grid, *recieved, *label, *label2;
 g_signal_connect(G_OBJECT(btn), "clicked", 
      G_CALLBACK(button_clicked), NULL);
};

static void data_usage_app_window_class_init(DataUsageAppWindowClass *class)
{
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class),
                                                "/com/krc/datausageapp/window.ui");

    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), DataUsageAppWindow, content_box);
}

void data_usage_app_window_open(DataUsageAppWindow *appWindow)
{
    DataUsageAppWindowPrivate *priv;
    gchar *basename;

    GtkLabel *sentlabel, *recievedlabel;
    GtkWidget *sent;
    priv = data_usage_app_window_get_instance_private(appWindow);

    sent = gtk_label_new("Recieved");
    //  gtk_container_add (GTK_CONTAINER (a), sent);
    exit(0);
    gtk_widget_show(sent);
}