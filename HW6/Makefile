CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -Werror -std=c++17 -g

all:	tree

tree: tree.o test_tree.o
		$(CXX) $(CXXFLAGS) -o tree tree.o test_tree.o
test_tree.o: test_tree.cc tree.hh
		$(CXX) $(CXXFLAGS) -c test_tree.cc
tree.o: tree.cc tree.hh
		$(CXX) $(CXXFLAGS) -c tree.cc
clean:
		rm -f *.o
		rm -f tree