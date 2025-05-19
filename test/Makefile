# File: Makefile test folder

CC      := gcc
CFLAGS  := -I../src -Wall -Wextra

SRCDIR  := src
BINDIR  := bin
OBJDIR  := ../obj

.PHONY: tests clean

# Main target of this folder: Build all test
# 1) compile test
# 2) Look if src/.o's is generated
# 3) executable link
tests: | $(BINDIR)

	$(MAKE) -C $(SRCDIR) all 
	
	$(MAKE) -C ../src all
	
	$(CC) $(CFLAGS) -o $(BINDIR)/cpuinfo_test $(OBJDIR)/cpuinfo_test.o $(OBJDIR)/cpuinfo_manip.o
	$(CC) $(CFLAGS) -o $(BINDIR)/meminfo_test  $(OBJDIR)/meminfo_test.o  $(OBJDIR)/meminfo_manip.o
	$(CC) $(CFLAGS) -o $(BINDIR)/tui_test      $(OBJDIR)/tui_test.o      $(OBJDIR)/tui.o

clean:
	@rm -f $(BINDIR)/*
	@$(MAKE) -C $(SRCDIR) clean

$(BINDIR):
	mkdir -p $@
