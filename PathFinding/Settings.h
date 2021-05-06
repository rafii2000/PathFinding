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
	inline static bool fastVisualization = false;
	

private:

	//settings card properties
	const int width = 650;	//const value
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
	sf::Text mazeDensityLable;
	sf::Text fastFizualizationLabel;
	int labelFontSize = 30;

	Textbox nodesInRowTextbox;
	Textbox nodesInColumnTextbox;
	Textbox nodeSizeTextbox;
	Textbox mazeDensityTextbox;
	Textbox fastVisualizationTextbox;
	Textbox filePathLoadTextbox;
	Textbox filePathSaveTextbox;

	Button closeSettingsButton;
	Button saveBoardButtons;
	Button loadBoardButton;
	Button applySettingsChanges;
	Button onOffFastVisualizationButton;


public:
	Settings(sf::RenderWindow* window, Board* board, sf::Font* font);


	void updateButtons();

	void draw();

	void callFunctionOnButtonClick();

	void closeWindowSettings();

	void onApplyButtonClick();

	bool newBoardSizeValidation(int row, int col, int size);

	void newMazeDensityValidation(int value);

	void onSaveBoardButtonClick();

	void onLoadBoardButtonClick();

	void onFastVisualizationButtonClick();



	int str_to_int(std::string str);
	
};

