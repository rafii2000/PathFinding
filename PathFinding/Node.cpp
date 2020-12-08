#include "Node.h"



bool Node::isMouseOn()
{

	int mouseX = sf::Mouse::getPosition(*window).x;
	int mouseY = sf::Mouse::getPosition(*window).y;

	float nodeRange = origin + nodeBorder/2;

	if((mouseX >= screenX - nodeRange) and (mouseX <= screenX + nodeRange) and (mouseY >= screenY - nodeRange) and (mouseY <= screenY + nodeRange)) {

		return true;
	}

	return false;
}

void Node::putObstacles()
{
	//put obstacles
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		
		//prevent from making a startNode/endNode an obstacle
		if ( nodeType == START_NODE or nodeType == END_NODE ) return;

		node.setFillColor(sf::Color(70, 70, 70));
		nodeType = OBSTACLE;
	}
}

void Node::eraseObstacles()
{
	//erase obstacles
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		
		//prevent from erasing a startNode/endNode 
		if (nodeType == START_NODE or nodeType == END_NODE) return;

		node.setFillColor(sf::Color(170, 170, 170));
		nodeType = WALKABLE;
	}
}





void Node::draw()
{
	

	//allow or block dragging node
	if (nodeType == START_NODE and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false and sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) == false) {
		if (isMouseOn()) {
			node.setFillColor(sf::Color(0,235,0));
			dragStartNode = true;

		}
		else {
			node.setFillColor(sf::Color::Green);
			dragStartNode = false;
		}
	}

	//allow or block dragging node
	if (nodeType == END_NODE and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false and sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) == false) {
		if (isMouseOn()) {
			node.setFillColor(sf::Color(225, 0, 0));
			dragEndNode = true;

		}
		else {
			node.setFillColor(sf::Color::Red);
			dragEndNode = false;
		}
	}

	
	
	if (isMouseOn()) {

		currentNode = this;

		//dragMode for startNode
		if (dragStartNode == true) {

			//drag node
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) or sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
				
				//prevent from putting node on an obstacle
				if (nodeType == WALKABLE) {
					node.setFillColor(sf::Color::Green);
					nodeType = START_NODE;
					previousStartNode = this;
				}		

			}
			
		}
		//dragMode  for endNode
		else if (dragEndNode == true) {

			//drag node
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) or sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {

				//prevent from putting node on an obstacle
				if (nodeType == WALKABLE) {
					node.setFillColor(sf::Color::Red);
					nodeType = END_NODE;
					previousEndNode = this;
				}

			}
		}
		else {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				putObstacles();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
				eraseObstacles();
			}

		}

		
	}


	if (dragStartNode == true) {

		//this finds temporary starNodes/endNodes and delete them
		if (nodeType == START_NODE  and isMouseOn() == false) {
			
			//this prevent from disappearing previousNode if the mouse in over the obstacles
			if (currentNode != this) {

				//erase (temporary) startNode if mouse doesnt point to endNode or obstacle
				if (currentNode->nodeType == START_NODE) {
					
					nodeType = WALKABLE;
				}
			}
			
		}

	}


	if (dragEndNode == true) {

		//this finds temporary starNodes/endNodes and delete them
		if (nodeType == END_NODE and isMouseOn() == false) {
			
			//this prevent from disappearing previousNode if the mouse in over the obstacles
			if (currentNode != this) {

				//erase (temporary) endNode if mouse doesnt point to startNode or obstacle
				if (currentNode->nodeType == END_NODE) {

					nodeType = WALKABLE;
				}
			}
			
		}

	}


	//clear temporary nodes which was visited to find new place for startNode/endNode
	if (isMouseOn() == 0) {
		
		//if (isObstacle == false and startNode == false and endNode == false) 
		if(nodeType == WALKABLE){
			node.setFillColor(sf::Color(170, 170, 170));
		}

	}
	
	
	//TODO: if mouseToIndex(x,y) == this->node then highlight else return default color
	window->draw(node);

}

void Node::draw2()
{
	window->draw(node);
}

void Node::draw3()
{
	window->draw(node);
}
