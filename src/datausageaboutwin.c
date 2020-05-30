#include <stdio.h>
#include <gtk/gtk.h>
#include "datausageapp.h"
#include "datausageaboutwin.h"

struct _DataUsageAboutWindow
{
    GtkAboutDialog parent;
};

DataUsageAboutWindow *data_usage_about_window_new(const gchar *app)
{
    return g_object_new(DATA_USAGE_ABOUT_WINDOW_TYPE, "title", app, NULL);
};
G_DEFINE_TYPE(DataUsageAboutWindow, data_usage_about_window, GTK_TYPE_ABOUT_DIALOG);

static void data_usage_about_window_class_init(DataUsageAboutWindowClass* class) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class),
                                                "/com/krc/datausageapp/about.ui");
}

static void data_usage_about_window_init(DataUsageAboutWindow *win) {
    gtk_widget_init_template(GTK_WIDGET(win));
}