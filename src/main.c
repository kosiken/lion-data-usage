#include <stdio.h>
#include <gtk/gtk.h>

#include "datausageapp.h"
gint cb(gpointer data);
int
main (int argc, char *argv[])
{
  guint interval = 1000;
  DataUsageApp *a = data_usage_app_new ();
 
 
    gint l = g_timeout_add(interval, (GSourceFunc)data_usage_app_update_usage, a);


  return g_application_run (G_APPLICATION (a), argc, argv);
}

