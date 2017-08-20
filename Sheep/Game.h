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
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif //_USE_MATH_DEFINES
#include <math.h>
#include <irrKlang.h>

#include "TextUtil.h"
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
	GAME_MENU,
	GAME_PLAYING,
	GAME_END
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// Game state
	GameState State;
	GLboolean gamestateInitialized;
	GLuint Width, Height;
	
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
	SpriteRenderer* textRenderer;

	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state
	void InitGamestate();
	void InitGraphics();
	// clear game state
	void clearGamestate();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void RenderGame(GLfloat dt);

	// other global and debugging stuff
	GLfloat gameTime = 0;
	GLint gameScore = 0;
	GLint incDebug = 0;
};

#endif
