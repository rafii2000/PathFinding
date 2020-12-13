#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Node.h"




enum board_states { ACTIVE = 0, BLOCK };  //ACTIVE jest nie fajne EDITABLE chyba lepsze

extern const std::string START_BTN;
extern const std::string BREAK_BTN;
extern const std::string PATH_RESET_BTN;
extern const std::string BOARD_RESET_BTN;
extern std::string CLICKED_BTN;

extern bool RUN_ALGORITHM;
extern bool IS_PATH_FOUND;
extern bool PATH_NOT_EXIST;

struct Coordinates {
	int x;
	int y;
};

class Board
{

//friend void putObstacles(Board& board);
//friend void eraseObstacles(Board& board);
//friend Cords mouseToBoardIndexes(Board& board, int mouse_x, int mouse_y);
//friend bool checkIsMouseOnBoard(Board& board, int mouse_x, int mouse_y);




friend int main(); //to jest mocno niefajne




private:

	//Node's properties
	int nodeSize;
	int nodeBorder;
	int nodeOrigin;
	int nodesRowAmount;
	int nodesColumnAmount;

	//Node's colors flags
	sf::Color LIGHT_GREEN = sf::Color(128, 255, 0, 200);
	sf::Color LIGHT_YELLOW = sf::Color(255, 255, 0, 200);
	sf::Color LIGHT_CYAN = sf::Color(138, 249, 255, 200);

	
	//Board
	int leftBorder;
	int topBorder;
	int rightBorder;
	int bottomBorder;

	short unsigned boardState = ACTIVE;
	bool isMouseOnBoard = false;
	sf::RenderWindow* window;
	std::vector< std::vector<Node> > nodesBoard2D;


	//Mouse




	//A* alghoritm
	Coordinates startNodeCords;
	Coordinates endNodeCords;
	Node* nextMasterNode = nullptr; // maybe nextClosedNode would be a better name ?

	int diagonalCost = 14;
	int forwardCost = 10;

	std::vector<Node*> openNodes;  //openNodes
	std::vector<Node*> closedNodes;  //closedNodes


	
	





public:


	Board(){}

	Board(sf::RenderWindow& window, int nodeSize, int nodeBorder,  int nodesRowAmt, int nodesColAmt) {

		this->window = &window;
		this->nodeSize = nodeSize;
		this->nodeOrigin = nodeSize / 2;
		this->nodeBorder = nodeBorder;
		this->nodesRowAmount = nodesRowAmt;
		this->nodesColumnAmount = nodesColAmt;

		createBoard();
		setBoardBordersCords();
	}



	void createBoard();

	void setBoardBordersCords();

	void draw();

	

	//Functionalities

	Coordinates mouseToBoardIndexes(int mouseX, int mouseY);

	bool checkIsMouseOnBoard(int mouse_x, int mouse_y);

	void putObstacles(int mouseX, int mouseY);

	void eraseObstacles(int mouseX, int mouseY);

	



	void callFunctionOnButtonClick();

	void clearObstacles();

	void clearPath();

	void clearBoard();

	void resetAlgorithmAttributes();




	
	







	// -------- A* alghoritm -------- //

	void exploreNodes();

	void setNodeAttributesWhileOpenning(int masterX, int masterY, int selfX, int selfY, int offset);

	int calcGCost(int masterX, int masterY, int selfX, int selfY, int offset);
	int calcHCost(int selfX, int selfY);
	

	bool isNodeInBoard(int x, int y);

	void showPath();

	// -------- A* alghoritm -------- //
	

	



};

