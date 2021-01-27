#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"
#include "Node.h"
#include "Board.h"
#include "Button.h"
#include "Settings.h"
#include "Layout.h"




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

void detectResolution(int screenWidth, int screenHeight);

int main()
{

    // ------------ INITIALIZE ELEMENTS / OBJECTS ------------ //

    // FPS variables
    float fps;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    // Create the main window    
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height-40), "SFML PathFinding", sf::Style::Titlebar | sf::Style::Close);
    
    //Set proper layout based on screen resolution
    detectResolution(desktopMode.width, desktopMode.width);
    std::cout << "Screen resolution: " << desktopMode.width << " x " << desktopMode.height << std::endl;   

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial_narrow_7.ttf")) return EXIT_FAILURE;
   
    // Create lables
    sf::Text appTitle("SFML PathFinding visualization", font, Layout::APP_TITLE_LABLE_FONT_SIZE);
    appTitle.setPosition(sf::Vector2f(Layout::APP_TITLE_LABLE_X, Layout::APP_TITLE_LABLE_Y));
   
    sf::Text appResultLabel("Path between points doesn't exist", font, Layout::APP_RESULT_LABLE_FONT_SIZE);
    appResultLabel.setPosition(sf::Vector2f(Layout::APP_RESULT_LABLE_X, Layout::APP_RESULT_LABLE_Y));
    appResultLabel.setFillColor(sf::Color::Transparent);
    
    sf::Text appFPSLabel("150", font, 16);
    appFPSLabel.setPosition(10,5);
    appFPSLabel.setFillColor(sf::Color::Blue);
   
    // Create board of nodes
    Board nodesBoard(window, 30, 1, 1000, 1000);

    // Create settings panel card
    Settings settingsWindow(&window, &nodesBoard, &font);
            
    // Create a buttons    
    Button startButton(Layout::START_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "Start",     Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::START_BTN);
    Button breakButton(Layout::BREAK_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "Break",           Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::BREAK_BTN);
    Button pathResetButton(Layout::PATH_RESET_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "Path Reset",  Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::PATH_RESET_BTN);
    Button boardResetButton(Layout::BOARD_RESET_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "Board Reset", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::BOARD_RESET_BTN);
    Button generateMaze(Layout::GENERATE_MAZE_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH_S, Layout::MW_TOP_BTNS_HEIGHT_S, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "",                Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::GENERATE_MAZE_BTN, "maze2.png");
    Button openSettingsButton(Layout::OPEN_SETTINGS_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH_S, Layout::MW_TOP_BTNS_HEIGHT_S, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "",          Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::OPEN_SETTINGS_BTN, "settings2.png");
   
    // ------------ INITIALIZE ELEMENTS / OBJECTS ------------ //
    


      
    // Start the game loop
    while (window.isOpen())
    {

        //clean up previous loop iteration actions
        CLICKED_BTN = btn_id::NONE;
        CLICK_EVENT = false;    
        
        
        // ------------ EVENT LOOP ------------ //
        // Process events
        sf::Event event;
       
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }           

            //Mouse events
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
                appResultLabel.setFillColor(sf::Color::Transparent);
            }

            if (event.type == sf::Event::MouseMoved) {

                //set mouse position
                mouseX = sf::Mouse::getPosition(window).x;
                mouseY = sf::Mouse::getPosition(window).y;

                //check is mouse on board 
                nodesBoard.isMouseOnBoard = nodesBoard.checkIsMouseOnBoard(mouseX, mouseY);

            }

            //Keyboard events
            if (event.type == sf::Event::TextEntered)
            {

                int charUnicode = event.text.unicode;

                if (charUnicode < 128) {

                    //activeTextboxPtr ma zawsze wskaznik na ostatni uzyty Textbox, ale poniewaz ten 
                    //ostatniTextbox ma hasFocus=false to funkcja writeText() nic nie wstawi
                    if(Textbox::activeTextboxPtr != nullptr)
                        Textbox::activeTextboxPtr->writeText(charUnicode); 
                }
            }
        }
        // ------------ EVENT LOOP ------------ //





        // ------------ CALL FUNCTION ON BUTTON CLICK  ------------ //
        
         //idle, hover, click, set CLICKED_BTN id
        if (Settings::isOpen == false) {
           
            startButton.update(mouseX, mouseY);
            breakButton.update(mouseX, mouseY);

            if (RUN_ALGORITHM == false) {
                pathResetButton.update(mouseX, mouseY);
                boardResetButton.update(mouseX, mouseY);
                openSettingsButton.update(mouseX, mouseY);
                generateMaze.update(mouseX, mouseY);
            }
          
            //call proper function
            nodesBoard.callFunctionOnButtonClick();
        }

        if (Settings::isOpen == true) {

            settingsWindow.updateButtons();
            settingsWindow.callFunctionOnButtonClick();
        }

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

            //sf::sleep(sf::microseconds(10));  //visualization delay
            //nodesBoard.exploreNodes();          //main visualization function
        }

        //condition of ending visualization
        if (IS_PATH_FOUND == true or PATH_NOT_EXIST == true) {

            if (PATH_NOT_EXIST)
                appResultLabel.setFillColor(sf::Color(50, 50, 50));

            RUN_ALGORITHM = false;
            IS_PATH_FOUND = false;
            PATH_NOT_EXIST = false;
            nodesBoard.boardState = ACTIVE;           
        }  
        
        // ------------ A* ALGHORITHM ------------ //

       
       


        
        // ------------ RENDERING FUNCTIONS ------------ //
        //object render sequence is important, objects cover each other

        // Clear screen
        window.clear(sf::Color(170, 170, 170));
        window.setPosition(sf::Vector2i(-8, 0));

        // Draw elements
        window.draw(appTitle);
        window.draw(appResultLabel);
        window.draw(appFPSLabel);       
        
        nodesBoard.draw();        
       
        startButton.render(&window);
        breakButton.render(&window);
        pathResetButton.render(&window);
        boardResetButton.render(&window);
        openSettingsButton.render(&window);
        generateMaze.render(&window);

        settingsWindow.draw();  //render last, must cover other elements

        // Update the window
        window.display();
       
        // ------------ RENDERING FUNCTIONS ------------ //
        




        // ------------ FPS SECTION ------------ //

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        appFPSLabel.setString(std::to_string(int(fps)));
        previousTime = currentTime;

        // ------------ FPS SECTION ------------ //
    }
    return EXIT_SUCCESS;

}




