//-----------------------------------------------------------------------------
// CRobot.h
// The robot class, which contains the robot's pose, wheel speeds, and controller.
//-----------------------------------------------------------------------------
#ifndef CROBOT_H
#define CROBOT_H

#include "CController.h"
#include "CLoopReader.h"
#include "CRender.h"

#include <string>
#include <vector>

class CRobot{
    public:
       //---Ctor/Dtor---
        CRobot( CPose aStartPose, std::string aLabel, CController* apController );
        virtual ~CRobot();

        void Update( const CLoopReader& aTrack );
        void Draw( CRender& aRender ) const;

        //---Access---
        const std::string& GetLabel() const { return mLabel; }
        float GetX() const { return mPose.mPosition.x; }
        float GetY() const { return mPose.mPosition.y; }
        float GetDir() const { return mPose.mHeading; }   // radians, CW from +x
        float GetLeftSpeed() const { return mLeftSpeed; }
        float GetRightSpeed() const { return mRightSpeed; }

        //End-of-run reporting, for the pass/fail gate
        int GetUpdateCount() const { return mUpdateCount; }
        int GetCollisionCount() const { return mCollisionCount; }

    private:
        bool HasCollided( const CLoopReader& aTrack ) const;

        //Fixed dimensions
        static const float kWheelBase;     // distance between the two wheels
        static const float kRadius;        // drawn body radius, and collision radius
        static const float kFixedTimestep; // seconds simulated per Update() call

        CController* mController;
        CPose mPose;
        float mLeftSpeed;
        float mRightSpeed;
        std::string mLabel;
        std::vector<Vec2D> mTrail;
        int mUpdateCount;
        int mCollisionCount;
        bool mWasColliding;
        
};

#endif