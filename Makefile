CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++14 -pedantic -O2
SRC=parser.cc	\
	node.cc
OBJ=$(SRC:.cc=.o)
EXEC=parser
all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

