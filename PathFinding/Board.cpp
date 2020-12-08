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

	std::cout << "moargins:" << margin_x << " " << margin_y << std::endl;

	int x = margin_x; //first Node X position
	int y = margin_y; //first Node Y position

	std::cout << "first Node cords x: " << x << " y: " << y << std::endl;


	
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
				startNodeCords.x = x;
				startNodeCords.y = y;

			}
			else if (nodeColumnPos == j and endNodeRowPos == i) {
				//add endNode to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, x, y, window, "endNode"));
				endNodeCords.x = x;
				endNodeCords.y = y;
			}
			else {
				//add walkable nodes to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, x, y, window, "walkable"));
			}

			x += nodeSize + nodeBorder; //obramowki nakaldaja sie na siebie
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

void Board::callFunctionFromButton()
{
	//after call function, change buttons clicked state
	if (CLICKED_BTN == START_BTN) {

		//block board
		boardState = BLOCK;
		//tutaj nie ma CLICKED_BTN = ""; bo po tym zdarzeniu program musi wrocic do petli glownej i
		//z tamtego poziomu wykonywac algorythm, bo inaczej nie bde mogl ladnie tego renderowac
		
	}
	else if (CLICKED_BTN == STOP_BTN) {

		//unlock board
		boardState = ACTIVE;
		CLICKED_BTN = "";
		
	}
	else if (CLICKED_BTN == RESET_BTN) {

		if(boardState == ACTIVE)
			clearObstacles();
		CLICKED_BTN = "";

	}
	
	//to zeruje wartosci, moze po to aby potem sie jakies inne funkcje nie wykonywaly
	//po wykonaniu funkcji ta wartosc musi zostac wyzerowana start wizualizacji to nie moze byc w tym miejsu, bo
	//wizualizacja musi byc wykonywana w petli glownej, bo inaczej nie bede mogl ladnie rysowac na Boardzie;
	/*CLICKED_BTN = "";*/
	
}

void Board::clearObstacles()
{
	for (int col = 0; col < nodesColumnAmount; col++) {
		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodesBoard2D[col][row].nodeType == OBSTACLE) {

				nodesBoard2D[col][row].nodeType = WALKABLE;
				nodesBoard2D[col][row].node.setFillColor(sf::Color(170, 170, 170));
			}

		}
	}

}

bool Board::checkIsMouseOnBoard(int mouse_x, int mouse_y)
{

	int size = nodeSize;
	int origin = nodeSize / 2;
	int border = nodeBorder;

	////w przypadku gdy granice sie na siebie nakladaja, nalozona granica wskazuje na kolejny"wezel"
	////dlatego tu nie moze byc origin+border, poniewaz ten border przy dzieleniu przez (size+borde) wskazuje na kolejny wezel
	////o wspolrzednych ktorych nie ma w nodesBoard
	
	int firstNodeX = nodesBoard2D[0][0].screenX;
	int firstNodeY = nodesBoard2D[0][0].screenY;
	int lastNodeX = nodesBoard2D.back().back().screenX;
	int lastNodeY = nodesBoard2D.back().back().screenY;

	int leftBoardBorder = firstNodeX - origin - border;
	int topBoardBorder = firstNodeY - origin - border;
	int rightBoardBorder = lastNodeX + origin;
	int bottomBoardBorder = lastNodeY + origin;

	//check if mouse is outside nodesBoard
	if (mouse_x <= leftBoardBorder or mouse_x >= rightBoardBorder) return false;
	if (mouse_y <= topBoardBorder or mouse_y >= bottomBoardBorder) return false;

	std::cout << "cursor on the nodesBoard" << std::endl;
	return true;
}






void Board::A_star()
{
	// po kliknieciu start uruchomi sie ta funkcja, ktora "pochlonie dzialanie calego programu" dopoki sie nie wywola
	//dlatego po kazdej iteracji jeje petli bede musial wywolywac renderowanie kadego noda'a

	// czy podczas uruchomienia tej funkcji, moje przyciski beda aktywne???? jesli nie to troche kiepsko bo nie bede mogl przerwac tej sumulacji :(
	// i moze nawet nie bedzie potrzebna blokada Board'u bo eventy nie beda odbierane

	for (int col = 0; col < nodesColumnAmount; col++) {

		for (int row = 0; row < nodesRowAmount; row++) {
			//nodesBoard2D[col][row].draw();

			//window->clear();
			if (nodesBoard2D[col][row].nodeType == WALKABLE) {
				nodesBoard2D[col][row].node.setFillColor(sf::Color::Cyan);
			}

			nodesBoard2D[col][row].draw2();// overKill zmieniam  tylko jednego noda
			sf::sleep(sf::milliseconds(2));
			//window->display();	
			
		}

	}

	boardState = ACTIVE;
}

void Board::exploreNodes()
{
	//At the beggining discover nodes around the startNode
	if (dicoveredNodes.size() == 0) {
		int x = startNodeCords.x;
		int y = startNodeCords.y;

		//STEP I
		//1) determine nodes coordinates
		//2) check if it is in the board
		//3) dicover 

		//STEP II
		// 1) for each discove Node, calculate fCost, reference form parrent 
	}
	else {

		//z listy wybierz wezel o najmniejszym koszcie i go odkryj

	}

}

int Board::calcGCost(int x, int y)
{	
	//distance form startNode to endNode
	int cost = 0;
	int deltaX = abs(x - startNodeCords.x);
	int deltaY = abs(y - startNodeCords.y);
	int deltaDelta = abs(deltaX - deltaY);

	if (deltaX < deltaY) cost = deltaX * diagonalCost + deltaDelta * forwardCost;
	else cost = deltaY = diagonalCost + deltaDelta * forwardCost;
	
	return cost;
	
}

int Board::calcHCost(int x, int y)
{	
	//distance from endNode to startNode

	int cost = 0;
	int deltaX = abs(x - endNodeCords.x);
	int deltaY = abs(y - endNodeCords.y);
	int deltaDelta = abs(deltaX - deltaY);

	if (deltaX < deltaY) cost = deltaX * diagonalCost + deltaDelta * forwardCost;
	else cost = deltaY = diagonalCost + deltaDelta * forwardCost;

	return cost;

	return 0;
}





