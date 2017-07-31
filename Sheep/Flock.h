#ifndef FLOCK_H
#define FLOCK_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Unit.h"
#include "CollisionUtil.h"

class Flock
{
public:
	vector<Unit*> units;
	GLfloat velocity;
	glm::vec2 destination;
	glm::vec2 position;
	GLfloat angle;
	GLfloat worldWidth, worldHeight;	// holds the bounds of the world so that the movement 
										// can head out of the bounds of the world
	GLfloat minX, minY, maxX, maxY;

	// constructor
	Flock(GLfloat, GLfloat);
	// aggregating units into the flock
	void add(Unit* argUnit);
	// position
	glm::vec2 center();
	// movement
	void setDestination(glm::vec2 argDestination);
};

/// helper functions
// function that will put units into flocks accordingly
void recreateFlocks(vector<Unit>& argUnits, vector<Flock>& argFlocks, GLfloat argWidth, GLfloat argHeight, GLfloat distanceMax);
// function that will test if units are close enough to be put into the same cluster
bool closeEnough(Unit& unit1, Unit& unit2, GLfloat distanceTolerance);
bool closeEnough(glm::vec2 position1, glm::vec2 position2, GLfloat distanceTolerance);

#endif