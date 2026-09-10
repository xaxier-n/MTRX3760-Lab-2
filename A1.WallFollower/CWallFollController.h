//-----------------------------------------------------------------------------
// CWallFollController.h
// Wall-following controller: keeps one side of the robot at a fixed standoff
// distance from the wall, using a side-facing sensor (distance to the wall
// abeam) and a diagonal sensor (distance to the wall ahead) to steer.
//-----------------------------------------------------------------------------
#ifndef CWALLFOLLCONTROLLER_H
#define CWALLFOLLCONTROLLER_H

#include "CController.h"
#include "CDistSensor.h"

struct CPose;

class CWallFollController : public CController
{
    public:
        CWallFollController();

        // See CController::Step - reads the two sensors and sets the wheel
        // speeds needed to hold the target standoff distance from the wall.
        virtual void Step( const CPose& aPose, const CLoopReader& aTrack,
                           float& arLeftSpeed, float& arRightSpeed );

    private:
        // Sensor Geometry
        static const float kDiagSensorAngle;
        static const float kSideSensorAngle;

        // Steering Parameters
        static const float kBaseSpeed;
        static const float kGentleCorrection;
        static const float kSharpCorrection;

        // Control Parameters
        static const float kTargetDistance;
        static const float kTolerance;
        static const float kHeadingTolerance;

        // Sensors
        CDistSensor mDiagSensor;   // ahead, at kDiagSensorAngle - watches for the wall/corner coming up
        CDistSensor mSideSensor;   // abeam, at kSideSensorAngle - watches the standoff distance

};

#endif
