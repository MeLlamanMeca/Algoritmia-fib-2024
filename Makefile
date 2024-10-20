TARGET = main

CXX = g++
CXXFLAGS = -O2

SRCS = main.cpp class/graph/Graph.cpp class/graph/GraphNxN.cpp class/graph/GraphTrg.cpp class/graph/RandGeomGraph.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)