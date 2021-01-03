#include "Node.h"



bool Node::isMouseOn(int mouse_x, int mouse_y)
{
	
	int mouseX = mouse_x;
	int mouseY = mouse_y;

	float nodeRange = origin + nodeBorder/2;

	if((mouseX >= screenX - nodeRange) and (mouseX <= screenX + nodeRange) and (mouseY >= screenY - nodeRange) and (mouseY <= screenY + nodeRange))
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
	// Node stuff
	nodeState = NONE;
	nodeType = WALKABLE;
	node.setFillColor(sf::Color(170, 170, 170));

	// A* stuff
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


