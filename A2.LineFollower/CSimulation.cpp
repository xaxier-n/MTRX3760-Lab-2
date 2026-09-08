//-----------------------------------------------------------------------------
// CSimulation.cpp
//-----------------------------------------------------------------------------

#include "CSimulation.h"
#include "CLineFollowerController.h"

#include <iostream>

const char* const CSimulation::kLineFilename = "SimpleLine.map";
const float CSimulation::kLineThickness      = 2.0f;


//-----------------------------------------------------------------------------
CSimulation::CSimulation()
{
    if( !mLine.ReadFile( kLineFilename ) )
    {
        std::cout << "CSimulation: failed to read '" << kLineFilename << "'" << std::endl;
    }

    // CRobot takes ownership of the CController pointer - deletes it in its
    // own destructor.
    mRobots.push_back( new CRobot( mLine.GetStartPose(), "LineFollower", new CLineFollowerController() ) );
}


//-----------------------------------------------------------------------------
CSimulation::~CSimulation()
{
    for( CRobot* pRobot : mRobots )
    {
        delete pRobot;
    }
}


void CSimulation::Run()
{
    while( !mRender.WindowShouldClose() )
    {
        for( CRobot* pRobot : mRobots )
        {
            pRobot->Update( mLine );
        }

        mRender.BeginDrawing();
        DrawLine();
        for( CRobot* pRobot : mRobots )
        {
            pRobot->Draw( mRender );
        }
        mRender.EndDrawing();
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
void CSimulation::PrintSummary() const
{
    std::cout << std::endl << "--- Simulation summary ---" << std::endl;
    for( std::size_t i = 0; i < mRobots.size(); ++i )
    {
        std::cout << mRobots[i]->GetLabel() << ": " << mRobots[i]->GetUpdateCount()
                   << " updates completed, " << mRobots[i]->GetCollisionCount()
                   << " collisions." << std::endl;
    }
}