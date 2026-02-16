#ifndef SIDE_INCLUDED
#define SIDE_INCLUDED

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;
const int MAXTIME = 4900; 
const int MAX_EVAL = 1000; 
const int MIN_EVAL = -1000; 
const int MID_EVAL = 0; 

const int LOW_EVAL = -1000; 
const int HIGH_EVAL = 1000;

inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}

#endif //SIDE_INCLUDED