//-----------------------------------------------------------------------------
// CDistSensor.h
// The distance sensor class, which returns the distance from the nearest wall 
// in a straight line
//-----------------------------------------------------------------------------
#ifndef CDISTSENSOR_H
#define CDISTSENSOR_H

#include "CGeometry.h"
#include "CLoopReader.h"
#include "CRender.h"

class CDistSensor 
{
    public:
        CDistSensor( float aAngleOffset );

        float GetReading( const CPose& aPose, const std::vector<Vec2D>& aVertices ) const;

    private:
        float mOffset;
        static const float kEpsilon;
        static const float kMaxSensorRange;
        
        float CheckSegment( const Vec2D& aDir, const Vec2D& aOrigin, 
                            const Vec2D& aSegStart, const Vec2D& aSegEnd ) const;
};

#endif