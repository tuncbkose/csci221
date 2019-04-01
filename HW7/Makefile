CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -Werror -std=c++17 -g

.cpp.o:
	$(CXX) $(CCFLAGS) -c $<

all:	htree hforest

hforest: hforest.o test_hforest.o htree.o
		$(CXX) $(CXXFLAGS) -o hforest hforest.o test_hforest.o htree.o

htree: htree.o test_htree.o
		$(CXX) $(CXXFLAGS) -o htree htree.o test_htree.o

clean:
		rm -f *.o
		rm -f htree
		rm -f hforest