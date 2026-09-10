//-----------------------------------------------------------------------------
// CLineSensor.h
//
// One "is there floor-line under me" sensor, rigidly mounted at a fixed
// forward/side offset from the robot's own centre and heading. Reports a
// plain bool rather than a distance
//-----------------------------------------------------------------------------

#ifndef CLINESENSOR_H
#define CLINESENSOR_H

#include "CLoopReader.h" //For the CPose and CLoopReader classes

class CLineSensor{
    public:
    //aForwardOffset: dist ahead of the robot centre
    //aSideOffset: dist to the right of the robot centre
        CLineSensor( float aForwardOffset, float aSideOffset ); //Constructor
        bool Sense( const CPose& aRobotPose, const CLoopReader& aTrack ) const; //Returns true if the sensor is over the line  
        
    private:
        static const float kSensorRadius; //radius of the sensor
        static const float kFarThreshold; //distance from the line at which the sensor is considered to be over the line 

        float mForwardOffset; //dist ahead of the robot centre
        float mSideOffset; //dist to the right of the robot centre
};
#endif
