#include "Board.h"
#include "Node.h"


void Board::calculateBoardSize() {

	int availableWidth = window->getSize().x - MAIN_LEFT_PADDING - MAIN_RIGHT_PADDING;
	int availableHeight = window->getSize().y - MAIN_TOP_PADDING - MAIN_BOTTOM_PADDING;

	int inputtedBoardWidth = nodesRowAmount * nodeSize + (nodesRowAmount + 1) * nodeBorder;
	int inputtedBoardHeight = nodesColumnAmount * nodeSize + (nodesColumnAmount + 1) * nodeBorder;

	if(inputtedBoardWidth > availableWidth)
		nodesRowAmount = (availableWidth - 1) / (nodeSize + 1);

	if(inputtedBoardHeight > availableHeight)
		nodesColumnAmount = (availableHeight - 1) / (nodeSize + 1);

	//std::cout << "nodes in row: " << (availableWidth - 1) / (nodeSize + 1) << std::endl;
	//std::cout << "nodes in col: " << (availableHeight - 1) / (nodeSize + 1) << std::endl;

}

void Board::createBoard()
{

	int margin_x; 
	int margin_y;
	
	//center nodesBoard on the screen, means find position for the first node
	int nodesBoardWidth = (nodesRowAmount * nodeSize) + ((nodesRowAmount + 1) * nodeBorder);
	int nodesBoardHeight = (nodesColumnAmount * nodeSize) + ((nodesColumnAmount + 1) * nodeBorder);

	std::cout << window->getSize().x << " " << window->getSize().y << std::endl;
	std::cout << nodesBoardWidth << " " << nodesBoardHeight << std::endl;

	margin_x = (window->getSize().x - nodesBoardWidth) / 2 + (nodeSize / 2);
	margin_y = (window->getSize().y - nodesBoardHeight) / 2 + (nodeSize / 2) + board2DMargin;;

	int screenX = margin_x; //first Node X position
	int screenY = margin_y; //first Node Y position

	//std::cout << "margins:" << margin_x << " " << margin_y << std::endl;
	//std::cout << "first Node cords x: " << screenX << " y: " << screenY << std::endl;

	//determine startNode and endNode horizontal position
	int startNodeRowPos = nodesRowAmount / 4;
	int endNodeRowPos = nodesRowAmount / 4 * 3;

	//determine startNode and endNode vertical position
	int nodeColumnPos = nodesColumnAmount / 2;


	//col - vertical	row - horizontal
	for (int col = 0; col < nodesColumnAmount; col++) {

		std::vector<Node> nodesRow;

		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodeColumnPos == col and startNodeRowPos == row) {
				//add startNode to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, START_NODE));
				startNodeCords.x = row;
				startNodeCords.y = col;

			}
			else if (nodeColumnPos == col and endNodeRowPos == row) {
				//add endNode to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, END_NODE));
				endNodeCords.x = row;
				endNodeCords.y = col;
			}
			else {
				//add walkable nodes to the nodesBoard
				nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, WALKABLE));
			}

			screenX += nodeSize + nodeBorder;
		}

		screenX = margin_x;
		screenY += nodeSize + nodeBorder;

		nodesBoard2D.push_back(nodesRow);		

	}

}

void Board::setBoardBordersCords()
{
	//this values help detect if mouse is IN or OUTSIDE the board

	int firstNodeX = nodesBoard2D[0][0].screenX;
	int firstNodeY = nodesBoard2D[0][0].screenY;
	int lastNodeX = nodesBoard2D.back().back().screenX;
	int lastNodeY = nodesBoard2D.back().back().screenY;

	
	leftBorder = firstNodeX - nodeOrigin - nodeBorder;
	topBorder = firstNodeY - nodeOrigin - nodeBorder;

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
	//if mouse is on the board then function convert its position to
	//X and Y coordinates in nodesBoard2D
	
	
	Coordinates nodeCords;
	nodeCords.x = -1;    //bad value
	nodeCords.y = -1;    //bad value
	
	if(isMouseOnBoard == false) return nodeCords; //returns bad coords
	
	//determine node position based on mouse coordinates
	int row = (mouseX - leftBorder) / (nodeSize + nodeBorder);
	int col = (mouseY - topBorder) / (nodeSize + nodeBorder);

	nodeCords.x = row;   //good value
	nodeCords.y = col;   //good value

	return nodeCords; //returns good coords

}

