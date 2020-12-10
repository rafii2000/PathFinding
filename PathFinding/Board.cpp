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

	std::cout << "margins:" << margin_x << " " << margin_y << std::endl;

	int screenX = margin_x; //first Node X position
	int screenY = margin_y; //first Node Y position

	std::cout << "first Node cords x: " << screenX << " y: " << screenY << std::endl;


	
	//determine startNode and endNode horizontal position
	int startNodeRowPos = nodesRowAmount / 4;
	int endNodeRowPos = nodesRowAmount / 4 * 3;

	//determine startNode and endNode vertical position
	int nodeColumnPos = nodesColumnAmount / 2;


	//col = vertical	row = horizontal
	for (int col = 0; col < nodesColumnAmount; col++) {

		std::vector<Node> nodesRow;  //is this a good practice?

		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodeColumnPos == col and startNodeRowPos == row) {
				//add startNode to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, "startNode"));
				startNodeCords.x = row;
				startNodeCords.y = col;

			}
			else if (nodeColumnPos == col and endNodeRowPos == row) {
				//add endNode to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, "endNode"));
				endNodeCords.x = row;
				endNodeCords.y = col;
			}
			else {
				//add walkable nodes to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, "walkable"));
			}

			screenX += nodeSize + nodeBorder; //obramowki nakaldaja sie na siebie
		}

		screenX = margin_x;
		screenY += nodeSize + nodeBorder;

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


