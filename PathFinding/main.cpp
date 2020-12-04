#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Node.h"
#include "Board.h"
#include "A_star.h"


bool dragStartNode;
bool dragEndNode;
Node *previousStartNode  = nullptr;
Node *previousEndNode = nullptr;
Node *currentNode = nullptr;


void mouseFunction(Board &board, int mouse_x, int mouse_y) {
    
    int size = board.nodeSize;
    int origin = board.nodeSize / 2;
    int border = board.nodeBorder;

    int firstNodeX = board.nodesBoard2D[0][0].screenX - origin - border;
    int firstNodeY = board.nodesBoard2D[0][0].screenY - origin - border;
    int lastNodeX = board.nodesBoard2D.back().back().screenX + origin;
    int lastNodeY = board.nodesBoard2D.back().back().screenY + origin;

    //check if mouse is outside nodesBoard
    if (mouse_x <= firstNodeX or mouse_x >= lastNodeX) return;
    if (mouse_y <= firstNodeY or mouse_y >= lastNodeY) return;
    std::cout << "cursor on the nodesBoard" << std::endl;

    //determine node position based on mouse coordinates
    int row = (mouse_x- firstNodeX) / (size + border);
    int col = (mouse_y- firstNodeY) / (size + border);

    if (row >= 0 or row <= board.nodesRowAmount) {
        if (col >= 0 or col <= board.nodesColumnAmount) {
            std::cout << mouse_x << " " << mouse_y << std::endl;
            board.nodesBoard2D[col][row].node.setFillColor(sf::Color::Cyan);
        }
    }
    else {
        std::cout << "ZA DUZA WARTOSC" << std::endl;
    }

    

}

int main()
{
    // Create the main window    
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height), "SFML PathFinding");
    
   
   
    window.setPosition(sf::Vector2i(-8, 0));

    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial_narrow_7.ttf"))
        return EXIT_FAILURE;
    sf::Text text("SFML PathFinding visualization", font, 50);
    text.setPosition(sf::Vector2f(79, 0));


      

    //Create a board of nodes
    Board nodesBoard(window, 30, 1, 58, 27);

    A_star algorithm(nodesBoard);

    //algorithm.print_nodes(nodesBoard);
    //algorithm.print_nodes();

    nodesBoard.print_nodes();

   

   
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
            if (event.type == sf::Event::MouseButtonPressed) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    std::cout << "LEFT pressed detected" << std::endl;
                   

                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    std::cout << "RIGHT pressed detected" << std::endl;
                }
                
            }

            
            if (event.type == sf::Event::MouseButtonReleased) {
                std::cout << "released detected" << std::endl;
            }

            if (event.type == sf::Event::MouseMoved) {
                std::cout << "mouse move detected" << std::endl;

                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;

                mouseFunction(nodesBoard, x, y);
                
            }
            

           
        }

       
        // Clear screen
        window.clear(sf::Color(170, 170, 170));

        
    
        // Draw elements
        window.draw(text);
        nodesBoard.draw();    

       
        


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}