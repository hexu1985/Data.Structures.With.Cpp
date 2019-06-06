#include <iostream.h>
#pragma hdrstop

#include "strclass.h"
#include "findpat.h"

void main()
{
    // define pattern string and string to search
    String pattern, lineStr;
    
    // search parameters
    int    lineno = 0, lenLineStr, startSearch, patIndex;
    
    // number of matches in current string
    int numberOfMatches;
    
    cout << "Enter the pattern to search for: ";
    pattern.ReadString();
    
    cout << "Enter a line or EOF:" << endl;
    while(lineStr.ReadString() != -1)
    {
        // maintain line count and setup search parameters
        lineno++;
        lenLineStr = lineStr.Length();
        startSearch = 0;
        numberOfMatches = 0;
        
        // search for the pattern up to end of string
        while(startSearch <= lenLineStr-1 && 
         (patIndex = FindPat(lineStr,pattern,startSearch)) != -1)
        {
            numberOfMatches++;
            // continue search for next occurrence of pattern
            startSearch = patIndex+1;
        }   
        cout << numberOfMatches << " matches on line "
             << lineno << endl;
        cout << "Enter a line or EOF:" << endl;
    }
}

/*
<Run of Program 8.5>

Enter the pattern to search for: iss
Enter a line or EOF:
Alfred the snake hissed because he missed his Missy.
3 matches on line 1
Enter a line or EOF:
Mississippi
2 matches on line 2
Enter a line or EOF:
He blissfully walked down the sunny lane.
1 matches on line 3
Enter a line or EOF:
It is so.
0 matches on line 4
Enter a line or EOF:
*/
