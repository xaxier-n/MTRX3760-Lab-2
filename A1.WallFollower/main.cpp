//-----------------------------------------------------------------------------
// main.cpp
// Entry point for the Lab 2 A1 wall-follower simulation.
//-----------------------------------------------------------------------------
#include "CSimulation.h"

int main()
{
    CSimulation Simulation( "SimpleWalls.map" );
    Simulation.Run();

    return 0;
}
