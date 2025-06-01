PROJECT = cyclicalList
TEST_PROJECT = test-cyclicalList

CXX = g++
CXXFLAGS = -std=c++20 -I.
LIBS =
TESTFLAGS = -lgtest -lgmock -pthread

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

TEST_SRC = tests/tests.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

DEPS = CyclicalList.h

.PHONY: all clean cleanall test

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_PROJECT)

$(TEST_PROJECT): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(TESTFLAGS)

clean:
	rm -f $(OBJ) $(TEST_OBJ) *~ core $(TEST_PROJECT)

cleanall: clean
	rm -f $(PROJECT)
