#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"
#include "Board.h"
#include "Button.h"


extern int mouseX;
extern int mouseY;

class Settings
{

private:

	bool isOpen = false;

	
	sf::RenderWindow *window;
	sf::RectangleShape settings_window;
	sf::Text windowTitle;

	Button closeSettingsButton;
	



public:
	Settings(sf::RenderWindow* window, sf::Font* font) :
		closeSettingsButton(1525, 850, 200, 50, font, "Close",
			sf::Color(170, 170, 170),
			sf::Color(150, 150, 150),
			sf::Color(120, 120, 120), btn_id::CLOSE_SETTINGS_BTN)
	{

		this->window = window;

		settings_window.setFillColor(sf::Color(51, 51, 51, 255));
		settings_window.setPosition(1300, 0);
		settings_window.setSize({ 620, 1080 });

		
		windowTitle.setString("Settings");
		windowTitle.setPosition(sf::Vector2f(1300+225,40));
		windowTitle.setFont(*font);
		windowTitle.setCharacterSize(50);
	}


	void openWindowSettings();

	void closeWindowSettings();

	void updateButtons();

	void draw();
};

