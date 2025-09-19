/*
* ui.c
*
* (C) Copyright 2025 AtlantisOS Project
* by @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Notes:
* This is started by the autoreplacer.c (int main)
*/

#include <glib.h>
#include <gtk/gtk.h>
#include <adwaita.h>
#include "design.h"
#include "autoreplacer.h"

// global widgets
GtkWidget *status_label;
GtkWidget *progress_bar;
GtkWidget *replace_button;

// radio buttons
GtkWidget *radio_default;
GtkWidget *radio_markdown;
GtkWidget *radio_latex;
GtkWidget *radio_emacs;

// define the default config file
static const char *selected_config = "default.conf";

// set the active button
static void on_config_toggled(GtkToggleButton *button, gpointer user_data)
 {
    if (gtk_toggle_button_get_active(button)) 
    {
        selected_config = (const char *)user_data;
        LOGD("Selected config: %s\n", selected_config);
    }
}


// selecte files
static void on_file_selected(const char *filename) 
{
    LOGI("Selected file: %s with config %s\n", filename, selected_config);
	char new_name[512];
	snprintf(new_name, sizeof(new_name), "replaced_%s", filename);
    run_to_replacer(selected_config, filename, new_name);
}

// callback for the button
// use the filechooser
static void on_replace_clicked(GtkButton *button, gpointer user_data) 
{
    show_file_chooser(GTK_WIDGET(button), (gpointer)on_file_selected);
}

// main window
void activate_autoreplacer(GtkApplication *app, gpointer user_data) 
{
    // start logging
    // using journald - 1
    set_logging_mode(1);

    // use speciell adw theme provider
    use_adw_provider();

    // create the new window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), _("Autoreplacer"));
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

    // create a new main box
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), content_box);
    gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(content_box, TRUE);
    gtk_widget_set_vexpand(content_box, TRUE);

    // create the stack for navigation
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 300);
    gtk_widget_set_hexpand(stack, TRUE);
    gtk_widget_set_vexpand(stack, TRUE);

    // add the headerbar
    GtkWidget *headerbar = create_custom_headerbar(stack);
    gtk_widget_set_halign(headerbar, GTK_ALIGN_START);
    gtk_widget_set_valign(headerbar, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(content_box), headerbar);

    // add the stack to the main box
    gtk_box_append(GTK_BOX(content_box), stack);

    // create a new home page 
    // used for other widgets
    GtkWidget *home_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

    // add a status label
    status_label = gtk_label_new(_("Waiting for action"));
    gtk_box_append(GTK_BOX(home_page), status_label);

    // create a new progress bar
    progress_bar = gtk_progress_bar_new();
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), TRUE);
    gtk_box_append(GTK_BOX(home_page), progress_bar);
	
	// create new box for the button
	GtkWidget *config_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
	gtk_box_append(GTK_BOX(home_page), gtk_label_new(_("Select Config:")));

    radio_default = gtk_check_button_new_with_label(_("Default"));
    radio_markdown = gtk_check_button_new_with_label(_("Markdown"));
    radio_latex = gtk_check_button_new_with_label(_("LaTeX"));
    radio_emacs = gtk_check_button_new_with_label(_("Emacs"));

    gtk_check_button_set_group(GTK_CHECK_BUTTON(radio_markdown), GTK_CHECK_BUTTON(radio_default));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radio_latex), GTK_CHECK_BUTTON(radio_default));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radio_emacs), GTK_CHECK_BUTTON(radio_default));

    gtk_check_button_set_active(GTK_CHECK_BUTTON(radio_default), TRUE);

    g_signal_connect(radio_default, "toggled", G_CALLBACK(on_config_toggled), (gpointer)"default.conf");
    g_signal_connect(radio_markdown, "toggled", G_CALLBACK(on_config_toggled), (gpointer)"markdown.conf");
    g_signal_connect(radio_latex, "toggled", G_CALLBACK(on_config_toggled), (gpointer)"latex.conf");
    g_signal_connect(radio_emacs, "toggled", G_CALLBACK(on_config_toggled), (gpointer)"emacs.conf");

    gtk_box_append(GTK_BOX(config_box), radio_default);
    gtk_box_append(GTK_BOX(config_box), radio_markdown);
    gtk_box_append(GTK_BOX(config_box), radio_latex);
    gtk_box_append(GTK_BOX(config_box), radio_emacs);

    gtk_box_append(GTK_BOX(home_page), config_box);

    // button to start the replacing
    replace_button = gtk_button_new_with_label(_("Replace Elements"));
    g_signal_connect(replace_button, "clicked", G_CALLBACK(on_replace_clicked), NULL);
    gtk_box_append(GTK_BOX(home_page), replace_button);

    // add the home page to the stack
    gtk_stack_add_named(GTK_STACK(stack), home_page, "home_page");
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "home_page");

    // show the main window
    gtk_window_present(GTK_WINDOW(window));

    // cloas the logging
    close_logging();
}

