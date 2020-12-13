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

void Board::setBoardBordersCords()
{
	
	int firstNodeX = nodesBoard2D[0][0].screenX;
	int firstNodeY = nodesBoard2D[0][0].screenY;
	int lastNodeX = nodesBoard2D.back().back().screenX;
	int lastNodeY = nodesBoard2D.back().back().screenY;

	
	leftBorder = firstNodeX - nodeOrigin - nodeBorder;
	topBorder = firstNodeY - nodeOrigin - nodeBorder;

	//w przypadku gdy granice sie na siebie nakladaja, nalozona granica wskazuje na kolejny"wezel"
	//dlatego tu nie moze byc origin+border, poniewaz ten border przy dzieleniu przez (size+borde) wskazuje na kolejny wezel
	//o wspolrzednych ktorych nie ma w nodesBoard
	rightBorder = lastNodeX + nodeOrigin;
	bottomBorder = lastNodeY + nodeOrigin;
}

void Board::draw()
{
	
	for (int col = 0; col < nodesColumnAmount; col++) {

		for (int row = 0; row < nodesRowAmount; row++) {
			
			nodesBoard2D[col][row].draw();
		}
				
	}
}




Coordinates Board::mouseToBoardIndexes(int mouseX, int mouseY)
{
	//function converts mouse possition to node coordinates in nodesBoard2D
	//wykonuj tylko wtedy gdy mysz jest w Boardzie

	Coordinates nodeCords;
	nodeCords.x = -1;    //bad value
	nodeCords.y = -1;    //bad value

	//jak w tym miejscu nic nie zwracac zeby uniknac sprawdzania czy przeslane wspolrzedne sa dobre czy zle???
	//gdyby cos nie dzialalo to tutaj musze sam w tej funkcji sprawdzac isMouseOnBoard
	//nie moge polegac na inncyh rzeczach
	
	if(isMouseOnBoard == false) return nodeCords; //returns bad coords
	//if(checkIsMouseOnBoard(mouseX, mouseY) == false) return nodeCords; //returns bad coords, na wrazie W

	//determine node position based on mouse coordinates
	int row = (mouseX - leftBorder) / (nodeSize + nodeBorder);
	int col = (mouseY - topBorder) / (nodeSize + nodeBorder);

	nodeCords.x = row;   //good value
	nodeCords.y = col;   //good value

	return nodeCords; //returns good coords

}

bool Board::checkIsMouseOnBoard(int mouse_x, int mouse_y)
{
	//ta funkcja moze nic nie zwracac, tylko przypisac do atrybutu wartosc true lub false

	//check if mouse is outside nodesBoard
	if (mouse_x <= leftBorder or mouse_x >= rightBorder) return false;
	if (mouse_y <= topBorder or mouse_y >= bottomBorder) return false;

	return true;
}

void Board::putObstacles(int mouseX, int mouseY)
{
	
	Coordinates nodeCordsInBoard;
	nodeCordsInBoard = mouseToBoardIndexes(mouseX, mouseY);
	int row = nodeCordsInBoard.x;
	int col = nodeCordsInBoard.y;

	//sprawdzam co zwrocila funkcja mouseToBoardIndexes()
	if (row == -1 or col == -1) return;
	
	//wywoluje moetode obiektu Node 
	//(kod jest bardziej przejrzysty, nie mam dlugich nazw zmiennych)
	nodesBoard2D[col][row].putObstacles();
	
}

void Board::eraseObstacles(int mouseX, int mouseY)
{
	
	Coordinates nodeCordsInBoard;
	nodeCordsInBoard = mouseToBoardIndexes(mouseX, mouseY); //przez ta funkcje dodalem tylko parametry
	int row = nodeCordsInBoard.x;
	int col = nodeCordsInBoard.y;

	//sprawdzam co zwrocila funkcja mouseToBoardIndexes()
	if (row == -1 or col == -1) return;

	nodesBoard2D[col][row].eraseObstacles();
}







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
		resetAlgorithmAttributes();
		//tutaj nie ma CLICKED_BTN = ""; bo po tym zdarzeniu program musi wrocic do petli glownej i
		//z tamtego poziomu wykonywac algorythm, bo inaczej nie bde mogl ladnie tego renderowac
		
	}
	else if (CLICKED_BTN == BREAK_BTN) {

		boardState = ACTIVE;
		
	}
	else if (CLICKED_BTN == BOARD_RESET_BTN) {
		
		//po kliknieciu reset nie moge zrestartowac miejsca wykonywania 
		//symulacji poniewaz te moje int j, int i sa zadeklarowane w main()
		if (boardState == ACTIVE) {
			clearObstacles();
			clearPath();
		}
			
	}
	else if (CLICKED_BTN == PATH_RESET_BTN) {
		
		if (boardState == ACTIVE)
			clearPath();
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

				nodesBoard2D[col][row].nodeState = NONE; //tak dla bezpieczenstwa
				nodesBoard2D[col][row].nodeType = WALKABLE;
				nodesBoard2D[col][row].node.setFillColor(sf::Color(170, 170, 170));
			}

		}
	}

}

