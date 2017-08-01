/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <algorithm>
#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>

#include "game.h"

using namespace std;
using namespace irrklang;
ISoundEngine* SoundEngine = createIrrKlangDevice();

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete spriteRenderer;
	delete selectionBoxRenderer;
	delete selectionBox;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("Shaders/sprite.vs", "Shaders/sprite.fs", nullptr, "sprite");
	ResourceManager::LoadShader("Shaders/selectionBox.vs", "Shaders/selectionBox.fs", nullptr, "selectionBox");

	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("selectionBox").Use().SetInteger("image", 0);
	ResourceManager::GetShader("selectionBox").SetMatrix4("projection", projection);

	// Set render-specific controls
	spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	selectionBoxRenderer = new SpriteRenderer(ResourceManager::GetShader("selectionBox"));

	// Load textures
	ResourceManager::LoadTexture("Textures/TempSheep.png", GL_TRUE, "sheep");
	ResourceManager::LoadTexture("Textures/GrassBackground.png", GL_TRUE, "background");
	ResourceManager::LoadTexture("Textures/White.png", GL_TRUE, "selectionBox");

	
	/// Set Game Variables
	// sheep
	glm::vec2 locs[] = { glm::vec2(0, 0), glm::vec2(750, 0), glm::vec2(0, 550), glm::vec2(750, 550), glm::vec2(400, 250),
						glm::vec2(125, 50), glm::vec2(600, 100), glm::vec2(400, 400), glm::vec2(400, 0), glm::vec2(300, 100),
						glm::vec2(200, 200), glm::vec2(100, 300) };
	for (unsigned int i = 0; i < 12; i++)
	{
		units.push_back(Unit(locs[i], glm::vec2(50, 50),
			ResourceManager::GetTexture("sheep"), glm::vec4(1.0f), true, 0.0f, .1f));
	}
	// selection box - don't draw it initially
	selectionBox = new Drawable(glm::vec2(0, 0), glm::vec2(0,0),
		ResourceManager::GetTexture("selectionBox"), glm::vec4(1.0, 1.0, .4, .25), 0.0, false);
}

void Game::Update(GLfloat dt)
{
	// updating values in units
	for (unsigned int i = 0; i < units.size(); i++)
	{
		units[i].move();
		for (unsigned int j = 0; j < units.size(); j++)
		{
			if (i == j)  // if the unit we're looking at is not the same one we just moved, skip
				continue;
			if (doesPenetrate(units[i], units[j]))
			{
				units[i].position -= penetrationVector(units[i], units[j]);
				if (!units[j].moving)
				{
					units[i].stop();
					units[j].stop();
				}
			}
		}
	}
}

void Game::ProcessInput(GLfloat dt)
{
	// selection input
	if (mbButton == GLFW_MOUSE_BUTTON_LEFT && mbAction == GLFW_PRESS && mbActionPrev == GLFW_RELEASE)
	{
		// place first point of selection box
		selectionBox->position = glm::vec2(mXpos, mYpos);
		selectionBox->size = glm::vec2(0.0);
		selectionBox->bDraw = true;
	}
	if (mbButton == GLFW_MOUSE_BUTTON_LEFT && mbAction == GLFW_PRESS && mbActionPrev == GLFW_PRESS)
	{
		selectionBox->size = glm::vec2(mXpos, mYpos) - selectionBox->position;
	}
	if (mbButton == GLFW_MOUSE_BUTTON_LEFT && mbActionPrev != GLFW_RELEASE && mbAction == GLFW_RELEASE)
	{
		// place second point of selection box - also, stop rendering it
		selectionBox->size = glm::vec2(mXpos, mYpos) - selectionBox->position;
		selectionBox->bDraw = false;
		// for convenience of calculation, I'm gonna force the starting position to be the top-left
		if (selectionBox->size.x < 0)
		{
			selectionBox->size.x *= -1;
			selectionBox->position.x -= selectionBox->size.x;
		}
		if (selectionBox->size.y < 0)
		{
			selectionBox->size.y *= -1;
			selectionBox->position.y -= selectionBox->size.y;
		}


		// select units within bounds
		for (unsigned int i = 0; i < units.size(); i++)
		{
			// if within box, select unit
			if (((units[i].center().x + units[i].size.x / 2) > selectionBox->position.x)
				&& ((units[i].center().x - units[i].size.x / 2) < selectionBox->position.x + selectionBox->size.x)
				&& ((units[i].center().y + units[i].size.y / 2) > selectionBox->position.y)
				&& ((units[i].center().y - units[i].size.y / 2) < selectionBox->position.y + selectionBox->size.y))
				units[i].select();
			//if not within box
			else
			{
				// if not holding shift, deselect
				if (mbMods != GLFW_MOD_SHIFT)
					units[i].deselect();
			}
		}
	}
	// movement input
	else if (mbButton == GLFW_MOUSE_BUTTON_RIGHT && mbAction == GLFW_PRESS && mbActionPrev == GLFW_RELEASE)
	{
		// use helper function to recreate flocks, which destroys previous flocks
		recreateFlocks(units, flocks, 1.0 * Width, 1.0 * Height, 65.0);
		for (unsigned int temp = 0; temp < flocks.size(); temp++)
		{
			cout << "flock " << temp << " size: " << flocks[temp].units.size() << endl;
		}

		for (unsigned int i = 0; i < units.size(); i++)
		{
			int tempRadius = units[i].radius();
			if (units[i].selected)
			{
				// make sure that the unit placement is within bounds of the map
				if (mXpos < tempRadius) mXpos = tempRadius;
				if (mXpos > this->Width - tempRadius) mXpos = this->Width - tempRadius;
				if (mYpos < tempRadius) mYpos = tempRadius;
				if (mYpos > this->Height - tempRadius) mYpos = this->Height - tempRadius;
				
				units[i].setDestination(glm::vec2(mXpos - tempRadius, mYpos - tempRadius));
			}
		}
	}
	if (keys[GLFW_KEY_S])
	{
		for (unsigned int i = 0; i < units.size(); i++)
		{
			if (units[i].selected)
				units[i].stop();
		}
	}
	// update previous frame stuff
	mbButtonPrev = mbButton;
	mbActionPrev = mbAction;
	mbModsPrev = mbMods;
}

void Game::Render()
{	
	// draw background
	spriteRenderer->DrawSprite(ResourceManager::GetTexture("background"),
		glm::vec2(0, 0), glm::vec2(800, 600), 0.0f, glm::vec4(1.0f));
	// draw units
	for (unsigned int i = 0; i < units.size(); i++)
		units[i].draw(*spriteRenderer);
	// draw selection box - low alpha value, so I can draw it over stuff
	selectionBox->draw(*selectionBoxRenderer);
}

