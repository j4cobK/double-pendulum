CC := gcc
TARGET := dp
FRAMEWORKS := -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework CoreFoundation -framework AudioToolbox -framework CoreAudio

all:
	$(CC) -Iinclude -o $(TARGET) dp.c lib/libraylib.a -lm $(FRAMEWORKS)

clean:
	rm -f $(TARGET)