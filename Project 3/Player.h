#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED 

#include <string>
#include "Board.h"
#include "Side.h"
#include <chrono>




//---------------------------------------------------------------------------------------------------------------------------------------------


//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================



class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};



//---------------------------------------------------------------------------------------------------------------------------------------------

class Player
{
public: 
	Player(std::string name);
	std::string name() const;
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player();
private: 
	std::string m_name; 
};




//---------------------------------------------------------------------------------------------------------------------------------------------

//A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person
//enters a valid hole number), and returning that choice. We will never test for a situation where the user doesn't enter an integer 
//when prompted for a hole number. (The techniques for dealing with the issue completely correctly are a distraction to this project, 
//and involve either a function like stoi or strtol, or the type istringstream.)

class HumanPlayer : public Player
{
private:
public:
	HumanPlayer(std::string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~HumanPlayer();
};



//---------------------------------------------------------------------------------------------------------------------------------------------

//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: 
//leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement 
//class that at least plays legally.

class BadPlayer : public Player
{
private:
public:
	BadPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~BadPlayer();
};




//---------------------------------------------------------------------------------------------------------------------------------------------
//A SmartPlayer chooses a valid move and returns it. For any game played on a board of up to six holes per side, with up to four initial 
//beans per hole, SmartPlayer::chooseMove must return its choice in no more than five seconds on the SEASnet Linux server 
//lnxsrv07.seas.ucla.edu or lnxsrv09.seas.ucla.edu: (We'll give you a way of determining the time soon; until then, you can meet this 
//requirement by limiting the depth of your game tree search or the number of game tree positions you explore to a limit you determine experimentally.)

class SmartPlayer : public Player
{
private:
	bool makeMove(Board& board, int moveVal, Side side) const;
	int returnEval(const Board& board, Side side) const;
	int findMinOrMax(const Board& board, Side side, bool searchForMax, int depth, Timer& timer) const;

	int m_maxDepth = 7;
public:
	SmartPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~SmartPlayer();
};


#endif //PLAYER_INCLUDED