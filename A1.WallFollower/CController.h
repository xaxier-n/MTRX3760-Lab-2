//-----------------------------------------------------------------------------
// CController.h
// The base class for all robot controllers, which defines the interface for controlling a robot.
//-----------------------------------------------------------------------------

#ifndef CCONTROLLER_H
#define CCONTROLLER_H

struct CPose;
class CLoopReader;

class CController
{
    public:
        // Interface
        virtual ~CController () {}   // virtual so deleting via a CController* (as CRobot does) destroys the real derived controller

        // Called once per simulation step. Implementations read the robot's
        // current aPose and whatever they can see of aTrack, then write the
        // wheel speeds they want into arLeftSpeed/arRightSpeed.
        virtual void Step( const CPose& aPose, const CLoopReader& aTrack, float& arLeftSpeed, float& arRightSpeed ) = 0;
};

#endif
