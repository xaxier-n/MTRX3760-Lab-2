//-----------------------------------------------------------------------------
// CDistSensor.cpp
//
// GetReading() walks every wall segment and keeps the closest ray/segment hit
// (see CheckSegment). CheckSegment solves the standard ray-vs-segment
// intersection: t is how far along the ray the hit is (>=0 means in front of
// the sensor), u is how far along the segment it is (0..1 means within the
// segment's own endpoints, not off one end).
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
    Vec2D Previous = aVertices.back();  // seed with the last vertex, so the first loop
                                         // iteration checks the wraparound segment (last -> first)

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

    // Denom is the (2D) cross product of the ray direction and the segment
    // vector; if it's ~0 the ray and segment are parallel and never cross.
    float Denom = aDir.x * SegVec.y - aDir.y * SegVec.x;
    if( std::fabs( Denom ) > kEpsilon )
    {
        float t = ( Diff.x * SegVec.y - Diff.y * SegVec.x ) / Denom;   // distance along the ray
        float u = ( Diff.x * aDir.y   - Diff.y * aDir.x   ) / Denom;   // position along the segment

        if( t >= 0.0f && u >= 0.0f && u <= 1.0f )
        { // in front of ray and within segment
            t_return = t;
        }
    }

    return t_return;

}
