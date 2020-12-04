#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Node.h"



class Board
{

friend class A_star;
friend void mouseFunction(Board& board, int mouse_x, int mouse_y);

private:

	int nodeSize;
	int nodeBorder;
	int nodesRowAmount;
	int nodesColumnAmount;

	sf::RenderWindow* window;

	//std::vector<Node> nodesRow;  //is it a good name?  it cant be initial here because then i have to clean it after each col iterration
	std::vector< std::vector<Node> > nodesBoard2D;



public:


	Board(){}

	Board(sf::RenderWindow& w, int nSize, int nBorder,  int nRowAmt, int nColAmt) {

		window = &w;
		nodeSize = nSize;
		nodeBorder = nBorder;
		nodesRowAmount = nRowAmt;
		nodesColumnAmount = nColAmt;

		createBoard();
	}


	void createBoard();

	void print_nodes();

	void draw();

	

	



};

