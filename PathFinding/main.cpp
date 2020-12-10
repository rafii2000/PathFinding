#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"



#include "Node.h"
#include "Board.h"
#include "Button.h"



struct  Cords
{
    int x;
    int y;
};



//to jest do susniecia trzymam tylko poto zeby dziala funkcja draw() w Node w razie W
bool dragStartNode;
bool dragEndNode;
Node* previousStartNode = nullptr; //indicate the last good node that mouse over was
Node* previousEndNode = nullptr; //indicate the last good node that mouse over was
Node* currentNode = nullptr; //indicate the node that mouse is over now




Node *mouseOnNode = nullptr;

//mouse state flags
const std::string PRESSED = "pressed";
const std::string LEFT_PRESSED = "left";
const std::string RIGHT_PRESSED = "right";
const std::string RELEASED = "released";

//mouse properties
int mouseX;
int mouseY;
bool isMouseOnBoard = false;
std::string mouseState = RELEASED;

//buttons state flags
bool CLICK_EVENT = false;
const std::string START_BTN = "start_btn";
const std::string STOP_BTN = "stop_btn";
const std::string RESET_BTN = "reset_btn";
std::string CLICKED_BTN = "";



//Node properties
Cords nodeCords;
int nodeRow = -1;
int nodeCol = -1;

std::string currentNodeType;

//A*

bool RUN_ALGORITHM = false;

bool IS_PATH_FOUND = false;
bool PATH_NOT_EXIST = false;







