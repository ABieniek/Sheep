/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#include "game.h"

using namespace std;
using namespace irrklang;
ISoundEngine* SoundEngine = createIrrKlangDevice();

// externals
GameState Game::State;
GLboolean Game::gamestateInitialized;
GLuint Game::Width, Game::Height;
vector<Unit*> Game::units;
vector<Unit*> Game::selectedUnits;
vector<Flock> Game::flocks;
HazardHandler* Game::hazardHandler;
Difficulty Game::difficulty;
vector<PowerUp*> Game::powerUps;
GLfloat Game::powerUpSpawnTime = 10;
Drawable* Game::selectionBox;
Button* Game::buttonEnd;
Button* Game::buttonStart;
Button* Game::buttonSetSimple; 
Button* Game::buttonSetNormal;
SpriteRenderer* Game::spriteRenderer;
SpriteRenderer* Game::selectionBoxRenderer;
SpriteRenderer* Game::textRenderer;
GLfloat Game::gameTime;
GLint Game::gameScore;
GLint Game::incDebug;

Game::~Game()
{
	clearGamestate();
	if (spriteRenderer) delete spriteRenderer;
	if (selectionBoxRenderer) delete selectionBoxRenderer;
	if (textRenderer) delete textRenderer;
}

void Game::InitVariables(GLuint width, GLuint height)
{
	Width = width;
	Height = height;
	gameTime = 0.f;
	gameScore = 0.f;
	incDebug = 0.f;
	State = GAME_START;
	difficulty = SIMPLE;
}
 
void Game::InitGraphics()
{
	// Load shaders
	ResourceManager::LoadShader("Shaders/sprite.vs", "Shaders/sprite.fs", nullptr, "sprite");
	ResourceManager::LoadShader("Shaders/selectionBox.vs", "Shaders/selectionBox.fs", nullptr, "selectionBox");
	ResourceManager::LoadShader("Shaders/text.vs", "Shaders/text.fs", nullptr, "text");

	/// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width),
		static_cast<GLfloat>(Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("selectionBox").Use().SetInteger("image", 0);
	ResourceManager::GetShader("selectionBox").SetMatrix4("projection", projection);
	ResourceManager::GetShader("text").Use();
	ResourceManager::GetShader("text").SetMatrix4("projection",
		glm::ortho(0.0f, static_cast<GLfloat> (Width), 0.0f, static_cast<GLfloat>(Height)));

	// Set render-specific controls
	spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	selectionBoxRenderer = new SpriteRenderer(ResourceManager::GetShader("selectionBox"));
	textRenderer = new SpriteRenderer(ResourceManager::GetShader("text"));

	// initializing text rendering
	TextUtil::init();

	/// Load textures
	// sprites
	ResourceManager::LoadTexture("Textures/SheepAnimated.png", GL_TRUE, "sheep");
	ResourceManager::LoadTexture("Textures/GrassBackground.png", GL_TRUE, "background");
	ResourceManager::LoadTexture("Textures/White.png", GL_FALSE, "selectionBox");
	ResourceManager::LoadTexture("Textures/LazerAnimated.png", GL_TRUE, "Lazer");
	ResourceManager::LoadTexture("Textures/LazerExplodedAnimated.png", GL_TRUE, "LazerExploded");
	ResourceManager::LoadTexture("Textures/Rocket.png", GL_TRUE, "Rocket");
	ResourceManager::LoadTexture("Textures/RocketExploded.png", GL_TRUE, "RocketExploded");
	ResourceManager::LoadTexture("Textures/RocketTarget.png", GL_TRUE, "RocketTarget");
	ResourceManager::LoadTexture("Textures/PowerUpLife.png", GL_TRUE, "Life");
	// buttons
	ResourceManager::LoadTexture("Textures/Buttons/StartButton.png", GL_TRUE, "startButton");
	ResourceManager::LoadTexture("Textures/Buttons/RadioButton.png", GL_TRUE, "radioButton");
	ResourceManager::LoadTexture("Textures/Buttons/RestartButton.png", GL_TRUE, "restartButton");
}

void Game::InitMenu()
{
	// start menu buttons
	buttonStart = new Button(glm::vec2(.5 * Width, .5 * Height), glm::vec2(250.0, 100.0), 
		ResourceManager::GetTexture("startButton"),	glm::vec4(1.0f), 0.0f, true, &(Game::cbStart));
	buttonSetSimple = new Button(glm::vec2(.4 * Width, .7 * Height), glm::vec2(150.0, 100.0),
		ResourceManager::GetTexture("radioButton"), glm::vec4(1.0f), 0.0f, true, &(Game::cbSetSimple));
	buttonSetNormal = new Button(glm::vec2(.6 * Width, .7 * Height), glm::vec2(150.0, 100.0),
		ResourceManager::GetTexture("radioButton"), glm::vec4(1.0f), 0.0f, true, &(Game::cbSetNormal));
	// end menu buttons
	buttonEnd = new Button(glm::vec2(.5 * Width, .8 * Height), glm::vec2(150.0, 100.0),
		ResourceManager::GetTexture("restartButton"), glm::vec4(1.0f), 0.0f, true, &(Game::cbRestart));
}

void Game::InitGamestate()
{
	/// Set Game Variables
	// sheep
	vector<glm::vec2> locs;
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			locs.push_back(glm::vec2(Width / 2 + i * 100, Height / 2 + j * 100));
		}
	}
	for (unsigned int i = 0; i < 12; i++)
	{
		units.push_back(new Unit(locs[i], glm::vec2(50, 50),
			ResourceManager::GetTexture("sheep"), glm::vec4(1.0f), true, 0.0f, 100.f));
	}
	// selection box - don't draw it initially
	selectionBox = new Drawable(glm::vec2(0, 0), glm::vec2(0, 0),
		ResourceManager::GetTexture("selectionBox"), glm::vec4(1.0, 1.0, .4, .25), 0.0, false);

	// hazards - test lazer, for now
	hazardHandler = new HazardHandler(difficulty, Width, Height,
		ResourceManager::GetTexture("Lazer"), ResourceManager::GetTexture("LazerExploded"),
		ResourceManager::GetTexture("Rocket"), ResourceManager::GetTexture("RocketExploded"), ResourceManager::GetTexture("RocketTarget"));
	hazardHandler->init();
	powerUpSpawnTime = glfwGetTime() + 10.f;
	srand(time(NULL));

	gameScore = 0;
	gameTime = 0;
	gamestateInitialized = true;
}

