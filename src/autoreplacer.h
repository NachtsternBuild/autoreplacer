/*
* autoreplacer.h
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* #include "autoreplacer.h"
*/

#ifndef AUTOREPLACER_H
#define AUTOREPLACER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include <libintl.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <locale.h>
#include "helper.h"
#include "language.h"
#include "design.h"

// define widget size
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// global widget for the UI
extern GtkWidget *status_label;
extern GtkWidget *progress_bar;
extern GtkWidget *check_button;
extern GtkWidget *download_button;
extern GtkWidget *install_button;
extern GtkWidget *full_button;

// function that run a special flag to the updater.sh
void run_to_replacer(const char *flag1, const char *flag2, const char *flag3);

// start the main UI of the updater
void activate_autoreplacer(GtkApplication *app, gpointer user_data);

#endif // AUTOREPLACER_H
