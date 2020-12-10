#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Node.h"


struct Cords;

enum board_states { ACTIVE = 0, BLOCK };

extern const std::string START_BTN;
extern const std::string STOP_BTN;
extern const std::string RESET_BTN;
extern std::string CLICKED_BTN;

extern bool IS_PATH_FOUND;
extern bool PATH_NOT_EXIST;



class Board
{


friend class Button;

friend void mouseFunction(Board& board, int mouse_x, int mouse_y);
friend void putObstacles(Board& board);
friend void eraseObstacles(Board& board);
friend Cords mouseToBoardIndexes(Board& board, int mouse_x, int mouse_y);
friend std::string getNodeType(Board& board);
friend bool checkIsMouseOnBoard(Board& board, int mouse_x, int mouse_y);

friend Node* getCurrentNode(Board& board);


friend int main(); //to jest mocno niefajne


struct Coordinates{
	int x;
	int y;
};



private:

	//Node's properties
	int nodeSize;
	int nodeBorder;
	int nodesRowAmount;
	int nodesColumnAmount;

	//Node's colors flags
	sf::Color LIGHT_GREEN = sf::Color(128, 255, 0, 200);
	sf::Color LIGHT_YELLOW = sf::Color(255, 255, 0, 200);
	sf::Color LIGHT_CYAN = sf::Color(138, 249, 255, 200);

	
	//Board
	short unsigned boardState = ACTIVE;
	sf::RenderWindow* window;
	std::vector< std::vector<Node> > nodesBoard2D;


	//A* alghoritm
	Coordinates startNodeCords;
	Coordinates endNodeCords;
	Node* nextMasterNode = nullptr; // maybe nextClosedNode would be a better name ?

	int diagonalCost = 14;
	int forwardCost = 10;

	std::vector<Node*> openNodes;  //openNodes
	std::vector<Node*> closedNodes;  //closedNodes


	//Variables to manage vizualization (start / stop / reset)
	//One beda zmienione, poniewaz wizualizacje bedzie wygladac w inny sposob
	//wartosci domyœlne dla zmiennych to: int i = 0, j = 0; int col = -1, row = 1; - wizualizacja sie nie wykonuje
	int i = 0, j = 0;  // zmiene ktore steruja aktualnym stanem wizualizacji, np: 10% lub 35% lub 90%
	int col = -1, row = 1; // zmienne ktore inicjalizuja rozpoczecie wizualizacji i mog¹ j¹ te¿ zakoñczyæ
	





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

	//to remove if project will work
	void print_nodes();

	void draw();

	
	//Functionalities

	void callFunctionOnButtonClick();
	void clearObstacles();
	void clearBoard();


	//using
	bool checkIsMouseOnBoard(int mouse_x, int mouse_y);
	







	// -------- A* alghoritm -------- //

	void exploreNodes();

	void setNodeAttributesWhileOpenning(int masterX, int masterY, int selfX, int selfY, int offset);

	int calcGCost(int masterX, int masterY, int selfX, int selfY, int offset);
	int calcHCost(int selfX, int selfY);
	int calcFCost(int x, int y);


	bool isNodeInBoard(int x, int y);

	void showPath(int x, int y);

	// -------- A* alghoritm -------- //
	

	



};

