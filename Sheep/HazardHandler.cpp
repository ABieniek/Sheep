#include "HazardHandler.h"

HazardHandler::HazardHandler(Difficulty argDifficulty, GLfloat argWidth, GLfloat argHeight,
	Texture2D argLazerSprite, Texture2D argLazerSpriteDetonated,
	Texture2D argRocketSprite, Texture2D argRocketSpriteDetonated, Texture2D argRocketSpriteTarget)
	:difficulty(argDifficulty), width(argWidth), height(argHeight),
	lazerSprite(argLazerSprite), lazerSPriteDetonated(argLazerSpriteDetonated),
	rocketSprite(argRocketSprite), rocketSpriteDetonated(argRocketSpriteDetonated), rocketSpriteTarget(argRocketSpriteTarget)
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
		// lazer stats
		lazerTimer = 5;
		lazerDuration = .5;
		lazerFrequency = 5;
		// rocket stats
		rocketFrequency = 15;
		rocketTimer = 10;
		rocketDuration = 1;
		rocketVelocity = 80.f;
		rocketAngularVelocity = .25f;
	}
	else if (difficulty == NORMAL)
	{
		// lazer stats
		lazerTimer = 5;
		lazerDuration = 5;
		lazerFrequency = 3;
		lazerDistribution = new std::normal_distribution<GLfloat>(lazerFrequency, lazerFrequency/4.f);
		nextLazerTime = glfwGetTime() + lazerFrequency;
		// rocket stats
		rocketFrequency = 15;
		rocketTimer = 15;
		rocketDuration = 1;
		rocketVelocity = 100.f;
		rocketAngularVelocity = .5f;
		rocketDistribution = new std::normal_distribution<GLfloat>(rocketFrequency, rocketFrequency/4.f);
		nextRocketTime = glfwGetTime() + rocketFrequency;
		seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
	}
	else
		cout << "difficulty not handled" << endl;
}

void HazardHandler::update(GLfloat deltaTime, vector<Unit*>& argUnits)
{
	// adding new hazards
	generate(deltaTime, argUnits);
	// updating lazers
	for (unsigned int i = 0; i < lazers.size(); i++)
	{
		lazers[i]->update(deltaTime, argUnits);
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
		updateRocketTargets(argUnits);
		rockets[i]->update(deltaTime, argUnits);
		// if the rocket has expired, remove it from the array of rockets
		if (rockets[i]->duration <= 0)
		{
			delete rockets[i];
			rockets.erase(rockets.begin() + i);
			i--; // push the counter back because the rocket was removed from the array
		}
	}
}

void HazardHandler::updateRocketTargets(vector<Unit*>& argUnits)
{
	// for each rocket, we won't choose to update the destination until we make sure
	// that the rocket's target is still in the array
	for (unsigned int i = 0; i < rockets.size(); i++)
	{
		GLboolean targetExists = false;
		for (unsigned int j = 0; j < argUnits.size(); j++)
		{
			if (rockets[i]->targetUnit == argUnits[j])
				targetExists = true;
		}
		if (targetExists)
		{
			rockets[i]->resetDestination();
		}
	}
}

// generation of hazards
void HazardHandler::generate(GLfloat deltaTime, vector<Unit*>& argUnits)
{
	if (difficulty == SIMPLE)
		simpleGenerate(deltaTime, argUnits);
	else if (difficulty = NORMAL)
		normalGenerate(deltaTime, argUnits);
	gameTime += deltaTime;
}

void HazardHandler::simpleGenerate(GLfloat deltaTime, vector<Unit*>& argUnits)
{
	// drop lazers and rockets every "frequency" seconds
	if (differentTimeInterval(gameTime, gameTime + deltaTime, lazerFrequency)) 
	{
		addLazer(glm::vec2(randomFloat(0, width), randomFloat(0, height)), (rand() % 2) * M_PI / 2);
	}
	if (differentTimeInterval(gameTime, gameTime + deltaTime, rocketFrequency))
	{
		addRocket(glm::vec2(-50 + (rand() % 2)*(width + 50), height / 2), argUnits);
	}
}

void HazardHandler::normalGenerate(GLfloat deltaTime, vector<Unit*>& argUnits)
{
	if (gameTime > nextLazerTime)
	{
		addLazer(glm::vec2(randomFloat(0, width), randomFloat(0, height)), (randomFloat(0, M_PI / 2)));
		nextLazerTime += (*lazerDistribution)(generator);
	}
	if (gameTime > nextRocketTime)
	{
		addRocket(glm::vec2(-50 + (rand() % 2)*(width + 50), height / 2), argUnits);
		nextRocketTime += (*rocketDistribution)(generator);
	}
}

void HazardHandler::addLazer(glm::vec2 argPosition, GLfloat argAngle)
{
	// x size of 2000 so that it can stretch across screen, corner to corner, worst case
	lazers.push_back(new Lazer(argPosition, glm::vec2(2000, 10),lazerSprite, lazerSPriteDetonated, glm::vec4(1.0f), argAngle,
		GL_TRUE, width, height, lazerTimer, lazerDuration, glm::vec2(50.f, 10.f)));
}

void HazardHandler::addRocket(glm::vec2 argPosition, vector<Unit*>& argUnits)
{
	// I'm gonna give the dude an angle that always points to the center of the map initially
	GLfloat tempAngle = -atan2(height / 2 - argPosition.y, width / 2 - argPosition.x);
	rockets.push_back(new Rocket(argPosition, glm::vec2(100, 100), rocketSprite, rocketSpriteDetonated, rocketSpriteTarget,
		glm::vec4(1.0f), tempAngle, true, width, height, 
		rocketTimer, rocketDuration, glm::vec2(width / 2, height / 2), rocketVelocity, rocketAngularVelocity));
	// immediately give the rocket a target, a random sheep
	if (!argUnits.empty())
		rockets[rockets.size() - 1]->setTarget(argUnits[rand() % argUnits.size()]);
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