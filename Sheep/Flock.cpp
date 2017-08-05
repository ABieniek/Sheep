#include "Flock.h"

Flock::Flock(GLfloat argWidth, GLfloat argHeight)
{

	worldWidth = argWidth;
	worldHeight = argHeight;

	// set mins and maxes to ridiculous values so they will inevitably be updated
	minX = argWidth;
	maxX = 0;
	minY = argHeight;
	maxY = 0;
}

void Flock::add(Unit* argUnit)
{
	units.push_back(argUnit);

	// handle calculation of new center
	if (argUnit->position.x < minX)
		minX = argUnit->position.x;
	if (argUnit->position.x > maxX)
		maxX = argUnit->position.x;
	if (argUnit->position.y < minY)
		minY = argUnit->position.y;
	if (argUnit->position.y > maxY)
		maxY = argUnit->position.y;
}

glm::vec2 Flock::center()
{
	return glm::vec2((maxX + minX) / 2, (maxY + minY) / 2);
}

void Flock::setDestination(glm::vec2 argDestination)
{
	// find the farthest point that each unit can travel
	// we're essentially subtracting by the vector of maximum x and y penetrations
	// that would result if our units left the bounds of the world
	glm::vec2 additionVector = argDestination - center();
	for (unsigned int i = 0; i < units.size(); i++)
	{
		// X
		if (minX + additionVector.x < units[0]->radius())
			additionVector.x = units[0]->radius() - minX;
		if (maxX + additionVector.x > worldWidth - units[0]->radius())
			additionVector.x = worldWidth - units[0]->radius() - maxX;
		if (minY + additionVector.y < units[0]->radius())
			additionVector.y = units[0]->radius() - minY;
		if (maxY + additionVector.y > worldHeight - units[0]->radius())
			additionVector.y = worldHeight - units[0]->radius() - maxY;
	}

	// above, the use of units[0] to get a radius is very hacky
	// as of now, I only anticipate having all units of the game to have the same size
	// I would pretty heavily need to modify the member variables of Flock if I were to use
	// units of varying sizes

	for (unsigned int i = 0; i < units.size(); i++)
	{
		// new destination is equal to the position of the unit
		// plus the vector from the flock's center to the new point
		// units[i]->setDestination(additionVector);
		units[i]->setDestination(units[i]->position + additionVector);
	}
}

void recreateFlocks(vector<Unit*>& argUnits, vector<Flock>& argFlocks, GLfloat argWidth, GLfloat argHeight, GLfloat distanceMax)
{
	// idea for algorithm: https://stackoverflow.com/questions/3937663/2d-point-clustering/3939542#3939542

	//destroy previous flock stuff
	while (argFlocks.size())
	{
		argFlocks.pop_back();
	}
	// use a tuple to label units as assigned or unassigned
	// index of argUnits will correspond with same index of indexAssignStatus
	vector<GLboolean> indexAssignStatus;
	for (unsigned int i = 0; i < argUnits.size(); i++)
		indexAssignStatus.push_back(GL_FALSE);	//initialize all to false because no unit has been assigned

	for (unsigned int i = 0; i < argUnits.size(); i++)
	{
		// if the unit has been assigned to a group, skip him
		if (indexAssignStatus[i]) continue;
		// otherwise, he must be the start of a group
		argFlocks.push_back(Flock(argWidth, argHeight));
		argFlocks[argFlocks.size() - 1].add(argUnits[i]);
		indexAssignStatus[i] = true;
		// start appending other units to the group
		for (unsigned int j = 0; j < argUnits.size(); j++)
		{
			// if the unit has already been assigned, don't look at him again
			if (i == j) continue;
			if (!indexAssignStatus[j] && closeEnough(argUnits[i], argUnits[j], distanceMax))
			{
				argFlocks[argFlocks.size() - 1].add(argUnits[j]);
				indexAssignStatus[j] = true;
			}
			for (unsigned int k = 0; k < argUnits.size(); k++)
			{
				// if the unit has already been assigned, don't look at him again
				if (!indexAssignStatus[j]) continue;
				if (indexAssignStatus[k]) continue;
				if (j == k) continue;
				if (closeEnough(argUnits[j], argUnits[k], distanceMax))
				{
					argFlocks[argFlocks.size() - 1].add(argUnits[k]);
					indexAssignStatus[k] = true;
					j = 0;
				}
			}
		}
	}
}

bool closeEnough(Unit* unit1, Unit* unit2, GLfloat distanceTolerance)
{
	return closeEnough(unit1->position, unit2->position, distanceTolerance);
}

bool closeEnough(glm::vec2 position1, glm::vec2 position2, GLfloat distanceTolerance)
{
	return (norm(position2 - position1) < distanceTolerance);
}
