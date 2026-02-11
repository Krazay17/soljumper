CXX			= g++
SDL_PATH	= C:/libs/SDL-release-3.2.28
SDL_LIB_DIR = $(SDL_PATH)/build
SDL_INC		= -I$(SDL_PATH)/include
# Static linking requires SDL3 and its Windows dependencies
LDFLAGS 	= -lmingw32 -L$(SDL_LIB_DIR) -lSDL3 -lsetupapi -lwinmm -lgdi32 -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -luser32
CXXFLAGS	= -O3 -Isrc $(SDL_INC) -static

BIN_DIR		= bin
TARGET		= $(BIN_DIR)/soljumper.exe
SRC_DIR		= src
OBJ_DIR		= obj

# Instead of one wildcard, we find all directories inside src
SUBDIRS     = $(wildcard $(SRC_DIR)/*/)
# We get files from src/ AND all subfolders
SOURCES     = $(wildcard $(SRC_DIR)/*.cpp) $(foreach dir,$(SUBDIRS),$(wildcard $(dir)*.cpp))
# --------------------------------
OBJECTS     = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(subst \,/,$(SOURCES)))

all: $(TARGET)

# Ensure the bin directory exists before linking
$(BIN_DIR):
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Rule to compile AND create subdirectories in obj/ automatically
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .cpp files into the obj/ folder
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist $(TARGET).exe del /q $(TARGET).exe
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)

run: all
	./$(TARGET)