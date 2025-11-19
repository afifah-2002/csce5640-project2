CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Object files
OBJS = main.o page_replacement.o fifo.o optimal.o lru.o lfu.o mfu.o

# Executable name
TARGET = page_replacement

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each source file
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run with sample test
test: $(TARGET)
	./$(TARGET) test_cases/sample_test.txt