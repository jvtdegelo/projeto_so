# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++11

# Source files directory
SRCDIR = src

# Object files directory
OBJDIR = obj

# Executable name
EXEC = myprogram

# Get all source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Generate object file names
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Default target
all: $(EXEC)

# Rule to compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files and create executable
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean target
clean:
	rm -f $(OBJDIR)/*.o $(EXEC)
