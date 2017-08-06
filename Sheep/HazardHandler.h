#ifndef HAZARD_HANDLER_H
#define HAZAR_DHANDLER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "Hazard.h"
#include "Rocket.h"
#include "Lazer.h"

#define _USE_MATH_DEFINES
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
	GLfloat gameTime = 0;
	Difficulty difficulty;

	// hazard generation values
	GLfloat frequency = -1;

	// lazer stuff
	GLfloat lazerTimer, lazerDuration;
	Texture2D lazerSprite;
	Texture2D lazerSPriteDetonated;

	// rocket stuff
	GLfloat rocketTimer, rocketDuration;
	Texture2D rocketSprite;
	Texture2D rocketSpriteDetonated;

	
	// constructors and initialization
	HazardHandler(Difficulty argDifficulty, GLfloat argWidth, GLfloat argHeight,
		Texture2D argLazerSprite, Texture2D argLazerSpriteDetonated, 
		Texture2D argRocketSprite, Texture2D argRocketSpriteDetonated);
	~HazardHandler();
	void init();
	// generating hazards
	void generate(GLfloat deltaTime);
	void simpleGenerate(GLfloat deltaTime);
	void addLazer(glm::vec2 argPosition, GLfloat argAngle);
	void addRocket();
	GLfloat randomFloat(GLfloat min, GLfloat max);
	// updating game logic
	void update(vector<Unit*>& argUnits, GLfloat deltaTime);
	// rendering - I'll separate rendering of hazards because I want some below and some above the units
	void drawLazers(SpriteRenderer& renderer);
	void drawRockets(SpriteRenderer& renderer);

};

#endif
