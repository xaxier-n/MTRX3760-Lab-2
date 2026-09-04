// #include "CRender.h"

#include <iostream>
#include <string>

class CController
{
    public:
        virtual void Step() = 0;
};

class CPose
{
    public:
        CPose(float& startingX, float& startingY, float& startingDir);
        float GetX() {return mX;}
        float GetY() {return mY;}
        float GetDir() {return mDir;}
        virtual ~CPose();

    private:
        float mX;           // units
        float mY;           // units
        float mDir;         // degrees from east (CCW 0-360)
};

class CRobot
{
    public:
        CRobot( float& startingX, float& startingY, float& startingDir,
                std::string& aLabel);
        float GetX();
        float GetY();
        float GetDir();
        float GetLeftSpeed() {return mLeftSpeed;}
        float GetRightSpeed() {return mRightSpeed;}
        ~CRobot();

    private:
        CController* mController;
        CPose mPose;
        float mLeftSpeed;
        float mRightSpeed;
        std::string mLabel;
        
};

//---CRobot Implementation----------------------------------------
CRobot::CRobot(float& startingX, float& startingY, float& startingDir,
    std::string& aLabel)
    : mPose(startingX, startingY, startingDir),
      mLeftSpeed(0.0),
      mRightSpeed(0.0),
      mLabel(aLabel)
{
    std::cout << "Ctor CRobot " << mLabel << std::endl;
}

float CRobot::GetX()
{
    return mPose.GetX();
}

float CRobot::GetY()
{
    return mPose.GetY();
}

float CRobot::GetDir()
{
    return mPose.GetDir();
}

CRobot::~CRobot()
{
    std::cout << "Dtor CRobot " << mLabel << std::endl;
}


//---CPose Implementation-----------------------------------------
CPose::CPose(float& startingX, float& startingY, float& startingDir)
    : mX(startingX), mY(startingY), mDir(startingDir)
{
    std::cout << "Ctor CPose" << std::endl;
    std::cout << "Starting pose: [" << mX << ", " << mY << ", "
              << mDir << "]" << std::endl;
}

CPose::~CPose()
{
    std::cout << "Dtor CPose" << std::endl;
}

int main()
{
    return 0;
}