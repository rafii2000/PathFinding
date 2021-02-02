#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Board.h"
#include "Settings.h"
#include "Button.h"
#include "Layout.h"

class MainWindow
{

friend int main();


private:
	sf::RenderWindow* renderTarget;


	Button startButton;
	Button breakButton;
	Button pathResetButton;
	Button boardResetButton;
	Button generateMaze;
	Button openSettingsButton;

	Board nodesBoard;
	Settings settingsPanel;

	sf::Text appTitle;
	sf::Text appResultLabel;
	sf::Text appFPSLabel;

	sf::RectangleShape appResultLabelBackground;

	// FPS variables
	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;


public:

	//construktor
	MainWindow(sf::RenderWindow* renderTarget);

	void fpsCounter();

	void update();

	void draw();


};

