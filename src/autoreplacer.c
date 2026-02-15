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

#include "autoreplacer.h"

// define option for debug mode
bool debug_lang = false;


// define the local domain
const char *LOCALE_DOMAIN = "autoreplacer";
// define the filter file
const char *DEFAULT_FILTER = "/etc/autoreplacer/filter.conf";
// define the local dir
const char *LOCALEDIR_PATH = "local/";

// define about infos
const char *app_icon = "sweet_unix"; // use the name, that safed in the desktop file
const char *app_name = "autoreplacer";
const char *developer_name = "NachtsternBuild";
const char *version = "0.1.dev";
const char *release_notes_version = "0.1";
const char *release_notes = "\
<p>\
  This release adds this features:\
</p>\
<ul>\
  <li>Switch UI to ATL UIBase.</li>\
  <li>Rework project structure.</li>\
  <li>Add support for flatpak.</li>\
  <li>Improve support for libadwaita.</li>\
  <li>Bug fixes and performance improvements.</li>\
  <li>Translation updates.</li>\
</ul>\
  ";
const char *comments = "Little program to replace symbols.";
const char *website = "https://github.com/NachtsternBuild/autoreplacer";
const char *issue_url = "https://github.com/NachtsternBuild/autoreplacer/issues";
const char *support_url = "https://github.com/NachtsternBuild/autoreplacer";
const char *copyright = "© 2026 NachtsternBuild";
const char *developers[] = {
	"NachtsternBuild",
	NULL
};
const char *artists[] = {
	"GNOME Design Team",
	"NachtsternBuild",
	NULL
};
const char *documentation_url = "https://github.com/NachtsternBuild/autoreplacer";
const char *font_usage = "This application uses font data from <a href='https://example.org'>somewhere</a>.";
const char *special_thanks[] = {
	"Tux",
	NULL
};

// main function
int main(int argc, char *argv[]) 
{
	g_autoptr(AdwApplication) app = NULL;

    app = adw_application_new("io.github.nachtsternbuild.autoreplacer", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate_autoreplacer), NULL);

    return g_application_run(G_APPLICATION (app), argc, argv);   
}
