/**
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

#include "atlbase.h"

/**
* @brief Function that replace everything by structure in .conf files 
*/
/**
* @brief Function that replace everything by structure in .conf files 
* @param config_path: selected config file
* @param input_path: input file
* @param output_path: output file
* @return success or not
*/
int replacer(const char* config_path, const char* input_path, const char* output_path);
void activate_autoreplacer(GtkApplication* app, gpointer user_data);

#endif // AUTOREPLACER_H
