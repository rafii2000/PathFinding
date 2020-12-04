#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class Node;

extern bool dragStartNode;
extern bool dragEndNode;
extern Node *previousStartNode; //indicate the last good node that mouse over was
extern Node* previousEndNode; //indicate the last good node that mouse over was
extern Node *currentNode; //indicate the node that mouse is over now

//define node types
//const std::string startNode = "startNode";
//const std::string endNode = "startNode";
//const std::string obstacles = "obstacles";
//const std::string walkable = "walkable";

const std::string START_NODE = "startNode";
const std::string END_NODE = "endNode";
const std::string OBSTACLE = "obstacle";
const std::string WALKABLE = "walkable";


class Node: sf::RectangleShape
{

friend class A_star;
friend class Board;

private:

	//A* algorithm properties
	int x;
	int y;
	int parrentX; //pointers to 
	int parrentY;
	int gCost; //distance form starting node
	int hCost; //distance from ending node
	int fCost; //sum gCost + hCost
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

	Node(int size, int border, int x, int y, sf::RenderWindow *w, std::string n_type) {
		nodeSize = size;
		nodeBorder = border;
		screenX = x;
		screenY = y;
		origin = size / 2;
		nodeType = n_type;
		window = w;

	
		node.setPosition(screenX, screenY);
		node.setSize(sf::Vector2f(nodeSize, nodeSize));
		node.setOrigin(sf::Vector2f(origin, origin));
		node.setOutlineThickness(nodeBorder);
		node.setFillColor(sf::Color(170, 170, 170));
		node.setOutlineColor(sf::Color(110, 110, 110));


		if (nodeType == START_NODE) {
			std::cout << "startNode" << std::endl;
			node.setFillColor(sf::Color::Green);
		}

		if (nodeType == END_NODE) {
			std::cout << "endNode" << std::endl;
			node.setFillColor(sf::Color::Red);
		}

	}



	bool isMouseOn();
	
	void putObstacles();
	void eraseObstacles();

	
	void draw();

	void draw2();


	friend void mouseFunction(Board& board, int mouse_x, int mouse_y);

};

