#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Node.h"
#include "Board.h"
#include "Button.h"




//mouse state flags
const std::string PRESSED = "pressed";
const std::string LEFT_PRESSED = "left";
const std::string RIGHT_PRESSED = "right";
const std::string RELEASED = "released";


//mouse properties
int mouseX; //zastanawiam sie czy importowac to jako zmienne globalne do klasy Board, zeby funkcje mogly byc bezparametrowe??
int mouseY; //zastanawiam sie czy importowac to jako zmienne globalne do klasy Board, zeby funkcje mogly byc bezparametrowe??
std::string mouseState = RELEASED;


//buttons state flags
bool CLICK_EVENT = false;
const std::string START_BTN = "start_btn";
const std::string BREAK_BTN = "break_btn";
const std::string PATH_RESET_BTN = "path_reset_btn";
const std::string BOARD_RESET_BTN = "board_reset_btn";
std::string CLICKED_BTN = "";


//drag mode flags
bool DRAG_MODE = false;
bool START_NODE_DRAG_MODE = false;
bool END_NODE_DRAG_MODE = false;


//A*
bool RUN_ALGORITHM = false; //change to ALGORITHM_STATE: RUNNING | STOPPED | FINISHED
bool IS_PATH_FOUND = false;
bool PATH_NOT_EXIST = false;
bool ALLOW_DIAGONAL = false;







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
        
    // Create buttons
    Button startButton(1100, 35, 130, 50, &font, "Start",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), START_BTN
    );

    Button breakButton(1300, 35, 130, 50, &font, "Break",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), BREAK_BTN
    );

    
    Button pathResetButton(1500, 35, 130, 50, &font, "Path Reset",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), PATH_RESET_BTN
    );

    Button boardResetButton(1700, 35, 130, 50, &font, "Board Reset",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), BOARD_RESET_BTN
    );

    //TODO: Add button allow/disallow diagonal
   
    
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
                    /*std::cout << "LEFT pressed detected" << std::endl;*/
                    mouseState = LEFT_PRESSED;
                }

                //erase obstacles
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    /*std::cout << "RIGHT pressed detected" << std::endl;*/
                    mouseState = RIGHT_PRESSED;
                }               
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                /*std::cout << "Released detected" << std::endl; */              
                mouseState = RELEASED;
                CLICK_EVENT = true;
            }
            

            if (event.type == sf::Event::MouseMoved) {        
                
                //set mouse position
                mouseX = sf::Mouse::getPosition(window).x;
                mouseY = sf::Mouse::getPosition(window).y;
                //std::cout << "X: " <<mouseX << " Y: " << mouseY << std::endl;

                //check is mouse on board 
                nodesBoard.isMouseOnBoard = nodesBoard.checkIsMouseOnBoard(mouseX, mouseY);

            }    
        }





        // ------ SET MAIN VARIABLES EVERY EACH ITERATION ------ //
        if (nodesBoard.isMouseOnBoard == true) {

                                  
        }
        // ------ SET MAIN VARIABLES EVERY EACH ITERATION ------ //
        






        // ------------ BUTTONS LOGIC FUNCTION ------------ //

        if (nodesBoard.isMouseOnBoard == false) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            startButton.update(mousePos);
            breakButton.update(mousePos);
            pathResetButton.update(mousePos);
            boardResetButton.update(mousePos);
        }

        nodesBoard.callFunctionOnButtonClick();

        // ------------ BUTTONS LOGIC FUNCTION ------------ //






        // ------------ BOARD FUNCTIONALITIES ------------ //

        if (nodesBoard.isMouseOnBoard == true and nodesBoard.boardState == ACTIVE) {

            //ISTNIEJE BLAD START_NODE I END_NODE MOGA NALOZYC SIE NA SIEBIE I WTEDY POJAWIA SIE PROBLEM !!!!!!!!!
            //po najechaniu na end node i nastepnie po kliknieciu w end node i przejechaniu przez start node cos sie buguje
           
            //drag mode cases
            if (mouseState == LEFT_PRESSED and START_NODE_DRAG_MODE == true) {

               /* std::cout << "koloruj na zielono" << std::endl;*/
                int currentNodeX = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).x; //dwa razy wywoluje ta sama funckje
                int currentNodeY = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).y; //dwa razy wywoluje ta sama funckje


                //forbid dragging starNode on obstaclesand endNode
                if (nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].nodeType == WALKABLE) {

                    //tu musze sprawdzic czy nie podmieniam samego siebie 

                    if (&nodesBoard.nodesBoard2D[currentNodeY][currentNodeX] != nodesBoard.currentDrgged) {
                        nodesBoard.previousDrgged = nodesBoard.currentDrgged;
                        nodesBoard.currentDrgged = &nodesBoard.nodesBoard2D[currentNodeY][currentNodeX];

                        //swap walkable Node's  with starNode 
                        nodesBoard.startNodeCords.x = currentNodeX;
                        nodesBoard.startNodeCords.y = currentNodeY;
                        nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].nodeType = START_NODE;

                        nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].node.setFillColor(sf::Color::Green);
                    }                  
                    
                }
                    
            }
            else if (mouseState == LEFT_PRESSED and END_NODE_DRAG_MODE == true) {

                /*std::cout << "koloruj na czerwono" << std::endl;*/
                int currentNodeX = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).x;
                int currentNodeY = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).y;

                //forbid dragging endNode on obstacles and startNode
                if (nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].nodeType == WALKABLE) {

                    if (&nodesBoard.nodesBoard2D[currentNodeY][currentNodeX] != nodesBoard.currentDrgged) {
                        nodesBoard.previousDrgged = nodesBoard.currentDrgged;
                        nodesBoard.currentDrgged = &nodesBoard.nodesBoard2D[currentNodeY][currentNodeX];

                        //swap walkable Node's  with endNode                        
                        nodesBoard.endNodeCords.x = currentNodeX;
                        nodesBoard.endNodeCords.y = currentNodeY;

                        nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].nodeType = END_NODE;

                        nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].node.setFillColor(sf::Color::Red);
                    }

                }
                    
            }


            //clear doubled startNode
            if (START_NODE_DRAG_MODE == true) {

                if (nodesBoard.previousDrgged != nullptr) {
                    nodesBoard.previousDrgged->makeWalkable();
                }
                                                                
            }
            //clear doubled endNode
            else if (END_NODE_DRAG_MODE == true) {

                if (nodesBoard.previousDrgged != nullptr) {
                    nodesBoard.previousDrgged->makeWalkable();
                }
                                    
            }





            if (mouseState == LEFT_PRESSED and DRAG_MODE == false) {
                
                nodesBoard.putObstacles(mouseX, mouseY);
            }

            if (mouseState == RIGHT_PRESSED and DRAG_MODE == false ) {
                
                nodesBoard.eraseObstacles(mouseX, mouseY);
            }




            if (mouseState == RELEASED) {
                
                //Manage draging mode
                sf::Color START_NODE_HOVER = sf::Color(0, 220, 0);
                sf::Color END_NODE_HOVER = sf::Color(220, 0, 0);

                //START_NODE_DRAG_MODE
                int startNodeX = nodesBoard.startNodeCords.x;
                int startNodeY = nodesBoard.startNodeCords.y;

                //END_NODE_DRAG_MODE
                int endNodeX = nodesBoard.endNodeCords.x;
                int endNodeY = nodesBoard.endNodeCords.y;


                //tutaj to wszystko pod jednym ifem nie nie zadzaial, DRAG_MODE mode musze rozbic na dwa 
                if (nodesBoard.nodesBoard2D[startNodeY][startNodeX].isMouseOn(mouseX, mouseY) == true) {
                   
                    START_NODE_DRAG_MODE = true;
                   
                    nodesBoard.currentDrgged = &nodesBoard.nodesBoard2D[startNodeY][startNodeX];
                    nodesBoard.nodesBoard2D[startNodeY][startNodeX].node.setFillColor(START_NODE_HOVER);
                }
                else {

                    START_NODE_DRAG_MODE = false;                                     
                    nodesBoard.nodesBoard2D[startNodeY][startNodeX].node.setFillColor(sf::Color::Green);
                }
                

                //else tego ifa czysci mi currentNode dla startNode
                if (nodesBoard.nodesBoard2D[endNodeY][endNodeX].isMouseOn(mouseX, mouseY) == true) {

                    END_NODE_DRAG_MODE = true;
                  
                    nodesBoard.currentDrgged = &nodesBoard.nodesBoard2D[endNodeY][endNodeX];
                    nodesBoard.nodesBoard2D[endNodeY][endNodeX].node.setFillColor(END_NODE_HOVER);
                }
                else {                                       
                    END_NODE_DRAG_MODE = false;                     
                    nodesBoard.nodesBoard2D[endNodeY][endNodeX].node.setFillColor(sf::Color::Red);
                }

                //konieczny if, bez niego nie moge ustalac prawidlowych wartosci zmiennych
                //zapobiega usuwaniu przez if'a dla endNode to co bylo ustawione w if'e startNode
                if (START_NODE_DRAG_MODE == true or END_NODE_DRAG_MODE == true) {
                    
                    DRAG_MODE = true;
                }
                else {

                    DRAG_MODE = false;
                    nodesBoard.previousDrgged = nullptr;
                    nodesBoard.currentDrgged = nullptr;
                }
                            
                    
            }

        }

        // ------------ BOARD FUNCTIONALITIES ------------ //






        // ------------ A* ALGHORITHM ------------ //
        // ------------ BUTTONS LOGIC ------------ //
        
        //sprawdzanie flag przyciskow
        //TODO: bycmoze moge sie tych ifów pozbyc ustawiajac  CLICKED_BTN = ""; pod koniec tej sekcji
        // a w kazdej funkcji przy nacisnieciu klawisz modyfikowac zmienne globalne
        //po kazdym kliknieciu klawisz CLICKED_BTN musi byc zresetowany, zeby te ify sie nie wykonywale, ale to chyba nic nie zmienia i tak
        if (CLICKED_BTN == START_BTN) {
            std::cout << "START_BTN" << std::endl;
            RUN_ALGORITHM = true;
            CLICKED_BTN = "";
        }
        else if (CLICKED_BTN == BREAK_BTN) {
            RUN_ALGORITHM = false;
            CLICKED_BTN = "";
        }
        else if (CLICKED_BTN == BOARD_RESET_BTN and nodesBoard.boardState == ACTIVE) {
            //TODO:: wykonaj operacje usuwania obecnych informacji
            
            CLICKED_BTN = "";
        }
        else if (CLICKED_BTN == PATH_RESET_BTN and nodesBoard.boardState == ACTIVE) {
            
            CLICKED_BTN = "";
        }


        //tego nie moge usunac z main() poniewaz  exploreNodes() nodes musi wykonac x iteracji
        // a jak wykonalbym to w funkcji przycisku, no to byla by tylko jedna iteracja, chyba ze 
        //nie zmienilbym flagi przycisku i bylby ciagle wlaczony, ale to chyba nie ma sensu???
        if (RUN_ALGORITHM == true) {

           //vizualization delay
            sf::sleep(sf::microseconds(10));
            nodesBoard.exploreNodes();
        }


        // warunek zakonczenia wizualizacji
        if (IS_PATH_FOUND == true or PATH_NOT_EXIST == true) {
            CLICKED_BTN = "";
            RUN_ALGORITHM = false;
            nodesBoard.boardState = ACTIVE;
            //dla warunku PATH_NOT_EXIST nie moge tu wywolac funkcji showPAth()

        }

       /* CLICKED_BTN = "";*/ //TODO:: do sprawdzenia pozniej
       
        // ------------ A* ALGHORITHM ------------ //

       
       


        
        // ------------ RENDERING FUNCTION ------------ //
        // Clear screen
        window.clear(sf::Color(170, 170, 170));


        // Draw elements
        window.draw(text);
        
        nodesBoard.draw();

        startButton.render(&window);
        breakButton.render(&window);
        pathResetButton.render(&window);
        boardResetButton.render(&window);


        // Update the window
        window.display();

        // ------------ RENDERING FUNCTION ------------ //
        

    }
    return EXIT_SUCCESS;
}