// ta funkcja nie tobi tego co ma w nazwie, poniewaz funkcje nie sa wywolywane z jej poziomu, ona tylko zmienia wartosci zmiennej globalnej,
void Board::callFunctionOnButtonClick()
{
	//after call function, change CLICKED_BTN state
	if (CLICKED_BTN == START_BTN) {

		//block board
		//ta funkcja sie niw wywoluje poniewaz przenioslem logike algorytmu do gory,
		//a funkcja nodesBoard.callFunctionOnButtonClick() jest ponizej w sekcji RENDER i dlatego to sie nie wykonuje 
		// no bo CLICKED_BTN jest zmieniony na ""
		std::cout << "boardState = BLOCK;" << std::endl;
		boardState = BLOCK;
		//tutaj nie ma CLICKED_BTN = ""; bo po tym zdarzeniu program musi wrocic do petli glownej i
		//z tamtego poziomu wykonywac algorythm, bo inaczej nie bde mogl ladnie tego renderowac
		
	}
	else if (CLICKED_BTN == STOP_BTN) {

		//unlock board
		boardState = ACTIVE;

		//zakomentowane z tego zamoego powodu co wyzej, przy START_BTN
		/*CLICKED_BTN = "";*/

		//moze warto dodac jeszcze zmienna globalna RUN_ALGHORITHM ktora tu modyfikowac ??
		
	}
	else if (CLICKED_BTN == RESET_BTN) {


		//po kliknieciu reset nie moge zrestartowac miejsca wykonywania 
		//symulacji poniewaz te moje int j, int i sa zadeklarowane w main()
		if(boardState == ACTIVE)
			clearBoard();
		//CLICKED_BTN = "";

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

void Board::clearBoard()
{
	for (int col = 0; col < nodesColumnAmount; col++) {
		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodesBoard2D[col][row].nodeType != START_NODE and nodesBoard2D[col][row].nodeType != END_NODE) {

				//set default values on each Node in nodesBoard
				nodesBoard2D[col][row].setDefaulValues();
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

	//std::cout << "cursor on the nodesBoard" << std::endl;
	return true;
}






// -------- A* ALGORITHM LOGIC -------- //




void Board::exploreNodes()
{
	/*
	 Nodes indication
		1  2  3
		8  X  4
		7  6  5
	*/

	int x = 0;  //wspolrzedne aktualnie zamknietego wezla (masterX)
	int y = 0; //wspolrzedne aktualnie zamknietego wezla (masterY)

	//At the beggining discover nodes around the startNode
	
	/*moge to isntrukcje dodac poza ta funkcja i wszytko powinno smigac*/
	if (openNodes.size() == 0) {
		//jako wezel poczatkowy uwstaw startNode
		//dodaj do do listy wezlow zbadanych (CLOSED)
		x = startNodeCords.x;
		y = startNodeCords.y;		

		nodesBoard2D[y][x].nodeState = CLOSED;
		closedNodes.push_back(&nodesBoard2D[y][x]); // add startNode to closedNodes vector
	}
	else {
		//z listy wybierz wezel o najmniejszym koszcie i go zbadaj(stan CLOSED)
		//x = przypisz wspolrzedna X wybranego Node'a
		//y = przypisz wspolrzedna Y wybranego Node'a
		//dodaj do do listy wezlow zbadanych (CLOSED)


		//TODO: podczas dodawania wezlow do openNodes na bierzaco tworz zestawienie  jaki kolejny wezel bedzie MASTEREM


		//nie moge zrobic ustalanie nextMasterNode w clacGCost poniewaz tam tylko rozpatruje w danum momencie tylko 3 Node'y a nie wszystkie mozliwe
		
		//byc moze tu bdzie jeszcze potrzebny warunek ktory sprawdza czy droga zostala odnaleziona 
		

		//std::cout << "openNodes.size() = " << openNodes.size() << std::endl;
		
		

		
			

		nextMasterNode = openNodes[0];
		int index = 0;  // przechowuje index najmnijeszego elementu z vectora openNodes
		for (int i = 0; i < openNodes.size(); i++) {

			//Find minimum fCost from all openNodes
			//TODO: improve this condition, I this sth is wrong here
			//najpierw porownaj fCost jesli takie same sprawdz hCost
			if (openNodes[i]->fCost < nextMasterNode->fCost){
				nextMasterNode = openNodes[i];
				index = i;
			}
			else if (openNodes[i]->fCost == nextMasterNode->fCost and openNodes[i]->hCost < nextMasterNode->hCost) {
				nextMasterNode = openNodes[i];
				index = i;
			}
		}


		std::cout << "usun z openNodes" << std::endl;
		x = nextMasterNode->x;
		y = nextMasterNode->y;

		nodesBoard2D[y][x].nodeState = CLOSED;
		closedNodes.push_back(&nodesBoard2D[y][x]);
		nodesBoard2D[y][x].node.setFillColor(LIGHT_CYAN);

		
		openNodes.erase(openNodes.begin() + index);	
		std::cout << "openNodes.size(): " << openNodes.size() << std::endl;

	}

	

	
	//odkrywaj ciagle te wezly ktore sa WALKABLE i nie sa CLOSED (umozliwia to aktualizowanie fCost)


	//left Node, offset = 10
	if (isNodeInBoard(x - 1, y) == true and nodesBoard2D[y][x-1].nodeState != CLOSED and nodesBoard2D[y][x-1].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x-1, y, forwardCost);
	}

	//right Node
	if (isNodeInBoard(x + 1, y) == true and nodesBoard2D[y][x+1].nodeState != CLOSED and nodesBoard2D[y][x+1].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x+1, y, forwardCost);
	}

	//top Node
	if (isNodeInBoard(x, y - 1) == true and nodesBoard2D[y-1][x].nodeState != CLOSED and nodesBoard2D[y-1][x].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x, y-1, forwardCost);
	}

	//bottom Node
	if (isNodeInBoard(x, y + 1) == true and nodesBoard2D[y+1][x].nodeState != CLOSED and nodesBoard2D[y+1][x].nodeType != OBSTACLE) {
		
		setNodeAttributesWhileOpenning(x, y, x, y+1, forwardCost);
	}
		
		
	//!!!!!nigdy nie mam openNodes.size() == 1, dla openNodes.size() == 0 inicjuje petle!!!!!!
	if (openNodes.size() == 0) {

		PATH_NOT_EXIST = true;
		return;
	}

	
	

}

void Board::setNodeAttributesWhileOpenning(int masterX, int masterY, int selfX, int selfY, int offset)
{

	if (nodesBoard2D[selfY][selfX].x == endNodeCords.x and nodesBoard2D[selfY][selfX].y == endNodeCords.y) {

		//koniec algorytmu droga znaleziona
		//jak openNode jest endNode to wczesnijesze sprawdzenie go tu nie wpusci
		IS_PATH_FOUND = true;
		showPath(masterX, masterY);
		return;
	}

	/*std::cout << "Node on board" << std::endl;*/
	nodesBoard2D[selfY][selfX].gCost = calcGCost(masterX, masterY, selfX, selfY, offset);
	nodesBoard2D[selfY][selfX].hCost = calcHCost(selfX, selfY);
	nodesBoard2D[selfY][selfX].fCost = nodesBoard2D[selfY][selfX].gCost + nodesBoard2D[selfY][selfX].hCost;
	
	
	

	//poniewaz wczesniej nie sprawdzam czy stan jest OPEN zeby nie wykluczyc tego wezla przy liczeniu gCost oraz podmiany rodzica
	//ale nie moge go ponownie dodawac do listy openNodes
	if (nodesBoard2D[selfY][selfX].nodeState == OPEN) {
		//nie dodawaj ponownie do listy openNodes i nie koloruj
		//nodeState moze miec trzy wartosci NONE / OPEN / ACTIVE
	}
	else if(nodesBoard2D[selfY][selfX].nodeState == NONE){
		nodesBoard2D[selfY][selfX].nodeState = OPEN;
		nodesBoard2D[selfY][selfX].node.setFillColor(LIGHT_GREEN);
		openNodes.push_back(&nodesBoard2D[selfY][selfX]);
	}
	

	//TODO: sprawdz czy odkryty wezel ma taka sama pozycje jak endNode

	

	std::cout << "gCost = " << nodesBoard2D[selfY][selfX].gCost <<" ";
	std::cout << "hCost = " << nodesBoard2D[selfY][selfX].hCost << " ";
	std::cout << "fCost = " << nodesBoard2D[selfY][selfX].fCost << " ";
	std::cout << std::endl;


	
}

