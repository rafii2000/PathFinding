#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"



enum node_states { NONE = 0, OPEN, CLOSED };
enum node_types { START_NODE =0, END_NODE, OBSTACLE, WALKABLE};


class Node
{

friend class Board;
friend class Settings;
friend int main();


private:

	sf::RenderWindow* window;	//Render target pointer

	//A* algorithm properties
	int x;		//node position in the nodesBoard2D (index X)
	int y;		//node position in the nodesBoard2D (index Y)
	int gCost;	//distance form starting node to currentNode
	int hCost;	//distance from ending node to currentNode
	int fCost;	//sum gCost + hCost
	short unsigned nodeState = NONE;
	short unsigned nodeType;
	Node* parentNode = nullptr;
	
	//RectangleShape properties
	int screenX;
	int screenY;
	int nodeSize;
	int nodeBorder;
	int origin;	
	sf::RectangleShape node;	

	//Node's colors flags
	sf::Color OBSTACLE_COLOR = sf::Color(70, 70, 70);
	sf::Color WALKABLE_COLOR = sf::Color(170, 170, 170);



public:

	
	//constructor	
	Node(int nodeSize, int nodeBorder, int screenX, int screenY, int boardX, int boardY, sf::RenderWindow *window, short unsigned nodeType) {
		
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

		//set proper Node's color while board is creating
		if (nodeType == START_NODE) {
			node.setFillColor(sf::Color::Green);
			gCost = 0;
		}
		else if (nodeType == END_NODE) {
			node.setFillColor(sf::Color::Red);
		}
		else if (nodeType == WALKABLE) {			
			node.setFillColor(WALKABLE_COLOR);			
		}
		else if (nodeType == OBSTACLE) {
			node.setFillColor(OBSTACLE_COLOR);
		}

	}

	

	bool isMouseOn(int mouseX, int mouseY);

	void putObstacles();
	
	void eraseObstacles();

	void setDefaultAttributes();

	void makeWalkable();
	
	void draw();	

};

