# src/Makefile
CC      := gcc
CFLAGS  := -I. -Wall -Wextra

SRCS    := cpuinfo_manip.c \
           meminfo_manip.c \
           resource_mon.c \
           tui.c

OBJDIR  := ../obj
OBJS    := $(SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: all clean

# Default target generates all object files
all: $(OBJS)

# Generic compilation rule for object files
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj/ directory if it doesn't exist
$(OBJDIR):
	mkdir -p $@

# Clean only removes .o files generated by this Makefile
clean:
	@rm -f $(OBJS)