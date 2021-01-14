#pragma once

#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"


#define BACKSPACE_KEY 8

extern int mouseX;
extern int mouseY;
extern bool CLICK_EVENT;


class Textbox
{

friend int main();
friend class Settings;

private:

	int screenX;
	int screenY;
	int width;
	int height;

	int fontSize;
	int charLimit;
	

	std::string text = "";
	std::string placeholder;
	sf::Font* font;
	sf::Text typedText;	
	sf::RenderWindow* window;
	sf::RectangleShape shape;

	bool hasFocus = false;



public:

	Textbox(sf::RenderWindow* window, sf::Font* font, 
			int fontSize, int screenX, int screenY, int width, int height, 
			std::string text, int charLimit, const char justify, std::string placeholder = "") {

		this->window = window;
		this->font = font;
		this->fontSize = fontSize;
		this->placeholder = placeholder;
		this->charLimit = charLimit;
		
		this->screenX = screenX;
		this->screenY= screenY;
		this->width = width;
		this->height = height;

		

		typedText.setPosition(screenX, screenY);
		typedText.setFillColor(sf::Color(220,220,220));
		typedText.setString(text);
		typedText.setCharacterSize(fontSize);
		typedText.setFont(*font);
		if (placeholder != "") setPlaceholderInTextbox();
		justifyText(justify);


		shape.setPosition(screenX, screenY);
		shape.setSize({ (float)width, (float)height });
		shape.setOutlineThickness(1);
		shape.setOutlineColor(sf::Color::White);
		shape.setFillColor(sf::Color::Transparent);

	}

	bool isMouseOn();

	void update();

	void draw();
	

	void writeText(int char_unicode);	

	void justifyText(const char option);
	
	void setPlaceholderInTextbox();

	void setTextboxString(std::string str);

	
	

};

