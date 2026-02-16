
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;



void doBoardTests()
{
	Board b(3, 2);
	assert(b.holes() == 3 && b.totalBeans() == 12 &&
		b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
	b.setBeans(SOUTH, 1, 1);
	b.moveToPot(SOUTH, 2, SOUTH);
	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
		b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
		b.beansInPlay(SOUTH) == 3);
	Side es;
	int eh;
	b.sow(SOUTH, 3, es, eh);
	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
}





/* 
//TESTING FOR BOARD CLASS!!!
int main()
{
	//Supplied Board Test 
	doBoardTests();
	cout << "Passed all tests!" << endl;

	//Basic Board Test 
	Board b(3, 2);
	cout << endl << endl << "******************************************** CONSTRUCTOR TEST ********************************************" << endl;
	b.printBoard();


	cout << endl << "holes per side: " << b.holes() << endl;
	cout << "total beans: " << b.totalBeans() << endl;


	cout << "beans in south pot: " << b.beans(SOUTH, POT) << endl; // 0 
	cout << "beans in north pot: " << b.beans(NORTH, POT) << endl; // 0 
	cout << "beans in play south: " << b.beansInPlay(SOUTH) << endl;  // 6
	cout << "beans in play north: " << b.beansInPlay(NORTH) << endl;  // 6

	cout << endl << endl << "******************************************** FIRST SOW TEST ********************************************" << endl;
	cout << "Now sow beans in third pot south." << endl; 
	Side es; 
	int eh; 
	b.sow(SOUTH, 3, es, eh);
	b.printBoard();

	cout << "es: " << es << " eh: " << eh << endl;  //NORTH (0) and 3 
	cout << "beans in south, hole 3: " << b.beans(SOUTH, 3) << endl; //0
	cout << "beans in north, hole 3: " << b.beans(NORTH, 3) << endl; //3
	cout << "beans in south pot: " << b.beans(SOUTH, POT) << endl; //1
	cout << "beans in north pot: " << b.beans(NORTH, POT) << endl; //0
	cout << "beans in play south: " << b.beansInPlay(SOUTH) << endl; //4
	cout << "beans in play north: " << b.beansInPlay(NORTH) << endl; //7

	//Sow Across Multiple Pots, starting on NORTH
	cout << endl << endl << "******************************************** NEW BOARD ********************************************" << endl; 
	cout << "Sow North, space 3" << endl;
	Board b2(3, 10);
	b2.printBoard();
	cout << endl; 
	b2.sow(NORTH, 3, es, eh);
	b2.printBoard();
	cout << "end side: " << es << " end hole: " << eh << endl; 

	//Sow Across Multiple Pots, starting on SOUTH
	Board b3(3, 10);
	cout << endl << endl << "******************************************** NEW BOARD ********************************************" << endl;
	cout << "Sow SOUTH, space 1" << endl;
	b3.printBoard();
	cout << endl;
	b3.sow(SOUTH, 1, es, eh);
	b3.printBoard();


	cout << endl << "end side: " << es << " end hole: " << eh << endl;
	cout << "beans in south pot: " << b3.beans(SOUTH, POT) << endl;
	cout << "beans in north pot: " << b3.beans(NORTH, POT) << endl;
	cout << "beans in play south: " << b3.beansInPlay(SOUTH) << endl;
	cout << "beans in play north: " << b3.beansInPlay(NORTH) << endl;
	cout << "beans in south, hole 2: " << b3.beans(SOUTH, 3) << endl;
	cout << "beans in north, hole 5: " << b3.beans(NORTH, 5) << endl;


	//Test with many beans, starting on SOUTH
	cout << endl << endl << "******************************************** NEW BOARD ********************************************" << endl;
	cout << "Sow SOUTH, space 1" << endl;
	Board b4(6, 20);
	b4.printBoard();
	cout << endl;
	b4.sow(SOUTH, 1, es, eh);
	b4.printBoard();
	cout << "end side: " << es << " end hole: " << eh << endl;

	//Test with many beans, starting on NORTH
	cout << endl << endl << "******************************************** NEW BOARD ********************************************" << endl;
	cout << "Sow NORTH, space 3" << endl;
	Board b5(6, 20);
	b5.printBoard();
	cout << endl;
	b5.sow(NORTH, 3, es, eh);
	b5.printBoard();

	cout << endl << "end side: " << es << " end hole: " << eh << endl; 
	cout << "beans in south pot: " << b5.beans(SOUTH, POT) << endl;
	cout << "beans in north pot: " << b5.beans(NORTH, POT) << endl; 
	cout << "beans in play south: " << b5.beansInPlay(SOUTH) << endl;  
	cout << "beans in play north: " << b5.beansInPlay(NORTH) << endl;  
	cout << "beans in south, hole 2: " << b5.beans(SOUTH, 3) << endl; 
	cout << "beans in north, hole 5: " << b5.beans(NORTH, 5) << endl; 

	cout << endl << endl << "******************************************** INVALID INPUT TESTS ********************************************" << endl;
}	
*/






