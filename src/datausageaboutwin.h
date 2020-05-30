#ifndef ABOUT_WIN_C
#define ABOUT_WIN_C


#include <gtk/gtk.h>
#include "datausageapp.h"
#define DATA_USAGE_ABOUT_WINDOW_TYPE (data_usage_about_window_get_type ())

G_DECLARE_FINAL_TYPE(DataUsageAboutWindow,data_usage_about_window, DATA_USAGE, ABOUT_DIALOG, GtkAboutDialog)
DataUsageAboutWindow * data_usage_about_window_new(const gchar* app);
void data_usage_about_window_open(DataUsageAboutWindow * appWindow);

#endif