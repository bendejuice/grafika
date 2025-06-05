CC = gcc
SRC = src
BUILD = build
GLEW_PATH = /opt/homebrew # Adjust this path if GLEW is installed elsewhere

# Strip any potential whitespace from GLEW_PATH to prevent compilation errors
STRIPPED_GLEW_PATH := $(strip $(GLEW_PATH))

# CFLAGS: Compiler flags
# -Wall: Enable all warnings
# -g: Include debugging information
# `sdl2-config --cflags`: Includes SDL2 compiler flags (e.g., -I/usr/local/include/SDL2)
# -I$(SRC): Add source directory to include paths
# -I$(STRIPPED_GLEW_PATH)/include: Add GLEW include path, ensuring no extra spaces
# -D_DEFAULT_SOURCE: Required for some functions on Linux (e.g., for `stb_image`)
CFLAGS = -Wall -g `sdl2-config --cflags` -I$(SRC) -I$(STRIPPED_GLEW_PATH)/include -D_DEFAULT_SOURCE

# LDFLAGS: Linker flags
# `sdl2-config --libs`: Includes SDL2 linker flags (e.g., -L/usr/local/lib -lSDL2)
# -L$(STRIPPED_GLEW_PATH)/lib: Add GLEW library path, ensuring no extra spaces
# -lGLEW: Link against GLEW library
# -framework OpenGL: Link against OpenGL framework (macOS specific)
# -lm: Link against math library (for sin, cos, etc.)
LDFLAGS = `sdl2-config --libs` -L$(STRIPPED_GLEW_PATH)/lib -lGLEW -framework OpenGL -lm

# SRCS: All .c files in the src directory
SRCS = $(wildcard $(SRC)/*.c)

# OBJS: Corresponding .o files in the build directory
OBJS = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

# EXEC: The final executable name and path
EXEC = $(BUILD)/main

# all: Default target, builds the executable
all: $(EXEC)

# Create the build directory if it doesn't exist
$(BUILD):
	mkdir -p $(BUILD)

# Rule to link the executable
$(EXEC): $(OBJS) | $(BUILD)
	$(CC) -o $@ $^ $(LDFLAGS)

# Rule to compile .c files into .o files
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# clean: Removes all compiled objects and the executable
clean:
	rm -f $(BUILD)/*.o $(EXEC)
	# Attempt to remove the build directory, suppress error if it's not empty or doesn't exist
	rmdir $(BUILD) 2>/dev/null || true