void detectResolution(int screenWidth, int screenHeight) {

    //1364 x 768
    if (screenWidth < 1920 and screenHeight < 1080) {

        //MAIN WINDOW
        Layout::APP_TITLE_LABLE_FONT_SIZE = 40;
        Layout::APP_TITLE_LABLE_X = 60;
        Layout::APP_RESULT_LABLE_FONT_SIZE = 22;
        Layout::APP_RESULT_LABLE_X = 60;
        
        //common properties
        Layout::MW_TOP_BTNS_X = 725;
        Layout::MW_TOP_BTNS_Y = 35;
        Layout::MW_TOP_BTNS_MARGIN = 25;
        Layout::MW_TOP_BTNS_FONT_SIZE = 17;

        //half common properties
        Layout::MW_TOP_BTNS_WIDTH = 95;
        Layout::MW_TOP_BTNS_HEIGHT = 35;
        Layout::MW_TOP_BTNS_WIDTH_S = 35;
        Layout::MW_TOP_BTNS_HEIGHT_S = 35;

        //individual properties
        Layout::set_MW_TOP_BTNS_X();
;      
        //SETTINGS WINDOW
        Layout::FILE_PATH_SAVE_GROUP_Y = 525;
        Layout::FILE_PATH_LOAD_GROUP_Y = 625;
    }

}
