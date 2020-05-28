#include <stdio.h>
#include <gtk/gtk.h>

#include "datausageapp.h"

int
main (int argc, char *argv[])
{
 // printf("%s", "lion");
  return g_application_run (G_APPLICATION (data_usage_app_new ()), argc, argv);
}