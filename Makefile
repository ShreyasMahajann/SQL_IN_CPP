
CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRCS = main.cpp table.cpp database.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = dbms

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