void Board::clearPath()
{
	//TODO:  wyczysc openNodes i closedNodes i nextMasterNode

	//Czysci kolory Node'ow, i zmienia ich wartosci? chyba niekonieczne boi robie to na klikniecie start, ale wtedy nie bede mogl rysowac po tym obstacles

	for (int col = 0; col < nodesColumnAmount; col++) {
		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodesBoard2D[col][row].nodeType == WALKABLE) {

				//set default values on each Node in nodesBoard
				nodesBoard2D[col][row].setDefaultAttributes();
			}

		}
	}

}

void Board::clearBoard()
{

	//TODO:  wyczysc openNodes i closedNodes i nextMasterNode

	for (int col = 0; col < nodesColumnAmount; col++) {
		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodesBoard2D[col][row].nodeType != START_NODE and nodesBoard2D[col][row].nodeType != END_NODE) {

				//set default values on each Node in nodesBoard
				nodesBoard2D[col][row].setDefaultAttributes();
			}

		}
	}
}

void Board::resetAlgorithmAttributes()
{
	//ta funkcja wywoluje sie na klikniecie przycisku START

	//this provides that visualization will continue
	//if (IS_PATH_FOUND == true or PATH_NOT_EXIST == true and RUN_ALGORITHM == false) return;

	IS_PATH_FOUND = false;
	PATH_NOT_EXIST = false;

	nextMasterNode = nullptr;
	openNodes.clear();
	closedNodes.clear();
	

	for (int col = 0; col < nodesColumnAmount; col++) {
		for (int row = 0; row < nodesRowAmount; row++) {

			//if (nodesBoard2D[col][row].nodeType != START_NODE and nodesBoard2D[col][row].nodeType != END_NODE and nodesBoard2D[col][row].nodeType != OBSTACLE) {
			if (nodesBoard2D[col][row].nodeType == WALKABLE){
				//set default values on each Node in nodesBoard
				nodesBoard2D[col][row].setDefaultAttributes();
			}

		}
	}

	
	
	
}








// -------- A* ALGORITHM LOGIC -------- //



//TODO: cos jest do poprawy, nie dziala idealnie

//nie dziala bo moj diagonal przenika przez sciany i w momencie gdy przeniknie to Node za sciana ma mniejszy 
//fCost ni potem jak normalnie dotrze do niego algorytm przez masterNode ktory ma offset=10 i wtedy nie podmienia rodzicow
//najprawdopodobniej zakladam taka przyczyne niepoprawnosci algorytmu
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


	/*
	//top-left Node
	if (isNodeInBoard(x - 1, y - 1) == true and nodesBoard2D[y-1][x-1].nodeState != CLOSED and nodesBoard2D[y-1][x-1].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x-1, y-1, forwardCost);
	}

	//top-right Node
	if (isNodeInBoard(x + 1, y - 1) == true and nodesBoard2D[y - 1][x + 1].nodeState != CLOSED and nodesBoard2D[y - 1][x + 1].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x + 1, y - 1, forwardCost);
	}

	//bottom-left Node
	if (isNodeInBoard(x - 1, y + 1) == true and nodesBoard2D[y + 1][x - 1].nodeState != CLOSED and nodesBoard2D[y + 1][x - 1].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x - 1, y + 1, forwardCost);
	}

	//bottom-right Node
	if (isNodeInBoard(x + 1, y + 1) == true and nodesBoard2D[y + 1][x + 1].nodeState != CLOSED and nodesBoard2D[y + 1][x + 1].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x + 1, y + 1, forwardCost);
	}
	*/
		
		
	//sprawdzanie czy openNodes.size() == 0 musi byc w tym miejscu poniewaz inaczej(gdyby bylo u gory) 
	//mam nieskonczona petle, poniewaz dla openNodes.size() == 0 inicjuje petle wstawiajac do niej 
	//jako wartosc poczatkowa starNode a w tym miejscu nie dopuszczam aby wykonala sie instrukcja 
	// if(openNodes.size() == 0 ) po raz drugi i algorytm konczy sie
	if (openNodes.size() == 0) {

		PATH_NOT_EXIST = true;
		return;
	}

	
	

}