//bool checkIsMouseOnBoard(Board& board, int mouse_x, int mouse_y) {
//
//    int size = board.nodeSize;
//    int origin = board.nodeSize / 2;
//    int border = board.nodeBorder;
//
//    //int firstNodeX = board.nodesBoard2D[0][0].screenX - origin - border;
//    //int firstNodeY = board.nodesBoard2D[0][0].screenY - origin - border;
//    ////w przypadku gdy granice sie na siebie nakladaja, nalozona granica wskazuje na kolejny"wezel"
//    ////dlatego tu nie moze byc origin+border, poniewaz ten border przy dzieleniu przez (size+borde) wskazuje na kolejny wezel
//    ////o wspolrzednych ktorych nie ma w nodesBoard
//    //int lastNodeX = board.nodesBoard2D.back().back().screenX + origin;
//    //int lastNodeY = board.nodesBoard2D.back().back().screenY + origin;
//
//    int firstNodeX = board.nodesBoard2D[0][0].screenX;
//    int firstNodeY = board.nodesBoard2D[0][0].screenY;
//    int lastNodeX = board.nodesBoard2D.back().back().screenX;
//    int lastNodeY = board.nodesBoard2D.back().back().screenY;
//
//    int leftBoardBorder = firstNodeX - origin - border;
//    int topBoardBorder = firstNodeY - origin - border;
//    int rightBoardBorder = lastNodeX + origin;
//    int bottomBoardBorder = lastNodeY + origin;
//
//    //check if mouse is outside nodesBoard
//    std::cout << "check cursor possition" << std::endl;
//
//    //jak w tym miejscu nic nie zwracac zeby uniknac sprawdzania czy przeslane wspolrzedne sa dobre czy zle
//    if (mouse_x <= leftBoardBorder or mouse_x >= rightBoardBorder) return false;    
//    if (mouse_y <= topBoardBorder or mouse_y >= bottomBoardBorder) return false;
//
//    std::cout << "cursor on the nodesBoard" << std::endl;
//    return true;
//   
//}




