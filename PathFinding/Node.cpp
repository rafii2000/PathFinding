#include "Node.h"



bool Node::isMouseOn(int mouseX, int mouseY)
{
	if (node.getGlobalBounds().contains(mouseX, mouseY))
		return true;

	return false;
}

void Node::putObstacles()
{
	//put obstacles
	//prevent from making a startNode/endNode an obstacle
	if (nodeType == START_NODE or nodeType == END_NODE) return;

	node.setFillColor(sf::Color(70, 70, 70));
	nodeType = OBSTACLE;
}

void Node::eraseObstacles()
{
	//erase obstacles
	//prevent from erasing a startNode/endNode 
	if (nodeType == START_NODE or nodeType == END_NODE) return;

	node.setFillColor(sf::Color(170, 170, 170));
	nodeType = WALKABLE;
	
}

void Node::setDefaultAttributes()
{
	// Node properties
	nodeState = NONE;
	nodeType = WALKABLE;
	node.setFillColor(sf::Color(170, 170, 170));

	// A* properties
	gCost = 0;
	hCost = 0;
	fCost = 0;
	parentNode = nullptr;

}

void Node::makeWalkable()
{
	nodeType = WALKABLE;
	node.setFillColor(WALKABLE_COLOR);
}

void Node::draw()
{

	window->draw(node);
}


