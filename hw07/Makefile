# HW7 (Intro to C) - CS2110: Spring 2022
# GCC flags from the syllabus (each flag described for the curious minds!)
# Flag info credit: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

CFLAGS = -std=c99					# Using the C99 standard
CFLAGS += -Wall						# This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros
CFLAGS += -pedantic					# Issue all the warnings demanded by strict ISO C and ISO C++; reject all programs that use forbidden extensions, and some other programs that do not follow ISO C and ISO C++
CFLAGS += -Wextra					# This enables some extra warning flags that are not enabled by -Wall
CFLAGS += -Werror					# Make all warnings into errors
CFLAGS += -O0						# Optimize even more. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff.
CFLAGS += -Wstrict-prototypes		# Warn if a function is declared or defined without specifying the argument types
CFLAGS += -Wold-style-definition	# Warn if an old-style function definition is used. A warning is given even if there is a previous prototype
CFLAGS += -g						# Generate debugging information
CFLAGS += -Werror=vla                                   # Generate an error if variable-length arrays (bad practice in C!) are used

# Source files to be compiled together (for local command line testing)
CFILES = main.c hw7.c my_string.c
HFILES = hw7.h suites/test_utils.h

# Executable name
OBJNAME = hw7

%.o: %.c $(HFILES)
	gcc $(CFLAGS) -c $< -o $@

# Note: '@' added to disable echo on the command
hw7: $(CFILES)
	@ # Compile all source files with the given flags into the specified executable object!
	@ gcc -fno-asm $(CFLAGS) $(CFILES) -o $(OBJNAME)

.PHONY: clean
clean:
	@ # Removing all sort of object files and executables
	@ rm -f $(OBJNAME) tests *.o *.out


##########################################################################################
# NOTE: AUTOGRADING BELOW

# Source files for the autograder (skipping main, cause check has it's own main method)
AUTOGRADER_C_FILES = hw7.c my_string.c

# Uses pkg-config to retrieve package information about check -- Unit Testing Framework
CHECK_LIBS = $(shell pkg-config --cflags --libs check)
ARCH = $(shell uname -m)
TEST_FILES = suites/$(ARCH)/test_entry.o\
			 suites/$(ARCH)/hw7_suite.o\
			 suites/$(ARCH)/my_string_suite.o

# Testing with check library
.PHONY: tests
tests: $(AUTOGRADER_C_FILES) $(TEST_FILES)
	@ gcc -fno-asm $(CFLAGS) $(AUTOGRADER_C_FILES) $(TEST_FILES) $(CHECK_LIBS) -o tests

# To run a specific test case (or all similar to tests)
.PHONY: run-case
run-case: tests
	@ ./tests $(TEST)

# To run gdb on testcase(s)
.PHONY: run-gdb
run-gdb: tests
	@ CK_FORK=no gdb --args ./tests $(TEST)
