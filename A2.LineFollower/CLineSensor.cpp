//-----------------------------------------------------------------------------
// CLineSensor.cpp
//
// Rotates this sensor's fixed (forward, side) mounting offset by the robot's
// current heading to get the sensor's actual position in world space, then
// checks that position against every segment of the track via
// CGeometry::DistanceFromPointToSeg, keeping only the nearest one. The
// sensor counts as "over the line" if that nearest distance is within
// kSensorRadius.
//-----------------------------------------------------------------------------

#include "CLineSensor.h"
#include "CGeometry.h"

#include <cmath>

const float CLineSensor::kSensorRadius = 2.5f; //radius of the sensor
const float CLineSensor::kFarThreshold = 1500.0f; //distance from the line at which the sensor is considered to be over the line

//Constructor
CLineSensor::CLineSensor( float aForwardOffset, float aSideOffset )
    : mForwardOffset( aForwardOffset ),
      mSideOffset( aSideOffset )
{
}

bool CLineSensor::Sense( const CPose& aRobotPose, const CLoopReader& aTrack ) const
{
    //Get the sensor's position in world coordinates
    const float CosHeading = std::cos( aRobotPose.mHeading );
    const float SinHeading = std::sin( aRobotPose.mHeading );

    //Get the sensor's position in world coordinates
    const Vec2D SensorPos{
        aRobotPose.mPosition.x +mForwardOffset * CosHeading - mSideOffset * SinHeading,
        aRobotPose.mPosition.y +mForwardOffset * SinHeading + mSideOffset * CosHeading
    };

    //Get the loop's vertices
    const std::vector<Vec2D>& Vertices = aTrack.GetVertices();
    if( Vertices.empty())
    {
        return false;
    }

    float NearestDist = kFarThreshold; //distance from the sensor to the nearest line segment
    Vec2D Previous = Vertices.back(); //The last vertex is connected to the first

    //Iterate through the loop's vertices, checking the distance from the sensor to each line segment
    for( const Vec2D& Current : Vertices )
    {
        const float Dist = CGeometry::DistanceFromPointToSeg( SensorPos, Previous, Current );
        if( Dist < NearestDist ) //If this segment is closer than the previous closest segment
        {
            NearestDist = Dist; //Update the nearest distance
        }
        Previous = Current; //Update the previous vertex
    }

    return NearestDist < kSensorRadius; //Return true if the sensor is over the line
}
