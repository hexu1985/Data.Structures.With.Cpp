#include <iostream.h>
#pragma hdrstop

#include "strclass.h"

// move n disks from startpeg to endpeg,
// using middlepeg as the intermediate peg
void hanoi(int n, String startpeg, String middlepeg, 
            String endpeg)
{
    // stopping condition: move one disk
    if (n == 1)
        cout << "move " << startpeg << " to " << endpeg << endl;
        
    // move n-1 disks to middlepeg, move bottom disk to
    // endpeg, then move n-1 disks from middlepeg to endpeg
    else
    {
        hanoi(n-1,startpeg,endpeg,middlepeg);
        cout << "move  " << startpeg << " to " << endpeg << endl;
        hanoi(n-1,middlepeg,startpeg,endpeg);
    }
}

void main()
{
    // number of disks and the peg names
    int n;
    String startpeg = "start ", 
           middlepeg = "middle", 
           endpeg = "end   ";

    // prompt for n and solve the puzzle for n disks
    cout << "Enter the number of disks: ";
    cin >> n;
    cout << "The solution for n = " << n << endl;
    hanoi(n,startpeg, middlepeg, endpeg);
}

/*
<Run of Program 10.5>

Enter the number of disks: 3
The solution for n = 3
move  start  to end
move  start  to middle
move  end    to middle
move  start  to end
move  middle to start
move  middle to end
move  start  to end
*/
