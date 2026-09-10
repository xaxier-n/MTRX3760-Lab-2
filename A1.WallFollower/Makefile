# -----------------------------------------------------------------------------
# Makefile for MTRX3760 Lab 2, A1 (wall-follower simulation).
#
#     make        builds the program as ./A1
#     make run    builds (if needed) and runs it
#     make clean  removes the built binary (do this before zipping up your
#                 submission -- code only, no binaries)
# -----------------------------------------------------------------------------

CXX      := g++
CXXFLAGS := -Wall -Wextra -I$(HOME)/raylib/include
LDFLAGS  := -L$(HOME)/raylib/lib
LDLIBS   := -lraylib

TARGET := A1.out
SRCS   := CDistSensor.cpp CGeometry.cpp CLoopReader.cpp CRender.cpp \
          CRobot.cpp CSimulation.cpp CWallFollController.cpp main.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)