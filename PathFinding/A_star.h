#pragma once
#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Board.h"


class A_star
{
	

private:

	std::vector<Node> nodesBoard;
	Board *board;

	

public:

	A_star(Board &board);  //is this a good name?
	
	

	void exploreNodes();

	

	void print_nodes(Board& board);

	void print_nodes2();


};