/* 
//TESTING FOR PLAYER CLASS
int main()
{
	//Testing human player 
	cout << "--------------------------------------------------TESTING HUMAN PLAYER-----------------------------------------------" << endl; 
	HumanPlayer p1("AJ"); 
	cout << "Is this player interactive: "  << p1.isInteractive() << "  Answer: 1" << endl;
	Board board1(2, 2); 
	cout << "Board before change: " << endl; 
	board1.printBoard(); 
	p1.chooseMove(board1, SOUTH); 
	cout << endl << endl; 



	//Testing bad player 
	cout << "--------------------------------------------------TESTING BAD PLAYER-----------------------------------------------" << endl;
	cout << "FIRST WE WILL TEST SOUTH SIDE" << endl;
	BadPlayer p2("SB");
	cout << "Is " << p2.name() << " interacitive: " << p2.isInteractive() << "  Answer : 0" << endl << endl;

	cout << "Board before any changes." << endl; 
	Board board2(3, 3); 
	board2.printBoard(); 
	cout << endl << endl; 

	p2.chooseMove(board2, SOUTH); 
	cout << "Answer: should select hole 1" << endl; 
	cout << "Sow hole 1, South side" << endl; 
	Side es; 
	int eh; 
	board2.sow(SOUTH, 1, es, eh); 
	board2.printBoard(); 
	cout << endl << endl;

	p2.chooseMove(board2, SOUTH); 
	cout << "Answer: should select hole 2" << endl;
	cout << "Sow hole 2, South side" << endl;
	board2.sow(SOUTH, 2, es, eh);
	board2.printBoard();
	cout << endl << endl;

	p2.chooseMove(board2, SOUTH);
	cout << "Answer: should select hole 3" << endl;
	cout << "Sow hole 3, South side" << endl;
	board2.sow(SOUTH, 3, es, eh);
	board2.printBoard();
	cout << endl << endl;

	cout << endl << "NEXT WE WILL TEST NORTH SIDE" << endl << endl << endl;

	p2.chooseMove(board2, NORTH);
	cout << "Answer: Now we are looking at north side. Should select hole 1" << endl;
	cout << "Sow hole 1, NORTH side" << endl;
	board2.sow(NORTH, 1, es, eh);
	board2.printBoard();
	cout << endl << endl;

	p2.chooseMove(board2, NORTH);
	cout << "Should select hole 2" << endl;
	cout << "Sow hole 2, NORTH side" << endl;
	board2.sow(NORTH, 2, es, eh);
	board2.printBoard();
	cout << endl << endl;

	p2.chooseMove(board2, NORTH);
	cout << "Answer: Should select hole 3" << endl;
	cout << "Sow hole 3, NORTH side" << endl;
	board2.sow(NORTH, 3, es, eh);
	board2.printBoard();
	cout << endl << endl;


	cout << "--------------------------------------------------TESTING SMART PLAYER-----------------------------------------------" << endl;
	
}
*/





