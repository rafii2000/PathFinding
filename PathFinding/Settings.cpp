#include "Settings.h"

Settings::Settings(sf::RenderWindow* window, Board* board, sf::Font* font) :
	screenX(window->getSize().x - width),
	height(window->getSize().y),
	closeSettingsButton(1525, 850, 200, 50, font, 20, "Close settings", sf::Color(170, 170, 170), sf::Color(150, 150, 150), sf::Color(120, 120, 120), btn_id::CLOSE_SETTINGS_BTN),
	saveBoardButtons(screenX+50, Layout::FILE_PATH_SAVE_GROUP_Y-5, 130, 50, font, 20, "Save board", sf::Color(170, 170, 170), sf::Color(150, 150, 150), sf::Color(120, 120, 120), btn_id::SAVE_BOARD_BTN),
	loadBoardButton(screenX + 50, Layout::FILE_PATH_LOAD_GROUP_Y-5, 130, 50, font, 20, "Load board", sf::Color(170, 170, 170), sf::Color(150, 150, 150), sf::Color(120, 120, 120), btn_id::LOAD_BOARD_BTN),
	applySettingsChanges(screenX + 470, 500, 100, 35, font, 18, "Apply", sf::Color(170, 170, 170), sf::Color(150, 150, 150), sf::Color(120, 120, 120), btn_id::APPLY_BOARD_RESIZE_BTN),
	nodesInRowTextbox(window, font, 30, screenX + 70 + 250, 200, 70, 40, std::to_string(board->nodesRowAmount), 3, 'L'),
	nodesInColumnTextbox(window, font, 30, screenX + 70 + 250, 275, 70, 40, std::to_string(board->nodesColumnAmount), 3, 'L'),
	nodeSizeTextbox(window, font, 30, screenX + 70 + 250, 350, 70, 40, std::to_string(board->nodeSize), 3, 'L'),
	mazeDensityTextbox(window, font, 30, screenX + 70 + 250, 450, 70, 40, std::to_string(board->mazeDensity), 3, 'L'),

	filePathSaveTextbox(window, font, 20, screenX + 50 + 150, Layout::FILE_PATH_SAVE_GROUP_Y, 400, 40, "", 40, 'L', "Type file name"),
	filePathLoadTextbox(window, font, 20, screenX + 50 + 150, Layout::FILE_PATH_LOAD_GROUP_Y, 400, 40, "", 40, 'L', "Type path to file")
{

	this->window = window;
	this->board = board;

	settingsWindow.setFillColor(sf::Color(51, 51, 51, 255));
	settingsWindow.setPosition(screenX, screenY);
	settingsWindow.setSize({ (float)width, (float)height });

	overlapRect.setFillColor(sf::Color(0, 0, 0, 75));
	overlapRect.setPosition(0, 0);
	overlapRect.setSize({ (float)window->getSize().x, (float)window->getSize().y });


	windowTitle.setString("Settings");
	windowTitle.setPosition(sf::Vector2f(screenX + 225, 40));
	windowTitle.setFont(*font);
	windowTitle.setCharacterSize(50);

	nodesInRowLabel.setString("Nodes in row: ");
	nodesInRowLabel.setPosition(sf::Vector2f(screenX+50, 200));
	nodesInRowLabel.setFont(*font);
	nodesInRowLabel.setCharacterSize(labelFontSize);

	nodesInColLabel.setString("Nodes in column: ");
	nodesInColLabel.setPosition(sf::Vector2f(screenX+50, 275));
	nodesInColLabel.setFont(*font);
	nodesInColLabel.setCharacterSize(labelFontSize);

	nodesSizeLable.setString("Node size: ");
	nodesSizeLable.setPosition(sf::Vector2f(screenX + 50, 350));
	nodesSizeLable.setFont(*font);
	nodesSizeLable.setCharacterSize(labelFontSize);

	mazeDensityLable.setString("Maze density: ");
	mazeDensityLable.setPosition(sf::Vector2f(screenX + 50, 450));
	mazeDensityLable.setFont(*font);
	mazeDensityLable.setCharacterSize(labelFontSize);

}


void Settings::updateButtons()
{

	closeSettingsButton.update(mouseX, mouseY);
	saveBoardButtons.update(mouseX, mouseY);
	loadBoardButton.update(mouseX, mouseY);
	applySettingsChanges.update(mouseX, mouseY);
}

void Settings::draw()
{
	if (isOpen == true) {
		
		//Containers
		window->draw(overlapRect);
		window->draw(settingsWindow);		

		//Lables
		window->draw(windowTitle);
		window->draw(nodesInRowLabel);
		window->draw(nodesInColLabel);
		window->draw(nodesSizeLable);
		window->draw(mazeDensityLable);

		//Textboxes
		nodesInRowTextbox.draw();
		nodesInColumnTextbox.draw();
		nodeSizeTextbox.draw();
		mazeDensityTextbox.draw();
		filePathSaveTextbox.draw();
		filePathLoadTextbox.draw();

		//Buttons
		//closeSettingsButton.render(window);
		saveBoardButtons.render(window);
		loadBoardButton.render(window);
		applySettingsChanges.render(window);

	}
}


