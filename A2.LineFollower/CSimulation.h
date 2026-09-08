//-----------------------------------------------------------------------------
// CSimulation.h - test harness for the line follower alone, for verification.
//-----------------------------------------------------------------------------

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CLoopReader.h"
#include "CRender.h"
#include "CRobot.h"

#include <vector>

class CSimulation
{
    public:
        //---Ctor/Dtor---
        CSimulation();
        ~CSimulation();

        void Run(); //Run the simulation until the window is closed

    private:
        void DrawLine(); //Draw the line on the screen
        void PrintSummary() const; //Print a summary of the simulation results to the console

        static const char* const kLineFilename;
        static const float kLineThickness;

        CLoopReader mLine; //The line to follow
        CRender mRender; //The renderer for drawing the line and the robot
        std::vector<CRobot*> mRobots; //The robots in the simulation
};

#endif