/* 
//Testing Game class PART 1
int main()
{
	//Display test
	cout << "--------------------------------------------------TESTING DISPLAY-----------------------------------------------" << endl;
	HumanPlayer hp("Marge");
	BadPlayer bp("Homer");
	Board b(3, 2);
	Game g(b, &hp, &bp);
	g.display();

	
	//Display test
	cout << "--------------------------------------------------TESTING STATUS-----------------------------------------------" << endl;
	
	//for this test my move function was not working yet, so I set my m_gameOver to true in the compiler, when it is normally set to false as default 
	cout << "BOARD WITH EMPTY SOUTH" << endl; 
	Board b2(2, 2);
	cout << "Print first board: " << endl; 
	b2.printBoard(); 
	Side endSide; 
	int  endHole; 
	b2.sow(SOUTH, 2, endSide, endHole);     //In this test I modified this part and tested for each sensario: South win, North win, tie 
	cout << endl << "Print board after modification: " << endl; 
	b2.printBoard(); 
	Game g2(b2, &hp, &bp);
	cout << endl << "Display using display function:" << endl; 
	g2.display();


	bool over; 
	bool hasWinner; 
	Side winningSide(SOUTH); 
	cout << endl << "STATUS: " << endl;
	g2.status(over, hasWinner, winningSide);
	cout << endl << "over: " << over;
	cout << endl << "has Winner: " << hasWinner; 
	cout << endl << "winning side: " << winningSide; 
}
*/





/*
//testing game class PART 2 
int main()
{
	
	cout << "----------------------------------------------TEST MOVE Human vs. Human------------------------------------------" << endl;
	HumanPlayer hp1("Marge");
	HumanPlayer hp2("Homer");
	Board b(3, 2);
	Game g(b, &hp1, &hp2);
	cout << "ORIGINAL BOARD: " << endl; 
	g.display();
	g.move(SOUTH);   //start with south side 
	


	cout << "----------------------------------------------TEST MOVE H v. H and Capture------------------------------------------" << endl;
	Board b(3, 1);
	Side endSide; 
	int endHole; 
	b.sow(SOUTH, 2, endSide, endHole); 
	cout << "ORIGINAL BOARD: " << endl;
	b.printBoard(); 



	HumanPlayer hp1("Steve"); //south 
	HumanPlayer hp2("Ava");   //north 
	Game g(b, &hp1, &hp2);
	cout << endl << "ORIGINAL BOARD PRINTED WITH DISPLAY: " << endl;
	g.display();

	cout << endl << "BOARD AFTER MOVE: " << endl;
	g.move(SOUTH); 
	


	cout << "----------------------------------------------TEST MOVE Human vs. Human NORTH------------------------------------------" << endl;
	HumanPlayer hp1("Marge");
	HumanPlayer hp2("Homer");
	Board b(3, 2);
	Game g(b, &hp1, &hp2);
	cout << "ORIGINAL BOARD: " << endl;
	g.display();
	g.move(NORTH);   //start with north side in this case
	


	cout << "----------------------------------------------TEST MOVE H v. H and Capture NORTH------------------------------------------" << endl;
	Board b(3, 1);
	Side endSide;
	int endHole;
	b.sow(NORTH, 2, endSide, endHole);
	cout << "ORIGINAL BOARD: " << endl;
	b.printBoard();



	HumanPlayer hp1("Steve"); //south
	HumanPlayer hp2("Ava");   //north
	Game g(b, &hp1, &hp2);
	cout << endl << "ORIGINAL BOARD PRINTED WITH DISPLAY: " << endl;
	g.display();

	cout << endl << "BOARD AFTER MOVE: " << endl;
	g.move(NORTH);
	


	cout << "----------------------------------------------BAD PLAYER vs. BAD PLAYER - SOUTH------------------------------------------" << endl;
	Board b(3, 1);
	Side endSide;
	int endHole;
	BadPlayer bp1("Bot 1"); 
	BadPlayer bp2("Bot 2"); 
	cout << "ORIGINAL BOARD: " << endl;
	b.printBoard();
	Game g(b, &bp1, &bp2);
	g.move(SOUTH); 
	


	cout << "----------------------------------------------BAD PLAYER vs. BAD PLAYER - NORTH------------------------------------------" << endl;
	Board b(3, 1);
	Side endSide;
	int endHole;
	BadPlayer bp1("Bot 1");
	BadPlayer bp2("Bot 2");
	cout << "ORIGINAL BOARD: " << endl;
	b.printBoard();
	Game g(b, &bp1, &bp2);
	g.move(NORTH);
	


	cout << "----------------------------------------------BAD PLAYER vs. BAD PLAYER - NORTH------------------------------------------" << endl;
	Board b(3, 1);
	Side endSide;
	int endHole;
	BadPlayer bp1("Bot 1");
	BadPlayer bp2("Bot 2");
	cout << "ORIGINAL BOARD: " << endl;
	b.printBoard();
	Game g(b, &bp1, &bp2);
	g.move(SOUTH);
	
}
*/



