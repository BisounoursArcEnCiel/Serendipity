CXX=g++

CXXFLAGS= -std=c++11 -DBOOST_LOG_DYN_LINK -W -Wall -Wno-reorder -Wunreachable-code
CXXFLAGS+=-g

CPPFLAGS = -D ENABLE_LOG_STATUS=1

LDFLAGS= -lboost_serialization -lboost_filesystem -lboost_system -lboost_log -lboost_log_setup -lboost_thread
LDFLAGS+= -pthread  -lboost_unit_test_framework

OPTFLAG=-O3

EXEC= serendipity
SRC= $(wildcard */*/*.cpp)
SRC+= $(wildcard */*.cpp)
SRC+= $(wildcard *.cpp)

SRC := $(filter-out wildcard tests/test.cpp, $(SRC))

TEST_FILES = $(wildcard tests/*.cpp)
TEST_FILES+= $(SRC)
TEST_FILES := $(filter-out wildcard main.cpp, $(TEST_FILES))
	
OBJ= $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_FILES:.cpp=.o)
MAX_PARALLEL = 3

all: $(EXEC)

serendipity: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

_test: $(TEST_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)
	
%.o: %.cpp 
	$(CXX) $(CPPFLAGS) $(OPTFLAG) -c -o $@  $< $(CXXFLAGS)

.PHONY: clean mrproper multi doc test
test:
	CPPFLAGS=-D ENABLE_LOG_STATUS=0
	$(MAKE) _test
	./_test
	rm _test

clean:
	rm -rf */*/*.o
	rm -rf */*.o
	rm -rf *.o

cleanlog:
	rm -rf log/*.log
	
cleandoc:
	rm -rf doc/html
	rm -rf doc/latex

cleanfiles: cleanlog cleanreport cleandoc

mrproper: clean cleanfiles
	rm -rf $(EXEC)

doc:
	doxygen
