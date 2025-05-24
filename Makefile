# Root Makefile
CC      := gcc
CFLAGS  := -Isrc -Wall -Wextra

SRCDIR  := src
TESTDIR := test
BINDIR  := bin
OBJDIR  := obj

.PHONY: all resource_mon tests clean

# Default target builds both main program and tests
all: resource_mon tests

# ----------------------------------------------------------------
#   Main Program
# ----------------------------------------------------------------
resource_mon: $(BINDIR)/resource_mon

$(BINDIR)/resource_mon: \
    $(OBJDIR)/cpuinfo_manip.o \
    $(OBJDIR)/meminfo_manip.o \
    $(OBJDIR)/resource_mon.o \
    $(OBJDIR)/tui.o \
    | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lm

# ----------------------------------------------------------------
#   Object files compilation (delegated to src/Makefile)
# ----------------------------------------------------------------
$(OBJDIR)/%.o: | $(OBJDIR)
	$(MAKE) -C $(SRCDIR)

# ----------------------------------------------------------------
#   Tests
# ----------------------------------------------------------------
tests: cpuinfo_test meminfo_test tui_test

cpuinfo_test: $(BINDIR)/cpuinfo_test
meminfo_test: $(BINDIR)/meminfo_test  
tui_test: $(BINDIR)/tui_test

$(BINDIR)/cpuinfo_test: $(OBJDIR)/cpuinfo_manip.o | $(BINDIR)
	$(MAKE) -C $(TESTDIR) cpuinfo_test

$(BINDIR)/meminfo_test: $(OBJDIR)/meminfo_manip.o | $(BINDIR)
	$(MAKE) -C $(TESTDIR) meminfo_test

$(BINDIR)/tui_test: $(OBJDIR)/tui.o | $(BINDIR)
	$(MAKE) -C $(TESTDIR) tui_test

# ----------------------------------------------------------------
#   Directory creation
# ----------------------------------------------------------------
$(BINDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@

# ----------------------------------------------------------------
#   Clean targets
# ----------------------------------------------------------------
clean:
	@rm -f $(OBJDIR)/*.o
	@rm -f $(BINDIR)/*
	@$(MAKE) -C $(SRCDIR) clean
	@$(MAKE) -C $(TESTDIR) clean