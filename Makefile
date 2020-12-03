EXENAME = wiki
OBJS = main.o graph.o game.o interpreter.o 

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm


all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp graph.h game.h interpreter.h edge.h random.h
	$(CXX) $(CXXFLAGS) main.cpp

edge.o : edge.h
	$(CXX) $(CXXFLAGS) edge.h

random.o : random.cpp random.h
	$(CXX) $(CXXFLAGS) random.cpp

graph.o : graph.cpp graph.h edge.h random.h
	$(CXX) $(CXXFLAGS) graph.cpp

game.o : game.cpp game.h graph.h edge.h random.h
	$(CXX) $(CXXFLAGS) game.cpp

interpreter.o : interpreter.cpp interpreter.h game.h graph.h edge.h random.h
	$(CXX) $(CXXFLAGS) interpreter.cpp

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

output_msg: ; $(CLANG_VERSION_MSG)

# Be sure to add output_msg as dependency target for your `intro` binary

test: output_msg tests.o graph.o game.o interpreter.o 
	$(LD) tests.o graph.o game.o interpreter.o $(LDFLAGS) -o test

tests.o: tests/tests.cpp tests/catch.hpp graph.h game.h interpreter.h
	$(CXX) $(CXXFLAGS) tests/tests.cpp
    
.PHONY: output_msg