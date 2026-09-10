//-----------------------------------------------------------------------------
// CLineFollowerController.h
//
// Line-following behaviour built from two sensors: mCentreSensor sits ahead
// of the robot and, when tracking correctly, directly over the line;
// mSideSensor sits offset to one side of that. As the line curves toward
// mSideSensor's side, mSideSensor picks it up before mCentreSensor loses it,
// giving an early "gentle correction" signal before a later "sharp
// correction" one, and a "search" behaviour if both sensors lose the line
// at once.
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
