# File: Makefile test/src folder

CC      := gcc
CFLAGS  := -I../../src -Wall -Wextra

SRCS    := cpuinfo_test.c \
           meminfo_test.c \
           tui_test.c

OBJDIR  := ../../obj
OBJS    := $(SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: all clean

# Compile only the .o files of the tests in obj/
all: $(OBJS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@  -lncurses -lm

$(OBJDIR):
	mkdir -p $@

clean:
	@rm -f $(OBJDIR)/cpuinfo_test.o \
	         $(OBJDIR)/meminfo_test.o  \
	         $(OBJDIR)/tui_test.o
