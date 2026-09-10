//-----------------------------------------------------------------------------
// CGeometry.cpp
//-----------------------------------------------------------------------------
#include "CGeometry.h"

#include <cmath>
#include <algorithm>


const float CGeometry::kParallelEpsilon = 1e-6f; //Threshold for considering two vectors to be parallel

float CGeometry::DistanceFromPointToSeg( Vec2D aPoint, Vec2D aSegStart, Vec2D aSegEnd )
{
    Vec2D SegVector = { aSegEnd.x - aSegStart.x, aSegEnd.y - aSegStart.y }; //Vector from start to end of segment
    Vec2D PointVector = { aPoint.x - aSegStart.x, aPoint.y - aSegStart.y }; //Vector from start of segment to point

    float SegLengthSquared = SegVector.x * SegVector.x + SegVector.y * SegVector.y; //Squared length of the segment

    float PositionAlongSeg = 0.0f;
    if( SegLengthSquared > kParallelEpsilon ) //Avoid divide by zero
    {
        PositionAlongSeg = ( PointVector.x * SegVector.x + PointVector.y * SegVector.y ) / SegLengthSquared; //Project point onto segment
        PositionAlongSeg = std::max( 0.0f, std::min( 1.0f, PositionAlongSeg ) ); //Clamp to segment
    }

    //Find the closest point on the segment to the point
    Vec2D ClosestPoint = {
        aSegStart.x + SegVector.x * PositionAlongSeg,
        aSegStart.y + SegVector.y * PositionAlongSeg
    };

    //Calculate the distance from the point to the closest point on the segment
    float DistX = aPoint.x - ClosestPoint.x;
    float DistY = aPoint.y - ClosestPoint.y;
    return std::sqrt( DistX * DistX + DistY * DistY ); //Return distance from point to closest point on segment
}