//Cords mouseToBoardIndexes(Board& board, int mouse_x, int mouse_y) {
//    
//    Cords newCords;
//    newCords.x = -1;    //bad value
//    newCords.y = -1;    //bad value
//
//    int size = board.nodeSize;
//    int origin = board.nodeSize / 2;
//    int border = board.nodeBorder;
//
//    //int firstNodeX = board.nodesBoard2D[0][0].screenX - origin - border;
//    //int firstNodeY = board.nodesBoard2D[0][0].screenY - origin - border;
//    ////w przypadku gdy granice sie na siebie nakladaja, nalozona granica wskazuje na kolejny"wezel"
//    ////dlatego tu nie moze byc origin+border, poniewaz ten border przy dzieleniu przez (size+borde) wskazuje na kolejny wezel
//    ////o wspolrzednych ktorych nie ma w nodesBoard
//    //int lastNodeX = board.nodesBoard2D.back().back().screenX + origin;
//    //int lastNodeY = board.nodesBoard2D.back().back().screenY + origin;
//
//    int firstNodeX = board.nodesBoard2D[0][0].screenX;
//    int firstNodeY = board.nodesBoard2D[0][0].screenY;
//    int lastNodeX = board.nodesBoard2D.back().back().screenX;
//    int lastNodeY = board.nodesBoard2D.back().back().screenY;
//
//    int leftBoardBorder = firstNodeX - origin - border;
//    int topBoardBorder = firstNodeY - origin - border;
//    int rightBoardBorder = lastNodeX + origin;
//    int bottomBoardBorder = lastNodeY + origin;
//
//    //check if mouse is outside nodesBoard
//    //std::cout << "check cursor possition" << std::endl;
//
//    //jak w tym miejscu nic nie zwracac zeby uniknac sprawdzania czy przeslane wspolrzedne sa dobre czy zle
//    if (mouse_x <= leftBoardBorder or mouse_x >= rightBoardBorder) {
//        isMouseOnBoard = false;
//        return newCords;  //returns bad coords
//    }
//    if (mouse_y <= topBoardBorder or mouse_y >= bottomBoardBorder) {
//        isMouseOnBoard = false;
//        return newCords; //returns bad coords
//    }
//        
//    //std::cout << "cursor on the nodesBoard" << std::endl;
//    isMouseOnBoard = true;
//    //determine node position based on mouse coordinates
//    int row = (mouse_x - leftBoardBorder) / (size + border);
//    int col = (mouse_y - topBoardBorder) / (size + border);
//    
//    newCords.x = row;   //good value
//    newCords.y = col;   //good value
//    
//    return newCords;
//  
//}



