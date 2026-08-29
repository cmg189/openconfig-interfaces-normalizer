# Makefile - openconfig-interfaces parser
#
#   make            build ./switch
#   make run        build and run against the sample data
#   make asan       build ./switch-asan with Address/UB sanitizers
#   make check      build and run under the sanitizers
#   make strict     build with -Werror (warnings become errors)
#   make clean      remove build artifacts

TARGET      := switch
ASAN_TARGET := switch-asan
SAMPLE      := openconfig-interfaces-data.json

SRCS := switch.c switch_utils.c switch_generate.c
OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

CC       ?= gcc
STD      := -std=c11
# _DEFAULT_SOURCE exposes getdelim() and strlcpy() while keeping -std=c11 strict.
FEATURES := -D_DEFAULT_SOURCE

WARNINGS := -Wall -Wextra \
            -Wshadow \
            -Wpointer-arith \
            -Wcast-qual \
            -Wstrict-prototypes \
            -Wmissing-prototypes \
            -Wwrite-strings \
            -Wformat=2 \
            -Wvla

# Set to -Werror to make warnings fatal:  make WERROR=-Werror
WERROR ?=

# json-c: prefer pkg-config, fall back to a plain -ljson-c.
JSONC_CFLAGS := $(shell pkg-config --cflags json-c 2>/dev/null)
JSONC_LIBS   := $(shell pkg-config --libs json-c 2>/dev/null || echo -ljson-c)

CFLAGS  ?= -O2 -g
CFLAGS  += $(STD) $(FEATURES) $(WARNINGS) $(WERROR) -I. $(JSONC_CFLAGS) -MMD -MP
LDLIBS  += $(JSONC_LIBS)

SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer -g -O1

.PHONY: all run asan check strict clean help

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
    ./$(TARGET) $(SAMPLE)

# Sanitizer build: compiled straight from source so it never shares
# objects with the normal build.
$(ASAN_TARGET): $(SRCS)
    $(CC) $(STD) $(FEATURES) $(WARNINGS) $(SANFLAGS) -I. $(JSONC_CFLAGS) \
          -o $@ $^ $(LDLIBS)

asan: $(ASAN_TARGET)

check: $(ASAN_TARGET)
    ASAN_OPTIONS=detect_leaks=1 ./$(ASAN_TARGET) $(SAMPLE)

strict:
    $(MAKE) WERROR=-Werror

clean:
    $(RM) $(TARGET) $(ASAN_TARGET) $(OBJS) $(DEPS)

help:
    @echo "make        - build ./$(TARGET)"
    @echo "make run    - build and run against $(SAMPLE)"
    @echo "make asan   - build ./$(ASAN_TARGET) with sanitizers"
    @echo "make check  - run under Address/UB sanitizers + leak check"
    @echo "make strict - build with -Werror"
    @echo "make clean  - remove build artifacts"

-include $(DEPS)