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

using namespace std;
using namespace irrklang;
ISoundEngine* SoundEngine = createIrrKlangDevice();

Unit* units[1024];
SpriteRenderer* Renderer;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
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
	units[0] = new Unit(glm::vec2(0, 0), glm::vec2(200, 200),
		ResourceManager::GetTexture("sheep"), glm::vec3(1.0f, 1.0f, 1.0f), true, 5.0f);

}

void Game::Update(GLfloat dt)
{
	
}

void Game::ProcessInput(GLfloat dt)
{
	
}

void Game::Render()
{	
	Renderer->DrawSprite(ResourceManager::GetTexture("background"),
		glm::vec2(0, 0), glm::vec2(800, 600), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	
	/*for (Drawable* e : drawables)
	{
		e->draw(*Renderer);
	}*/
	units[0]->draw(*Renderer);
}

