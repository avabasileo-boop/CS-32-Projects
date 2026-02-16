#include "Board.h"



//Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole.
//If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
Board::Board(int nHoles, int nInitialBeansPerHole)
{
	// If nHoles is not positive, make it 1
	if (nHoles <= 0) 
		nHoles = 1; 

	//if nInitialBeansPerHole is negative, make it 0
	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0; 

	m_holes = nHoles; 
	m_beansPerHole = nInitialBeansPerHole; 

	//construct the vectors 
	m_northBoard.push_back(0); 
	m_southBoard.push_back(0); 

	for (int i = 1; i <= m_holes; i++)
	{
		m_northBoard.push_back(m_beansPerHole); 
		m_southBoard.push_back(m_beansPerHole); 
	}
}




//Copy constructor 
Board::Board(const Board& other)
	: m_northBoard(other.m_northBoard), m_southBoard(other.m_southBoard)
{
	m_holes = other.m_holes; 
	m_beansPerHole = other.m_beansPerHole; 
}




//Return the number of holes on a side (not counting the pot).
int Board::holes() const
{
	return m_holes; 
}



//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const
{
	//invalid hole 
	if (hole < 0 || hole > m_holes)
		return -1; 

	//return number of beans 
	if (s == NORTH)
	{
		return m_northBoard.at(hole); 
	}
	return m_southBoard.at(hole); 
}




//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const
{
	int count = 0; 

	if (s == NORTH) //count up beans on north board or . . . 
	{
		for (int i = 1; i <= m_holes; i++)
		{
			count += m_northBoard.at(i); 
		}
		return count; 
	}
	else          //. . . count up beans on south board 
	{
		for (int i = 1; i <= m_holes; i++)
		{
			count += m_southBoard.at(i); 
		}
		return count; 
	}
	
	return -999; //dummy return for g++
}




//Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const
{
	int count = 0; 
	//cycle through and count beans from BOTH South and North holes 
	for (int i = 0; i <= m_holes; i++)
	{
		count += m_northBoard.at(i) + m_southBoard.at(i); 
	}
	return count; 
}




//-----------------------------------------------------------------------------------------------------------------------
//Below is a collection of several function all involved in sowing beans across holes 
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{

	//check for invalid hole value 
	if (hole <= 0 || hole > m_holes)
		return false; 


	//get the number of beans at that hole 
	int beanNum = getBeanNum(s, hole);
	if (beanNum < 0) //negative bean num means hole had no beans to begin with 
	{
		return false; 
	}                                                          


	//Below is the procedure if you are starting on the North side
	if (s == NORTH)
	{
		int currentPos = hole - 1;
		while (beanNum != 0)
		{
			//loop backward through north board 
			for (int i = currentPos; i >= 0 && beanNum != 0; i--)
			{
				m_northBoard.at(i)++; //add bean 
				beanNum--; 

				//check if you are out of beans 
				if (beanNum == 0)
				{
					endSide = NORTH;
					endHole = i; 
					return true;
				}
			}
																												
			//Done with NORTH board, set new starting position 
			//currentPos = holes();  
			currentPos = 1; 

			//loop forward through south board 
			for (int i = currentPos; i < m_southBoard.size(); i++)
			{
				m_southBoard.at(i)++; 
				beanNum--; 

				//check if you are out of beans 
				if (beanNum == 0)
				{
					endSide = SOUTH; 
					endHole = i; 
					return true; 
				}
			}

			//resent currentPos to the end of NorthBoard 
			currentPos = holes(); 
		}
		return true; //finished! 
	}


	//Below is the procedure if you are starting on the South side
	if (s == SOUTH)
	{
		int currentPos = hole + 1;
		while (beanNum != 0)
		{
			//loop forward through SOUTH vector 
			for (int i = currentPos; i < m_southBoard.size() && beanNum != 0; i++)
			{
				m_southBoard.at(i)++;
				beanNum--;

				//check if you are out of beans 
				if (beanNum == 0)
				{
					endSide = SOUTH;
					endHole = i;
					return true;
				}
			}

			//Done with SOUTH board, set new starting position 
			currentPos = 1;

			//add to pot 
			if (beanNum != 0)
			{
				m_southBoard.at(0)++;
				beanNum--;
			}

			//check if you are out of beans 
			if (beanNum == 0)
			{
				endSide = SOUTH;
				endHole = 0;
				return true;
			}

			//Loop backwards through NORTH board
			for (int i = m_holes; i > 0; i--)
			{
				m_northBoard.at(i)++;
				beanNum--;

				//check if you are out of beans 
				if (beanNum == 0)
				{
					endSide = NORTH;
					endHole = i;
					return true;
				}
			}

			currentPos = 1;
		}
		return true; //finished!
	}
	return false; //dummy return for g++ 
}




