CC := gcc
SRCS := dp.c
TARGET := dp
INCLUDE_DIR := include
LIB_DIR := lib

CFLAGS := -I$(INCLUDE_DIR) -Wall -Wextra -Werror -std=c99
LDFLAGS := -L$(LIB_DIR)
LIBS := -lraylib

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
    FRAMEWORKS := -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework CoreFoundation -framework AudioToolbox -framework CoreAudio
else
    FRAMEWORKS :=
endif

.PHONY: all clean run dbg

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS) $(FRAMEWORKS)

clean:
	rm -f $(TARGET) *.o

run: all
	./$(TARGET)

dbg: CFLAGS += -g -O0
dbg: clean all
