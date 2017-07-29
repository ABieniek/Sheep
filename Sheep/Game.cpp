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
#include <vector>

using namespace std;
using namespace irrklang;
ISoundEngine* SoundEngine = createIrrKlangDevice();

// ugly constants
const static int selectRange = 25;

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
	glm::vec2 locs[] = { glm::vec2(0, 0), glm::vec2(750, 0), glm::vec2(0, 550), glm::vec2(750, 550), glm::vec2(400, 250) };
	for (int i = 0; i < 5; i++)
	{
		units.push_back(Unit(locs[i], glm::vec2(50, 50),
			ResourceManager::GetTexture("sheep"), glm::vec3(1.0f, 1.0f, 1.0f), true, .1));
	}
	
	

}

void Game::Update(GLfloat dt)
{
	// updating values in units
	for (int i = 0; i < units.size(); i++)
	{
		units[i].move();
	}
}

void Game::ProcessInput(GLfloat dt)
{
	// selection input
	if (mbButton == GLFW_MOUSE_BUTTON_LEFT && mbAction == GLFW_PRESS && mbActionPrev == GLFW_RELEASE)
	{
		// place first point of selection box
		selectPosStart = glm::vec2(mXpos, mYpos);
	}
	if (mbButton == GLFW_MOUSE_BUTTON_LEFT && mbActionPrev != GLFW_RELEASE && mbAction == GLFW_RELEASE)
	{
		// place second point of selection box
		selectPosEnd = glm::vec2(mXpos, mYpos);
		// for convenience of calculation, I'm gonna swap around the selection box vertices
		// so that the start is at the top left and the end is at the bottom right
		if (selectPosStart.x > selectPosEnd.x)
			swap(selectPosStart.x, selectPosEnd.x);
		if (selectPosStart.y > selectPosEnd.y)
			swap(selectPosStart.y, selectPosEnd.y);

		// select units within bounds
		for (int i = 0; i < units.size(); i++)
		{
			// if within box, select unit
			if (((units[i].center().x + units[i].size.x / 2) > selectPosStart.x)
				&& ((units[i].center().x - units[i].size.x / 2) < selectPosEnd.x)
				&& ((units[i].center().y + units[i].size.y / 2) > selectPosStart.y)
				&& ((units[i].center().y - units[i].size.y / 2) < selectPosEnd.y))
				units[i].select();
			//if not within box
			else
			{
				// if not holding shift, deselect
				if (mbMods != GLFW_MOD_SHIFT)
					units[i].deselect();
			}
		}
		// clear selection box positions
		selectPosStart = glm::vec2(-100.0, -100.0);
		selectPosEnd = glm::vec2(-100.0, -100.0);
	}
	/*
	for (int i = 0; i < unitsSize; i++)
		{
			if (abs(units[i]->position.x + selectRange - mXpos) <= selectRange
				&& abs(units[i]->position.y + selectRange - mYpos) <= selectRange)
			{
				units[i]->select();
			}
			else if (mbMods != GLFW_MOD_SHIFT)
			{
				units[i]->deselect();
			}
		}*/
	// movement input
	else if (mbButton == GLFW_MOUSE_BUTTON_RIGHT && mbAction == GLFW_PRESS)
	{
		for (int i = 0; i < units.size(); i++)
		{
			if (units[i].selected)
			{
				units[i].setDestination(glm::vec2(mXpos-25, mYpos-25));
			}
		}
	}
	mbButtonPrev = mbButton;
	mbActionPrev = mbAction;
	mbModsPrev = mbMods;
}

void Game::Render()
{	
	Renderer->DrawSprite(ResourceManager::GetTexture("background"),
		glm::vec2(0, 0), glm::vec2(800, 600), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	
	/*for (Drawable* e : drawables)
	{
		e->draw(*Renderer);
	}*/
	for (int i = 0; i < units.size(); i++)
		units[i].draw(*Renderer);
}

