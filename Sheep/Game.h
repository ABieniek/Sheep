/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>
#define _USE_MATH_DEFINES
#include <math.h>

#include <irrKlang.h>
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Drawable.h"
#include "Unit.h"
#include "Flock.h"
#include "CollisionUtil.h"
#include "Hazard.h"
#include "Rocket.h"
#include "Lazer.h"
#include "HazardHandler.h"
#include "PowerUp.h"


// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// Game state
	GameState				State;
	GLuint					Width, Height;
	
	/// controls
	// key
	GLboolean keys[1024];
	int scancode;
	int action;
	int mode;
	// mouse position
	double mXpos;
	double mYpos;
	// mouse button - this frame
	int mbButton;
	int mbAction;
	int mbMods;
	// mouse button - last frame
	int mbButtonPrev;
	int mbActionPrev;
	int mbModsPrev;

	// units
	vector<Unit*> units;
	vector<Unit*> selectedUnits;
	vector<Flock> flocks;
	
	// hazards & powerups
	HazardHandler* hazardHandler;
	vector<PowerUp*> powerUps;

	// other stuff to draw
	Drawable* selectionBox;

	// renderers
	SpriteRenderer* spriteRenderer;
	SpriteRenderer* selectionBoxRenderer;

	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

	// other global stuff
	GLfloat gameTime = 0;
	GLint gameScore = 0;
};

#endif
