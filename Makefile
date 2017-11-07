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

#Create the executable from the object files
Main.exe : $(OBJ_FILES) 
	$(CXX) $(CXXFLAGS) -o $@ $^

#If an impllementation file has been changed rebuild the object file(s)
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean : 
	rm $(OBJ_DIR)/*.o && rm Main.exe

