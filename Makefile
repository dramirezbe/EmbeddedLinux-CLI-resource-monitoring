# File: MakeFile Project Root

CC      := gcc
CFLAGS  := -Isrc -Wall -Wextra

SRCDIR  := src
TESTDIR := test
BINDIR  := bin
OBJDIR  := obj

.PHONY: all resource_mon tests clean

all: resource_mon tests

# ----------------------------------------------------------------
#   Main Program
# ----------------------------------------------------------------
resource_mon: \
    $(OBJDIR)/cpuinfo_manip.o \
    $(OBJDIR)/meminfo_manip.o \
    $(OBJDIR)/resource_mon.o \
    $(OBJDIR)/tui.o \
    | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

# ----------------------------------------------------------------
#   Tests
# ----------------------------------------------------------------
tests:
	$(MAKE) -C $(TESTDIR) tests

# ----------------------------------------------------------------
#   General clean
# ----------------------------------------------------------------
clean:
	@rm -f $(OBJDIR)/*.o
	@rm -f $(BINDIR)/*
	@$(MAKE) -C $(SRCDIR) clean
	@$(MAKE) -C $(TESTDIR) clean

# ----------------------------------------------------------------
#   Helpers
# ----------------------------------------------------------------
$(BINDIR):
	mkdir -p $@
