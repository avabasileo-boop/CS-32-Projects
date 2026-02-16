#ifndef GAME_INCLUDED
#define GAME_INCLUDED


#include "Side.h"
#include "Board.h"
#include "Player.h"


class Board;
class Player;

class Game
{
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move(Side s);
	void play();
	int beans(Side s, int hole) const;
private: 
	Player* m_northPlayer; 
	Player* m_southPlayer; 
	Board m_board; 
	int m_turnNum; 
	bool m_GameOver; 
	void performCapture(Side s, int hole);
};

#endif //GAME_INCLUDED