CXX = g++
CXXFLAGS = -Wall -g
TESTFLAGS = -lgtest -lgmock -pthread

TEST_SRC = tests/tests.cpp
TEST_TARGET = test-cyclicalList

all: test

test: $(TEST_SRC)
	$(CXX) $(TEST_SRC) $(CXXFLAGS) -o $(TEST_TARGET) $(TESTFLAGS)

clean:
	rm -f $(TEST_TARGET)

