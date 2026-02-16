#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;
#include "History.h"
#include "globals.h"



////////////////constructor////////////////////////// 
History::History(int nRows, int nCols)
	:hisRows(nRows), hisCols(nCols)
{
	//first initialize the area, set each space to a dot for 0
	for (int rowCounter = 0; rowCounter < hisRows; rowCounter++)
	{
		for (int colCounter = 0; colCounter < hisCols; colCounter++)
		{
			hisArray[rowCounter][colCounter] = '.'; 
		}

	}	
}



///////////////record function/////////////////////
bool History::record(int r, int c)
{
	int indexR = r - 1; 
	int indexC = c - 1; 

	//return false if the r and c are not within the bounds
	if (r > hisRows || r < 1 || c > hisCols ||c < 1)
	{
		return false; 
	}
	
	
	//record the change in the array for (r,c)
	//if there is a period at that point, change it to A 
	if (hisArray[indexR][indexC] == '.')
	{
		hisArray[indexR][indexC] = 'A'; 
		return true; 
	}
	
	//if there is a letter and the letter is not Z
	//increment the ascii by 1
	//(isalpha(hisArray[r][c])  > 0)
	if ((hisArray[indexR][indexC] >= 65)   &&   (hisArray[indexR][indexC]  <= 90)  &&  (hisArray[indexR][indexC] != 'Z'))
	{
		hisArray[indexR][indexC]++; 
	}
	
	//return true if it got to this point
	return true; 
}




//////////////display function/////////////////// 
void History::display() const
{
	//clear screen 
	clearScreen(); 

	//print array to screen 
	for (int rowCounter = 0; rowCounter < hisRows; rowCounter++)
	{
		for (int colCounter = 0; colCounter < hisCols; colCounter++)
		{
			cout << hisArray[rowCounter][colCounter];
		}
		cout << endl; //write an empty line after history grid 
	}
	cout << endl; 
}
