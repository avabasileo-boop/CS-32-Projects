#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private:
	//2d area containing the history information 
	char hisArray[MAXROWS][MAXCOLS];
	int hisRows; 
	int hisCols; 
};

#endif
