ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # Not in a bash-like shell
    CLEANUP = del /F /Q
    MKDIR = mkdir
  else
    CLEANUP = rm -f
    MKDIR = mkdir -p
  endif
  TARGET_EXTENSION = .exe
else
  CLEANUP = rm -fr
  MKDIR = mkdir -p
  TARGET_EXTENSION =
endif

# Directory paths
PATHU = unity/src/
PATHS = src/
PATHM = src/math/
PATHI = inc/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

# Source files
SRCS = $(PATHS)chapter_1.c \
       $(wildcard $(PATHM)*.c)

_BASENAMES = $(notdir $(SRCS))
_OBJS = $(patsubst %.c,%.o,$(_BASENAMES))
OBJS = $(patsubst %,$(PATHO)%,$(_OBJS))

# Compilation tools
CC = gcc

CFLAGS_COMMON = -I. -I$(PATHU) -I$(PATHS) -I$(PATHM) -I$(PATHI) -I$(PATHI)/math -DTEST

# General flags with extra warnings (but excluding strict-prototypes)
CFLAGS_GENERAL = $(CFLAGS_COMMON) -Wall -Wextra -Wpedantic -Werror -Wshadow -Wuninitialized -Wunused \
                 -Wconversion -Wnull-dereference -Wfloat-equal -Wformat -Wmissing-declarations \
                 -Wlogical-op -Wsizeof-pointer-memaccess -Wunused-result -Wdeprecated-declarations \
                 -Wstrict-aliasing -Wmissing-include-dirs -Wredundant-decls -Wnonnull -Wcast-align \
                 -Wempty-body -Wwrite-strings

# Test-specific flags: Only -Wall, -Wextra, -Wpedantic, and -Werror
CFLAGS_TEST  = $(CFLAGS_COMMON) -Wall -Wextra -Wpedantic -Werror

# Flags to disable strict-prototypes for files like main.c
CFLAGS_MAIN = $(filter-out -Wstrict-prototypes,$(CFLAGS_GENERAL))

# Linking and dependency tools
LINK = gcc
DEPEND = gcc -MM -MG -MF

# Directories to ensure exist
BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

# Test source files
SRCT = $(wildcard $(PATHT)*.c)
RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCT))

# Sample extracted test dependencies (extend as needed)
TEST_DEPS_Testcolor = \
	$(PATHO)Testcolor.o \
	$(PATHO)color.o \
	$(PATHO)tuple.o \
	$(PATHO)unity.o

TEST_DEPS_Testtuple = \
	$(PATHO)Testtuple.o \
	$(PATHO)color.o \
	$(PATHO)tuple.o \
	$(PATHO)unity.o

# Default target
all: test compile install

test: $(BUILD_PATHS) $(RESULTS)
	@echo -e "-----------------------\n\033[0;33mIGNORES:\033[0m\n-----------------------"
	@grep -s IGNORE $(PATHR)*.txt | while read -r line; do \
		echo -e "\033[0;33m$$line\033[0m"; \
	done || true

	@echo -e "-----------------------\n\033[0;31mFAILURES:\033[0m\n-----------------------"
	@grep -s FAIL $(PATHR)*.txt | while read -r line; do \
		echo -e "\033[0;31m$$line\033[0m"; \
	done || true

	@echo -e "-----------------------\n\033[0;32mPASSED:\033[0m\n-----------------------"
	@grep -s PASS $(PATHR)*.txt | while read -r line; do \
		echo -e "\033[0;32m$$line\033[0m"; \
	done || true

	@echo -e "\nDONE"

# Rule to generate test output
$(PATHR)%.txt: $(PATHB)%$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

# Link test executables
$(PATHB)Testcolor$(TARGET_EXTENSION): $(TEST_DEPS_Testcolor)
	$(LINK) -o $@ $^ -lm

$(PATHB)Testtuple$(TARGET_EXTENSION): $(TEST_DEPS_Testtuple)
	$(LINK) -o $@ $^ -lm

# Object file rules
$(PATHO)%.o: $(PATHS)%.c
	$(CC) -c $(CFLAGS_GENERAL) $< -o $@

$(PATHO)%.o: $(PATHM)%.c
	$(CC) -c $(CFLAGS_GENERAL) $< -o $@

$(PATHO)%.o: $(PATHT)%.c
	$(CC) -c $(CFLAGS_TEST) $< -o $@

# Use test flags to compile Unity framework
$(PATHO)%.o: $(PATHU)%.c
	$(CC) -c $(CFLAGS_TEST) $< -o $@

# If you have a main.c or other specific files, disable strict-prototypes warning
$(PATHO)main.o: $(PATHS)main.c
	$(CC) -c $(CFLAGS_MAIN) $< -o $@

# Build directories
$(PATHB) $(PATHD) $(PATHO) $(PATHR):
	$(MKDIR) $@

# Compile non-test object files
compile: $(OBJS)

# Link final program
install: $(OBJS)
	$(LINK) -o raytracer $^ -lm

# Format source code
format:
	indent -linux $(PATHS)*.c $(PATHS)*.h $(PATHM)*.c || true
	$(CLEANUP) $(PATHS)*~ $(PATHI)*~ $(PATHT)*~

# Clean all build artifacts
clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHB)
	$(CLEANUP) raytracer

# Keep intermediate files
.PRECIOUS: $(PATHB)%$(TARGET_EXTENSION) $(PATHO)%.o $(PATHR)%.txt
