#ifndef SPATIAL_PARTITION_H
#define SPATIAL_PARTITION_H

#include <iostream>
#include "rigidBody.h"

///@brief Spatial Partitioning Class for broad phase collision detection. Used to split the world into separate cells.
/// Based on the location in space of the rigid bodies, each are stored into array of rigid bodies to be further compared for each cell.
/// If rigid body overlaps two or more cells then this rigid body is stored in all bordering cells to be compared.
/// Note : This class is incomplete and not yet implemented.
///@file spatialPartition.h
///@author Carla Moy
///@class SpatialGrid
class RigidBody;

class SpatialGrid
{
public:
    ///@brief Constructor for SpatialGrid
    SpatialGrid()
    {
      for(int x=0; x<NUM_CELLS; ++x)
      {
        for(int y=0; y<NUM_CELLS; ++y)
        {
          for(int z=0; z<NUM_CELLS; ++z)
          {
            cells[x][y][z] = nullptr;
          }
        }
      }
    }

    ///@brief Method for adding a rigid body object
    void addEntity(std::unique_ptr<RigidBody> _rigidBody);

    ///@brief Const intergers for the cell size and number of cells
    static const int NUM_CELLS = 64;//512;
    static const int CELL_SIZE = 50;//25;

private:
    ///@brief Unique pointer for storing rigid bodies into the cells
    std::unique_ptr<RigidBody> cells[NUM_CELLS][NUM_CELLS][NUM_CELLS];
    ///@brief Vector for the minimum bound of the world (The same as the ground wall bounds in PhysicsEngine class)
    ngl::Vec3 m_minBound = ngl::Vec3(-100.0f, 0.0f, -100.0f);
};



#endif
