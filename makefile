# Compiler and flags
CC = g++
CFLAGS_DEBUG = -Wall -std=c++20 -O0 -g -Iinclude
CFLAGS_RELEASE = -Wall -std=c++20 -O3 -DNDEBUG -Iinclude

# Add required Windows libraries to LDFLAGS
LDFLAGS = -Llib \
		-lmingw32 \
		-lSDL2main \
		-lSDL2 \
		-lSDL2_ttf \
		-lkernel32 \
		-luser32 \
		-lgdi32 \
		-lwinmm \
		-limm32 \
		-lsetupapi \
		-lole32 \
		-luuid \
		-lversion \
		-lhid \
		-lshcore \
		-loleaut32 \
		-lrpcrt4  


# Directories
SRC_DIR = src
OBJ_DIR_DEBUG = build/debug/obj
OBJ_DIR_RELEASE = build/release/obj
BIN_DIR_DEBUG = build/debug/bin
BIN_DIR_RELEASE = build/release/bin

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS_DEBUG = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR_DEBUG)/%.o, $(SRCS))
OBJS_RELEASE = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR_RELEASE)/%.o, $(SRCS))

# Targets
DEBUG_TARGET = $(BIN_DIR_DEBUG)/main.exe
RELEASE_TARGET = $(BIN_DIR_RELEASE)/main.exe

# Default target
all: debug

# Debug build
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(OBJS_DEBUG)
	@mkdir -p $(BIN_DIR_DEBUG)
	cp bin/*.dll $(BIN_DIR_DEBUG)  # Copy DLLs to the output directory
	$(CC) $(OBJS_DEBUG) -o $@ $(LDFLAGS)  # Add -mwindows here

$(OBJ_DIR_DEBUG)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR_DEBUG)
	$(CC) -c $< -o $@ $(CFLAGS_DEBUG)

# Release build
release: $(RELEASE_TARGET)

$(RELEASE_TARGET): $(OBJS_RELEASE)
	@mkdir -p $(BIN_DIR_RELEASE)
	cp bin/*.dll $(BIN_DIR_RELEASE)  # Copy DLLs to the output directory
	$(CC) $(OBJS_RELEASE) -o $@ $(LDFLAGS)  # Add -mwindows here

$(OBJ_DIR_RELEASE)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR_RELEASE)
	$(CC) -c $< -o $@ $(CFLAGS_RELEASE)

# Clean
clean:
	rm -rf build

.PHONY: all debug release clean