//-----------------------------------------------------------------------------
// CGeometry.h
// A collection of geometry functions
//-----------------------------------------------------------------------------

#ifndef CGEOMETRY_H
#define CGEOMETRY_H

#include "CRender.h"

class CGeometry
{
    public:
        // Public interface
    //Returns the distance from aPoint to Segment (aSegStart, aSegEnd)
        static float DistanceFromPointToSeg( Vec2D aPoint, Vec2D aSegStart, Vec2D aSegEnd );

    private:
        // Private consts
        static const float kParallelEpsilon;   // below this squared segment length, treat the segment as a single point
};
#endif
