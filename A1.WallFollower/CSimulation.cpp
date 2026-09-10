//-----------------------------------------------------------------------------
// CSimulation.cpp
//-----------------------------------------------------------------------------
#include "CSimulation.h"
#include "CWallFollController.h"

#include <iostream>
#include <vector>

const int CSimulation::kMaxUpdates = 1100;   // enough steps for one lap of SimpleWalls.map

//-----------------------------------------------------------------------------
CSimulation::CSimulation( const std::string& aMapFilename )
    : mWalls(),
      mRender(),
      mRobot( LoadStartPose( aMapFilename ), "WallFollower", new CWallFollController() )
{
}

CSimulation::~CSimulation()
{
    mRender.CloseWindow();
}

//-----------------------------------------------------------------------------
CPose CSimulation::LoadStartPose( const std::string& aMapFilename )
{
    if( !mWalls.ReadFile( aMapFilename ) )
    {
        std::cout << "Failed to read " << aMapFilename << std::endl;
    }
    return mWalls.GetStartPose();
}

//-----------------------------------------------------------------------------
void CSimulation::Run()
{
    while( !mRender.WindowShouldClose() && mRobot.GetUpdateCount() < kMaxUpdates )
    {
        mRobot.Update( mWalls );

        mRender.BeginDrawing();
        DrawWalls();
        mRobot.Draw( mRender );
        mRender.EndDrawing();
    }

    PrintSummary();
}

//-----------------------------------------------------------------------------
// Draw the room's walls as a closed outline, same approach as TestLoopReader.
//-----------------------------------------------------------------------------
void CSimulation::DrawWalls()
{
    const float kEdgeThickness = 2.0f;

    const std::vector<Vec2D>& Vertices = mWalls.GetVertices();
    if( !Vertices.empty() )
    {
        Vec2D Previous = Vertices.back();
        for( const Vec2D& Vertex : Vertices )
        {
            mRender.DrawLine( Previous, Vertex, kEdgeThickness, RAYWHITE );
            Previous = Vertex;
        }
    }
}

//-----------------------------------------------------------------------------
void CSimulation::PrintSummary() const
{
    std::cout << "Updates completed: " << mRobot.GetUpdateCount() << std::endl;
    std::cout << "Total collisions: "  << mRobot.GetCollisionCount() << std::endl;
}
