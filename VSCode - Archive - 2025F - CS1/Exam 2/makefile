# Author: Anthony Candelas
# Date: 24OCT2025
# Email: tsallinger2@unl.edu
#
# Description:
# Makefile for Exam 2 - Flood Utilities
# Builds and runs the C implementation of flood monitoring utilities.
# Supports compile, run, and clean targets.

# Compiler and flags
CC = gcc
# CFLAGS should not include libraries like -lm because when compiling with -c
# the linker flags are unused and clang prints a warning. Put linker libraries
# into LIBS (or LDLIBS) and only use them at link time.
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lm

# Executable name
TARGET = floodTest

# Source files
SRCS = floodTester.c flood_utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Compile and link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LIBS)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
# Author: Anthony Candelas
# Date: 24OCT2025
# Email: tsallinger2@unl.edu
#
# Description:
# Makefile for Exam 2 - Flood Utilities
# Builds and runs the C implementation of flood monitoring utilities.
# Supports compile, run, and clean targets.

# Compiler and flags
CC = gcc
# CFLAGS should not include libraries like -lm because when compiling with -c
# the linker flags are unused and clang prints a warning. Put linker libraries
# into LIBS (or LDLIBS) and only use them at link time.
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lm

# Executable name
TARGET = floodTest

# Source files
SRCS = floodTester.c flood_utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Compile and link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LIBS)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)