int main()
{

    // ------------ INITIALIZE ELEMENTS / OBJECTS ------------ //

    // Create the main window    
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height), "SFML PathFinding");
    window.setPosition(sf::Vector2i(-8, 0));
    window.setFramerateLimit(140);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial_narrow_7.ttf")) return EXIT_FAILURE;
    sf::Text text("SFML PathFinding visualization", font, 50);
    text.setPosition(sf::Vector2f(79, 20));
   
    // Create a most important part of program - board of nodes
    Board nodesBoard(window, 30, 1, 58, 27);
        
    // Create buttons to display
    Button startButton(1300, 35, 130, 50, &font, "Start",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), "start_btn"
    );

    Button stopButton(1500, 35, 130, 50, &font, "Stop",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), "stop_btn"
    );

    Button resetButton(1700, 35, 130, 50, &font, "Reset",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), "reset_btn"
    );
    
    // ------------ INITIALIZE ELEMENTS / OBJECTS ------------ //
    

  
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            //Mouse events
            CLICK_EVENT = false;
            if (event.type == sf::Event::MouseButtonPressed) {

                //put obstacles
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    std::cout << "LEFT pressed detected" << std::endl;
                    mouseState = LEFT_PRESSED;
                }

                //erase obstacles
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    std::cout << "RIGHT pressed detected" << std::endl;
                    mouseState = RIGHT_PRESSED;
                }               
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                //std::cout << "released detected" << std::endl;
               
                mouseState = RELEASED;
                CLICK_EVENT = true;
            }
            

            if (event.type == sf::Event::MouseMoved) {        
                
                //set mouse position
                mouseX = sf::Mouse::getPosition(window).x;
                mouseY = sf::Mouse::getPosition(window).y;
                //std::cout << "X: " <<mouseX << " Y: " << mouseY << std::endl;

                //check is mouse on board 
                isMouseOnBoard = nodesBoard.checkIsMouseOnBoard(mouseX, mouseY);

            }    
        }

        // ------ SET MAIN VARIABLES EVERY EACH ITERATION ------ //
        
        if (isMouseOnBoard == true) {

            mouseOnNode = getCurrentNode(nodesBoard);
           
            nodeCords = mouseToBoardIndexes(nodesBoard, mouseX, mouseY);
            nodeRow = nodeCords.x; //current which Node mouse is over
            nodeCol = nodeCords.y; //current which Node mouse is over
                      
        }
       
        // ------ SET MAIN VARIABLES EVERY EACH ITERATION ------ //
        




        // ------------ BUTTONS LOGIC FUNCTION ------------ //

        if (isMouseOnBoard == false) {
            sf::Vector2f Mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            startButton.update(Mouse);
            stopButton.update(Mouse);
            resetButton.update(Mouse);
        }

        nodesBoard.callFunctionOnButtonClick();

        // ------------ BUTTONS LOGIC FUNCTION ------------ //






        // ------------ BOARD LOGIC FUNCTION ------------ //

        if (isMouseOnBoard == true and nodesBoard.boardState == ACTIVE) {

            if (mouseState == LEFT_PRESSED) {

                putObstacles(nodesBoard);
            }

            if (mouseState == RIGHT_PRESSED) {

                eraseObstacles(nodesBoard);
            }

            if (mouseState == RELEASED) {
            }

        }

        // ------------ BOARD LOGIC FUNCTION ------------ //






        // ------------ A* ALGHORITHM ------------ //
        
        if (CLICKED_BTN == START_BTN) {
            std::cout << "START_BTN" << std::endl;
            //zainicjuj rozpoczecie wizualizacji, tylko raz
            nodesBoard.col = nodesBoard.nodesColumnAmount;
            nodesBoard.row = nodesBoard.nodesRowAmount;

            RUN_ALGORITHM = true;
            CLICKED_BTN = "";
        }
        else if (CLICKED_BTN == STOP_BTN) {
            RUN_ALGORITHM = false;
            CLICKED_BTN = "";
        }
        else if (CLICKED_BTN == RESET_BTN and nodesBoard.boardState == ACTIVE) {
            
            nodesBoard.col = -1;
            nodesBoard.row = -1;
            nodesBoard.j = 0;
            nodesBoard.i = 0;
            CLICKED_BTN = "";
        }


        if (RUN_ALGORITHM == true) {

            //std::cout << "RUN_ALGORITHM == true" << std::endl;
            //std::cout << j << " " << i << std::endl;
            //nodesBoard.nodesBoard2D[nodesBoard.j][nodesBoard.i].node.setFillColor(sf::Color::Cyan);
            sf::sleep(sf::microseconds(10));
            nodesBoard.i++;

            nodesBoard.exploreNodes();
        }


        //ta czesc kodu jest niepotrzebna iteracja jest na innej zasadzie
        /*if (nodesBoard.i % nodesBoard.row == 0 and RUN_ALGORITHM == true) {
           
            nodesBoard.i = 0;
            nodesBoard.j++;
        }*/


        // warunek zakonczenia wizualizacji
        if (IS_PATH_FOUND == true or PATH_NOT_EXIST == true) {
            CLICKED_BTN = "";
            RUN_ALGORITHM = false;
            nodesBoard.boardState = ACTIVE;
        }

       /* if (nodesBoard.j == 27 and nodesBoard.i == 0) {
            std::cout << "wizualizacja zakonczona" << std::endl;
            nodesBoard.col = -1;
            nodesBoard.row = -1;
            nodesBoard.j = 0;
            nodesBoard.i = 0;
            CLICKED_BTN = "";
            RUN_ALGORITHM = false;
            nodesBoard.boardState = ACTIVE;
        }*/

        // ------------ A* ALGHORITHM ------------ //

       
       


        
        // ------------ RENDERING FUNCTION ------------ //
        // Clear screen
        window.clear(sf::Color(170, 170, 170));


        // Draw elements
        window.draw(text);
        
        nodesBoard.draw();

       
        startButton.render(&window);
        stopButton.render(&window);
        resetButton.render(&window);


        // Update the window
        window.display();

        // ------------ RENDERING FUNCTION ------------ //
        

    }
    return EXIT_SUCCESS;
}




