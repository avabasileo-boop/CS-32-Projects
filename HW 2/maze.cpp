//QUESTION #3
//For this part of the homework, you will turn in one file named maze.cpp that contains the Coord class (only if you use it) 
//and the pathExists function and nothing more.



// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    //If the start location is equal to the ending location, then we've
    //solved the maze, so return true.
    if ((sr == er) && (sc == ec))
    {
        return true; 
    }

    //Mark the start location as visted.                                                             //can you make it with anything???
    maze[sr][sc] = '#';

    //SOUTH
    if (maze[sr + 1][sc] == '.')
    {
        if (pathExists(maze, sr + 1, sc, er, ec))
            return true; 
    }
    //EAST 
    if (maze[sr][sc + 1] == '.')
    {
        if (pathExists(maze, sr, sc + 1, er, ec))
            return true;
    }
    //NORTH 
    if (maze[sr - 1][sc] == '.')
    {
        if (pathExists(maze, sr - 1, sc, er, ec))
            return true; 
    }
    //WEST
    if (maze[sr][sc - 1] == '.')
    {
        if (pathExists(maze, sr, sc - 1, er, ec))
            return true; 
    }

    return false; 
}




