# test/Makefile
CC      := gcc
CFLAGS  := -I../src -Wall -Wextra

SRCDIR  := src
BINDIR  := bin
OBJDIR  := ../obj

# Test binaries directory
TEST_BINDIR := bin

TEST_SRCS := cpuinfo_test.c meminfo_test.c tui_test.c
TEST_OBJS := $(TEST_SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: tests clean cpuinfo_test meminfo_test tui_test

# Main target: build all tests
tests: cpuinfo_test meminfo_test tui_test

# Individual test targets
cpuinfo_test: $(TEST_BINDIR)/cpuinfo_test
meminfo_test: $(TEST_BINDIR)/meminfo_test
tui_test: $(TEST_BINDIR)/tui_test

# ----------------------------------------------------------------
#   Test executables linking
# ----------------------------------------------------------------
$(TEST_BINDIR)/cpuinfo_test: $(OBJDIR)/cpuinfo_test.o $(OBJDIR)/cpuinfo_manip.o | $(TEST_BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lm

$(TEST_BINDIR)/meminfo_test: $(OBJDIR)/meminfo_test.o $(OBJDIR)/meminfo_manip.o | $(TEST_BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lm

$(TEST_BINDIR)/tui_test: $(OBJDIR)/tui_test.o $(OBJDIR)/tui.o | $(TEST_BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lm

# ----------------------------------------------------------------
#   Object file compilation
# ----------------------------------------------------------------
# Test object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure main source objects exist by delegating to ../src
$(OBJDIR)/cpuinfo_manip.o $(OBJDIR)/meminfo_manip.o $(OBJDIR)/tui.o:
	$(MAKE) -C ../src

# ----------------------------------------------------------------
#   Directory creation
# ----------------------------------------------------------------
$(BINDIR):
	mkdir -p $@

$(TEST_BINDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@

# ----------------------------------------------------------------
#   Clean
# ----------------------------------------------------------------
clean:
	@rm -f $(TEST_BINDIR)/cpuinfo_test $(TEST_BINDIR)/meminfo_test $(TEST_BINDIR)/tui_test
	@rm -f $(TEST_OBJS)
	@$(MAKE) -C $(SRCDIR) clean