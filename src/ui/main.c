/**
* main.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "autoreplacer.h"

// for the main window
GtkWidget *main_window = NULL;
GtkWidget *radio_default = NULL;
GtkWidget *radio_markdown = NULL;
GtkWidget *radio_latex = NULL;
GtkWidget *radio_emacs = NULL;

// define the default config file
static const char *selected_config = "/etc/autoreplacer/default.conf";
static const char *default_file = "/var/default.txt";

// set the active button
static void on_config_toggled(GtkToggleButton *button, gpointer user_data)
 {
    if (gtk_toggle_button_get_active(button)) 
    {
        selected_config = (const char *)user_data;
        LOGD("Selected config: %s\n", selected_config);
    }
}

static void set_file(const char *filename) 
{
	LOGI("Selected file: %s with config %s\n", filename, selected_config);
	default_file = (const char *)filename;
	LOGD("Selected config: %s\n", default_file);
	
}

void run_replacer(gpointer user_data) 
{
	char new_name[512];
	snprintf(new_name, sizeof(new_name), "%s.replaced", default_file);
	if (replacer(selected_config, default_file, new_name) == 0) 
	{
        LOGI("Processing complete. Result in %s", new_name);
    } 
    
    else 
    {
        perror("Error with processing");
        exit(1);
    }
}

// selecte files
void on_file_selected(const char *filename) 
{
    LOGI("Selected file: %s with config %s\n", filename, selected_config);
	set_file(filename);
	
	show_spinner_dialog_function(main_window, _("Replacing elements"), _("Please wait..."), run_replacer, NULL);
}

// function that show the fastboot-assistant window
void activate_autoreplacer(GtkApplication* app, gpointer user_data) 
{
    // start logging
    // 0 → manual logging
    // 1 → syslog
    set_logging_mode(1);
    
    // apply language
    init_language();
    
    // use the advanced custom css provider
    use_adw_provider();
       
    // create the main window
    AdwApplicationWindow *main_window = ADW_APPLICATION_WINDOW(adw_application_window_new(app));
    
    // create toolbar for header and content
    GtkWidget *toolbar_view = adw_toolbar_view_new();

    // create headerbar
    GtkWidget *header_bar = adw_header_bar_new();
    GtkWidget *title = gtk_label_new(_("Autoreplacer"));
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header_bar), title);

    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header_bar);
        
    gtk_window_set_default_size(GTK_WINDOW(main_window), WINDOW_WIDTH, WINDOW_HEIGHT);

    // create a box container for the main content
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(content_box, TRUE);
    gtk_widget_set_vexpand(content_box, TRUE);

    radio_default = gtk_check_button_new_with_label(_("Default"));
    radio_markdown = gtk_check_button_new_with_label(_("Markdown"));
    radio_latex = gtk_check_button_new_with_label(_("LaTeX"));
    radio_emacs = gtk_check_button_new_with_label(_("Emacs"));

    gtk_check_button_set_group(GTK_CHECK_BUTTON(radio_markdown), GTK_CHECK_BUTTON(radio_default));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radio_latex), GTK_CHECK_BUTTON(radio_default));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radio_emacs), GTK_CHECK_BUTTON(radio_default));

    gtk_check_button_set_active(GTK_CHECK_BUTTON(radio_default), TRUE);

    g_signal_connect(radio_default, "toggled", G_CALLBACK(on_config_toggled), (gpointer)"/etc/autoreplacer/default.conf");
    g_signal_connect(radio_markdown, "toggled", G_CALLBACK(on_config_toggled), (gpointer)"/etc/autoreplacer/markdown.conf");
    g_signal_connect(radio_latex, "toggled", G_CALLBACK(on_config_toggled), (gpointer)"/etc/autoreplacer/latex.conf");
    g_signal_connect(radio_emacs, "toggled", G_CALLBACK(on_config_toggled), (gpointer)"/etc/autoreplacer/emacs.conf");

    gtk_box_append(GTK_BOX(content_box), radio_default);
    gtk_box_append(GTK_BOX(content_box), radio_markdown);
    gtk_box_append(GTK_BOX(content_box), radio_latex);
    gtk_box_append(GTK_BOX(content_box), radio_emacs);

    // button to start the replacing
    GtkWidget *button = gtk_label_new("");
    GtkWidget *replace_button = create_button_icon("pan-end-large-symbolic", "Replace", G_CALLBACK(show_file_chooser), (gpointer)on_file_selected);
    gtk_box_append(GTK_BOX(content_box), button);
    gtk_box_append(GTK_BOX(content_box), replace_button);

	adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), content_box);
	
	adw_application_window_set_content(main_window, toolbar_view);
	
    gtk_window_present(GTK_WINDOW(main_window));
	
	// stop logging
    close_logging();
}

