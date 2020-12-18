#include "Node.h"


//unused functions because logic has been changed, 
//now any nodesBoard changes are triggered on mouse events, 
//not trggier by Node while rendering in loop
bool Node::isMouseOn(int mouse_x, int mouse_y)
{
	//to chyba nie jest dobra praktyka zeby funkcja ustaala pozycje myszki poza petla pollEvent
	//wiec musze dodac do tej funkcji parametry
	/*int mouseX = sf::Mouse::getPosition(*window).x;
	int mouseY = sf::Mouse::getPosition(*window).y;*/
	int mouseX = mouse_x;
	int mouseY = mouse_y;


	float nodeRange = origin + nodeBorder/2;

	if((mouseX >= screenX - nodeRange) and (mouseX <= screenX + nodeRange) and (mouseY >= screenY - nodeRange) and (mouseY <= screenY + nodeRange)) {

		return true;
	}

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

	nodeState = NONE;
	nodeType = WALKABLE; //to moze do usuniecia
	node.setFillColor(sf::Color(170, 170, 170));

	//TODO: maybe add some A* stuff
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


