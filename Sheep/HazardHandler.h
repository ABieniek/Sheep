#ifndef HAZARD_HANDLER_H
#define HAZAR_DHANDLER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Hazard.h"
#include "Rocket.h"
#include "Lazer.h"

#include <math.h>
#include <vector>
#include <algorithm>
#include <stdlib.h> // srand, rand
#include <time.h> // time

enum Difficulty
{
	DEBUG = 0,
	SIMPLE,
	EASY,
	MEDIUM,
	HARD,
	IMPOSSIBLE
};

class HazardHandler
{
public:
	vector<Lazer*> lazers;
	vector<Rocket*> rockets;
	GLfloat width, height;
	Difficulty difficulty;
	
	// constructors
	HazardHandler(Difficulty argDifficulty, GLfloat argWidth, GLfloat argHeight);
	// generating hazards

	// updating game logic
	void update(vector<Unit*>& argUnits, GLfloat deltaTime);
	// rendering - I'll separate rendering of hazards because I want some below and some above the units
	void drawLazers(SpriteRenderer& renderer);
	void drawRockets(SpriteRenderer& renderer);

};

#endif
