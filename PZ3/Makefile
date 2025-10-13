CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = noise_removal
SOURCES = main.cpp pgm_utils.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) test_results.csv

.PHONY: clean