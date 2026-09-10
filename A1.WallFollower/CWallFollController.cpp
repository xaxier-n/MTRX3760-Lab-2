#include "CWallFollController.h"
#include "CDistSensor.h"
#include "CGeometry.h"
#include "CLoopReader.h"
#include "CRender.h"

#include <cmath>

const float CWallFollController::kDiagSensorAngle = 45.0f * (M_PI / 180.0f);    // rad CW from forward
const float CWallFollController::kSideSensorAngle = 90.0f * (M_PI / 180.0f);    // rad CW from forward

const float CWallFollController::kBaseSpeed = 20.0f;                            // base wheel speed
const float CWallFollController::kGentleCorrection = 0.5f;                      // wheel speed multiplier
const float CWallFollController::kSharpCorrection = 0.01f;                      // wheel speed multiplier

const float CWallFollController::kTargetDistance = 35.0f;                       // target standoff distance
const float CWallFollController::kTolerance = 2.0f;                             // distance tolerance
const float CWallFollController::kHeadingTolerance = 5.0f * (M_PI / 180.0f);    // heading tolerance

CWallFollController::CWallFollController()
    : mDiagSensor(kDiagSensorAngle),
      mSideSensor(kSideSensorAngle)
{
}

void CWallFollController::Step( const CPose& aPose, const CLoopReader& aTrack, 
                                float& arLeftSpeed, float& arRightSpeed )
{
    const std::vector<Vec2D>& Vertices = aTrack.GetVertices();

    float ExpectedDiagDist = kTargetDistance * std::sqrt(2);

    float SideDist = mSideSensor.GetReading( aPose, Vertices );
    float DiagDist = mDiagSensor.GetReading( aPose, Vertices );

    float ExpectedDiagForCurrentSide = SideDist * std::sqrt(2.0f);
    bool FacingAwayFromWall = ( DiagDist > ExpectedDiagForCurrentSide + kHeadingTolerance );

    if( SideDist < kTargetDistance - kTolerance )
    {
        if( FacingAwayFromWall )
        {
            // Still too close, but already turning away — ease off before we overshoot.
            arLeftSpeed = kBaseSpeed;
            arRightSpeed = kBaseSpeed * kGentleCorrection;
        }
        else
        {
            // Too close and still heading toward/parallel to the wall — turn away hard.
            arLeftSpeed = kBaseSpeed;
            arRightSpeed = kBaseSpeed * kSharpCorrection;
        }
    }
    else if( DiagDist < ExpectedDiagDist - kTolerance )
    {
        // wall/corner coming up ahead — steer away before we hit it
        arLeftSpeed = kBaseSpeed;
        arRightSpeed = kBaseSpeed * kSharpCorrection;
    }
    else if( SideDist > kTargetDistance + kTolerance )
    {
        // too far from the wall — steer toward it
        arLeftSpeed = kBaseSpeed * kGentleCorrection;
        arRightSpeed = kBaseSpeed;
    }
    else
    {
        // holding the target distance — go straight
        arLeftSpeed = kBaseSpeed;
        arRightSpeed = kBaseSpeed;
    }
}