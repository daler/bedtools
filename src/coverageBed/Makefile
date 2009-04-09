CXX = g++
CXXFLAGS = -O3
LDFLAGS = -m64 

UTILITIES_DIR = ../utils/
OBJ_DIR = ../../obj/
BIN_DIR = ../../bin/

# -------------------
# define our includes
# -------------------
INCLUDES = -I$(UTILITIES_DIR)/bedFile/

# ----------------------------------
# define our source and object files
# ----------------------------------
SOURCES= coverageMain.cpp coverageBed.cpp
OBJECTS= $(SOURCES:.cpp=.o)
_EXT_OBJECTS=bedFile.o
EXT_OBJECTS=$(patsubst %,$(OBJ_DIR)/%,$(_EXT_OBJECTS))
BUILT_OBJECTS= $(patsubst %,$(OBJ_DIR)/%,$(OBJECTS))
PROGRAM= coverageBed
LIBS=

all: $(PROGRAM)

.PHONY: all

$(PROGRAM): $(BUILT_OBJECTS) $(EXT_OBJECTS)
	@echo "  * linking $(PROGRAM)"
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)	
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

$(BUILT_OBJECTS): $(SOURCES)
	@echo "  * compiling" $(*F).cpp
	@$(CXX) -c -o $@ $(*F).cpp $(LDFLAGS) $(CXXFLAGS) $(INCLUDES)

$(EXT_OBJECTS):
	@$(MAKE) --no-print-directory -C $(UTILITIES_DIR)/bedFile/

clean:
	@echo "Cleaning up."
	@rm -f $(OBJ_DIR)/* $(BIN_DIR)/*

.PHONY: clean