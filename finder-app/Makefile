# Compiler (native hoặc cross-compile)
CC = $(CROSS_COMPILE)gcc

# Flags
CFLAGS ?= -Wall -Werror -g
LDFLAGS ?=

# Output executable
TARGET = writer

# Source files
SRC = writer.c
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Build writer từ object files
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean

