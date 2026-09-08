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
        virtual ~CController () {}
        virtual void Step( const CPose& aPose, const CLoopReader& aTrack, float& arLeftSpeed, float& arRightSpeed ) = 0;
};

#endif