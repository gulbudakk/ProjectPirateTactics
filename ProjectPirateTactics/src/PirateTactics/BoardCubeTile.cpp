#include "BoardCubeTile.h"

VisualGameObject& BoardCubeTile::operator=(VisualGameObject& other)
{
	VisualGameObject::Swap(other);

	return *this;
}
