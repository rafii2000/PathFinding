#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"

#include "Node.h"
#include "Board.h"
#include "Button.h"
#include "Settings.h"

short unsigned Board::boardState = ACTIVE;

//mouse properties
int mouseX;
int mouseY;
mf MOUSE_STATE = mf::RELEASED;


//buttons state flags
btn_id CLICKED_BTN = btn_id::NONE;
bool CLICK_EVENT = false;


//drag mode flags
bool DRAG_MODE = false;
bool START_NODE_DRAG_MODE = false;
bool END_NODE_DRAG_MODE = false;

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
    Board nodesBoard(window, 30, 1, 1000, 1000);   

    Settings settingsWindow(&window, &font);
        
    // Create a buttons
    Button startButton(1000, 35, 130, 50, &font, "Start",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), btn_id::START_BTN
    );

    Button breakButton(1200, 35, 130, 50, &font, "Break",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), btn_id::BREAK_BTN
    );
    
    Button pathResetButton(1400, 35, 130, 50, &font, "Path Reset",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), btn_id::PATH_RESET_BTN
    );

    Button boardResetButton(1600, 35, 130, 50, &font, "Board Reset",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), btn_id::BOARD_RESET_BTN
    );

    Button settingsButton(1800, 35, 50, 50, &font, "",
        sf::Color(170, 170, 170),
        sf::Color(150, 150, 150),
        sf::Color(120, 120, 120), btn_id::OPEN_SETTINGS_BTN, "settings2.png"
                                                        
    );


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
                    MOUSE_STATE = mf::LEFT_PRESSED;
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {                    
                    MOUSE_STATE = mf::RIGHT_PRESSED;
                }               
            }
            else if (event.type == sf::Event::MouseButtonReleased) {                         
                MOUSE_STATE = mf::RELEASED;
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
            
            //idle, hover, clicl, set CLICKED_BTN id
            startButton.update(mouseX, mouseY);
            breakButton.update(mouseX, mouseY);
            pathResetButton.update(mouseX, mouseY);
            boardResetButton.update(mouseX, mouseY);
            settingsButton.update(mouseX, mouseY);

            //call proper function
            //TODO: dodac zmienna opisujaca jakie okno zostalo klikniete 
            nodesBoard.callFunctionOnButtonClick();
        }     

        if (CLICKED_BTN == btn_id::OPEN_SETTINGS_BTN)
            settingsWindow.openWindowSettings();
        else if (CLICKED_BTN == btn_id::CLOSE_SETTINGS_BTN)
            settingsWindow.closeWindowSettings();

        CLICKED_BTN = btn_id::NONE;

        // ------------ CALL FUNCTION ON BUTTON CLICK  ------------ //






        // ------------ BOARD FUNCTIONALITIES ------------ //

        if (nodesBoard.isMouseOnBoard == true and nodesBoard.boardState == ACTIVE) {                 
           
            //drag selected node (startNode or endNode) 
            if (MOUSE_STATE == mf::LEFT_PRESSED and START_NODE_DRAG_MODE == true) {

                int currentNodeX = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).x;
                int currentNodeY = nodesBoard.mouseToBoardIndexes(mouseX, mouseY).y;

                //forbid dragging startNode on obstacles and endNode
                if (nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].nodeType == WALKABLE) {

                    //prevent from clearing the node, which mouse is pointing and is already highlighted
                    if (&nodesBoard.nodesBoard2D[currentNodeY][currentNodeX] != nodesBoard.currentDrgged) {
                        nodesBoard.previousDrgged = nodesBoard.currentDrgged;
                        nodesBoard.currentDrgged = &nodesBoard.nodesBoard2D[currentNodeY][currentNodeX];

                        //swap walkable Node's with starNode 
                        nodesBoard.startNodeCords.x = currentNodeX;
                        nodesBoard.startNodeCords.y = currentNodeY;
                        nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].nodeType = START_NODE;
                        nodesBoard.nodesBoard2D[currentNodeY][currentNodeX].node.setFillColor(sf::Color::Green);
                    }                  
                    
                }
                    
            }
            else if (MOUSE_STATE == mf::LEFT_PRESSED and END_NODE_DRAG_MODE == true) {
                
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


            //put obstacle on Node, which mouse is pointing
            if (MOUSE_STATE == mf::LEFT_PRESSED and DRAG_MODE == false) {
                
                nodesBoard.putObstacles(mouseX, mouseY);
            }

            //remove obstacle from Node is pointed by mouse
            if (MOUSE_STATE == mf::RIGHT_PRESSED and DRAG_MODE == false ) {
                
                nodesBoard.eraseObstacles(mouseX, mouseY);
            }


            //Turn on/off drag mode
            if (MOUSE_STATE == mf::RELEASED) {                
                
                //Node's color flags
                sf::Color START_NODE_HOVER = sf::Color(0, 220, 0);
                sf::Color END_NODE_HOVER = sf::Color(220, 0, 0);

                //START_NODE_DRAG_MODE
                int startNodeX = nodesBoard.startNodeCords.x;
                int startNodeY = nodesBoard.startNodeCords.y;

                //END_NODE_DRAG_MODE
                int endNodeX = nodesBoard.endNodeCords.x;
                int endNodeY = nodesBoard.endNodeCords.y;

               //turn on / turn off START_NODE_DRAG_MODE
                if (nodesBoard.nodesBoard2D[startNodeY][startNodeX].isMouseOn(mouseX, mouseY) == true) {
                   
                    START_NODE_DRAG_MODE = true;
                   
                    nodesBoard.currentDrgged = &nodesBoard.nodesBoard2D[startNodeY][startNodeX];
                    nodesBoard.nodesBoard2D[startNodeY][startNodeX].node.setFillColor(START_NODE_HOVER);
                }
                else {

                    START_NODE_DRAG_MODE = false;                                     
                    nodesBoard.nodesBoard2D[startNodeY][startNodeX].node.setFillColor(sf::Color::Green);
                }
                
                //turn on / turn off END_NODE_DRAG_MODE
                if (nodesBoard.nodesBoard2D[endNodeY][endNodeX].isMouseOn(mouseX, mouseY) == true) {

                    END_NODE_DRAG_MODE = true;
                  
                    nodesBoard.currentDrgged = &nodesBoard.nodesBoard2D[endNodeY][endNodeX];
                    nodesBoard.nodesBoard2D[endNodeY][endNodeX].node.setFillColor(END_NODE_HOVER);
                }
                else {                                       
                    END_NODE_DRAG_MODE = false;                     
                    nodesBoard.nodesBoard2D[endNodeY][endNodeX].node.setFillColor(sf::Color::Red);
                }


                //set DRAG_MODE value (bool DRAG_MODE - additional variable to simplify code)
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

            //sf::sleep(sf::microseconds(10));    //visualization delay
            nodesBoard.exploreNodes();          //main visualization function
        }

        //condition of ending visualization
        if (IS_PATH_FOUND == true or PATH_NOT_EXIST == true) {
            RUN_ALGORITHM = false;
            IS_PATH_FOUND = false;
            PATH_NOT_EXIST = false;
            nodesBoard.boardState = ACTIVE;           
        }
       
        // ------------ A* ALGHORITHM ------------ //

       
       


        
        // ------------ RENDERING FUNCTIONS ------------ //
        // Clear screen
        window.clear(sf::Color(170, 170, 170));


        // Draw elements
        window.draw(text);
        
        nodesBoard.draw();
        
        startButton.render(&window);
        breakButton.render(&window);
        pathResetButton.render(&window);
        boardResetButton.render(&window);
        settingsButton.render(&window);

        settingsWindow.draw();

        

       


        // Update the window
        window.display();

        // ------------ RENDERING FUNCTIONS ------------ //
        

    }
    return EXIT_SUCCESS;

}








