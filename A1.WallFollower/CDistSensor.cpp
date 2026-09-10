//-----------------------------------------------------------------------------
// CDistSensor.cpp 
//-----------------------------------------------------------------------------

#include "CDistSensor.h"
#include "CGeometry.h"
#include "CLoopReader.h"
#include "CRender.h"

#include <cmath>

const float CDistSensor::kEpsilon = 1e-6f;
const float CDistSensor::kMaxSensorRange = 1e6f;

CDistSensor::CDistSensor( float aAngleOffset )
    : mOffset( aAngleOffset )
{
}

float CDistSensor::GetReading( const CPose& aPose, const std::vector<Vec2D>& aVertices) const
{
    float Angle = aPose.mHeading + mOffset;
    Vec2D Dir = { std::cos( Angle ), std::sin(Angle) };     // unit vector
    Vec2D Origin = aPose.mPosition;

    float t;
    float ClosestT = kMaxSensorRange;   // sentinel: "nothing hit within range"
    Vec2D Previous = aVertices.back();

    for( const Vec2D& Current : aVertices )
    {
        t = CheckSegment( Dir, Origin, Previous, Current );
        if( t < ClosestT )
        {
            ClosestT = t;
        }
        Previous = Current;
    }
    return ClosestT;
    

}

float CDistSensor::CheckSegment( const Vec2D& aDir, const Vec2D& aOrigin, 
                                 const Vec2D& aSegStart, const Vec2D& aSegEnd ) const
{
    Vec2D SegVec = { aSegEnd.x - aSegStart.x, aSegEnd.y - aSegStart.y };
    Vec2D Diff   = { aSegStart.x - aOrigin.x, aSegStart.y - aOrigin.y };

    float t_return = kMaxSensorRange;     // Sentinel value

    float Denom = aDir.x * SegVec.y - aDir.y * SegVec.x;
    if( std::fabs( Denom ) > kEpsilon )
    {
        float t = ( Diff.x * SegVec.y - Diff.y * SegVec.x ) / Denom;
        float u = ( Diff.x * aDir.y   - Diff.y * aDir.x   ) / Denom;

        if( t >= 0.0f && u >= 0.0f && u <= 1.0f )
        { // in front of ray and within segment
            t_return = t;
        }
    }

    return t_return;
    
}