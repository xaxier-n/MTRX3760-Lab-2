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
        // Ctor
        // aAngleOffset: the sensor's mounting angle, in radians, measured CW
        // from the robot's own heading (e.g. 0 = straight ahead, +90deg = right side).
        CDistSensor( float aAngleOffset );

        // Public interface
        // Casts a ray from aPose, in this sensor's direction, and returns the
        // distance to the nearest segment of aVertices it hits (or
        // kMaxSensorRange if it hits nothing).
        float GetReading( const CPose& aPose, const std::vector<Vec2D>& aVertices ) const;

    private:
        // Member variables
        float mOffset;                     // mounting angle offset, radians CW from heading
        static const float kEpsilon;
        static const float kMaxSensorRange;

        // Private helper functions
        // Ray/segment intersection: how far along the ray (from aOrigin, in
        // direction aDir) it first crosses the segment (aSegStart, aSegEnd).
        // Returns kMaxSensorRange if the ray misses the segment entirely.
        float CheckSegment( const Vec2D& aDir, const Vec2D& aOrigin,
                            const Vec2D& aSegStart, const Vec2D& aSegEnd ) const;
};

#endif