bool Board::checkIsMouseOnBoard(int mouse_x, int mouse_y)
{
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

	//Check, what values have been returned
	if (row == -1 or col == -1) return;
	
	nodesBoard2D[col][row].putObstacles();
	
}

void Board::eraseObstacles(int mouseX, int mouseY)
{
	
	Coordinates nodeCordsInBoard;
	nodeCordsInBoard = mouseToBoardIndexes(mouseX, mouseY);
	int row = nodeCordsInBoard.x;
	int col = nodeCordsInBoard.y;

	//Check, what values have been returned
	if (row == -1 or col == -1) return;

	nodesBoard2D[col][row].eraseObstacles();
}





// -------- BUTTONS FUNCTION -------- //

void Board::callFunctionOnButtonClick()
{

	if (CLICKED_BTN == btn_id::START_BTN) {

		//block board because the visualization is runnig
		std::cout << "START_BTN" << std::endl;
		std::cout << "boardState = BLOCK;" << std::endl;
		RUN_ALGORITHM = true;
		boardState = BLOCK;				
		resetAlgorithmAttributes();				
	}
	else if (CLICKED_BTN == btn_id::BREAK_BTN) {

		RUN_ALGORITHM = false;
		boardState = ACTIVE;		
	}
	else if (CLICKED_BTN == btn_id::BOARD_RESET_BTN) {
		/*if (boardState == ACTIVE)*/
		clearBoard();			
	}
	else if (CLICKED_BTN == btn_id::PATH_RESET_BTN) {		
		/*if (boardState == ACTIVE)*/
		clearPath();
	}
	else if (CLICKED_BTN == btn_id::GENERATE_MAZE_BTN) {
		/*if (boardState == ACTIVE)*/
		boardState = BLOCK;
		std::cout << "Maze is generating" << std::endl;
		generateMaze();		
		boardState = ACTIVE;		
	}
	else if (CLICKED_BTN == btn_id::OPEN_SETTINGS_BTN) {
		/*if (boardState == ACTIVE)*/
		Settings::isOpen = true;
		boardState = BLOCK;
	}

	//sometimes keeping saved previous clicked buttond ID can cause some unexpected behaviour, it is better to reset it
	//CLICKED_BTN = btn_id::NONE;	//move to main()

}

void Board::clearObstacles()
{
	for (int col = 0; col < nodesColumnAmount; col++) {
		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodesBoard2D[col][row].nodeType == OBSTACLE) {

				nodesBoard2D[col][row].nodeState = NONE;
				nodesBoard2D[col][row].nodeType = WALKABLE;
				nodesBoard2D[col][row].node.setFillColor(sf::Color(170, 170, 170));
			}

		}
	}

}

void Board::clearPath()
{
	
	for (int col = 0; col < nodesColumnAmount; col++) {

		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodesBoard2D[col][row].nodeType == WALKABLE) {

				//set default values on choosen node in nodesBoard
				nodesBoard2D[col][row].setDefaultAttributes();
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
				nodesBoard2D[col][row].setDefaultAttributes();
			}
		}
	}
}

void Board::resetAlgorithmAttributes()
{
	
	//function is called on START_BUTTON click
	//reset all Nodes without obstacles, startNode, endNode

	IS_PATH_FOUND = false;
	PATH_NOT_EXIST = false;

	nextMasterNode = nullptr;
	openNodes.clear();
	closedNodes.clear();
	
	for (int col = 0; col < nodesColumnAmount; col++) {

		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodesBoard2D[col][row].nodeType == WALKABLE){
				//set default values on each Node in nodesBoard, which nodeType = WALKABLE
				nodesBoard2D[col][row].setDefaultAttributes();
			}
		}
	}	

}

void Board::generateMaze() {

	srand((unsigned)time(0));

	clearBoard();
	
	int randomRange = 35;

	for (int col = 0; col < nodesColumnAmount; col++) {
		for (int row = 0; row < nodesRowAmount; row++) {

			if (nodesBoard2D[col][row].nodeType == WALKABLE) {

				int result = 1 + (rand() % 100);

				if (result <= randomRange)
					nodesBoard2D[col][row].putObstacles();
			}
		}
	}
}

// -------- BUTTONS FUNCTION -------- //





// -------- A* ALGORITHM LOGIC -------- //

