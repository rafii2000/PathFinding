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
	inline static bool isOpen = false;
	

private:

	//settings card properties
	const int width = 620;	//const value
	const int height;		//take user display height
	const int screenX;		//take user display width minus self width
	const int screenY = 0;	//const value 

	
	Board* board;						//pointer to nodesBoard2D
	sf::RenderWindow *window;			//pointer to render target
	sf::RectangleShape settingsWindow;	//background container for settingsWindow entities
	sf::RectangleShape overlapRect;		//rectangle which darken rest part of main window


	//settings card elements
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
	
};

