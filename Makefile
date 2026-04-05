# Compiler and flags
CC      := gcc
WARN	:= -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wdouble-promotion -Wformat=2 -Wnull-dereference -Wimplicit-fallthrough -Wstrict-prototypes -Wmissing-prototypes

# Target executable name
TARGET  := bh

# Source and object files
SRCS 	:= $(wildcard ./src/*.c)
INCS	:= -I./include/
LIBS 	:= -lm

# Default target
all:
	$(CC) $(CFLAGS) $(INCS) $(SRCS) $(LIBS) -o $(TARGET)
	./$(TARGET)
	feh --force-aliasing -FZ ./image.png


# Clean build artifacts
clean:
	rm $(TARGET)
