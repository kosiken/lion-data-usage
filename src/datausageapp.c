#include <gtk/gtk.h>

#include "datausageapp.h"
#include "datausagewin.h"
#include "dataUsage.h"
#include "datausageaboutwin.h"
struct _DataUsageApp
{
    GtkApplication parent;
};
typedef struct _DataUsageAppPrivate DataUsageAppPrivate;
struct _DataUsageAppPrivate
{
    dataUsage *mdataUsage;
    u_int64_t max_usage;
    gint notified;
    GtkWidget *app_max;
};
// G_DEFINE_TYPE (DataUsageApp, data_usage_app,GTK_TYPE_APPLICATION)
G_DEFINE_TYPE_WITH_PRIVATE(DataUsageApp, data_usage_app, GTK_TYPE_APPLICATION);
void set_max(uint64_t max, DataUsageAppPrivate *priv);
static void
data_usage_app_init(DataUsageApp *app)
{

    DataUsageAppPrivate *priv;
// GApplication *application = g_application_new("com.krc.datausageapp", G_APPLICATION_NON_UNIQUE );
// gboolean g = g_application_register(application, NULL, NULL);
// g_print("%d", g);
    priv = data_usage_app_get_instance_private(app);
    uint64_t m = MAX_DATA_USE;
    set_max(m, priv);
    priv->mdataUsage = (dataUsage *)malloc(sizeof(dataUsage));
    get_default_interface(&(priv->mdataUsage->ifa_name));
}

// s

static void data_usage_app_open(GApplication *app, GFile **files,
                                gint n_files,
                                const gchar *hint)
{
    GList *windows;
    DataUsageAppWindow *win;
    int i;
    windows = gtk_application_get_windows(GTK_APPLICATION(app));
    if (windows)
        win = DATA_USAGE_APP_WINDOW(windows->data);
    else
    {
    }
    win = data_usage_app_window_new(DATA_USAGE_APP(app));

    exit(0);
    gtk_window_present(GTK_WINDOW(win));
}

static void
data_usage_app_activate(GApplication *app)
{
    DataUsageAppWindow *win;

    win = data_usage_app_window_new(DATA_USAGE_APP(app));

    init_start_stats(DATA_USAGE_APP(app));
    data_usage_app_window_set_app((DataUsageApp *)app, win);

    data_usage_app_window_open(win, (uint64_t)MAX_DATA_USE);
    gtk_window_present(GTK_WINDOW(win));
}

static void
data_usage_app_class_init(DataUsageAppClass *class)
{

    G_APPLICATION_CLASS(class)->activate = data_usage_app_activate;
    G_APPLICATION_CLASS(class)->open = data_usage_app_open;
    
}

DataUsageApp *data_usage_app_new(void)
{
    return g_object_new(DATA_USAGE_APP_TYPE, "application-id",
                        "com.krc.datausageapp", "flags",
                        G_APPLICATION_HANDLES_OPEN, NULL);
};
void item_clicked_app()
{
    GtkBuilder *builder;
    DataUsageAboutWindow *window;
    const gchar *title = "lion";
    window = data_usage_about_window_new(title);
    gtk_window_present(GTK_WINDOW(window));
}
void open_full_window()
{
    GtkBuilder *builder;
    builder = gtk_builder_new();
    // GError *err = g_error_new()
    gtk_builder_add_from_resource(builder, "/com/krc/datausageapp/full_stats.ui", NULL);
    GtkWindow *window;
    window = GTK_WINDOW(gtk_builder_get_object(builder, "full_stats"));
    GtkLabel *sent;
    GtkLabel *recieved;
    dataUsage *d = (dataUsage *)malloc(sizeof(dataUsage));
    if (get_default_interface(&(d->ifa_name)) == -1)
    {
        printf("%s", "error");
        return;
    };

    mbs_poll_interfaces(d, &(d->snapshot));
    char buffer[10];
    sent = GTK_LABEL(gtk_builder_get_object(builder, "sent_full"));

    recieved = GTK_LABEL(gtk_builder_get_object(builder, "recieved_full"));
    to_human_readable(d->snapshot.sent, buffer);
    gtk_label_set_text(sent, buffer);
    to_human_readable(d->snapshot.recieved, buffer);
    gtk_label_set_text(recieved, buffer);
    gtk_window_resize(window, 600, 400);
    gtk_widget_show((GtkWidget *)window);
}

int data_usage_app_update_usage(DataUsageApp *app)
{
    GList *windows;
    DataUsageAppWindow *win;
    DataUsageAppPrivate *priv;
    priv = data_usage_app_get_instance_private(app);

    windows = gtk_application_get_windows(GTK_APPLICATION(app));
    if (windows)
        win = DATA_USAGE_APP_WINDOW(windows->data);
    else
        return 0;
    if (mbs_poll_interfaces(priv->mdataUsage, &(priv->mdataUsage->snapshot)) == -1)
    {
        g_printerr("%s", "err");
        exit(0);
    }
    uint64_t *values = malloc(sizeof(uint64_t) * 3);

    *values = priv->mdataUsage->snapshot.recieved - priv->mdataUsage->used.recieved;
    *(values + 1) = priv->mdataUsage->snapshot.sent - priv->mdataUsage->used.sent;
    *(values + 2) = priv->max_usage;
   gint notify = data_usage_app_window_update_wids(win, values);
 if(priv->notified ==1) return 1;

   if(notify == -1){
       notify_end(app,*values);
       priv->notified=1;
   }

    return 1;
}

void notify_end(DataUsageApp *app, uint64_t usage)
{
    GNotification *notification;
    GFile *file;
    GFileIcon *icon;
    char buffer[256], buf[10];
   to_human_readable(usage, buf);
   sprintf(buffer, "You have used %s of amount data", buf);
   notification = g_notification_new ("Data usage warning");
   g_notification_set_body(notification, buffer);
    file = g_file_new_for_path("leo.png");
    icon = (GFileIcon*)g_file_icon_new (file);
    g_notification_set_icon (notification, G_ICON (icon));
    g_object_unref (icon);
g_object_unref (file);

//GApplication *application = g_application_new("com.krc.datausageapp", G_APPLICATION_NON_UNIQUE );
gboolean g = g_application_get_is_registered((GApplication *)app);
if(g) {
g_application_send_notification ((GApplication *)app, "data-usage-warning", notification);
}

//
g_object_unref (notification);

};

void set_max(uint64_t max, DataUsageAppPrivate *priv)
{
    priv->max_usage = max;
}
void init_start_stats(DataUsageApp *app)
{
    DataUsageAppPrivate *priv;
    priv = data_usage_app_get_instance_private(app);
    get_default_interface(&(priv->mdataUsage->ifa_name));
    mbs_poll_interfaces(priv->mdataUsage, &priv->mdataUsage->used);
}

void update_max(DataUsageApp *app,gpointer win, uint64_t max){
      DataUsageAppPrivate *priv;
    priv = data_usage_app_get_instance_private(app);
   set_max(max, priv);
DataUsageAppWindow*window = (DataUsageAppWindow *)win;
data_usage_app_window_open(win, priv->max_usage);

};