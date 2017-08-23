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
#include "Button.h"
#include "InputHandler.h"


// Represents the current state of the game
enum GameState {
	GAME_START,
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
	static GameState State;
	static GLboolean gamestateInitialized;
	static GLuint Width, Height;
	
	// units
	static vector<Unit*> units;
	static vector<Unit*> selectedUnits;
	static vector<Flock> flocks;
	
	// hazards & powerups
	static HazardHandler* hazardHandler;
	static Difficulty difficulty;
	static vector<PowerUp*> powerUps;
	static GLfloat powerUpSpawnTime;

	// other stuff to draw
	static Drawable* selectionBox;

	// menu stuff
	static Button *buttonStart, *buttonSetSimple, *buttonSetNormal, *buttonEnd;

	// renderers
	static SpriteRenderer* spriteRenderer;
	static SpriteRenderer* selectionBoxRenderer;
	static SpriteRenderer* textRenderer;

	// Constructor/Destructor
	~Game();
	// Initialize game state
	static void InitVariables(GLuint width, GLuint height);
	static void InitGamestate();
	static void InitMenu();
	static void InitGraphics();
	// clear game state
	static void clearGamestate();
	// gamestate handling callbacks
	static void cbStart() {InitGamestate(); State = GAME_PLAYING; };
	static void cbSetSimple() { difficulty = SIMPLE;};
	static void cbSetNormal() {difficulty = NORMAL;};
	static void cbRestart() { State = GAME_START; clearGamestate(); }
	// GameLoop
	static void ProcessInput(GLfloat dt);
	static void UpdateGame(GLfloat dt);
	static void UpdateMenu(GLfloat dt);
	static void RenderGame(GLfloat dt);
	static void RenderMenu(GLfloat dt);

	// other global and debugging stuff
	static GLfloat gameTime;
	static GLint gameScore;
	static GLint incDebug;
};

#endif
