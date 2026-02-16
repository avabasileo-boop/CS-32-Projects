#include<iostream>
#include <stack>
using namespace std;






//Coord Class//
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};







//PathExists Function//
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    

    stack<Coord> coordStack;           //create a stack of Coord objects 
    Coord firstCoord(sr, sc);          //Make a Coord from the sr and sc 
    coordStack.push(firstCoord);       //push starting coordinate onto stack 
    maze[sr][sc] = '@';                //set maze[sr][sc] to have a value other than '.'

   

    //While the stack is not empty
    while (coordStack.empty() == false)
    {
        //set currentCord to whatever is at the top of the stack 
        Coord currentCord = coordStack.top(); 
        coordStack.pop();

        //check if you have suceeded
        if (currentCord.r() == er && currentCord.c() == ec)
            return true;

        //set possible n, s, e, w coordinates
        Coord north(currentCord.r() - 1, currentCord.c());
        Coord south(currentCord.r() + 1, currentCord.c());
        Coord east(currentCord.r(), currentCord.c() + 1);
        Coord west(currentCord.r(), currentCord.c() - 1);

        //Check that you can move in that direction 
        //AND that the cell hasn't been encountered already 
        
        //check south 
        if (maze[south.r()][south.c()] == '.')
        {
            coordStack.push(south); 
            maze[south.r()][south.c()] = '@'; 
        }

       //check east
        if (maze[east.r()][east.c()] == '.')
        {
            coordStack.push(east);
            maze[east.r()][east.c()] = '@';
        }

        //check north
        if (maze[north.r()][north.c()] == '.')
        {
            coordStack.push(north);
            maze[north.r()][north.c()] = '@';
        }

        //check west
        if (maze[west.r()][west.c()] == '.')
        {
            coordStack.push(west);
            maze[west.r()][west.c()] = '@';
        }
    }
    //No solution found
    return false;
}



int main()
{

}

