void Game::clearGamestate()
{
	if (selectionBox)
	delete selectionBox;
	for (unsigned int i = 0; i < units.size(); i++)
		delete units[i];
	units.clear();
	for (unsigned int i = 0; i < powerUps.size(); i++)
		delete powerUps[i];
	powerUps.clear();
	if (hazardHandler)
	delete hazardHandler;
	gamestateInitialized = false;
}

void Game::UpdateGame(GLfloat dt)
{
	// updating values in units
	for (unsigned int i = 0; i < units.size(); i++)
	{
		//updating unit positions
		units[i]->move(dt);

		for (unsigned int j = 0; j < units.size(); j++)
		{
			if (i == j)  // if the unit we're looking at is not the same one we just moved, skip
				continue;
			if (doesPenetrate(units[i], units[j]))
			{
				units[i]->position -= penetrationVector(units[i], units[j]);
				if (!units[j]->moving)
				{
					units[i]->stop();
					units[j]->stop();
				}
			}
		}
	}
	// handling powerups
	for (unsigned int i = 0; i < powerUps.size(); i++)
	{
		powerUps[i]->update(dt);
		for (unsigned int j = 0; j < units.size(); j++)
		{
			if (powerUps[i]->inHitbox(units[j])) // here
			{
				glm::vec2 tempPosition = powerUps[i]->position;
				// getting rid of powerup
				delete powerUps[i];
				powerUps.erase(powerUps.begin() + i);
				i--;
				//adding new unit
				units.push_back(new Unit(tempPosition, glm::vec2(50, 50),
					ResourceManager::GetTexture("sheep"), glm::vec4(1.0f), true, 0.0f, 100.f));
				break;
			}
		}
	}
	// generating new powerups
	if (gameTime > powerUpSpawnTime)
	{
		glm::vec2 randomLocation = glm::vec2((100 + (rand() % (Width - 50)))*1.f, (100 + (rand() % (Height - 50))*1.f));
		powerUps.push_back(new PowerUp(randomLocation, glm::vec2(50, 50), ResourceManager::GetTexture("Life"), glm::vec4(1.0f),
			GL_TRUE, 100));
		powerUpSpawnTime += powerUpSpawnTime + 1.f;
	}
	// killing units - must occur at the end of updating because
	// array size and such get modified when a unit is killed
	hazardHandler->update(dt, units);

	// score will increase, each second, for the number of units that are still alive
	if (differentTimeInterval(gameTime, gameTime + dt, 1))
		gameScore += units.size();

	// lose condition
	if (units.size() < 5)
		State = GAME_END;

	gameTime += dt;
}

