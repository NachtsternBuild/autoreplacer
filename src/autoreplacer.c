/*
* updater.c
*
* (C) Copyright 2025 AtlantisOS Project
* by @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* ./autoreplacer
*
* Notes:
* This are only the startup function for GTK4 and libadwaita
*/

#include <glib.h>
#include <gtk/gtk.h>
#include <adwaita.h>
#include "design.h"
#include "autoreplacer.h"

// define the local domian
const char *LOCALE_DOMAIN = "autoreplacer";
// define the default file filters
const char *DEFAULT_FILTER = "/etc/autoreplacer/filter.conf";

// main function
int main(int argc, char *argv[]) 
{
	g_autoptr(AdwApplication) app = NULL;

    app = adw_application_new("io.github.nachtsternbuild.autoreplacer", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate_autoreplacer), NULL);

    return g_application_run(G_APPLICATION (app), argc, argv);
}

