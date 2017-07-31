#ifndef FLOCK_H
#define FLOCK_H

#include <iostream>
#include <vector>
#include "Unit.h"

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
	glm::vec2 center;

	// constructor
	Flock(GLfloat, GLfloat);
	// aggregating units into the flock
	void add(Unit* argUnit);
	// position
	glm::vec2 center();
	// movement
	void setDestination(glm::vec2 argDestination);
};

#endif