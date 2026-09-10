//-----------------------------------------------------------------------------
// CSimulation.cpp
//-----------------------------------------------------------------------------

#include "CSimulation.h"
#include "CLineFollowerController.h"
#include "CWallFollController.h"

#include <iostream>

const char* const CSimulation::kLineFilename = "SimpleLine.map";
const char* const CSimulation::kWallFilename = "SimpleWalls.map";
const float CSimulation::kLineThickness      = 2.0f;
const int CSimulation::kMaxUpdates           = 1200;  // simulation ends after this many steps

// Draw colours
const Color CSimulation::kLineFollowerBodyColour  = GREEN;
const Color CSimulation::kLineFollowerTrailColour = Color{ 144, 238, 144, 255 };  // light green
const Color CSimulation::kWallFollowerBodyColour  = BLUE;
const Color CSimulation::kWallFollowerTrailColour = SKYBLUE;                      // light blue


//-----------------------------------------------------------------------------
CSimulation::CSimulation()
{
    if( !mLine.ReadFile( kLineFilename ) )
    {
        std::cout << "CSimulation: failed to read '" << kLineFilename << "'" << std::endl;
    }
    if( !mWalls.ReadFile( kWallFilename ) )
    {
        std::cout << "CSimulation: failed to read '" << kWallFilename << "'" << std::endl;
    }

    // CRobot takes ownership of the CController pointers - deletes them in their
    // own destructors.
    mRobots.push_back( new CRobot( "LineFollower", new CLineFollowerController(), mRender, mLine,
                                    kLineFollowerBodyColour, kLineFollowerTrailColour ) );
    mRobots.push_back( new CRobot( "WallFollower", new CWallFollController(), mRender, mWalls,
                                    kWallFollowerBodyColour, kWallFollowerTrailColour ) );
}


//-----------------------------------------------------------------------------
CSimulation::~CSimulation()
{
    for( CRobot* pRobot : mRobots )
    {
        delete pRobot;
    }
}


// Main loop: update every robot, then draw the line, walls and every robot,
// once per frame, until the window closes or kMaxUpdates is reached.
void CSimulation::Run()
{
    int UpdateCount = 0;
    while( !mRender.WindowShouldClose() && UpdateCount < kMaxUpdates )
    {
        for( CRobot* pRobot : mRobots )
        {
            pRobot->Update();
        }

        mRender.BeginDrawing();
        DrawLine();
        DrawWalls();
        for( CRobot* pRobot : mRobots )
        {
            pRobot->Draw();
        }
        mRender.EndDrawing();

        ++UpdateCount;
    }

    mRender.CloseWindow();
    PrintSummary();
}


//-----------------------------------------------------------------------------
void CSimulation::DrawLine()
{
    const std::vector<Vec2D>& Vertices = mLine.GetVertices();
    if( !Vertices.empty() )
    {
        Vec2D Previous = Vertices.back();
        for( const Vec2D& Vertex : Vertices )
        {
            mRender.DrawLine( Previous, Vertex, kLineThickness, RAYWHITE );
            Previous = Vertex;
        }
    }
}

//-----------------------------------------------------------------------------
// Draw the room's walls as a closed outline, same approach as TestLoopReader.
//-----------------------------------------------------------------------------
void CSimulation::DrawWalls()
{
    const std::vector<Vec2D>& Vertices = mWalls.GetVertices();
    if( !Vertices.empty() )
    {
        Vec2D Previous = Vertices.back();
        for( const Vec2D& Vertex : Vertices )
        {
            mRender.DrawLine( Previous, Vertex, kLineThickness, RAYWHITE );
            Previous = Vertex;
        }
    }
}


//-----------------------------------------------------------------------------
void CSimulation::PrintSummary() const
{
    std::cout << std::endl << "--- Simulation summary ---" << std::endl;
    for( std::size_t i = 0; i < mRobots.size(); ++i )
    {
        std::cout << mRobots[i]->GetLabel() << ": " << mRobots[i]->GetUpdateCount()
                   << " updates completed, " << mRobots[i]->GetCollisionCount()
                   << " collisions." << std::endl;
    }
    std::cout << "--------------------------" << std::endl << std::endl;
}
