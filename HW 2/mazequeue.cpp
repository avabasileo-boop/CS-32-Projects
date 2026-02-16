#include<iostream>
#include <queue>
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


    queue<Coord> coordQueue;           //create a Queue of Coord objects 
    Coord firstCoord(sr, sc);          //Make a Coord from the sr and sc 
    coordQueue.push(firstCoord);       //push enqueue coordinate at the back 
    maze[sr][sc] = '@';                //set maze[sr][sc] to have a value other than '.'                                                                                      //DELETE THIS!
    int counter = 1; 

    //While the stack is not empty
    while (coordQueue.empty() == false)
    {
        //set currentCord to whatever is at the top of the queue
        Coord currentCord = coordQueue.front();          //get item in the front of queue
        counter++; 
        coordQueue.pop();                                //dequeue front item in queue
        

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
            coordQueue.push(south);
            maze[south.r()][south.c()] = '@';
        }

        //check east
        if (maze[east.r()][east.c()] == '.')
        {
            coordQueue.push(east);
            maze[east.r()][east.c()] = '@';
        }

        //check north
        if (maze[north.r()][north.c()] == '.')
        {
            coordQueue.push(north);
            maze[north.r()][north.c()] = '@';
        }

        //check west
        if (maze[west.r()][west.c()] == '.')
        {
            coordQueue.push(west);
            maze[west.r()][west.c()] = '@';
        }
    }
    //No solution found
    return false;
}







int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','.','.','X' },
        { 'X','.','.','X','X','.','X','X','.','X' },
        { 'X','.','X','.','.','.','.','X','X','X' },
        { 'X','X','X','X','.','X','X','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','.','.','X','.','X','.','.','.','X' },
        { 'X','X','.','X','.','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3, 4, 8, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}