void Board::setNodeAttributesWhileOpenning(int masterX, int masterY, int selfX, int selfY, int offset)
{

	if (nodesBoard2D[selfY][selfX].x == endNodeCords.x and nodesBoard2D[selfY][selfX].y == endNodeCords.y) {

		//koniec algorytmu droga znaleziona (openNode pokryl sie z endNode)
		
		// w wezle endNode ustawiam jako rodzica masterNode'a (wtedy funckja showPath() moze byc bezparametrowa);
		IS_PATH_FOUND = true;
		nodesBoard2D[endNodeCords.y][endNodeCords.x].parentNode = &nodesBoard2D[masterY][masterX];
		showPath();
		return;
	}

	nodesBoard2D[selfY][selfX].gCost = calcGCost(masterX, masterY, selfX, selfY, offset);
	nodesBoard2D[selfY][selfX].hCost = calcHCost(selfX, selfY);
	nodesBoard2D[selfY][selfX].fCost = nodesBoard2D[selfY][selfX].gCost + nodesBoard2D[selfY][selfX].hCost;
	
	
	//do otwierania wezlow dopuszczam wszystkie wezly ktore nie sa CLOSED oraz nie sa OBSTACLES, 
	//zeby nie wykluczyc tego wezla przy liczeniu gCost's oraz ewentualnej podmiany rodzica
	//Dlatego zanim dodam wezel do <vectora> openNodes, musze sprawdzic jego nodeState, aby nie zdublowac wynikow 
	if (nodesBoard2D[selfY][selfX].nodeState == NONE) {

		nodesBoard2D[selfY][selfX].nodeState = OPEN;
		nodesBoard2D[selfY][selfX].node.setFillColor(LIGHT_GREEN);
		openNodes.push_back(&nodesBoard2D[selfY][selfX]);
	}

	
	std::cout << "gCost = " << nodesBoard2D[selfY][selfX].gCost <<" ";
	std::cout << "hCost = " << nodesBoard2D[selfY][selfX].hCost << " ";
	std::cout << "fCost = " << nodesBoard2D[selfY][selfX].fCost << " ";
	std::cout << std::endl;


	
}

int Board::calcGCost(int masterX, int masterY, int selfX, int selfY, int offset)
{	
	//gCost - distance form startNode to endNode

	//gCost dla openNode oblicza sie jako suma: openNode.parentNode.gCost oraz offset
	//jesli gCost okaze sie mniejszy od aktualnego, to zmien rodzica oraz gCost


	int cost = 0;

	cost = nodesBoard2D[masterY][masterX].gCost + offset;

	//1) jesli openNode nie ma rodzica to ustaw rodzica jako masterNode oraz obliczony gCost
	if (nodesBoard2D[selfY][selfX].parentNode == nullptr) {
		nodesBoard2D[selfY][selfX].parentNode = &nodesBoard2D[masterY][masterX];
		return cost;
	}

	//2) jesli openNode ma rodzica, to rozwaz czy go podmienic:
	//podmiana zachodzi tylko wtedy gdy droga do openNode przechodza przez masterNode 
	//jest mniejsza od drogi prowadzacej do openNode przez openNode.parentNode
	if (cost < nodesBoard2D[selfY][selfX].gCost) {

		nodesBoard2D[selfY][selfX].parentNode = &nodesBoard2D[masterY][masterX];
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

void Board::showPath()
{
	//STARA WERSJA
	//w parametrach przekazuje wspolrzedne Rodzica wezla ktory dotarl do endNode 
	//wracam sie do tylu po rodzicach az dotre do wezla poczatkowego
	/*Node* currentPathNode = &nodesBoard2D[y][x];
	Node* tempNode;*/


	//NOWA WERSJA
	//funkcja jest bezparametrowa, bo zaczynam wyznaczac droge od endNode'a
	//poniewaz przypisuje mu jako parentNode wartosc masterNode's ktorego openNode pokryl sie z endNode'em
	Node* currentPathNode = nodesBoard2D[endNodeCords.y][endNodeCords.x].parentNode;
	Node* tempNode;
	
	while (currentPathNode->nodeType != START_NODE) {

		currentPathNode->node.setFillColor(LIGHT_YELLOW);
		tempNode = currentPathNode->parentNode;
		currentPathNode = tempNode;
	}

}

// -------- A* ALGORITHM LOGIC -------- //




