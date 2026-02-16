#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include "Side.h"
#include <vector>


class Board
{
public: 
	Board(int nHoles, int nInitialBeansPerHole);
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);


	//housekeeping functions 
	Board(const Board& other); //copy constructor

	//delete 
	void printBoard();                                           //DELETE ME!

private:
	std::vector <int> m_northBoard; 
	std::vector <int> m_southBoard; 
	int m_holes; 
	int m_beansPerHole; 

	//functions used in public functions 
	int getBeanNum(int s, int hole);
	
};

#endif //BOARD_INCLUDED
