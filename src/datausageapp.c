#include <gtk/gtk.h>

#include "datausageapp.h"
#include "datausagewin.h"
#include "dataUsage.h"

struct _DataUsageApp
{
    GtkApplication parent;
};

G_DEFINE_TYPE (DataUsageApp, data_usage_app,GTK_TYPE_APPLICATION)

static void
data_usage_app_init (DataUsageApp *app)
{
  
}

// s

static void data_usage_app_open(GApplication *app, GFile        **files,
                  gint           n_files,
                  const gchar   *hint) {
    GList *windows;
    DataUsageAppWindow *win;
    int i;
    windows = gtk_application_get_windows(GTK_APPLICATION(app));
    if(windows)
        win = DATA_USAGE_APP_WINDOW(windows->data);
    else 
        win = data_usage_app_window_new(DATA_USAGE_APP(app));
    data_usage_app_window_open(win);
    gtk_window_present(GTK_WINDOW(win));
}

static void
data_usage_app_activate (GApplication *app)
{
 DataUsageAppWindow  *win;

  win = data_usage_app_window_new (DATA_USAGE_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void
data_usage_app_class_init (DataUsageAppClass *class)
{
  G_APPLICATION_CLASS (class)->activate = data_usage_app_activate;
  G_APPLICATION_CLASS (class)->open = data_usage_app_open;
}


DataUsageApp *data_usage_app_new(void) 
{
    return g_object_new(DATA_USAGE_APP_TYPE, "application-id",
    "com.krc.datausageapp", "flags",
    G_APPLICATION_HANDLES_OPEN, NULL);
    
};
void item_clicked() {
    
}