#include "HazardHandler.h"

HazardHandler::HazardHandler(Difficulty argDifficulty, GLfloat argWidth, GLfloat argHeight,
	Texture2D argLazerSprite, Texture2D argLazerSpriteDetonated,
	Texture2D argRocketSprite, Texture2D argRocketSpriteDetonated, Texture2D argRocketSpriteTarget)
	:difficulty(argDifficulty), width(argWidth), height(argHeight),
	lazerSprite(argLazerSprite), lazerSPriteDetonated(argLazerSpriteDetonated),
	rocketSprite(argRocketSprite), rocketSpriteDetonated(argRocketSpriteDetonated), rocketSpriteTarget(argRocketSpriteDetonated)
{

}

HazardHandler::~HazardHandler()
{
	for (unsigned int i = 0; i < lazers.size(); i++)
		delete lazers[i];
	lazers.clear();
	for (unsigned int i = 0; i < rockets.size(); i++)
		delete rockets[i];
	rockets.clear();
}

void HazardHandler::init()
{
	// random seeds
	srand(time(NULL));
	
	if (difficulty == SIMPLE)
	{
		lazerTimer = 5;
		lazerDuration = .5;
		frequency = 1;
	}
	else
		cout << "difficulty not handled" << endl;
}

void HazardHandler::update(vector<Unit*>& argUnits, GLfloat deltaTime)
{
	// adding new hazards
	generate(deltaTime);
	// updating lazers
	for (unsigned int i = 0; i < lazers.size(); i++)
	{
		lazers[i]->update(deltaTime);
		// if the timer runs out, detonate the lazer
		if (lazers[i]->timer <= 0)
			lazers[i]->detonate(argUnits);
		// if the lazer has expired, remove it from the array of lazers
		if (lazers[i]->duration <= 0)
		{
			delete lazers[i];
			lazers.erase(lazers.begin() + i);
			i--; // push the counter back because the lazer was removed from the array
		}
	}
	// updating rockets
	for (unsigned int i = 0; i < rockets.size(); i++)
	{
		// if the vector isn't empty, give 
		if (!argUnits.empty())
			rockets[i]->update(deltaTime, argUnits[0]);
		// if the timer runs out, detonate the rocket
		if (rockets[i]->timer <= 0 && rockets[i]->position == rockets[i]->destination)
			rockets[i]->detonate(argUnits);
		// if the rocket has expired, remove it from the array of rockets
		if (rockets[i]->duration <= 0)
		{
			delete rockets[i];
			rockets.erase(rockets.begin() + i);
			i--; // push the counter back because the rocket was removed from the array
		}
	}
}

// generation of hazards
void HazardHandler::generate(GLfloat deltaTime)
{
	if (difficulty == SIMPLE)
	{
		simpleGenerate(deltaTime);
	}
	gameTime += deltaTime;
}

void HazardHandler::simpleGenerate(GLfloat deltaTime)
{
	// drop lazer every "frequency" seconds
	if (floor(gameTime/frequency) != floor((gameTime + deltaTime) / frequency))	
	{
		addLazer(glm::vec2(randomFloat(0, width), height / 2), randomFloat(0, M_PI));
	}
}

void HazardHandler::addLazer(glm::vec2 argPosition, GLfloat argAngle)
{
	// x size of 2000 so that it can stretch across screen, corner to corner, worst case
	lazers.push_back(new Lazer(argPosition, glm::vec2(2000, 10),lazerSprite, lazerSPriteDetonated, glm::vec4(1.0f), argAngle,
		GL_TRUE, width, height, lazerTimer, lazerDuration, glm::vec2(0, 0)));
}

void HazardHandler::addRocket()
{

}

GLfloat HazardHandler::randomFloat(GLfloat min, GLfloat max)
{
	// https://stackoverflow.com/a/686373
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max-min)));
}

void HazardHandler::drawLazers(SpriteRenderer& renderer)
{
	for (unsigned int i = 0; i < lazers.size(); i++)
	{
		if (lazers[i]->bDraw)
			lazers[i]->draw(renderer);
	}
}

void HazardHandler::drawRockets(SpriteRenderer& renderer)
{
	for (unsigned int i = 0; i < rockets.size(); i++)
	{
		if (rockets[i]->bDraw)
			rockets[i]->draw(renderer);
	}
}