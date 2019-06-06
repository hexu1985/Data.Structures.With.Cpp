// record that specifies the intersection you
// arrive at when departing left, forward or right
// from the current intersection
struct Intersection
{
    int left;
    int forward;
    int right;
};

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>

class Maze
{
    private:
        // number of intersections in the maze and number of
        // the intersection that leads out
        int mazesize;
        int EXIT;
        
        // the array of maze intersections
        Intersection *intsec;
    public:
        // constructor
        Maze(char *filename);
        
        // traverse and solve the maze
        int TraverseMaze(int intsecvalue);
};

// build maze by reading intersections and the exit
// intersection number from filename
Maze::Maze(char *filename)
{
    ifstream    fin;
    int i;

    // open filename. terminate if not found
    fin.open(filename, ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "The maze data file " << filename
             << " cannot be opened!" << endl;
        exit(1);
    }
    
    // 1st entry of file is number of intersections in maze
    fin >> mazesize;

    // allocate an array of maze intersections. we do not use
    // index 0, so we must allocate mazesize+1 records. a next
    //  intersection number of 0 indicates a dead end
    intsec = new Intersection[mazesize+1];

    // read the intersections from the file
    for (i = 1; i <= mazesize; i++)
        fin >> intsec[i].left >> intsec[i].forward 
            >> intsec[i].right;

    // read number at the ending intersection and close file
    fin >> EXIT;
    fin.close();
}

// solve the maze using backtracking
int Maze::TraverseMaze(int intsecvalue)
{
    // if intsecvalue = 0, we are at a dead end;
    // otherwise, we attempt to find a valid direction
    // in which to move
    if (intsecvalue > 0)
    {
        // stopping condition: we have located exit point
        if (intsecvalue == EXIT)
        {
            // print the ending intersection number
            cout << intsecvalue << "  ";
            return 1;
        }
        
        // attempt to go left
        else if (TraverseMaze(intsec[intsecvalue].left))
        {
            // print intersection number and return True
            cout << intsecvalue << "  ";
            return 1;
        }
        
        // left leads to dead end. try going forward
        else if (TraverseMaze(intsec[intsecvalue].forward))
        {
            // print intersection number and return True
            cout << intsecvalue << "  ";
            return 1;
        }
    
        // left and forward are dead end. try going right
        else if (TraverseMaze(intsec[intsecvalue].right))
        {
            // print intersection number and return True
            cout << intsecvalue << "  ";
            return 1;
        }        
    }
    
    // we are at a dead end. return False.
    return 0;
}
