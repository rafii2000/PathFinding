#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"



extern mf MOUSE_STATE;
extern btn_id CLICKED_BTN;
extern bool CLICK_EVENT;


//Opis dzialania przyciskow:
//START - rozpoczyna  wizualizacje, blokuje dostep do tablicy, przywraca domysle atrybuty Node'om ktorych nodeType = WALKABLE
//BREAK - zatrzymuje wizualizacje, odblokowuje dostep do tablicy
//PATH_RESET - przywraca atrybuity domyslne wszystkim Node'om, ktore zostaly zaznaczone jako CLOSED i OPEN
//BOARD_RESET - przywraca atrybuity domyslne wszystkim Node'om, z wyj¹tkiem startNode  i endNode


enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button: sf::RectangleShape
{
	
private:

	
	btn_id buttonID;
	std::string texturePath="";
	short unsigned buttonState;
	int fontSize;

	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font* font;
	sf::Text text;
	
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	
	
public:

	//constructor
	Button(int x, int y, int width, int height, sf::Font* font, int fontSize, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, 
		btn_id buttonID, std::string texture_path="");

	
	//Accesors
	const bool isPressed();

	//Functions 
	void update(int mouseX, int mouseY);
	
	void render(sf::RenderWindow* window);

	void callButtonFunction();

	//Buttons functions 
	void onStartButtonClick();

	void onBreakButtonClick();

	void onPathResetButtonClick();

	void onBoardResetButtonClick();

	void onSettingsButtonClick();

	
};

