#include "Game.h"
#include <iostream>




//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north)
	:m_board(b), m_southPlayer(south), m_northPlayer(north), m_turnNum(0), m_GameOver(false)                                               
{}




//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation
//of the state of the board.
void Game::display() const
{
	//north's name 
	std::cout << std::endl << "              " << m_northPlayer->name() << std::endl;

	//north holes 
	std::cout << "             ";
	for (int i = 1; i <= m_board.holes(); i++)
	{
		std::cout << m_board.beans(NORTH, i) << "  ";
	}

	//north's pot 
	std::cout << std::endl << "North pot: " << m_board.beans(NORTH, 0);

	//spaces between pots        
	for (int i = 0; i <= m_board.holes(); i++)
	{
		std::cout << "   "; 
	}

	//south's pot 
	std::cout << "South pot: " << m_board.beans(SOUTH, 0) << std::endl;

	//south holes 
	std::cout << "             ";
	for (int i = 1; i <= m_board.holes(); i++)
	{
		std::cout << m_board.beans(SOUTH, i) << "  ";
	}

	//south's name 
	std::cout << std::endl << "              " << m_southPlayer->name() << std::endl << std::endl;

}




//If the game is over(i.e., the move member function has been called and returned false), set over to true; otherwise, 
//set over to false and do not change anything else.If the game is over, set hasWinner to true if the game has a winner, 
//or false if it resulted in a tie.If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{

	//the move function has been called and returned false 
	if (m_GameOver == true)                                              
	{
		over = true; 
		int totalNorthBeans = m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH); 
		int totalSouthBeans = m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH); 


		//if north wins
		if (totalNorthBeans > totalSouthBeans)
		{
			hasWinner = true;
			winner = NORTH;
		}
		//if south wins 
		else if (totalNorthBeans < totalSouthBeans)
		{
			hasWinner = true;
			winner = SOUTH;
		}
		//if there is a tie 
		else if (totalNorthBeans == totalSouthBeans)
		{
			hasWinner = false;
		}
		
	}
	else
	{
		over = false; 
	}
}




//-------------------------------------------------------------------------------------------------------------------------------------------
//Attempt to make a complete move for the player playing side s. "Complete" means that the player 
//sows the seeds from a hole and takes any additional turns required or completes a capture.
//Whenever the player gets an additional turn, you should display the board so someone looking at 
//the screen can follow what's happening. If the move can be completed, return true; if not, because the 
//move is not yet completed but side s has no holes with beans to pick up and sow, sweep any beans in s's 
//opponent's holes into that opponent's pot and return false.
bool Game::move(Side s)
{
	
	//get a pointer to the current player and the opponent 
	Player* currentPlayer; 
	//Player* opponentPlayer; 
	if (s == NORTH)
	{
		currentPlayer = m_northPlayer; 
	//	opponentPlayer = m_southPlayer; 
	}
	else
	{
		currentPlayer = m_southPlayer;
	//	opponentPlayer = m_northPlayer;
	}


	//have the currentPlayer choose a move and store the result 
	int moveResult = currentPlayer->chooseMove(m_board, s); 

	//a negative result means the move was not possible 
	if (moveResult <= 0)
	{
		
		// sweep any additional beans from the the opponent's board into their pot 
		for (int i = 1; i <= m_board.holes(); i++)
		{
			m_board.moveToPot(opponent(s), i, opponent(s)); 																								
		}
		m_GameOver = true; 
		return false; 

	}

	//a positive result means the move is possible 
	if (moveResult > 0)
	{

		//if the player is not interactive, announce their choice 
		if (currentPlayer->isInteractive() == false)
		{
			std::cout << std::endl << "NEXT MOVE: " << std::endl;
			std::cout << currentPlayer->name() << " choose to move the beans at hole " << moveResult << std::endl;
		}

		//if you can sow beans, perform the action 
		Side nextSide; 
		int endHole; 
		m_board.sow(s, moveResult, nextSide, endHole);


		// perform capture if necessary 
		if ( (nextSide == s) && (endHole != 0) && (m_board.beans(nextSide, endHole) == 1) && (m_board.beans(opponent(nextSide), endHole) > 0) )
		{
			std::cout << std::endl << "A capture was preformed!" << std::endl;
			performCapture(nextSide, endHole); 
			display(); 
			return true; 
		}

		//display game board 
		display();


		//If the last bean was placed in the player's pot, the player must take another turn.
		if (endHole == 0)
		{
			std::cout << std::endl << "You get another turn!" << std::endl;
			return move(s);
		}

		return true; 
	}

	return false; //dummy return for g++
}




