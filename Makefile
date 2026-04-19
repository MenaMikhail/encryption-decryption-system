# Compiler to use (g++)
CC = g++


# Compiler flags:
# - Wall: Enables most compiler warnings.
# - std=c++11: Specifies that the C++11 standard should be used for compilation.
CFLAGS = -Wall -std=c++11


# The target (executable) name
TARGET = encryption_program


# It specifies that the final target depends on the `$(TARGET)` target (the compiled executable).
all: $(TARGET)


# Rule for creating the target (encryption_program)
# It uses the compiler $(CC) with the flags $(CFLAGS) to compile the source file into an executable.
$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp


# Rule for cleaning up generated files
# This rule removes the executable file `encryption_program` and the output file `output.txt`.
clean:
	rm -f $(TARGET) output.txt
