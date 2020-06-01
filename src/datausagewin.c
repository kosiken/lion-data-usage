#include <stdio.h>
#include <gtk/gtk.h>
#include "datausageapp.h"
#include "datausagewin.h"
#include "dataUsage.h"


struct _DataUsageAppWindow
{
    GtkApplicationWindow parent;
};

typedef struct _DataUsageAppWindowPrivate DataUsageAppWindowPrivate;
struct _DataUsageAppWindowPrivate
{
    GtkWidget *content_box;
    GtkWidget *level;
    GtkWidget *sent, *recieved;
    GtkWidget *balance;
};
static void item_clicked(GtkButton *button, gpointer user_data)
{
    item_clicked_app();

}


static void full_clicked(GtkMenuItem *item, gpointer user_data) {
    open_full_window();

}
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
  
};

static void data_usage_app_window_class_init(DataUsageAppWindowClass *class)
{
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class),
                                                "/com/krc/datausageapp/window.ui");
    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(class), item_clicked);
    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(class),full_clicked);
   gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), DataUsageAppWindow, balance);
gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), DataUsageAppWindow, recieved);
gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), DataUsageAppWindow, sent);
}

void data_usage_app_window_open(DataUsageAppWindow *appWindow, uint64_t max)
{
    DataUsageAppWindowPrivate *priv;
    char buffer[10];
    to_human_readable(max, buffer);
    priv = data_usage_app_window_get_instance_private(appWindow);
     gtk_label_set_text((GtkLabel*)priv->balance, buffer);

  
}
void data_usage_app_window_update_wids(DataUsageAppWindow *win,  uint64_t *values){
    DataUsageAppWindowPrivate *priv;
    priv = data_usage_app_window_get_instance_private(win);
    char buffer[10];
    to_human_readable(*values, buffer);

    gtk_label_set_text((GtkLabel*)priv->sent, buffer);
    to_human_readable(*(values+1), buffer);
    gtk_label_set_text((GtkLabel*)priv->recieved, buffer);
}

