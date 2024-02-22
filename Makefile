#
# @file Makefile
# @brief this is Makefile for our program
# @details For implementation details, see GitHub.
# @authors Yoad Tamar, Lior Vinman
#

CXX = clang++ 				# compiler
CXXFLAGS = -std=c++11 -Wall	# compilation flags

# main list of targets
all: MyPrimeCounter

# rule that compiles our program
MyPrimeCounter: MyPrimeCounter.cpp MyPrimeCounter.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

# a cleanup rule
clean:
	rm -f *.h.gch *.hpp.gch *.o MyPrimeCounter
