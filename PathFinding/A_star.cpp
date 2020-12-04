#include "A_star.h"



//dwie opcje:
// 1) albo kazdej funckji przekazuje obiekt przez referencje i wykonuje na nim operacje, albo
// 2) przekazuje obiekt raz do zmiennej wskaznikowej i wykonuje operacje juz na zmiennej kalsy(wskazniku)

//constructor
A_star::A_star(Board& board)
{
	//Tworzy sie kopia zamiast referencji LOL

	/*for (int i = 0; i < board.nodesBoard.size(); i++) {
		board.nodesBoard[i].nodeType = OBSTACLE;
	}*/

	this->board = &board;
	
	
}

void A_star::print_nodes(Board& board)
{
	for (int col = 0; col < board.nodesColumnAmount; col++) {

		for (int row = 0; row < board.nodesRowAmount; row++) {

			board.nodesBoard2D[col][row].node.setFillColor(sf::Color::Black);
			board.nodesBoard2D[col][row].nodeType = OBSTACLE;
			std::cout << board.nodesBoard2D[col][row].nodeType << std::endl;
		}
	}
}

void A_star::print_nodes2()
{
	
	for (int col = 0; col < board->nodesColumnAmount; col++) {

		for (int row = 0; row < board->nodesRowAmount; row++) {

			board->nodesBoard2D[col][row].node.setFillColor(sf::Color::Black);
			board->nodesBoard2D[col][row].nodeType = OBSTACLE;
			std::cout << board->nodesBoard2D[col][row].nodeType << std::endl;
		}
	}
}
