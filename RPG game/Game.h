#pragma once

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "GraphicsSettings.h"

class Game
{
private:

	
	
	GraphicsSettings gfxSettings;

	StateData stateData;

	sf::RenderWindow* window;
	sf::View view;


	sf::Clock dtClock;
	float dt;

	float gridSize;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialize functions
	void initVariables();
	void initGraphicsSettings();
	void initStateData();
	void initWindow();	
	void initStates();
	void initKeys();

public:
	Game();
	~Game();


	//Functions

	void run();
	void endGame();

	void updateDt();
	void pollEvents();

	void update();
	

	void render();
};