void mouseFunction(Board& board, int mouse_x, int mouse_y) {

    int size = board.nodeSize;
    int origin = board.nodeSize / 2;
    int border = board.nodeBorder;

    int firstNodeX = board.nodesBoard2D[0][0].screenX - origin - border;
    int firstNodeY = board.nodesBoard2D[0][0].screenY - origin - border;
    //w przypadku gdy granice sie na siebie nakladaja, nalozona granica daje wskazuje na kolejny"wezel"
    //dlatego tu nie moze byc origin+border, poniewaz ten border przy dzieleniu przez (size+borde) wskazuje na kolejny wezel, 
    //o wspolrzednych ktorych nie ma w nodesBoard
    int lastNodeX = board.nodesBoard2D.back().back().screenX + origin;
    int lastNodeY = board.nodesBoard2D.back().back().screenY + origin;

    //check if mouse is outside nodesBoard
    if (mouse_x <= firstNodeX or mouse_x >= lastNodeX) return;
    if (mouse_y <= firstNodeY or mouse_y >= lastNodeY) return;
    std::cout << "cursor on the nodesBoard" << std::endl;

    //determine node position based on mouse coordinates
    int row = (mouse_x - firstNodeX) / (size + border);
    int col = (mouse_y - firstNodeY) / (size + border);

    std::cout << mouse_x << " " << mouse_y << std::endl;
    //w przypadku gdy granice sie na siebie nakladaja, nalozona granica daje wskazuje na kolejny"wezel"
    board.nodesBoard2D[col][row].node.setFillColor(sf::Color::Cyan);

 }


bool checkIsMouseOnBoard(Board& board, int mouse_x, int mouse_y) {

    int size = board.nodeSize;
    int origin = board.nodeSize / 2;
    int border = board.nodeBorder;

    //int firstNodeX = board.nodesBoard2D[0][0].screenX - origin - border;
    //int firstNodeY = board.nodesBoard2D[0][0].screenY - origin - border;
    ////w przypadku gdy granice sie na siebie nakladaja, nalozona granica wskazuje na kolejny"wezel"
    ////dlatego tu nie moze byc origin+border, poniewaz ten border przy dzieleniu przez (size+borde) wskazuje na kolejny wezel
    ////o wspolrzednych ktorych nie ma w nodesBoard
    //int lastNodeX = board.nodesBoard2D.back().back().screenX + origin;
    //int lastNodeY = board.nodesBoard2D.back().back().screenY + origin;

    int firstNodeX = board.nodesBoard2D[0][0].screenX;
    int firstNodeY = board.nodesBoard2D[0][0].screenY;
    int lastNodeX = board.nodesBoard2D.back().back().screenX;
    int lastNodeY = board.nodesBoard2D.back().back().screenY;

    int leftBoardBorder = firstNodeX - origin - border;
    int topBoardBorder = firstNodeY - origin - border;
    int rightBoardBorder = lastNodeX + origin;
    int bottomBoardBorder = lastNodeY + origin;

    //check if mouse is outside nodesBoard
    std::cout << "check cursor possition" << std::endl;

    //jak w tym miejscu nic nie zwracac zeby uniknac sprawdzania czy przeslane wspolrzedne sa dobre czy zle
    if (mouse_x <= leftBoardBorder or mouse_x >= rightBoardBorder) return false;    
    if (mouse_y <= topBoardBorder or mouse_y >= bottomBoardBorder) return false;

    std::cout << "cursor on the nodesBoard" << std::endl;
    return true;
   
}

