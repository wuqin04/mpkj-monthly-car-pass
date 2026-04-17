# Compiler settings
CXX = g++
# Added -Isrc to ensure the compiler can find system.h inside the src folder
CXXFLAGS = -Wall -Wextra -std=c++98 -Iheaders -Isrc

# The name of your final executable
TARGET = mpkj_car_pass

# Find main.cpp and .cpp files explicitly (Removed system.h)
SRCS = main.cpp \
       $(wildcard src/*.cpp)

# Generate a list of object files by replacing .cpp with .o
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the target
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up compiled files for Windows
clean:
	-del /Q /F $(subst /,\,$(OBJS)) $(TARGET).exe

# Phony targets
.PHONY: all clean