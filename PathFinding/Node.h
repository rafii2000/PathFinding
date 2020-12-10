#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class Node;
class Board;
struct Cords;

enum node_states { NONE = 0, OPEN, CLOSED };

extern bool dragStartNode;
extern bool dragEndNode;
extern Node* previousStartNode; //indicate the last good node that mouse over was
extern Node* previousEndNode; //indicate the last good node that mouse over was
extern Node* currentNode; //indicate the node that mouse is over now


const std::string START_NODE = "startNode";
const std::string END_NODE = "endNode";
const std::string OBSTACLE = "obstacle";
const std::string WALKABLE = "walkable";


class Node: sf::RectangleShape
{



friend class Board;
friend void mouseFunction(Board& board, int mouse_x, int mouse_y);
friend void putObstacles(Board& board);
friend void eraseObstacles(Board& board);
friend Cords mouseToBoardIndexes(Board& board, int mouse_x, int mouse_y);
friend std::string getNodeType(Board& board);
friend bool checkIsMouseOnBoard(Board& board, int mouse_x, int mouse_y);

friend Node* getCurrentNode(Board& board);



friend int main(); //to jest mocno niefajne



private:

	//A* algorithm properties
	int x;
	int y;
	int parrentX; //pointers to 
	int parrentY;
	int gCost; //distance form starting node
	int hCost; //distance from ending node
	int fCost; //sum gCost + hCost
	short unsigned nodeState = NONE;
	Node* parentNode = nullptr; // moze nie bedzie potrzebne ??
	std::string nodeType; // W-walkable | O-obstacle | S-starNode | E-endNode


	//RectangleShape properties
	int screenX;
	int screenY;
	int nodeSize;
	int nodeBorder;
	int origin;
	std::string color;
	sf::RenderWindow *window;
	RectangleShape node;



public:

	
	//constructor
	Node(){}

	Node(int nodeSize, int nodeBorder, int screenX, int screenY, int boardX, int boardY, sf::RenderWindow *window, std::string nodeType) {
		
		this->nodeSize = nodeSize;
		this->nodeBorder = nodeBorder;
		this->screenX = screenX;
		this->screenY = screenY;
		this->x = boardX;
		this->y = boardY;
		this->origin = nodeSize / 2;
		this->nodeType = nodeType;
		this->window = window;

	
		node.setPosition(screenX, screenY);
		node.setSize(sf::Vector2f(nodeSize, nodeSize));
		node.setOrigin(sf::Vector2f(origin, origin));
		node.setOutlineThickness(nodeBorder);
		node.setFillColor(sf::Color(170, 170, 170));
		node.setOutlineColor(sf::Color(110, 110, 110));


		if (nodeType == START_NODE) {
			std::cout << "startNode" << std::endl;
			node.setFillColor(sf::Color::Green);
			gCost = 0;
		}

		if (nodeType == END_NODE) {
			std::cout << "endNode" << std::endl;
			node.setFillColor(sf::Color::Red);
		}

	}



	bool isMouseOn();
	void putObstacles();
	void eraseObstacles();

	void setDefaulValues();

	
	void draw();

	void draw2();

	


	

};