void Settings::callFunctionOnButtonClick()
{

	if (CLICKED_BTN == btn_id::OPEN_SETTINGS_BTN) {
		//moved to Board.cpp
	}
	else if (CLICKED_BTN == btn_id::CLOSE_SETTINGS_BTN) {
		closeWindowSettings();				
	}
	else if (CLICKED_BTN == btn_id::APPLY_BOARD_RESIZE_BTN) {
		std::cout << "Apply" << std::endl;
		onApplyButtonClick();
	}
	else if (CLICKED_BTN == btn_id::SAVE_BOARD_BTN) {
		onSaveBoardButtonClick();
	}
	else if (CLICKED_BTN == btn_id::LOAD_BOARD_BTN) {
		onLoadBoardButtonClick();
	}

	//close settinsWindow on click outside the settings card
	if (!settingsWindow.getGlobalBounds().contains(float(mouseX), float(mouseY)))
		if (CLICK_EVENT)
			closeWindowSettings();			

	//sometimes keeping saved previous clicked buttond ID can cause some unexpected behaviour, it is better to reset it
	//CLICKED_BTN = btn_id::NONE;	//move to main()

}


void Settings::closeWindowSettings()
{
	//set attributes
	isOpen = false;
	board->boardState = ACTIVE;
	if(Textbox::activeTextboxPtr != nullptr) Textbox::activeTextboxPtr->update();


	//restore not applied Textboxes strings
	nodesInRowTextbox.setTextboxString(std::to_string(board->nodesRowAmount));
	nodesInColumnTextbox.setTextboxString(std::to_string(board->nodesColumnAmount));
	nodeSizeTextbox.setTextboxString(std::to_string(board->nodeSize));

	//restore Textboxes placeholders
	filePathSaveTextbox.setPlaceholderInTextbox();
	filePathLoadTextbox.setPlaceholderInTextbox();
}

void Settings::onApplyButtonClick()
{
	int newNodeRowAmt = str_to_int(nodesInRowTextbox.typedText.getString());
	int newNodeColAmt = str_to_int(nodesInColumnTextbox.typedText.getString());
	int newNodeSize = str_to_int(nodeSizeTextbox.typedText.getString());
	int newMazeDensity = str_to_int(mazeDensityTextbox.typedText.getString());

	bool boardSizeResult = newBoardSizeValidation(newNodeRowAmt, newNodeColAmt, newNodeSize);
	
	if (boardSizeResult) {

		//initialize new values
		board->nodesRowAmount = newNodeRowAmt;
		board->nodesColumnAmount = newNodeColAmt;
		board->nodeSize = newNodeSize;
		board->nodeOrigin = newNodeSize / 2;

		//resize nodesBoard2SD
		board->nodesBoard2D.clear();	
		board->calculateBoardSize();
		board->createBoard();
		board->setBoardBordersCords();				
		
	}

	newMazeDensityValidation(newMazeDensity);

	//update Textboxes
	nodesInRowTextbox.setTextboxString(std::to_string(board->nodesRowAmount));
	nodesInColumnTextbox.setTextboxString(std::to_string(board->nodesColumnAmount));
	nodeSizeTextbox.setTextboxString(std::to_string(board->nodeSize));
	mazeDensityTextbox.setTextboxString(std::to_string(board->mazeDensity));	

}

bool Settings::newBoardSizeValidation(int row, int col, int size)
{
	//It is not a major thing of a program
	if (row == 0 || col == 0 || size == 0) return false;	
	if (row < 5 || col < 5 || size < 5) return false;
	if (row == board->nodesRowAmount && col == board->nodesColumnAmount and size == board->nodeSize) return false;
	
	return true;
}

void Settings::newMazeDensityValidation(int value)
{
	//It is not a major thing of a program
	if (value >= 0 and value <= 100) {

		board->mazeDensity = value;
	}

}



void Settings::onSaveBoardButtonClick()
{	
	std::string fileName = filePathSaveTextbox.typedText.getString();
	
	if (fileName == filePathSaveTextbox.placeholder) {
		std::cout << "Save failed: File name cant be a placeholder!" << std::endl;
		return;
	}

	fileName = "saved/" + fileName;

	std::ofstream file(fileName.c_str());

	if (!file) { 
		std::cout << "Save failed: 'saved' directory has been removed, create new one!" << std::endl; 
	}
	else {

		//save board size
		file << std::to_string(board->nodesRowAmount) << "\n";
		file << std::to_string(board->nodesColumnAmount) << "\n";
		file<< std::to_string(board->nodeSize) << "\n";
		file <<  "\n";


		//save board
		for (int j = 0; j < board->nodesColumnAmount; j++) {

			for (int i = 0; i < board->nodesRowAmount; i++) {

				switch (board->nodesBoard2D[j][i].nodeType)
				{
					case WALKABLE:		file << "O";	break;
					case OBSTACLE:		file << "X";	break;
					case START_NODE:	file << "S";	break;
					case END_NODE:		file << "E";	break;

				default:
					break;
				}
			
			}
			file << "\n";
		}	

		std::cout << "File: '"<<fileName<<"' saved successfully!"<< std::endl;
	}

	file.close();
}

void Settings::onLoadBoardButtonClick()
{

	std::string fileName = "saved/" + filePathLoadTextbox.typedText.getString();

	board->createBoardFromFile(fileName);	

	//update Textboxes
	nodesInRowTextbox.setTextboxString(std::to_string(board->nodesRowAmount));
	nodesInColumnTextbox.setTextboxString(std::to_string(board->nodesColumnAmount));
	nodeSizeTextbox.setTextboxString(std::to_string(board->nodeSize));

}




int Settings::str_to_int(std::string str)
{
	return atoi(str.c_str());
}


