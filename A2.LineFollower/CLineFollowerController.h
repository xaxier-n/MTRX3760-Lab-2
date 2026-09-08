//-----------------------------------------------------------------------------
// CLineFollowerController.h
// The controller for the line follower robot, which uses two line sensors to follow a line.
//-----------------------------------------------------------------------------

#ifndef CLINEFOLLOWERCONTROLLER_H
#define CLINEFOLLOWERCONTROLLER_H

#include "CController.h"
#include "CLineSensor.h"

class CLineFollowerController : public CController
{
    public:
        CLineFollowerController();
        virtual void Step( const CPose& aPose, const CLoopReader& aTrack, float& arLeftSpeed, float& arRightSpeed ); 
    
    private:
        //Sensor Geometry
        static const float kForwardSensorOffset; //distance from robot centre to forward facing sensor
        static const float kSideSensorOffset; //distance from robot centre to side facing sensor


        //Steering parameters
        static const float kBaseSpeed; //base speed of the robot
        static const float kGentleCorrection; //speed to apply when correcting course
        static const float kSharpCorrection; //speed to apply when correcting course

        CLineSensor mCentreSensor; //forward facing sensor
        CLineSensor mSideSensor; //side facing sensor

        bool mLastCorrectionSide; //Which way to search if both sensors are off the line
};

#endif