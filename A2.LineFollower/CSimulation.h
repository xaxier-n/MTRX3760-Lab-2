//-----------------------------------------------------------------------------
// CSimulation.h - owns both robots, the room, and the renderer for A2.
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
        CSimulation();   // reads both map files and creates both robots
        ~CSimulation();  // deletes both robots

        void Run();                         // Run the simulation until the window is closed

    private:
        // Private helper functions
        void DrawLine();                    // Draw the line on the screen
        void DrawWalls();                   // Draw the walls on the screen
        void PrintSummary() const;          // Print a summary of the simulation results to the console

        // Simulation consts
        static const char* const kLineFilename;   // map file for the line-follower's line
        static const char* const kWallFilename;   // map file for the room's walls
        static const float kLineThickness;         // drawn thickness of the line/walls
        static const int kMaxUpdates;        // simulation ends after this many steps

        // Draw colours, per robot type
        static const Color kLineFollowerBodyColour;
        static const Color kLineFollowerTrailColour;
        static const Color kWallFollowerBodyColour;
        static const Color kWallFollowerTrailColour;

        // Member classes
        CLoopReader mLine;                  // The line to follow
        CLoopReader mWalls;                 // The walls to follow
        CRender mRender;                    // The renderer for drawing the line and the robot
        std::vector<CRobot*> mRobots;       // The robots in the simulation
};

#endif
