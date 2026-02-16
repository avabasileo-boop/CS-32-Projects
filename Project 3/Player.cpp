#include "Player.h"
#include <iostream>



//---------------------------------------------Abstract Player Class---------------------------------------------
//Create a Player with the indicated name.
Player::Player(std::string name)
{
	m_name = name; 
}


//Return the name of the player.
std::string Player::name() const
{
	return m_name;
}

//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
bool Player::isInteractive() const
{
	return false;
}


Player::~Player()
{

}



//---------------------------------------------HumanPlayer Class---------------------------------------------
HumanPlayer::HumanPlayer(std::string name) : Player(name)
{}


//Return true if the player is human.
bool HumanPlayer::isInteractive() const
{
	return true;
}


//Ask the player to choose a move. If there are no beans or the player has provided invalid input, return -1. 
int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	//if there are no beans, you cannot choose a move
	if (b.beansInPlay(s) == 0)
		return -1;

	int holeSelected = -1; 
	int input; 

	while (holeSelected == -1)
	{
		std::cout << "Player: " << name() << ", please select a hole: "; 
		std::cin >> input;

		//test for valid input 
		if (input <= 0 || input > b.holes()) 
		{
			std::cout << "Please select a value between 1 and " << b.holes() << "." << std::endl; 
		}
		else if (b.beans(s, input) <= 0)
		{
			std::cout << "There are no beans at hole " << input << "." << std::endl;
		}
		else
		{
			holeSelected = input; 
		}
	}
	return holeSelected; 
}

HumanPlayer::~HumanPlayer()
{}





//---------------------------------------------BadPlayer Class---------------------------------------------
BadPlayer::BadPlayer(std::string name) : Player(name)
{}


BadPlayer::~BadPlayer()
{}


int BadPlayer::chooseMove(const Board& b, Side s) const
{


	//return if there are no beans on s side 
	if (b.beansInPlay(s) == 0)
		return -1; 


	//find the first hole that has beans 
	int move = -1; 
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) > 0)
		{                                      
			move = i; 
			break; 
		}
	}
	return move; 
}












//---------------------------------------------SmartPlayer Class---------------------------------------------
//Constructor 
SmartPlayer::SmartPlayer(std::string name) : Player(name)
{}


//Destructor 
SmartPlayer::~SmartPlayer()
{}




//make the move, return true if you can make another move, false if you can't or if the game is over 
bool SmartPlayer::makeMove(Board& board, int hole, Side side) const
{
    Side endSide;
    int endHole;
    bool ableToMove = board.sow(side, hole, endSide, endHole);

    //if you can't make a move 
    if (ableToMove == false)
    {
        return false;
    }

    //if you can make a capture 
    if (side == endSide && board.beans(endSide, endHole) == 1 && board.beans(opponent(side), endHole) > 0)
    {
        board.moveToPot(opponent(side), endHole, side);  //move their baens to you pot 
        board.moveToPot(side, endHole, side);			 //move your bean to your pot 
    }

    //if you need to take another turn 
    if (endHole == 0 && endSide == side)
    {
        return true;  //retrun true if you can make another move
    }

    //return false if you made your move and can't make another 
    return false;
}













