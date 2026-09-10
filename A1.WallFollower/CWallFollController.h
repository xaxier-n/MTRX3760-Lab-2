#ifndef CWALLFOLLCONTROLLER_H
#define CWALLFOLLCONTROLLER_H

#include "CController.h"
#include "CDistSensor.h"

struct CPose;

class CWallFollController : public CController
{
    public:
        CWallFollController();
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
        CDistSensor mDiagSensor;
        CDistSensor mSideSensor;

};

#endif