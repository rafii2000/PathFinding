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
	sf::RenderWindow& renderTarget;


	Button startButton;
	Button breakButton;
	Button pathResetButton;
	Button boardResetButton;
	Button generateMaze;
	Button openSettingsButton;

	Board nodesBoard;
	Settings settingsWindow;

	sf::Text appTitle;
	sf::Text appResultLabel;
	sf::Text appFPSLabel;



public:

	//construktor
	MainWindow(sf::RenderWindow& renderTarget, sf::Font font);

	void drawButtons();

	void drawLables();



};

