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
        // aLabel: name used in on-screen/console reporting. apController: the
        // steering behaviour to drive this robot; CRobot takes ownership and
        // deletes it in the destructor. arRender: the shared window/renderer
        // this robot draws itself into. arTrack: the loop this robot senses
        // and is judged against (mLine for the line-follower, mWalls for the
        // wall-follower) - also supplies the robot's starting pose.
        // aBodyColour/aTrailColour: this robot's on-screen colours.
        CRobot( std::string aLabel, CController* apController,
                CRender& arRender, const CLoopReader& arTrack,
                Color aBodyColour, Color aTrailColour );
        virtual ~CRobot();   // deletes mController

        void Update();       // one simulation step: ask the controller for wheel speeds, move, check collision
        void Draw() const;   // draw the trail, body and heading nose

        //---Access---
        const std::string& GetLabel() const { return mLabel; }
        float GetX() const { return mPose.mPosition.x; }
        float GetY() const { return mPose.mPosition.y; }
        float GetDir() const { return mPose.mHeading; }   // radians, CW from +x
        float GetLeftSpeed() const { return mLeftSpeed; }
        float GetRightSpeed() const { return mRightSpeed; }

        // End-of-run reporting, for the pass/fail gate
        int GetUpdateCount() const { return mUpdateCount; }
        int GetCollisionCount() const { return mCollisionCount; }

    private:
        // Private helper functions
        bool HasCollided( const CLoopReader& aTrack ) const;   // true if the body circle overlaps any segment of aTrack

        // Fixed dimensions
        static const float kWheelBase;     // distance between the two wheels
        static const float kRadius;        // drawn body radius, and collision radius
        static const float kFixedTimestep; // seconds simulated per Update() call

        // Reference member variables
        CController* mController;      // steering behaviour; owned by this robot
        CRender& mrRender;              // shared renderer this robot draws into
        const CLoopReader& mrTrack;     // the loop this robot senses and is checked for collision against

        // Member classes and variables
        CPose mPose;                    // current position and heading
        float mLeftSpeed;               // current left wheel speed
        float mRightSpeed;              // current right wheel speed
        std::string mLabel;             // name used in reporting
        std::vector<Vec2D> mTrail;      // every past position, for drawing the trail
        int mUpdateCount;               // number of Update() calls so far
        int mCollisionCount;            // number of collisions detected so far
        bool mWasColliding;             // collision state on the previous Update(), so collisions are only counted once per contact

        // Draw colours
        Color mBodyColour;    // colour this robot's body is drawn in
        Color mTrailColour;   // colour this robot's trail is drawn in
};

#endif
