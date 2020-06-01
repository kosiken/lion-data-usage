#ifndef WIN_C
#define WIN_C

#include <gtk/gtk.h>
#include "datausageapp.h"
#define DATA_USAGE_APP_WINDOW_TYPE (data_usage_app_window_get_type ())

G_DECLARE_FINAL_TYPE(DataUsageAppWindow,data_usage_app_window, DATA_USAGE, APP_WINDOW, GtkApplicationWindow)

DataUsageAppWindow * data_usage_app_window_new(DataUsageApp* app);
void data_usage_app_window_open(DataUsageAppWindow * appWindow, uint64_t values);
gint data_usage_app_window_update_wids(DataUsageAppWindow *win,  uint64_t *values);
void data_usage_app_window_set_app(DataUsageApp* app, DataUsageAppWindow *win);

#endif