//mind hole with lowest or highest evaluation
int SmartPlayer::findMinOrMax(const Board& board, Side side, bool searchBestVal, int depth, Timer& timer) const
{
    
    //if the player whose turn it is has no more beans or we have reached max depth, finish recursion 
    if (board.beansInPlay(side) == 0 || depth == 0)
    {
        int finalMinMax = returnEval(board, side);
        return finalMinMax;
    }


	//check if you have timed out 
    if (timer.elapsed() >= MAXTIME || depth < 0)
    {
        return returnEval(board, side);
    }


    //--------------------------------------------------

    int bestEval = 0;
   //you searching for the lowest eval score 
    if (searchBestVal == false)
    {
        //set to high default value 
        bestEval = 2000;

        //cycle through each hole 
        for (int i = 1; i <= board.holes(); i++)
        {
            //check time 
            if (timer.elapsed() >= MAXTIME)
            {
                return returnEval(board, side);
            }

            //if that hole has beans in it 
            if (board.beans(side, i) > 0)
            {
                Board tempBoard(board);
                bool anotherTurn = makeMove(tempBoard, i, side);
                int newMinEval;

                //check time 
                if (timer.elapsed() >= MAXTIME)
                {
                    return returnEval(board, side);
                }

                //if you can get another turn 
                while (anotherTurn == true)
                {
                    searchBestVal = false;
                    newMinEval = findMinOrMax(tempBoard, opponent(side), searchBestVal, depth - 1, timer);
                    anotherTurn = false;
                }


                //By this point, you cannot make another move 
                //Search for the best move 
                searchBestVal = true;
                newMinEval = findMinOrMax(tempBoard, opponent(side), searchBestVal, depth - 1, timer);

                //update the bestEval if necessary 
                if (newMinEval < bestEval)
                {
                    bestEval = newMinEval;
                }
            }
        }
    }



    //--------------------------------------------------

 
	//you searching for the highest eval score 
    if (searchBestVal == true)
    {
        //set to low default value 
		bestEval = 2000;

		//cycle through each hole 
        for (int i = 1; i <= board.holes(); i++)
        {
			//check time again 
            if (timer.elapsed() >= MAXTIME)
            {
                return returnEval(board, side);
            }

			//if there are beans in that hole continue 
            if (board.beans(side, i) > 0)
            {
                //check time again 
                if (timer.elapsed() >= MAXTIME)
                {
                    return returnEval(board, side);
                }

                Board tempBoard(board);
				bool anotherTurn; 
				anotherTurn = makeMove(tempBoard, i, side);// make move
                

				//make more moves, while you can 
                int newBestEval;
                while (anotherTurn == true) 
                {
                    searchBestVal = true; 
                    newBestEval = findMinOrMax(tempBoard, side, searchBestVal, depth - 1, timer);
                    anotherTurn = false; 
                }
              
				//By this point, you cannot make another move 
				//Search for the worst move 
                 searchBestVal = false;
                 newBestEval = findMinOrMax(tempBoard, opponent(side), searchBestVal, depth - 1, timer);
                

                //update the bestEval if necessary 
                if (newBestEval > bestEval)
                {
					bestEval = newBestEval;
                }
            }
        }
    }
 
    return bestEval;
}








int SmartPlayer::returnEval(const Board& board, Side side) const
{
    //test if the game is over 
    if (board.beansInPlay(side) == 0)
    {
        int currentPlayerScore = board.beansInPlay(side) + board.beans(side, 0);
        int opponentScore = board.beansInPlay(opponent(side)) + board.beans(opponent(side), 0);

        //return high value if this resulted in a win 
        if (currentPlayerScore > opponentScore)
        {
            return 1000;
        }
        //return low value if this resulted in a lose 
        else if (currentPlayerScore < opponentScore)
        {
            return -1000;
        }
        //return 0 if they tie 
        else
        {
            return 0;
        }
    }

    
    


    //if this move did not end the game 
    // for int i = 0; i < board.
    // 
    //test if current side has more than half of the other side's beans in pot
    if (board.beans(side, 0) > board.totalBeans() / 2)
    {
        return 1000;
    }
    //test if other side has more than half of the current side's beans 
    else if (board.beans(opponent(side), 0) > board.totalBeans() / 2)
    {
        return -1000;
    }
     
    
    //return difference between pots
    return board.beans(side, 0) - board.beans(opponent(side), 0);
}







int SmartPlayer::chooseMove(const Board& b, Side s) const
{

    //Keep the function call under 5 seconds
    Timer timer;   //create a timer object 
    timer.start(); //start the timer 

    //check if the game is over 
    if (b.beansInPlay(s) == 0)
    {
        return -1;
    }

    //establish variables 
    int chosenHole = 0; 
    int bestEval = -2002; 
    int newEval = 0;
    bool searchForMax = true; 

    //cycle through holes 
    for (int i = 1; i <= b.holes(); i++)
    {
        if (b.beans(s, i) > 0)
        {
         
            Board tempBoard(b); 
            bool makeAnotherTurn = makeMove(tempBoard, i, s);
       

            //if you can make another turn
            if (makeAnotherTurn == true)
            {
                //return i; 
               searchForMax = true; 
               newEval = findMinOrMax(tempBoard, s, searchForMax, m_maxDepth, timer);// set your new move to compare with your old best move (moveVbest)
            }
            
            //if you cannot make another turn continue
            //look at opponent's perspecive
            searchForMax = false;
            newEval = findMinOrMax(tempBoard, s, searchForMax, m_maxDepth, timer);
       
            //compare the new and old value 
            if (newEval > bestEval)
            {
                bestEval = newEval;
                chosenHole = i;
            }


           // std::cerr << "BEST EVAL: " << bestEval <<  std::endl; 
        }
    }


   // std::cerr << "TIMEEEEEEEEEEEEEE: " << timer.elapsed() << std::endl;

    return chosenHole;
}


