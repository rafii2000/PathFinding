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

enum class mouse_flags { PRESSED = 0, LEFT_PRESSED, RIGHT_PRESSED, RELEASED };

mouse_flags mouseFlag = mouse_flags::RELEASED;


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
bool RUN_ALGORITHM = false;
bool IS_PATH_FOUND = false;
bool PATH_NOT_EXIST = false;
//bool ALLOW_DIAGONAL = false;    //TODO: add new functionality


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

        // ------------ EVENT LOOP ------------ //
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
                
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {                    
                    mouseState = LEFT_PRESSED;
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {                    
                    mouseState = RIGHT_PRESSED;
                }               
            }
            else if (event.type == sf::Event::MouseButtonReleased) {                         
                mouseState = RELEASED;
                CLICK_EVENT = true;
            }
            

            if (event.type == sf::Event::MouseMoved) {        
                
                //set mouse position
                mouseX = sf::Mouse::getPosition(window).x;
                mouseY = sf::Mouse::getPosition(window).y;
                
                //check is mouse on board 
                nodesBoard.isMouseOnBoard = nodesBoard.checkIsMouseOnBoard(mouseX, mouseY);

            }    
        }
        // ------------ EVENT LOOP ------------ //
                                               




        // ------------ CALL FUNCTION ON BUTTON CLICK  ------------ //

        //check if any buttons is being clicked or hovered
        if (nodesBoard.isMouseOnBoard == false) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            startButton.update(mousePos);
            breakButton.update(mousePos);
            pathResetButton.update(mousePos);
            boardResetButton.update(mousePos);            
        }

        //call proper function
        nodesBoard.callFunctionOnButtonClick();

        // ------------ CALL FUNCTION ON BUTTON CLICK  ------------ //






        // ------------ BOARD FUNCTIONALITIES ------------ //

        //przeniesienie tych funkcji do klasy Board, wymagalo by udostepniania pozycji kursora
        //i innych zmiennych informujacych o stanie programu, warto tak ????

        if (nodesBoard.isMouseOnBoard == true and nodesBoard.boardState == ACTIVE) {                 
           
            //drag selected node (startNode or endNode) 
            if (mouseState == LEFT_PRESSED and START_NODE_DRAG_MODE == true) {

                int currentNodeX = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).x; //dwa razy wywoluje ta sama funckje
                int currentNodeY = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).y; //dwa razy wywoluje ta sama funckje

                //forbid dragging starNode on obstacles and endNode
                if (nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].nodeType == WALKABLE) {

                    //prevent from clearing the node, which mouse is pointing and is already highlighted
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
                
                int currentNodeX = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).x;
                int currentNodeY = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).y;

                //forbid dragging endNode on obstacles and startNode
                if (nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].nodeType == WALKABLE) {

                    //prevent from clearing the node, which mouse is pointing and is already highlighted
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


            //Turn on/off drag mode
            if (mouseState == RELEASED) {                
                
                //Node's color flags
                sf::Color START_NODE_HOVER = sf::Color(0, 220, 0);
                sf::Color END_NODE_HOVER = sf::Color(220, 0, 0);

                //START_NODE_DRAG_MODE
                int startNodeX = nodesBoard.startNodeCords.x;
                int startNodeY = nodesBoard.startNodeCords.y;

                //END_NODE_DRAG_MODE
                int endNodeX = nodesBoard.endNodeCords.x;
                int endNodeY = nodesBoard.endNodeCords.y;

               //manage start_node_drag_mode
                if (nodesBoard.nodesBoard2D[startNodeY][startNodeX].isMouseOn(mouseX, mouseY) == true) {
                   
                    START_NODE_DRAG_MODE = true;
                   
                    nodesBoard.currentDrgged = &nodesBoard.nodesBoard2D[startNodeY][startNodeX];
                    nodesBoard.nodesBoard2D[startNodeY][startNodeX].node.setFillColor(START_NODE_HOVER);
                }
                else {

                    START_NODE_DRAG_MODE = false;                                     
                    nodesBoard.nodesBoard2D[startNodeY][startNodeX].node.setFillColor(sf::Color::Green);
                }
                
                //manage end_node_drag_mode
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
              
        
        if (RUN_ALGORITHM == true) {

            sf::sleep(sf::microseconds(10));    //visualization delay
            nodesBoard.exploreNodes();          //main visualization function
        }


        //condition of ending visualization
        if (IS_PATH_FOUND == true or PATH_NOT_EXIST == true) {
            RUN_ALGORITHM = false;
            nodesBoard.boardState = ACTIVE;           
        }
       
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








