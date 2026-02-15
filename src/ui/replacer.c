/**
* replacer.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/

#include "autoreplacer.h"

#define MAX_LINE_LENGTH 4096

/**
* @brief Function that search and replace in a string
*/
char* str_replace(char* target, const char* needle, const char* replacement) 
{
    char buffer[MAX_LINE_LENGTH];
    char* insert_point = &buffer[0];
    const char* tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) 
    {
        const char* p = strstr(tmp, needle);
        if (p == NULL) 
        {
            strcpy(insert_point, tmp);
            break;
        }
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;
        tmp = p + needle_len;
    }
    return strdup(buffer);
}

/**
* @brief Function that replace everything by structure in .conf files 
* @param config_path: selected config file
* @param input_path: input file
* @param output_path: output file
* @return success or not
*/
int replacer(const char* config_path, const char* input_path, const char* output_path) 
{
    FILE *config_fp, *input_fp, *output_fp;
    char line[MAX_LINE_LENGTH];
    char search_patterns[100][MAX_LINE_LENGTH];
    char replace_patterns[100][MAX_LINE_LENGTH];
    int pair_count = 0;

    // read config file
    config_fp = fopen(config_path, "r");
    if (!config_fp) 
    {
    	return -1;
	}
	
    while (fgets(line, sizeof(line), config_fp)) 
    {
        // skipt empty lines and comments
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') 
        {
        	continue;
		}
		
        char *equal_sign = strchr(line, '=');
        if (equal_sign) 
        {
            *equal_sign = '\0';
            char *s_raw = line;
            char *r_raw = equal_sign + 1;

            // remove '"'
            if (s_raw[0] == '"') 
            { 
            	s_raw++; s_raw[strlen(s_raw)-1] = '\0'; 
            }
            
            if (r_raw[0] == '"') 
            { 
            	r_raw++; 
            	
                // remove empty line
                size_t len = strlen(r_raw);
                if (r_raw[len-1] == '\n' || r_raw[len-1] == '\r') 
                {
                	r_raw[len-1] = '\0';
                }
                
                if (r_raw[strlen(r_raw)-1] == '"') 
                {
                	r_raw[strlen(r_raw)-1] = '\0';
                }
            }
            
            strncpy(search_patterns[pair_count], s_raw, MAX_LINE_LENGTH);
            strncpy(replace_patterns[pair_count], r_raw, MAX_LINE_LENGTH);
            pair_count++;
        }
    }
    fclose(config_fp);

    // read input file and create output file
    input_fp = fopen(input_path, "r");
    output_fp = fopen(output_path, "w");
    if (!input_fp || !output_fp) 
    {
    	return -1;
	}
	
    while (fgets(line, sizeof(line), input_fp)) 
    {
        char *current_line = strdup(line);
        
        for (int i = 0; i < pair_count; i++) 
        {
            char *temp = str_replace(current_line, search_patterns[i], replace_patterns[i]);
            free(current_line);
            current_line = temp;
        }
        
        fputs(current_line, output_fp);
        free(current_line);
    }

    fclose(input_fp);
    fclose(output_fp);
    return 0; // success
}
