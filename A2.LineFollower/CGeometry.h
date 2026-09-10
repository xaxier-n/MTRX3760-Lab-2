//-----------------------------------------------------------------------------
// CGeometry.h
//
// Shortest distance from a point to a line segment, with the closest point
// clamped to the segment's own endpoints.
//-----------------------------------------------------------------------------

#ifndef CGEOMETRY_H
#define CGEOMETRY_H

#include "CRender.h"

class CGeometry
{
    public:
    //Returns the distance from aPoint to Segment (aSegStart, aSegEnd)
        static float DistanceFromPointToSeg( Vec2D aPoint, Vec2D aSegStart, Vec2D aSegEnd ); 
    
    private:
        static const float kParallelEpsilon;
};
#endif