void Game::UpdateMenu(GLfloat dt)
{
	if (State == GAME_START)
	{
		buttonStart->process(InputHandler::mXpos, InputHandler::mYpos, 
			InputHandler::leftClickState, InputHandler::leftClickStatePrev);
		buttonSetSimple->process(InputHandler::mXpos, InputHandler::mYpos,
			InputHandler::leftClickState, InputHandler::leftClickStatePrev);
		buttonSetNormal->process(InputHandler::mXpos, InputHandler::mYpos,
			InputHandler::leftClickState, InputHandler::leftClickStatePrev);
		if (difficulty == SIMPLE)
			buttonSetSimple->sampleFrame = BUTTON_PRESSED;
		else if (difficulty == NORMAL)
			buttonSetNormal->sampleFrame = BUTTON_PRESSED;
	}
	else if (State == GAME_END)
		buttonEnd->process(InputHandler::mXpos, InputHandler::mYpos,
			InputHandler::leftClickState, InputHandler::leftClickStatePrev);
}

void Game::ProcessInput(GLfloat dt)
{
	// selection input
	if (InputHandler::leftClickState == GLFW_PRESS && InputHandler::leftClickStatePrev == GLFW_RELEASE)
	{
		// place first point of selection box
		selectionBox->position = glm::vec2(InputHandler::mXpos, InputHandler::mYpos);
		selectionBox->size = glm::vec2(0.0);
		selectionBox->bDraw = true;
	}
	if (InputHandler::leftClickState == GLFW_PRESS && InputHandler::leftClickStatePrev == GLFW_PRESS)
	{
		selectionBox->size = glm::vec2(InputHandler::mXpos, InputHandler::mYpos) - selectionBox->position;
	}
	if (InputHandler::leftClickState == GLFW_RELEASE && InputHandler::leftClickStatePrev == GLFW_PRESS)
	{
		// place second point of selection box - also, stop rendering it
		selectionBox->size = glm::vec2(InputHandler::mXpos, InputHandler::mYpos) - selectionBox->position;
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
			if (((units[i]->position.x + units[i]->size.x / 2) > selectionBox->position.x)
				&& ((units[i]->position.x - units[i]->size.x / 2) < selectionBox->position.x + selectionBox->size.x)
				&& ((units[i]->position.y + units[i]->size.y / 2) > selectionBox->position.y)
				&& ((units[i]->position.y - units[i]->size.y / 2) < selectionBox->position.y + selectionBox->size.y))
				units[i]->select();
			//if not within box
			else
			{
				// if not holding shift, deselect
				if (InputHandler::mod != GLFW_MOD_SHIFT)
					units[i]->deselect();
			}
		}
	}
	// movement input
	else if (InputHandler::rightClickState == GLFW_PRESS && InputHandler::rightClickStatePrev == GLFW_RELEASE)
	{
		// only consider units that are selected in the flock stuff
		selectedUnits.clear();
		for (unsigned int i = 0; i < units.size(); i++)
		{
			if (units[i]->selected)
				selectedUnits.push_back(units[i]);
		}
		// use helper function to recreate flocks, which destroys previous flocks
		recreateFlocks(selectedUnits, flocks, Width, Height, 65.f);

		for (unsigned int i = 0; i < flocks.size(); i++)
		{
			flocks[i].setDestination(glm::vec2(InputHandler::mXpos, InputHandler::mYpos));
		}
	}
	if (InputHandler::keys[GLFW_KEY_S])
	{
		for (unsigned int i = 0; i < units.size(); i++)
		{
			if (units[i]->selected)
				units[i]->stop();
		}
	}
}

