//-----------------------------------------------------------------------------
// CSimulation.h
// Owns the room, the wall-following robot, and the renderer, and drives the
// main loop: stepping the robot each fixed timestep, drawing the walls and
// robot, and reporting the run's summary once it finishes.
//-----------------------------------------------------------------------------
#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CLoopReader.h"
#include "CRender.h"
#include "CRobot.h"

#include <string>

class CSimulation
{
    public:
        //---Ctor/Dtor---
        CSimulation( const std::string& aMapFilename );
        ~CSimulation();

        //---Running---
        void Run();

    private:
        //---Setup helper---
        // Reads aMapFilename into mWalls and returns its starting pose, so
        // the robot can be constructed with that pose in this ctor's
        // initialiser list. This relies on mWalls being declared (and so
        // constructed) before mRobot below.
        CPose LoadStartPose( const std::string& aMapFilename );

        //---Per-frame helpers---
        void DrawWalls();
        void PrintSummary() const;

        //---Run length---
        static const int kMaxUpdates;   // enough steps for one lap of the map

        //---The world---
        CLoopReader mWalls;
        CRender mRender;
        CRobot mRobot;
};

#endif
