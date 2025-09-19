# Makefile
#
# (C) Copyright 2025 AtlantisOS Project
# by @NachtsternBuild
#
# License: GNU GENERAL PUBLIC LICENSE Version 3
#
# Usage:
# everything:
# make
# 
# building only object files
# make objects
#
# building libs
# make lib
#
# building test
# make test
#
# only languages:
# make -C po
# 
# init new languages:
# make -C po init-po
#
# update languages:
# make -C po update-po
#
# install everything
# sudo make install
#
# cleanup
# make clean
#
# create test app
# make test
#
# run test app
# make testing
# 
# create test config file
# make create-config
#
# make -f Dependcies.mk

include Dependencies.mk
# compiler
#CC = gcc
CC = ccache gcc
# pass on to GCC where to search
INCLUDES = -I. -IincludeINCLUDES -Iinclude -Ibuild/uibase

# compiler flags
CFLAGS = -Wall -fPIC $(INCLUDES) `pkg-config --cflags glib-2.0 gtk4 libadwaita-1 vte-2.91-gtk4`
# linker flags
LIBS   = `pkg-config --libs glib-2.0 gtk4 libadwaita-1 vte-2.91-gtk4`

# all .c files
HEADERS = $(shell find . -name '*.h')
SRC = $(shell find . -name '*.c' ! -name 'test.c')

# objectfiles
OBJ = $(SRC:.c=.o)

# targets
TARGET = autoreplacer

# paths
PO_PATH = build/uibase/po
UI_BASE = build/uibase

BUILD_DIR = build
OBJ = $(patsubst ./%.c,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all objects po clean help depends

all: depends objects po $(TARGET)

depends: prepare
	rm -f $(UI_BASE)/Makefile
	rm -rf $(PO_PATH)/*.po

# Building only object files
objects: $(OBJ)

# create objectfiles
#%.o: %.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $< -o $@ 
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# building test app
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# running language logic in /po
po:
	$(MAKE) -C $(PO_PATH)

help:
	@echo " Building everything: "
	@echo " make "
	@echo " Building only object files: "
	@echo " make objects "
	@echo " Only languages: "
	@echo " make -C $(PO_PATH) "
	@echo " Init new languages: "
	@echo " make -C $(PO_PATH) init-po "
	@echo " Update languages: "
	@echo " make -C $(PO_PATH) update-po "
	@echo " Cleanup: "
	@echo " make clean "
	@echo " Help: "
	@echo " make help "

# cleanup
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(PO_PATH) clean
	rm -f $(TARGET)
