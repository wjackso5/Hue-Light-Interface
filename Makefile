#Makefile for the project.

#Evnironment Variables
CXX = g++#C++ Compiler

SRC_DIR = src#Directory Containing the source files
OBJ_DIR = obj#Directory containing the object files
HDR_DIR = include#Directory containing header files

SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXXFLAGS = -I$(HDR_DIR) #Compiler flags
CXXFLAGS += -I$(SRC_DIR)
CXXFLAGS += -I$(OBJ_DIR)
CXXFLAGS += -std=c++11
WTFLAGS = -lwtdbo
WTFLAGS += -lwtdbosqlite3
WTFLAGS += -lwthttp
WTFLAGS += -lwt
WTFLAGS += -lboost_random
WTFLAGS += -lboost_regex
WTFLAGS += -lboost_signals
WTFLAGS += -lboost_system
WTFLAGS += -lboost_thread
WTFLAGS += -lboost_filesystem
WTFLAGS += -lboost_program_options
WTFLAGS += -lboost_date_time

#Create the executable from the object files
Main.exe : $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(WTFLAGS)

#If an impllementation file has been changed rebuild the object file(s)
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean :
	rm $(OBJ_DIR)/*.o & rm Main.exe & rm light.db & rm -r html & rm -r latex