//Helper Functions for the sow function:
//Get the number of beans at a specific hole 
int Board::getBeanNum(int s, int hole)
{
	int beanNum = -1; 
	if (s == NORTH)
	{
		
		if (beanNum != 0) //invalid if hole has no beans 
			beanNum = m_northBoard.at(hole);
		m_northBoard.at(hole) = 0;
	}
	else
	{
		
		if (beanNum != 0) //invalid if hole has no beans 
			beanNum = m_southBoard.at(hole);
		m_southBoard.at(hole) = 0;
	}

	return beanNum; 
}
//-----------------------------------------------------------------------------------------------------------------------




//Move all beans in hole s to potOwner and return true
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	//check for invalid hole value 
	if (hole <= 0 || hole > m_holes)
		return false; 

	int count = 0; 
	if (s == NORTH)
	{
		count = m_northBoard.at(hole); 
		m_northBoard.at(hole) = 0; 
	}
	if (s == SOUTH)
	{
		count = m_southBoard.at(hole); 
		m_southBoard.at(hole) = 0; 
	}

	if (potOwner == NORTH)
	{
		m_northBoard.at(0) += count; 
		return true; 
	}
	else if (potOwner == SOUTH)
	{
		m_southBoard.at(0) += count; 
		return true; 
	}

	return false; //dummy return for g++ 
}




//Set the number of beans at the specified hole and return true if it was able to do that.
bool Board::setBeans(Side s, int hole, int beans)
{
	//check for invalid hole value 
	if (hole < 0 || hole > m_holes)
		return false; 

	if (s == NORTH)
	{
		m_northBoard.at(hole) = beans; 
		return true;
	}
	else if (s == SOUTH)
	{
		m_southBoard.at(hole) = beans;
		return true;
	}

	return false;  //dummy return for g++ 
}









////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//not part of assignment, function is for testing 
#include<iostream>

void Board::printBoard()
{
	std::cout << std::endl << "                  NORTH" << std::endl; 
	
	//print hole numbers 
	std::cout << "            pos: ";
	for (int i = 1; i <= m_holes; i++)
	{
		std::cout << i << " "; 
	}
	std::cout << std::endl; 
	std::cout << "--------------------------------------------------" << std::endl;

	//print north vector
	std::cout << "                 ";
	for (int i = 1; i <= m_holes; i++)
	{
		std::cout << m_northBoard.at(i) << " ";
	}
	std::cout << std::endl;

	//print pots 
	std::cout << "North's pot: " << m_northBoard.at(0); 
	std::cout << "              "; 
	std::cout << "South's pot: " << m_southBoard.at(0) << std::endl; 

	//print south vector
	std::cout << "                 ";
	for (int i = 1; i <= m_holes; i++)
	{
		std::cout << m_southBoard.at(i) << " ";
	}
	std::cout << std::endl;

	//print hole numbers 
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "            pos: ";
	for (int i = 1; i <= m_holes; i++)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;


	std::cout << "                 SOUTH" << std::endl;
}





