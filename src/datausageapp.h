#ifndef L_APP_C
#define L_APP_C
#include <gtk/gtk.h>

#define DATA_USAGE_APP_TYPE (data_usage_app_get_type ())
G_DECLARE_FINAL_TYPE (DataUsageApp, data_usage_app, DATA_USAGE, APP, GtkApplication)

DataUsageApp *data_usage_app_new(void);
void item_clicked_app(void);
#endif