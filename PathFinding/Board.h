#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Node.h"


struct Cords;
struct WindowElements;

enum board_states { ACTIVE = 0, BLOCK };

extern const std::string START_BTN;
extern const std::string STOP_BTN;
extern const std::string RESET_BTN;
extern std::string CLICKED_BTN;

class Board
{

friend class A_star;
friend class Button;

friend void mouseFunction(Board& board, int mouse_x, int mouse_y);
friend void putObstacles(Board& board);
friend void eraseObstacles(Board& board);
friend Cords mouseToBoardIndexes(Board& board, int mouse_x, int mouse_y);
friend std::string getNodeType(Board& board);
friend bool checkIsMouseOnBoard(Board& board, int mouse_x, int mouse_y);

friend Node* getCurrentNode(Board& board);
friend void renderingThread(WindowElements* we);

friend int main(); //to jest mocno niefajne


struct Coordinates
{
	int x;
	int y;
};

private:

	//Node's properties
	int nodeSize;
	int nodeBorder;
	int nodesRowAmount;
	int nodesColumnAmount;


	sf::Vector2i wspolrzedne{10,10};
	

	//Board
	short unsigned boardState = ACTIVE;
	sf::RenderWindow* window;
	std::vector< std::vector<Node> > nodesBoard2D;

	//A* alghoritm
	Coordinates startNodeCords;
	Coordinates endNodeCords;

	int diagonalCost = 14;
	int forwardCost = 10;


	std::vector<Node> dicoveredNodes;





public:


	Board(){}

	Board(sf::RenderWindow& w, int nSize, int nBorder,  int nRowAmt, int nColAmt) {

		window = &w;
		nodeSize = nSize;
		nodeBorder = nBorder;
		nodesRowAmount = nRowAmt;
		nodesColumnAmount = nColAmt;

		createBoard();
	}


	void createBoard();

	void print_nodes();

	void draw();

	
	//Functionalities

	void callFunctionFromButton();
	void clearObstacles();



	bool checkIsMouseOnBoard(int mouse_x, int mouse_y);
	



	//A* alghoritm

	void A_star();

	void exploreNodes();

	bool isNodeOnBoard();

	int calcGCost(int x, int y);
	int calcHCost(int x, int y);
	

	



};

