#ifndef L_APP_C
#define L_APP_C
#include <gtk/gtk.h>
#define MAX_DATA_USE 1024*1024*500
#define DATA_USAGE_APP_TYPE (data_usage_app_get_type ())
G_DECLARE_FINAL_TYPE (DataUsageApp, data_usage_app, DATA_USAGE, APP, GtkApplication)

DataUsageApp *data_usage_app_new(void);
void item_clicked_app(void);
void open_full_window(void);
int data_usage_app_update_usage(DataUsageApp *app);
void init_start_stats(DataUsageApp *app);
#endif