void Game::RenderGame(GLfloat dt)
{
	// draw background
	spriteRenderer->DrawSprite(ResourceManager::GetTexture("background"),
		glm::vec2(Width/2, Height/2), glm::vec2(Width, Height), 0.0f, glm::vec4(1.0f));
	// draw Lazers behind units
	hazardHandler->drawLazers(*spriteRenderer);
	if (differentTimeInterval(gameTime, gameTime + dt, .05f))
		for (unsigned int i = 0; i < hazardHandler->lazers.size(); i++)
			hazardHandler->lazers[i]->sampleFrame++;
	// draw powerups
	for (unsigned int i = 0; i < powerUps.size(); i++)
		powerUps[i]->draw(*spriteRenderer);
	// draw units
	for (unsigned int i = 0; i < units.size(); i++)
	{
		if (!units[i]->moving)
			units[i]->sampleFrame = 0;
		else if (differentTimeInterval(gameTime, gameTime + dt, .1f) && units[i]->moving)
			units[i]->sampleFrame++;
		units[i]->draw(*spriteRenderer, glm::vec2(7.0f, 1.0f), units[i]->sampleFrame);
	}
	// draw rockets on top of units
	hazardHandler->drawRockets(*spriteRenderer);
	selectionBox->drawTopLeft(*selectionBoxRenderer);

	// rendering text test
	TextUtil::RenderText(ResourceManager::GetShader("text"), "Score: " + std::to_string(gameScore),
		5.f, Height - 20.f, .5f, glm::vec4(0.f, 0.f, 0.f, 1.f));
}

void Game::RenderMenu(GLfloat dt)
{
	// draw background
	spriteRenderer->DrawSprite(ResourceManager::GetTexture("background"),
		glm::vec2(Width / 2, Height / 2), glm::vec2(Width, Height), 0.0f, glm::vec4(1.0f));
	if (State == GAME_START)
	{
		buttonStart->render(*spriteRenderer, glm::vec2(3.f, 1.f), buttonStart->sampleFrame);
		buttonSetSimple->render(*spriteRenderer, glm::vec2(3.f, 1.f), buttonSetSimple->sampleFrame);
		buttonSetNormal->render(*spriteRenderer, glm::vec2(3.f, 1.f), buttonSetNormal->sampleFrame);
		TextUtil::RenderText(ResourceManager::GetShader("text"), "Sheep",
			.275 * Width, .65 * Height, 3.f, glm::vec4(0.f, 0.f, 0.f, 1.f));
		TextUtil::RenderText(ResourceManager::GetShader("text"), "Simple",
			.325 * Width, .32 * Height, .8f, glm::vec4(0.f, 0.f, 0.f, 1.f));
		TextUtil::RenderText(ResourceManager::GetShader("text"), "Normal",
			.525 * Width, .32 * Height, .8f, glm::vec4(0.f, 0.f, 0.f, 1.f));
	}
	else if (State == GAME_END)
	{
		RenderGame(dt);
		TextUtil::RenderText(ResourceManager::GetShader("text"), "Final Score:",
			.3 * Width, .4 * Height, 1.5f, glm::vec4(0.f, 0.f, 0.f, 1.f));
		TextUtil::RenderText(ResourceManager::GetShader("text"), std::to_string(gameScore),
			.4 * Width, .32 * Height, 1.5f, glm::vec4(0.f, 0.f, 0.f, 1.f));
		buttonEnd->render(*spriteRenderer, glm::vec2(3.f, 1.f), buttonEnd->sampleFrame);
	}
}