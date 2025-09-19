#!/bin/bash
#
# /usr/share/autoreplacer/autoreplacer.sh 
#
# (C) Copyright 2025 @NachtsternBuild
#
# License: GNU GENERAL PUBLIC LICENSE Version 3
#
# the background script, that interact with the GUI

set -euo pipefail

# check the commando build
if [ "$#" -ne 3 ]; then
	echo "[INFO] Usage: $0 <configurationfile> <inputfile> <outputfile>"
	exit 1
fi

# define the file names
CONFIG_FILE="$1"
INPUT_FILE="$2"
OUTPUT_FILE="$3"

# check for the input and config file
if [ ! -f "$CONFIG_FILE" ] || [ ! -f "$INPUT_FILE" ]; then
	echo "[ERROR] The configuration file or input file was not found."
	exit 1
fi

SED_COMMAND=""
while IFS="=" read -r search_quoted replace_quoted; do
	# skip commands and free lines
	[[ "$search_quoted" =~ ^[[:space:]]*# ]] && continue
    [[ -z "$search_quoted" ]] && continue

    # remove quotation marks
    search=$(echo "$search_quoted" | sed 's/^"//;s/"$//')
    replace=$(echo "$replace_quoted" | sed 's/^"//;s/"$//')

    # add the sed statement
    # use '#' as a separator to avoid conflicts with '/'
    search_escaped=$(printf '%s\n' "$search" | sed 's/[][#.$*^]/\\&/g')
    replace_escaped=$(printf '%s\n' "$replace" | sed 's/[][#.$*^]/\\&/g')
    
    # create the full sed command
    SED_COMMAND+="s#$search_escaped#$replace_escaped#g;"
done < "$CONFIG_FILE"

# run the sed command with backup
sed -i.bak "$SED_COMMAND" "$INPUT_FILE"
# change the input file to the ouptut file
mv "$INPUT_FILE" "$OUTPUT_FILE"
# remove the backup file
rm "$INPUT_FILE.bak"

echo "Die Verarbeitung ist abgeschlossen. Das Ergebnis befindet sich in $OUTPUT_FILE."
