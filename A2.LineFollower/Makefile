# -----------------------------------------------------------------------------
# Makefile for MTRX3760 Lab 2, A2 (wall-follower + line-follower simulation).
#
#     make        builds the program as ./A2
#     make run    builds (if needed) and runs it
#     make clean  removes the built binary (do this before zipping up your
#                 submission -- code only, no binaries)
#
# SRCS picks up every .cpp file in this folder automatically, so adding a new
# class later just means dropping its .cpp here -- no need to edit this file.

CXX      := g++
CXXFLAGS := -Wall -Wextra -I$(HOME)/raylib/include
LDFLAGS  := -L$(HOME)/raylib/lib
LDLIBS   := -lraylib

TARGET := A2.out
SRCS   := $(wildcard *.cpp)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)