Cords mouseToBoardIndexes(Board& board, int mouse_x, int mouse_y) {
    
    Cords newCords;
    newCords.x = -1;    //bad value
    newCords.y = -1;    //bad value

    int size = board.nodeSize;
    int origin = board.nodeSize / 2;
    int border = board.nodeBorder;

    //int firstNodeX = board.nodesBoard2D[0][0].screenX - origin - border;
    //int firstNodeY = board.nodesBoard2D[0][0].screenY - origin - border;
    ////w przypadku gdy granice sie na siebie nakladaja, nalozona granica wskazuje na kolejny"wezel"
    ////dlatego tu nie moze byc origin+border, poniewaz ten border przy dzieleniu przez (size+borde) wskazuje na kolejny wezel
    ////o wspolrzednych ktorych nie ma w nodesBoard
    //int lastNodeX = board.nodesBoard2D.back().back().screenX + origin;
    //int lastNodeY = board.nodesBoard2D.back().back().screenY + origin;

    int firstNodeX = board.nodesBoard2D[0][0].screenX;
    int firstNodeY = board.nodesBoard2D[0][0].screenY;
    int lastNodeX = board.nodesBoard2D.back().back().screenX;
    int lastNodeY = board.nodesBoard2D.back().back().screenY;

    int leftBoardBorder = firstNodeX - origin - border;
    int topBoardBorder = firstNodeY - origin - border;
    int rightBoardBorder = lastNodeX + origin;
    int bottomBoardBorder = lastNodeY + origin;

    //check if mouse is outside nodesBoard
    //std::cout << "check cursor possition" << std::endl;

    //jak w tym miejscu nic nie zwracac zeby uniknac sprawdzania czy przeslane wspolrzedne sa dobre czy zle
    if (mouse_x <= leftBoardBorder or mouse_x >= rightBoardBorder) {
        isMouseOnBoard = false;
        return newCords;  //returns bad coords
    }
    if (mouse_y <= topBoardBorder or mouse_y >= bottomBoardBorder) {
        isMouseOnBoard = false;
        return newCords; //returns bad coords
    }
        
    //std::cout << "cursor on the nodesBoard" << std::endl;
    isMouseOnBoard = true;
    //determine node position based on mouse coordinates
    int row = (mouse_x - leftBoardBorder) / (size + border);
    int col = (mouse_y - topBoardBorder) / (size + border);
    
    newCords.x = row;   //good value
    newCords.y = col;   //good value
    
    return newCords;
  
}





void putObstacles(Board &board)
{
    Cords nodeCordsInBoard;
    nodeCordsInBoard = mouseToBoardIndexes(board, mouseX, mouseY);
    int row = nodeCordsInBoard.x;
    int col = nodeCordsInBoard.y;

    //check if mouse is on the board
    if (row == -1 or col == -1) return;  
   
    Node *node = &board.nodesBoard2D[col][row];

    //check if mouse is not over the START_NODE or END_NODE
    if (node->nodeType == START_NODE or node->nodeType == END_NODE or node->nodeType == OBSTACLE) return;
    node->nodeType = OBSTACLE;     
    node->node.setFillColor(sf::Color(70,70,70));
}

void eraseObstacles(Board& board)
{
    Cords nodeCordsInBoard;
    nodeCordsInBoard = mouseToBoardIndexes(board, mouseX, mouseY);
    int row = nodeCordsInBoard.x;
    int col = nodeCordsInBoard.y;

    //check if mouse is on the board
    if (row == -1 or col == -1) return;

    Node* node = &board.nodesBoard2D[col][row];

    //check if mouse is not over the START_NODE or END_NODE
    if (node->nodeType == START_NODE or node->nodeType == END_NODE or node->nodeType == WALKABLE) return;
    node->nodeType = WALKABLE;
    node->node.setFillColor(sf::Color(170, 170, 170));
}

void dragNode(Board& board) {

}







std::string getNodeType(Board& board) {
    
    Cords nodeCords;
    nodeCords = mouseToBoardIndexes(board, mouseX, mouseY);
    if (isMouseOnBoard == true) {
        return board.nodesBoard2D[nodeCords.y][nodeCords.x].nodeType;
    }

    return "";
    
}

Node* getCurrentNode(Board &board) {

    nodeCords = mouseToBoardIndexes(board, mouseX, mouseY);
    return &board.nodesBoard2D[nodeCords.y][nodeCords.x];    
}



Cords getMouseCords() {

    Cords mouseCords;
    mouseCords.x = mouseX;
    mouseCords.y = mouseY;

    return mouseCords;

}



