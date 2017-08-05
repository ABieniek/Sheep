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

enum HazardHandlerDifficulty
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
	
	HazardHandler();
};

#endif
