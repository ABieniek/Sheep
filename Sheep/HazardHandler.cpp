#include "HazardHandler.h"

HazardHandler::HazardHandler(Difficulty argDifficulty, GLfloat argWidth, GLfloat argHeight)
	:difficulty(argDifficulty), width(argWidth), height(argHeight)
{

}

void HazardHandler::update(vector<Unit*>& argUnits, GLfloat deltaTime)
{
	// lazers
	for (int i = 0; i < lazers.size(); i++)
	{
		lazers[i]->decreaseTime(deltaTime);
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
	// rockets
	for (int i = 0; i < rockets.size(); i++)
	{
		rockets[i]->decreaseTime(deltaTime);
		// if the timer runs out, detonate the rocket
		if (rockets[i]->timer <= 0)
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