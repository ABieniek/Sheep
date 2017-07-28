/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;
using namespace irrklang;
ISoundEngine* SoundEngine = createIrrKlangDevice();

// ugly constants
const static int selectRange = 25;

// unit stuff
Unit* units[1024];
static int unitsSize = 0;
int unitsSizeMax = 1024;

SpriteRenderer* Renderer;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("Shaders/sprite.vs", "Shaders/sprite.fs", nullptr, "sprite");

	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	// Load textures
	ResourceManager::LoadTexture("Textures/TempSheep.png", true, "sheep");
	ResourceManager::LoadTexture("Textures/GrassBackground.png", GL_TRUE, "background");
	
	// Set Game Variables
	//Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	glm::vec2 locs[] = { glm::vec2(100, 100), glm::vec2(750, 0), glm::vec2(0, 550), glm::vec2(750, 550), glm::vec2(400, 250) };
	unitsSize = 5;
	for (int i = 0; i < unitsSize; i++)
	{
		units[i] = new Unit(locs[i], glm::vec2(50, 50),
			ResourceManager::GetTexture("sheep"), glm::vec3(1.0f, 1.0f, 1.0f), true, 1.0f);
	}
	
	

}

void Game::Update(GLfloat dt)
{
	// updating values in units
	for (int i = 0; i < unitsSize; i++)
	{
		units[i]->move();
	}
}

void Game::ProcessInput(GLfloat dt)
{
	if (mbButton == GLFW_MOUSE_BUTTON_LEFT && mbAction == GLFW_PRESS)
	{
		for (int i = 0; i < unitsSize; i++)
		{
			if (abs(units[i]->position.x + selectRange - mXpos) <= selectRange
				&& abs(units[i]->position.y + selectRange - mYpos) <= selectRange)
			{
				units[i]->select();
			}
			else
			{
				units[i]->deselect();
			}
		}
	}
	if (mbButton == GLFW_MOUSE_BUTTON_RIGHT && mbAction == GLFW_PRESS)
	{
		for (int i = 0; i < unitsSize; i++)
		{
			if (units[i]->selected)
			{
				units[i]->setDestination(glm::vec2(mXpos, mYpos));
			}
		}
	}
}

void Game::Render()
{	
	Renderer->DrawSprite(ResourceManager::GetTexture("background"),
		glm::vec2(0, 0), glm::vec2(800, 600), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	
	/*for (Drawable* e : drawables)
	{
		e->draw(*Renderer);
	}*/
	for (int i = 0; i < unitsSize; i++)
		units[i]->draw(*Renderer);
}