int Board::calcGCost(int masterX, int masterY, int selfX, int selfY, int offset)
{	
	//distance form startNode to endNode

	//obliczasz na podstawie gCost Node'a na podstawie ktroego zostala wywolana dla ciebie ta funkcja + dodajesz do niego przesuniecie wzgledem niego(10 lub 14)
	//jesli gCost okaze sie mniejszy od aktualnego, to zmien rodzica oraz gCost

	int cost = 0;

	//proste wnioskowanie: jesli nie ma rodzica no to nie ma gCostu
	//wiec wykonujemy inny zestaw instrukcji i nie sprawdzamy czy podmieniac rodzicow
	
	cost = nodesBoard2D[masterY][masterX].gCost + offset;

	//jesli nie ma rodzica to ustaw mu rodzica jako MASTER oraz obliczony gCost
	if (nodesBoard2D[selfY][selfX].parentNode == nullptr) {
		nodesBoard2D[selfY][selfX].parentNode = &nodesBoard2D[masterY][masterX];
		//std::cout << "wspolrzedne rodzica:" << nodesBoard2D[selfY][selfX].parentNode->x << " " << nodesBoard2D[selfY][selfX].parentNode->y << std::endl;
		return cost;
	}

	//podmiana rodzicow jesli warunek spelniony
	if (cost < nodesBoard2D[selfY][selfX].gCost) {

		nodesBoard2D[selfY][selfX].parentNode = &nodesBoard2D[masterY][masterX];
		//std::cout << "wspolrzedne rodzica:" << nodesBoard2D[selfY][selfX].parentNode->x << " " << nodesBoard2D[selfY][selfX].parentNode->y << std::endl;
		return cost;
	}
	

	return nodesBoard2D[selfY][selfX].gCost;
	
}

int Board::calcHCost(int selfX, int selfY)
{	
	//distance from endNode to startNode

	int cost = 0;
	int deltaX = abs(selfX - endNodeCords.x);
	int deltaY = abs(selfY - endNodeCords.y);
	int deltaDelta = abs(deltaX - deltaY);

	if (deltaX < deltaY) cost = deltaX * diagonalCost + deltaDelta * forwardCost;
	else cost = deltaY * diagonalCost + deltaDelta * forwardCost;

	return cost;

}



bool Board::isNodeInBoard(int x, int y)
{
	
	if (x >= 0 and x < nodesRowAmount) {
		if (y >= 0 and y < nodesColumnAmount) {
			return true;
		}
	}
	return false;
}

void Board::showPath(int x, int y)
{

	// w parametrach przekazuje wspolrzedne Rodzica wezla ktory dotarl do endNode 
	//wracam sie do tylu po jego rodzicach

	Node* currentPathNode = &nodesBoard2D[y][x];
	Node* tempNode;


	for (int i = 0; i < closedNodes.size(); i++) {
		if (closedNodes[i]->parentNode == NULL) { 
			std::cout << "NULL" << std::endl; 
		}
		else {
			std::cout << closedNodes[i]->parentNode->x << " " << closedNodes[i]->parentNode->y << std::endl;
		}
		
	}
	
	std::cout << "wspolrzedne rodzica ktorego dziecko znalazlo endNode "<< x << " " << y << std::endl;
	std::cout << "rodzic rodzica " << nodesBoard2D[y][x].parentNode->x << " " << nodesBoard2D[y][x].parentNode->y << std::endl;


	while (currentPathNode->nodeType != START_NODE) {

		currentPathNode->node.setFillColor(LIGHT_YELLOW);
		tempNode = currentPathNode->parentNode;
		currentPathNode = tempNode;

		//if (currentNode->nodeType == START_NODE) break;
	}



}

// -------- A* ALGORITHM LOGIC -------- //




