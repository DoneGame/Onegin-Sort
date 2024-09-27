# Compiler
CC=g++

# Result file
EXECUTABLE=onegin
EXECUTABLE_DEBUG=onegin_debug

ifeq ($(OS), Windows_NT)
	# Compilation flags
	CFLAGS=-c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_EJUDGE_CLIENT_SIDE

	# Linking flags
	LDFLAGS=
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		# Compilation flags
		CFLAGS=-c -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla

		# Linking flags
		LDFLAGS=-fsanitize=address -fsanitize=undefined
	else
		$(info Error. Unsupported OS!)
	endif
endif

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

# Linking object and header files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(CC) -DNDEBUG -Wno-unused-variable -Wno-unused-parameter -I$(HEADERS_DIR) $(CFLAGS) $< -o $@

# Compiling .cpp files into object files
$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@


# Order of execution for debug
debug: $(OBJ_DIR) info $(EXECUTABLE_DEBUG)
	$(info Done)

# Linking object and header files
$(OBJ_DIR)/%_debug.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(CC) -I$(HEADERS_DIR) $(CFLAGS) -Wcast-qual -Wsign-conversion -Wuseless-cast -Wconversion -D_DEBUG $< -o $@

# Compiling .cpp files into object files
$(EXECUTABLE_DEBUG): $(OBJECTS_DEBUG)
	$(CC) $(LDFLAGS) $(OBJECTS_DEBUG) -o $@


# Removing compilated files
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)
