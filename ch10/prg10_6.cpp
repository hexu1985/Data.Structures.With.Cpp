#include <iostream.h>
#pragma hdrstop

#include "maze.h"        // include the maze class

void main (void)
{
    // the file containing the maze parameters
    char filename[32];
    
    cout << "Enter the data file name: ";
    cin >> filename;
    
    // build the maze by reading the file
    Maze  M(filename);
    
    // solve the maze and print the result
    if (M.TraverseMaze(1))
        cout << "\nYou are free!" << endl;
    else
        cout << "No path out of the maze" << endl;
}

/*
<Run #1 of Program 10.6>

Enter the data file name: maze1.dat
7  6  2  1
You are free!

<Run #2 of Program 10.6>

Enter the data file name: maze2.dat
No path out of the maze

<Run #3 of Program 10.6>

Enter the data file name: bigmaze.dat
19  17  16  14  10  9  8  2  1
You are free.
*/
