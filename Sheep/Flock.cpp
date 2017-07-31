#include "Flock.h"

Flock::Flock(GLfloat argWidth, GLfloat argHeight)
{
	worldWidth = argWidth;
	worldHeight = argHeight;
}

void Flock::add(Unit* argUnit)
{
	units.push_back(argUnit);
	// handle calculation of new center
	if (argUnit->position.x < minX)
		minX = argUnit->position.x;
	else if (argUnit->position.x > maxX)
		maxX = argUnit->position.x;
	if (argUnit->position.y < minY)
		minY = argUnit->position.y;
	if (argUnit->position.y > minY)
		minY = argUnit->position.y;
}

glm::vec2 Flock::center()
{
	return glm::vec2((maxX - minX) / 2, (maxY - minY) / 2);
}

void Flock::setDestination(glm::vec2 argDestination)
{
	// find the farthest point that each unit can travel
	// we're essentially subtracting by the vector of maximum x and y penetrations
	// that would result if our units left the bounds of the world
	glm::vec2 additionVector = argDestination + center();
	for (unsigned int i = 0; i < units.size(); i++)
	{
		// X
		if (units[i]->position.x + additionVector.x < units[i]->radius())
			additionVector.x -= units[i]->radius() - argDestination.x;
		if (units[i]->position.x + additionVector.x > worldHeight - units[i]->radius())
			additionVector.x -= (worldWidth - units[i]->radius()) - argDestination.x;
		// Y
		if (units[i]->position.y + additionVector.y < units[i]->radius())
			additionVector.y -= units[i]->radius() - argDestination.y;
		if (units[i]->position.y + additionVector.y > worldHeight - units[i]->radius())
			additionVector.y -= (worldHeight - units[i]->radius()) - argDestination.y;
	}

	for (unsigned int i = 0; i < units.size(); i++)
	{
		// new destination is equal to the position of the unit
		// plus the vector from the flock's center to the new point
		units[i]->setDestination(units[i]->position + additionVector);
	}
}

void recreateFlocks(vector<Unit>& argUnits, vector<Flock>& argFlocks, GLfloat argWidth, GLfloat argHeight, GLfloat distanceMax)
{
	// use clustering algorithm to put units together into clusters
	for (unsigned int i = 0; i < argUnits.size(); i++)
	{
		// if the unit is not selected, then we won't be giving him a new destination
		// so skip him
		if (!argUnits[i].selected)
			continue;
		// keep track of if we've put this unit into a flock
		// otherwise, make a new flock
		GLboolean added = false;
		for (unsigned int j = 0; j < argFlocks.size(); j++)
		{
			for (unsigned int k = 0; k < argFlocks[j].units.size(); k++)
			{
				if (closeEnough(argUnits[i], *argFlocks[j].units[k],
					(argUnits[i].radius() + argFlocks[j].units[k]->radius() + distanceMax)))
				{
					argFlocks[j].add(&argUnits[i]);
					added = true;
					continue;
				}
			}
		}
		// if we haven't added the unit to a flock, make a new one and add it
		if (!added)
		{
			argFlocks.push_back(Flock(argWidth, argHeight));
			argFlocks[argFlocks.size() - 1].add(&argUnits[i]);
		}
	}
}

bool closeEnough(Unit & unit1, Unit & unit2, GLfloat distanceTolerance)
{
	return closeEnough(unit1.position, unit2.position, distanceTolerance);
}

bool closeEnough(glm::vec2 position1, glm::vec2 position2, GLfloat distanceTolerance)
{
	return (norm(position2 - position1) < distanceTolerance);
}