//If the last bean was placed in one of the player's own holes that was empty just a moment before, and if the 
//opponent's hole directly opposite from that hole is not empty, then that last bean and all beans in the opponent's
//hole directly opposite from that hole are put into the player's pot, and the turn ends. (This is a capture.) 
//Notice that it is not a capture if the player's last bean ends up in what was an empty hole on the opponent's side.
void Game::performCapture(Side s, int hole)
{



	//add the one bean on side s, to the pot on side s 
	m_board.moveToPot(s, hole, s); 


	//add the beans opposite side s, to s's pot 
	m_board.moveToPot(opponent(s), hole, s);

}
//-------------------------------------------------------------------------------------------------------------------------------------------






//-------------------------------------------------------------------------------------------------------------------------------------------
//Play the game. Display the progress of the game in a manner of your choosing, provided that someone 
//looking at the screen can follow what's happening. If neither player is interactive, then to keep the 
//display from quickly scrolling through the whole game, it would be reasonable periodically to prompt 
//the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for 
//input streams is useful here.) Announce the winner at the end of the game. You can apportion to your 
//liking the responsibility for displaying the board between this function and the move function.
void Game::play()
{
	//display start board
	std::cout << "Welcome! Before we start the game, here is what the board looks like: " << std::endl; 
	display(); 

	//default values for variables 
	Player* currentPlayer = m_southPlayer;   //south player starts first
	Player* opponentPlayer = m_northPlayer; 
	Player* tempPlayer = m_southPlayer; 
	Side currentSide(SOUTH);                //south side of board starts first 
	Side tempSide(SOUTH);  

	//variables used to check status
	bool gameOver = false;
	bool hasWinner = false;
	Side winnerSide(SOUTH); 

	//turn counter 
	int counter = 1; 
	
	while (gameOver == false)
	{
		std::cout << "******************************************************************************" << std::endl;

		//current player does their move 
		move(currentSide); 
		status(gameOver, hasWinner, winnerSide); 
	

		//if move returns false, the game is NOT over
		if (gameOver == false)
		{
			//swap currentPlayer and opponent 
			tempPlayer = currentPlayer;
			currentPlayer = opponentPlayer;
			opponentPlayer = tempPlayer;
			//swap which side the game is starting on 
			tempSide = opponent(currentSide);
			currentSide = tempSide;

		}

		
		//if both players are virtual, ask the view to press enter to continue 
		if (currentPlayer->isInteractive() == false && opponentPlayer->isInteractive() == false && gameOver == false)
		{
			std::cout << "Press ENTER to continue";
			std::cin.ignore();
		}
		
		

		if (gameOver == true)
		{
			//present winner's name at the end of the game 
			if (hasWinner == true)
			{
				//announce score 
				std::cout << "SCORE:  " << m_northPlayer->name() << "- " << m_board.beans(NORTH, 0) << "  " << m_southPlayer->name() << "- " << m_board.beans(SOUTH, 0) << std::endl;

				//announce winner 
				if (winnerSide == NORTH)
				{
					std::cout << "The winner is " << m_northPlayer->name() << "!" << std::endl;
				}
				else
				{
					std::cout << "The winner is " << m_southPlayer->name() << "!" << std::endl;
				}
			}
			else if (hasWinner == false)
			{
				std::cout << "It's a draw! The game has ended in a tie." << std::endl;
			}
		}

		counter++; 
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------





//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. 
//This function exists so that we and you can more easily test your program.
int Game::beans(Side s, int hole) const
{
	return m_board.beans(s, hole);
}

