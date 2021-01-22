#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"
#include "Board.h"
#include "Button.h"
#include "Textbox.h"
#include "Layout.h"


extern int mouseX;
extern int mouseY;

class Settings
{

friend int main();

public:
	static bool isOpen;
	

private:

	
	const int width = 620; //const
	const int height; //max display_height
	const int screenX; //screenX = display_width - settings_width;
	const int screenY = 0; //const

	
	Board* board;
	sf::RenderWindow *window;
	sf::RectangleShape settingsWindow;
	sf::RectangleShape overlapRect;

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

