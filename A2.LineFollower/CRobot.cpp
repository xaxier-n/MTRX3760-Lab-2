//-----------------------------------------------------------------------------
// CRobot.cpp
//-----------------------------------------------------------------------------
#include "CRobot.h"
#include "CGeometry.h"

#include <cmath>
#include <iostream>

//Fixed Dimensions
const float CRobot::kWheelBase     = 24.0f;   // distance between the two wheels? camn change to something between 0-30
const float CRobot::kRadius        = 15.0f;   // drawn body radius, and collision radius
const float CRobot::kFixedTimestep = 0.1f;    // seconds simulated per Update() call

// CRobot Implementation
CRobot::CRobot( std::string aLabel, CController* apController,
                 CRender& arRender, const CLoopReader& arTrack,
                 Color aBodyColour, Color aTrailColour )
    : mController( apController ),
      mrRender( arRender ),
      mrTrack( arTrack ),
      mPose( arTrack.GetStartPose() ),   // start where arTrack's own startpose says (mLine's for the line-follower, mWalls's for the wall-follower)
      mLeftSpeed( 0.0f ),
      mRightSpeed( 0.0f ),
      mLabel( aLabel ),
      mUpdateCount( 0 ),
      mCollisionCount( 0 ),
      mWasColliding( false ),
      mBodyColour( aBodyColour ),
      mTrailColour( aTrailColour )
{
    std::cout << "Ctor CRobot " << mLabel << std::endl;
}

CRobot::~CRobot()
{
    delete mController;
    std::cout << "Dtor CRobot " << mLabel << std::endl;
}

//Update the robot's pose based on the wheel speeds, and call the controller to get new wheel speeds
void CRobot::Update()
{
    //Call the controller to get the new wheel speeds
    mController->Step( mPose, mrTrack, mLeftSpeed, mRightSpeed );

    //Update the robot's pose based on the wheel speeds (differential drive kinematics)
    const float LinearSpeed = ( mLeftSpeed + mRightSpeed ) / 2.0f;
    const float AngularSpeed = ( mRightSpeed - mLeftSpeed ) / kWheelBase; // radians per second

    mPose.mHeading += AngularSpeed * kFixedTimestep;
    mPose.mPosition.x += LinearSpeed * std::cos( mPose.mHeading ) * kFixedTimestep;
    mPose.mPosition.y += LinearSpeed * std::sin( mPose.mHeading ) * kFixedTimestep;

    mTrail.push_back( mPose.mPosition ); //Add the new position to the trail

    // Only count a fresh collision (the moment contact starts), not every
    // frame the robot happens to still be touching.
    // Note: this checks against mrTrack, the same loop the controller senses
    // (mLine for the line-follower) rather than a separate "hazard" geometry,
    // so the line-follower's HasCollided() is being measured against the line
    // it is meant to sit on top of, not the room's walls.
    bool IsColliding = HasCollided( mrTrack );
    if( IsColliding && !mWasColliding )
    {
        ++mCollisionCount;
        std::cout << "Collision #" << mCollisionCount << " detected for robot "
            << mLabel << " at position (" << mPose.mPosition.x
            << ", " << mPose.mPosition.y << ")" << std::endl;
    }
    mWasColliding = IsColliding;

    ++mUpdateCount;
}


bool CRobot::HasCollided( const CLoopReader& aTrack ) const
{
    bool Collided = false;
    const std::vector<Vec2D>& Vertices = aTrack.GetVertices();
    if( !Vertices.empty())
    {
        Vec2D Previous = Vertices.back(); //The last vertex is connected to the first
        for( const Vec2D& Current : Vertices )
        {
            if( CGeometry::DistanceFromPointToSeg( mPose.mPosition, Previous, Current ) < kRadius )
            {
                Collided = true;
                break;
            }
            Previous = Current; //Update the previous vertex
        }
    }

    return Collided;
}

void CRobot::Draw() const
{
    // Trail: a line through every past position.
    if(mTrail.size() > 1 )
    {
        for(std::size_t i=1; i < mTrail.size(); ++i )
        {
            mrRender.DrawLine( mTrail[i-1], mTrail[i], 2.0f, mTrailColour );
        }
    }


    mrRender.DrawCircle( mPose.mPosition, kRadius, mBodyColour );

    // A short line from the centre out to the edge of the body, in the current
    // heading direction, so the robot's facing is visible on screen.
    Vec2D Nose{ mPose.mPosition.x + kRadius * std::cos( mPose.mHeading ),
                mPose.mPosition.y + kRadius * std::sin( mPose.mHeading ) };
    mrRender.DrawLine( mPose.mPosition, Nose, 2.0f, BLACK );
}