void Board::exploreNodes()
{
	
	int x = 0;  //wspolrzedne aktualnie zamknietego wezla (masterX)
	int y = 0; //wspolrzedne aktualnie zamknietego wezla (masterY)

	
	if (openNodes.size() == 0) {
		//jako wezel poczatkowy uwstaw startNode
		//dodaj go do listy wezlow zbadanych (CLOSED)
		x = startNodeCords.x;
		y = startNodeCords.y;		

		nodesBoard2D[y][x].nodeState = CLOSED;		// ustaw stan startNode's na CLOSED
		closedNodes.push_back(&nodesBoard2D[y][x]); // dodaj startNode do closedNodes
	}
	else {
			
		nextMasterNode = openNodes[0];	// inicjuje pierwsza zmienna do algorytmu szukania minimum
		int index = 0;					// przechowuje index najmniejszego elementu z vectora openNodes
		for (int i = 0; i < openNodes.size(); i++) {

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

		x = nextMasterNode->x;	//przypisuje wspolrzedna X wybranego wezla 
		y = nextMasterNode->y;	//przypisuje wspolrzedna Y wybranego wezla

		nodesBoard2D[y][x].nodeState = CLOSED;				//zmien stan wezla na CLOSED
		closedNodes.push_back(&nodesBoard2D[y][x]);			//dodaj wezel do listy wezlow zbadanych(CLOSED)
		nodesBoard2D[y][x].node.setFillColor(LIGHT_CYAN);	//zmien kolor wezla na kolor wezla o stanie CLOSED
		openNodes.erase(openNodes.begin() + index);			//usun wezel z listy openNodes

		//std::cout << "ClosedNode: " << closedNodes.size() << " OpenNodes: " << openNodes.size() << std::endl;

	}

	
	//odkrywaj ciagle te wezly ktore sa WALKABLE i nie sa CLOSED (umozliwia to aktualizowanie fCost)

	//left Node, offset = 10
	if (isNodeInBoard(x - 1, y) == true and nodesBoard2D[y][x-1].nodeState != CLOSED and nodesBoard2D[y][x-1].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x-1, y, forwardCost);
	}

	//right Node, offset = 10
	if (isNodeInBoard(x + 1, y) == true and nodesBoard2D[y][x+1].nodeState != CLOSED and nodesBoard2D[y][x+1].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x+1, y, forwardCost);
	}

	//top Node, offset = 10
	if (isNodeInBoard(x, y - 1) == true and nodesBoard2D[y-1][x].nodeState != CLOSED and nodesBoard2D[y-1][x].nodeType != OBSTACLE) {

		setNodeAttributesWhileOpenning(x, y, x, y-1, forwardCost);
	}

	//bottom Node, offset = 10
	if (isNodeInBoard(x, y + 1) == true and nodesBoard2D[y+1][x].nodeState != CLOSED and nodesBoard2D[y+1][x].nodeType != OBSTACLE) {
		
		setNodeAttributesWhileOpenning(x, y, x, y+1, forwardCost);
	}


	//Sprawdzanie czy openNodes.size() == 0 musi byc w tym miejscu poniewaz inaczej(gdyby bylo u gory) 
	//petla wykonuje sie w nieskonczonosc, poniewaz dla openNodes.size() == 0 inicjuje petle.
	//Jesli podczas odkrywania wezlow zaden nowy nie zostal dodany do openNodes i openNodes jest zero, algorytm sie konczy
	if (openNodes.size() == 0) {

		PATH_NOT_EXIST = true;
		return;
	}
		

}

