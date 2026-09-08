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