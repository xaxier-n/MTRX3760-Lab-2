//-----------------------------------------------------------------------------
// CWallFollController.cpp
//
// Step() picks one of four wheel-speed cases each call, checked in this
// order:
//   1. Too close to the wall (SideDist < target - tolerance): turn away.
//      FacingAwayFromWall compares the diagonal sensor's actual reading to
//      what it *would* read if the robot were already parallel at the
//      current side distance - if it's already reading further than that,
//      the heading has started to correct, so ease off (kGentleCorrection)
//      rather than keep turning hard and overshoot past parallel.
//   2. Wall/corner coming up ahead (diagonal reading closer than expected
//      for the target distance): steer away hard before hitting it.
//   3. Too far from the wall: steer gently back toward it.
//   4. Otherwise holding the target distance: go straight.
//
// Left/right assignment note: AngularSpeed in CRobot is (Right-Left)/kWheelBase,
// and with this project's CW-from-+x / y-down heading convention that means
// giving the *other* wheel (not the one nearer the sensor) the full speed is
// what turns the robot away from that side's wall.
//-----------------------------------------------------------------------------
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

    // What the diagonal sensor would read if the robot were parallel to the
    // wall, exactly at the target standoff distance (45 degree sensor -> sqrt(2) factor).
    float ExpectedDiagDist = kTargetDistance * std::sqrt(2);

    float SideDist = mSideSensor.GetReading( aPose, Vertices );
    float DiagDist = mDiagSensor.GetReading( aPose, Vertices );

    // What the diagonal sensor would read if the robot were parallel to the
    // wall at its *current* (not target) side distance - used to detect that
    // the heading has already started to correct, even while still too close.
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
