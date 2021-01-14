#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"
#include "Board.h"
#include "Button.h"
#include "Textbox.h"


extern int mouseX;
extern int mouseY;

class Settings
{

friend int main();

public:
	static bool isOpen;

private:

	
	int screenX = 1300;
	int screenY = 0;
	int width = 620;
	int height = 1080;

	
	Board* board;
	sf::RenderWindow *window;
	sf::RectangleShape settings_window;

	sf::Text windowTitle;
	sf::Text nodesInRowLabel;
	sf::Text nodesInColLabel;
	sf::Text nodesSizeLable;
	int labelFontSize = 30;

	Textbox nodesInRowTextbox;
	Textbox nodesInColumnTextbox;
	Textbox nodeSizeTextbox;
	Textbox filePathLoadTextbox;
	Textbox filePathSaveTextbox;

	Button closeSettingsButton;
	Button saveBoardButtons;
	Button loadBoardButton;
	Button applyBoardResizeButton;

	
	



public:
	Settings(sf::RenderWindow* window, Board* board, sf::Font* font);


	void updateButtons();

	void draw();



	void callFunctionOnButtonClick();

	void closeWindowSettings();

	void onApplyButtonClick();

	bool newBoardSizeValidation(int row, int col, int size);

	void onSaveBoardButtonClick();

	void onLoadBoardButtonClick();

	


	int str_to_int(std::string str);

	std::string int_to_str(int number);
};

