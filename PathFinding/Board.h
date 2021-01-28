#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"
#include "Node.h"
#include "Settings.h"


extern btn_id CLICKED_BTN;

//drag mode flags
extern bool DRAG_MODE;
extern bool START_NODE_DRAG_MODE;
extern bool END_NODE_DRAG_MODE;

//A*
extern bool RUN_ALGORITHM;
extern bool IS_PATH_FOUND;
extern bool PATH_NOT_EXIST;

enum board_states { ACTIVE = 0, BLOCK };

struct Coordinates {
	int x;
	int y;
};


class Board
{

friend int main();
friend class Settings;


	
private:

	//Window
	sf::RenderWindow* window;

	//Node's properties
	int nodeSize;
	int nodeBorder;
	int nodeOrigin;	

	//Node's colors flags
	sf::Color LIGHT_GREEN = sf::Color(128, 255, 0, 200);
	sf::Color LIGHT_YELLOW = sf::Color(255, 255, 0, 200);
	sf::Color LIGHT_CYAN = sf::Color(138, 249, 255, 200);
	sf::Color START_NODE_HOVER = sf::Color(0, 235, 0);
	sf::Color END_NODE_HOVER = sf::Color(225, 0, 0);


	//Board
	int leftBorder;
	int topBorder;
	int rightBorder;
	int bottomBorder;

	int nodesRowAmount;
	int nodesColumnAmount;
	short unsigned boardState = ACTIVE;
	bool isMouseOnBoard = false;
	std::vector< std::vector<Node> > nodesBoard2D;


	//Dragging mode
	Node* previousDrgged = nullptr;
	Node* currentDrgged = nullptr;


	//A* alghoritm
	Coordinates startNodeCords;
	Coordinates endNodeCords;
	Node* nextMasterNode = nullptr; // maybe nextClosedNode would be a better name ?
	std::vector<Node*> openNodes;
	std::vector<Node*> closedNodes;
	int diagonalCost = 14;
	int forwardCost = 10;



public:

	//constructor
	Board(sf::RenderWindow& window, int nodeSize, int nodeBorder,  int nodesRowAmt, int nodesColAmt) {

		this->window = &window;
		this->nodeSize = nodeSize;
		this->nodeOrigin = nodeSize / 2;
		this->nodeBorder = nodeBorder;
		this->nodesRowAmount = nodesRowAmt;
		this->nodesColumnAmount = nodesColAmt;
		
		calculateBoardSize();
		createBoard();
		setBoardBordersCords();
	}



	void calculateBoardSize();

	void createBoard();

	void setBoardBordersCords();

	void draw();	

	Coordinates mouseToBoardIndexes(int mouseX, int mouseY);

	bool checkIsMouseOnBoard(int mouse_x, int mouse_y);

	void putObstacles(int mouseX, int mouseY);

	void eraseObstacles(int mouseX, int mouseY);



	// -------- DIFFRENT FUNCTIONS -------- //

	void buttonsUpdate();

	void boardFunctionalities();




	// -------- BUTTONS FUNCTION -------- //
	
	void callFunctionOnButtonClick();

	void clearObstacles();

	void clearPath();

	void clearBoard();

	void resetAlgorithmAttributes();

	void generateMaze();
		



	// -------- A* ALGORITHM LOGIC -------- //

	void exploreNodes();

	void setNodeAttributesWhileOpenning(int masterX, int masterY, int selfX, int selfY, int offset);

	int calcGCost(int masterX, int masterY, int selfX, int selfY, int offset);
	
	int calcHCost(int selfX, int selfY);	

	void showPath();

	bool isNodeInBoard(int x, int y);
	



	// -------- SETTINGS PANEL-------- //

	void createBoardFromFile(std::string fileName);


};

