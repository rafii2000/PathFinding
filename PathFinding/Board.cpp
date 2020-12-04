#include "Board.h"

#include "Node.h"

void Board::createBoard()
{

	int margin_x; //32
	int margin_y; //96;
	
	//center nodesBoard on the screen, means find position for the first node
	int nodesBoardWidth = (nodesRowAmount * nodeSize) + ((nodesRowAmount + 1) * nodeBorder);
	int nodesBoardHeight = (nodesColumnAmount * nodeSize) + ((nodesColumnAmount + 1) * nodeBorder);

	std::cout << window->getSize().x << " " << window->getSize().y << std::endl;
	std::cout << nodesBoardWidth << " " << nodesBoardHeight << std::endl;

	margin_x = (window->getSize().x - nodesBoardWidth) / 2 + (nodeSize / 2);
	margin_y = (window->getSize().y - nodesBoardHeight) / 2 + (nodeSize / 2);

	std::cout << margin_x << " " << margin_y << std::endl;

	int x = margin_x; 
	int y = margin_y;


	
	//determine startNode and endNode horizontal position
	int startNodeRowPos = nodesRowAmount / 4;
	int endNodeRowPos = nodesRowAmount / 4 * 3;

	//determine startNode and endNode vertical position
	int nodeColumnPos = nodesColumnAmount / 2;


	//j - vertical	i=horizontal
	for (int j = 0; j < nodesColumnAmount; j++) {

		std::vector<Node> nodesRow;  //is this a good practice?

		for (int i = 0; i < nodesRowAmount; i++) {

			if (nodeColumnPos == j and startNodeRowPos == i) {
				//add startNode to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, x, y, window, "startNode"));
			}
			else if (nodeColumnPos == j and endNodeRowPos == i) {
				//add endNode to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, x, y, window, "endNode"));
			}
			else {
				//add walkable nodes to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, x, y, window, "walkable"));
			}

			x += nodeSize + nodeBorder;
		}

		x = margin_x;
		y += nodeSize + nodeBorder;

		nodesBoard2D.push_back(nodesRow);		

	}

}

void Board::print_nodes()
{

	for (int col = 0; col < nodesColumnAmount; col++) {

		for (int row = 0; row < nodesRowAmount; row++) {
			
			std::cout << nodesBoard2D[col][row].nodeType << std::endl;
		}
	}
}

void Board::draw()
{
	for (int col = 0; col < nodesColumnAmount; col++) {

		for (int row = 0; row < nodesRowAmount; row++) {
			//nodesBoard2D[col][row].draw();
			nodesBoard2D[col][row].draw2();
		}
		
	}
}

