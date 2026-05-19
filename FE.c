#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "Sprite.h"
#include "WeaponLvl.h"
#include "Character.h"
#include "Class.h"
#include "wrenNative.h"
UnitClass classes[256];
static void gen_screen(GtkApplication *app){
}
static void activate(GtkApplication *app, gpointer user_data){
  GtkWidget *window;
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Fire Emblem Maker");
  gtk_window_set_default_size(GTK_WINDOW(window), 960, 640);
  // 4 screen pixels per game pixel, thus 240 by 160 pixels
  gtk_window_present(GTK_WINDOW(window));
}
int main(int argc, char **argv){
  GtkApplication *app;
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.loadModuleFn = &loadModule;
  config.bindForeignMethodFn = &bindForeignMethod;
  config.bindForeignClassFn = &bindForeignClass;
  int status;
  app = gtk_application_new("com.EmacsIsBetterThanVi.FireEmblemMaker", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}
