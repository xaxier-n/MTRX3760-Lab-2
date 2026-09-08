//-----------------------------------------------------------------------------
// CSLineFollowerController.cpp 
//-----------------------------------------------------------------------------
#include "CLineFollowerController.h"

//Sensor Geometry
const float CLineFollowerController::kForwardSensorOffset = 20.0f; //distance from robot centre to forward facing sensor
const float CLineFollowerController::kSideSensorOffset = 6.0f; //distance from robot centre to side facing sensor

//Steering Behaviour
const float CLineFollowerController::kBaseSpeed = 20.0f; //base speed of the robot
const float CLineFollowerController::kGentleCorrection = 0.5f; //speed to apply when correcting course
const float CLineFollowerController::kSharpCorrection = 0.05f; //speed to apply when correcting course

//Constructor
CLineFollowerController::CLineFollowerController()
    : mCentreSensor( kForwardSensorOffset, 0.0f ),
      mSideSensor( kSideSensorOffset, 0.0f ),
      mLastCorrectionSide( false )
{
}

void CLineFollowerController::Step( const CPose& aPose, const CLoopReader& aTrack, float& arLeftSpeed, float& arRightSpeed )
{
    //Get sensor readings
    bool CentreOnLine = mCentreSensor.Sense( aPose, aTrack );
    bool SideOnLine = mSideSensor.Sense( aPose, aTrack );

    //If both sensors are on the line, go straight
    if( CentreOnLine && !SideOnLine )
    {
        arLeftSpeed = kBaseSpeed;
        arRightSpeed = kBaseSpeed;
        return;
    }
    // Line curving toward the side sensor, correct gently.
    else if( CentreOnLine &&SideOnLine)
    {
        arLeftSpeed = kBaseSpeed; 
        arRightSpeed = kBaseSpeed * kGentleCorrection; //Correct gently to the right
        mLastCorrectionSide = true; //
        return;
    }
    // Line curving away from the centresensor, correct sharply.
    else if( !CentreOnLine &&SideOnLine)
    {
        arLeftSpeed = kBaseSpeed; 
        arRightSpeed = kBaseSpeed * kSharpCorrection; //Correct sharply to the right
        mLastCorrectionSide = true; //
        return;
    }
    //Lost the line, search in the last correction of the line.
    else 
    {
        if (mLastCorrectionSide)
        {
            arLeftSpeed = kBaseSpeed * kSharpCorrection; //Correct sharply to the left
            arRightSpeed = kBaseSpeed;
            return;
        }
        else
        {
            arLeftSpeed = kBaseSpeed; 
            arRightSpeed = kBaseSpeed * kSharpCorrection; //Correct sharply to the right
            return;
        }
    }
}