//Testing game class -- testing play function 
int main()
{
	/*
	

	cout << "----------------------------------------------TEST Human vs. Human ------------------------------------------" << endl;
	HumanPlayer hp1("Ava");   //south 
	HumanPlayer hp2("Steve"); //north 
	Board b1(2, 2);
	Game g1(b1, &hp1, &hp2);
	g1.play();



	//cout << "----------------------------------------------TEST Human vs. BadPlayer ------------------------------------------" << endl;
	HumanPlayer hp21("Ava");   //south 
	BadPlayer bp22("Bot Player"); //north 
	Board b2(2, 2);
	Game g2(b2, &hp21, &bp22);
	g2.play();

		

	//cout << "----------------------------------------------TEST BadPlayer vs. BadPlayer ------------------------------------------" << endl;
	BadPlayer bp31("Bot 2");   //south 
	BadPlayer bp32("Bot 1"); //north 
	Board b3(3, 2);
	Game g3(b3, &bp31, &bp32);
	g3.play();

	*/

	BadPlayer bp("Bad Bot");   //south 
	SmartPlayer sp("Smart Bot"); //north 
	Board b1(5, 6);
	Game g1(b1, &bp, &sp);
	g1.play();

}





/*
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doPlayerTests()
{
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge" && hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	//SmartPlayer sp("Lisa");
	//assert(sp.name() == "Lisa" && !sp.isInteractive());
	Board b(3, 2);
	b.setBeans(SOUTH, 2, 0);
	cout << "=========" << endl;
	int n = hp.chooseMove(b, SOUTH);
	cout << "=========" << endl;
	assert(n == 1 || n == 3);
	n = bp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
	//n = sp.chooseMove(b, SOUTH);
	//assert(n == 1 || n == 3);
}

int main()
{
	doPlayerTests();
	cout << "Passed all tests" << endl;
}
*/


/*
#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);


	cout << ">>>>>>>>>>>>>>>Passed the first test! " << endl;

	g.move(SOUTH);
	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);


	cout << ">>>>>>>>>>>>>>>Passed the second test! " << endl;

	g.move(NORTH);
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	cout << ">>>>>>>>>>>>>>>Passed the third test! " << endl;

	g.move(SOUTH);
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	cout << ">>>>>>>>>>>>>>>Passed the forth test! " << endl;

	g.move(NORTH);
	
	//   0  0  0
	// 1         4
	//   0  0  0


	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);

	cout << ">>>>>>>>>>>>>>>Passed the fifth test! " << endl;
}

int main()
{
	doGameTests();
	cout << "Passed all tests" << endl;
}

*/
