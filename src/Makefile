# File:Makefile src folder

CC      := gcc
CFLAGS  := -I. -Wall -Wextra

SRCS    := cpuinfo_manip.c \
           meminfo_manip.c \
           resource_mon.c \
           tui.c

OBJDIR  := ../obj
OBJS    := $(SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: all clean

# Doing make in src/ just generate .o
all: $(OBJS)

# Generic compilation rule
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj/ if it doesn't exist
$(OBJDIR):
	mkdir -p $@

# Clean just .o in src/
clean:
	@rm -f $(OBJS)
