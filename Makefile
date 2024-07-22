CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = add-nbo
SRCS = main.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(TARGET)
