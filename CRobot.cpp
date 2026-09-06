#include "CRobot.h"

#include <iostream>
#include <string>

//Fixed Dimensions
const float CRobot::kWheelBase     = 24.0f;   // distance between the two wheels? camn change to something between 0-30
const float CRobot::kRadius        = 15.0f;   // drawn body radius, and collision radius
const float CRobot::kFixedTimestep = 0.1f;    // seconds simulated per Update() call

// CRobot Implementation
CRobot::CRobot(CPose aStartPose, std::string aLabel, CController* apController )
    : mController( apController ),
      mPose( aStartPose ),
      mLeftSpeed( 0.0f ),
      mRightSpeed( 0.0f ),
      mLabel( aLabel ),
      mUpdateCount( 0 ),
      mCollisionCount( 0 ),
      mWasColliding( false )
{
    std::cout << "Ctor CRobot " << mLabel << std::endl;
}

CRobot::~CRobot()
{
    std::cout << "Dtor CRobot " << mLabel << std::endl;
}

int main()
{
    return 0;
}