//void putObstacles(Board &board)
//{
//    Cords nodeCordsInBoard;
//    nodeCordsInBoard = mouseToBoardIndexes(board, mouseX, mouseY);
//    int row = nodeCordsInBoard.x;
//    int col = nodeCordsInBoard.y;
//
//    //check if mouse is on the board
//    //TODO: ten if jest do usuniecia
//    if (row == -1 or col == -1) return;  
//   
//    Node *node = &board.nodesBoard2D[col][row];
//
//    //check if mouse is not over the START_NODE or END_NODE
//    if (node->nodeType == START_NODE or node->nodeType == END_NODE or node->nodeType == OBSTACLE) return;
//    
//    //to zapobiega malowaniu Node'ow ktore sa CLOSED lub OPEN jak wcisnie sie STOP podczas wizualizacji
//    //TODO: blokada rysowania po polach CLOSED powinna byc regulowana przez ALGORITHM_STATE
//   //W aktualnej logice to jest nie potrzebne
//    /* if (node->nodeState == NONE) {
//        node->nodeType = OBSTACLE;
//        node->node.setFillColor(sf::Color(70, 70, 70));
//    }*/
//
//    node->nodeType = OBSTACLE;
//    node->node.setFillColor(sf::Color(70, 70, 70));
//    
//    
//}



//void eraseObstacles(Board& board)
//{
//    Cords nodeCordsInBoard;
//    nodeCordsInBoard = mouseToBoardIndexes(board, mouseX, mouseY);
//    int row = nodeCordsInBoard.x;
//    int col = nodeCordsInBoard.y;
//
//    //check if mouse is on the board
//    if (row == -1 or col == -1) return;
//
//    Node* node = &board.nodesBoard2D[col][row];
//
//    //check if mouse is not over the START_NODE or END_NODE
//    if (node->nodeType == START_NODE or node->nodeType == END_NODE or node->nodeType == WALKABLE) return;
//    node->nodeType = WALKABLE;
//    node->node.setFillColor(sf::Color(170, 170, 170));
//}





















