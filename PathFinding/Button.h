#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

extern std::string mouseState;
extern bool CLICK_EVENT;

extern const std::string START_BTN;
extern const std::string BREAK_BTN;
extern const std::string PATH_RESET_BTN;
extern const std::string BOARD_RESET_BTN;
extern std::string CLICKED_BTN;


//Opis dzialania przyciskow:
//START - rozpoczyna  wizualizacje, blokuje dostep do tablicy, przywraca domysle atrybuty Node'om ktorych nodeType = WALKABLE
//BREAK - zatrzymuje wizualizacje, odblokowuje dostep do tablicy
//PATH_RESET - czysci pola ktore zostaly zaznaczone jako CLOSED i OPEN
//BOARD_RESET - przywraca atrybuity domyslne wszystkim wez³om, z wyj¹tkiem startNode  i endNode


enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button: sf::RectangleShape
{
	
private:

	short unsigned buttonState;
	std::string buttonID;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	
	
public:

	Button(int x, int y, int width, int height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, std::string buttonID);

	~Button();


	//Accesors
	const bool isPressed();

	//Functions 
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderWindow* window);


	void callButtonFunction();

	void onStartButtonClick();

	void onBreakButtonClick();

	void onPathResetButtonClick();

	void onBoardResetButtonClick();

	

	
};

