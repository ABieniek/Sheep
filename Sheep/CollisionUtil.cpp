#include "CollisionUtil.h"

GLboolean doesPenetrate(glm::vec2 position1, GLfloat radius1, glm::vec2 position2, GLfloat radius2)
{
	// one unit is within another unit's hitbox if the sum of their radii is smaller than the distance between them
	return (glm::distance(position1, position2) < (radius1 + radius2));
}

GLboolean doesPenetrate(Unit & unit1, Unit & unit2)
{
	return (doesPenetrate(unit1.position, unit1.radius(), unit2.position, unit2.radius()));
}

glm::vec2 penetrationVector(glm::vec2 position1, GLfloat radius1, glm::vec2 position2, GLfloat radius2)
{
	// for each component, the amount of penetration should be r1 + r2 - (c1 - c2)
	return -(glm::normalize(position2 - position1) * ((norm(position2 - position1)) - (radius2 + radius1)));

	// @TODO as of right now, this code doesn't handle the case that, within one frame, the units have concentric hurtboxes
	// the position would be moved by 2r, so they would indeed be placed such that their borders are contiguous
	// but if the distance is zero, then the direction of movement can't be determined
}

glm::vec2 penetrationVector(Unit & unit1, Unit & unit2)
{
	return penetrationVector(unit1.position, unit1.radius(), unit2.position, unit2.radius());
}

GLfloat norm(glm::vec2 vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}
