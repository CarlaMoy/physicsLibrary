#include "spatialPartition.h"


void SpatialGrid::addEntity(std::unique_ptr<RigidBody> _rigidBody)
{
  //Determine which grid cell the rigid body is in
  int cellX = (int)((_rigidBody->getPosition().m_x - m_minBound.m_x) / CELL_SIZE);
  int cellY = (int)((_rigidBody->getPosition().m_y - m_minBound.m_y) / CELL_SIZE);
  int cellZ = (int)((_rigidBody->getPosition().m_z - m_minBound.m_z) / CELL_SIZE);

  //Add to the front of the list for the cell the rigid body is in
  //_rigidBody->m_prev = nullptr;
 // _rigidBody->m_next = cells[cellX][cellY][cellZ]
}
