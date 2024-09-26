# Compiler
CC=g++

# Result file
EXECUTABLE=onegin
EXECUTABLE_DEBUG=onegin_debug

# Compilation flags
CFLAGS=-c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_EJUDGE_CLIENT_SIDE

# Linking flags
LDFLAGS=

# Collecting names of all .cpp files in SRC_DIR
SRC_DIR=src
SOURCES=$(patsubst $(SRC_DIR)/%, %, $(wildcard $(SRC_DIR)/*.cpp))

# Creating path and names of all .o files 
OBJ_DIR=objects
OBJECTS=$(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
OBJECTS_DEBUG=$(SOURCES:%.cpp=$(OBJ_DIR)/%_debug.o)

# Collecting names of all .h files in HEADERS_DIR
HEADERS_DIR=include
HEADERS=$(wildcard $(HEADERS_DIR)/*.h)


# Order of execution for release
all: $(OBJ_DIR) info $(EXECUTABLE)
	$(info Done)

# Creating directory for object files
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Reassuring user
info:
	$(info Compiling...)

# Compiling .cpp files into object files
$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Linking object and header files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(CC) -DNDEBUG -Wno-unused-variable -Wno-unused-parameter -I$(HEADERS_DIR) $(CFLAGS) $< -o $@


# Order of execution for debug
debug: $(OBJ_DIR) info $(EXECUTABLE_DEBUG)
	$(info Done)

# Compiling .cpp files into object files
$(EXECUTABLE_DEBUG): $(OBJECTS_DEBUG)
	$(CC) $(LDFLAGS) $(OBJECTS_DEBUG) -o $@

# Linking object and header files
$(OBJ_DIR)/%_debug.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(CC) -I$(HEADERS_DIR) $(CFLAGS) -Wcast-qual $< -o $@


# Removing compilated files
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)