void Board::setNodeAttributesWhileOpenning(int masterX, int masterY, int selfX, int selfY, int offset)
{
	//sprawdzam czy aktualnie odkrywany wezel pokrywa sie z endNode
	if (nodesBoard2D[selfY][selfX].x == endNodeCords.x and nodesBoard2D[selfY][selfX].y == endNodeCords.y) {

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
	//Dlatego zanim dodam wezel do <vectora> openNodes, musze sprawdzic jego nodeState, aby nie zdublowac obiektow 
	if (nodesBoard2D[selfY][selfX].nodeState == NONE) {

		nodesBoard2D[selfY][selfX].nodeState = OPEN;
		nodesBoard2D[selfY][selfX].node.setFillColor(LIGHT_GREEN);
		openNodes.push_back(&nodesBoard2D[selfY][selfX]);
	}
	
}

int Board::calcGCost(int masterX, int masterY, int selfX, int selfY, int offset)
{	
	//gCost - odleglosc od startNode do aktualnie odkrywanego wezla
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
	//podmiana zachodzi tylko wtedy gdy droga do openNode przechodzaca przez masterNode 
	//jest mniejsza od drogi prowadzacej do openNode przez openNode.parentNode
	if (cost < nodesBoard2D[selfY][selfX].gCost) {

		nodesBoard2D[selfY][selfX].parentNode = &nodesBoard2D[masterY][masterX];
		return cost;
	}
	

	return nodesBoard2D[selfY][selfX].gCost;
	
}

int Board::calcHCost(int selfX, int selfY)
{	
	//odleglosc od currentNode do endNode

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
	//jesli droga zostanie znaleziona to endNode ma przypisany wskaznik na parentNode
	//i wtedy cofajac sie wyznaczana jest trasa

	Node* currentPathNode = nodesBoard2D[endNodeCords.y][endNodeCords.x].parentNode;
		
	while (currentPathNode->nodeType != START_NODE) {

		currentPathNode->node.setFillColor(LIGHT_YELLOW);
		currentPathNode = currentPathNode->parentNode;		
	}

}

// -------- A* ALGORITHM LOGIC -------- //





// -------- SETTINGS PANEL -------- //

void Board::createBoardFromFile(std::string fileName)
{

	std::ifstream file(fileName);

	if (file) {
		
		std::cout << "File: '" << fileName << "' loaded successfully!" << std::endl;
		 
		//new border values read from file
		int newNodeRowAmt = 0;
		int newNodeColAmt = 0;
		int newNodeSize = 0;

		//auxiliary values
		std::string line;
		int lineIndex = 1;
		int operations = 1;

		//index for nested loop
		int col;

		//values to center border
		int margin_x;
		int margin_y;

		//nodes coordinates
		int screenX; 
		int screenY;

		//clear nodesBoard2D before crete a new one
		nodesBoard2D.clear();

		//scan file and load a board
		while (getline(file, line)) {

			//break if last line is "\n"
			if (line.length() == 0 and lineIndex > 4) break;

			switch (lineIndex) {

				case 1: newNodeRowAmt = atoi(line.c_str()); operations++;	break;
				case 2: newNodeColAmt = atoi(line.c_str()); operations++;	break;
				case 3: newNodeSize = atoi(line.c_str()); operations++;		break;
				case 4: {
					
					//initialize new values
					nodesRowAmount = newNodeRowAmt;
					nodesColumnAmount = newNodeColAmt;
					nodeSize = newNodeSize;
					nodeOrigin = newNodeSize / 2;

					//center nodesBoard on the screen, means find position for the first node
					int nodesBoardWidth = (nodesRowAmount * nodeSize) + ((nodesRowAmount + 1) * nodeBorder);
					int nodesBoardHeight = (nodesColumnAmount * nodeSize) + ((nodesColumnAmount + 1) * nodeBorder);

					margin_x = (window->getSize().x - nodesBoardWidth) / 2 + (nodeSize / 2);
					margin_y = (window->getSize().y - nodesBoardHeight) / 2 + (nodeSize / 2) + board2DMargin;

					screenX = margin_x; //first Node X position
					screenY = margin_y; //first Node Y position

					operations++;					

				} break;
					  
					
				default: {

					std::vector<Node> nodesRow;
					
					col = lineIndex - operations;
					for (int row = 0;  row < line.length(); row++) {

						std::string readNodeType = line.substr(row, 1);

						if (readNodeType == "S") {
							//add startNode to the nodesBoard
							nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, START_NODE));
							startNodeCords.x = row;
							startNodeCords.y = col;

						}
						else if (readNodeType == "E") {
							//add endNode to the nodesBoard
							nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, END_NODE));
							endNodeCords.x = row;
							endNodeCords.y = col;
						}
						else if (readNodeType == "O") {
							//add walkalbelNode to the nodesBoard
							nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, WALKABLE));						
						}
						else if (readNodeType == "X") {
							//add obstacleNode to the nodesBoard
							nodesRow.push_back(Node(nodeSize, nodeBorder, screenX, screenY, row, col, window, OBSTACLE));						
						}						

						//set X possition for the next node
						screenX += nodeSize + nodeBorder;
					}

					//reset X possition and begin new row from margin
					//set Y position for the next row of nodes
					screenX = margin_x;				
					screenY += nodeSize + nodeBorder;

					nodesBoard2D.push_back(nodesRow);
					
				}break;
			}

			lineIndex++;

		}

		setBoardBordersCords();		

	}
	else {
		std::cout << "Load failed: " << "file '" << fileName << "' not found: " << std::endl;
	}

	file.close();
	
}

// -------- SETTINGS PANEL -------- //




