# Compiler (cho native và cross-compile)
CC = $(CROSS_COMPILE)gcc

# Output executable
TARGET = writer

# Source files
SRC = writer.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Build writer từ object files
$(TARGET): $(OBJ)
	$(CC) -o $@ $^

# Compile .c -> .o
%.o: %.c
	$(CC) -c $< -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJ)
