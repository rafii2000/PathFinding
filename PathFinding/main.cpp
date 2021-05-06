#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Constants.h"
#include "Node.h"
#include "Board.h"
#include "Button.h"
#include "Settings.h"
#include "Layout.h"
#include "MainWindow.h"


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
    sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height-40), "SFML PathFinding", sf::Style::Titlebar | sf::Style::Close);
    //window.setFramerateLimit(320);
    //window.setVerticalSyncEnabled(true);


    //Set proper layout based on screen resolution
    Layout::detectResolution(desktopMode.width, desktopMode.width);

    //Application
    MainWindow app(&window);

      
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
                app.appResultLabel.setFillColor(sf::Color::Transparent);
                app.appResultLabelBackground.setFillColor(sf::Color::Transparent);
            }

            if (event.type == sf::Event::MouseMoved) {

                //set mouse position
                mouseX = sf::Mouse::getPosition(window).x;
                mouseY = sf::Mouse::getPosition(window).y;

                //check is mouse on board 
                app.nodesBoard.isMouseOnBoard = app.nodesBoard.checkIsMouseOnBoard(mouseX, mouseY);

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


        
        // ------------ RENDER WINDOW ------------ //
        
        // Clear screen
        //window.clear(sf::Color(170, 170, 170));
        if (RUN_ALGORITHM == true and Settings::fastVisualization == true){        
            
        }
        else{
            window.clear(sf::Color(170, 170, 170));
            //std::cout << "wchodze tu" << std::endl;
        } 

        std::cout << RUN_ALGORITHM << " " << Settings::fastVisualization << std::endl;
        
        window.setPosition(sf::Vector2i(-8, 0));

        //Draw content
        app.draw();              

        // Update the window
        window.display();
       
        // ------------ RENDER WINDOW ------------ //
        

        app.fpsCounter();

      
    }
    return EXIT_SUCCESS;

}

