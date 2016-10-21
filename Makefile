#                    __
#    ____ ___  _____/ /__  ___  ____
#   / __ `__ \/ ___/ / _ \/ _ \/ __ \
#  / / / / / (__  ) /  __/  __/ /_/ /
# /_/ /_/ /_/____/_/\___/\___/ .___/
#                           /_/

PREFIX = /usr/bin/

CC = gcc
CFLAGS = -Wall

SRC_DIR = src
OBJ_DIR = obj
EXEC = msleep

LIBS = pthread
LFLAGS = $(addprefix -l,$(LIBS))

SRCS = $(shell find $(SRC_DIR) -type f -iname '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

#------------------------------------------------------------------------------

.PHONY: all install clean

all: $(EXEC)

install:
	install -D $(EXEC) $(PREFIX)

clean:
	rm -r $(OBJ_DIR) $(EXEC)

#------------------------------------------------------------------------------

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(OBJS)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LFLAGS) -c -o $@ $<
