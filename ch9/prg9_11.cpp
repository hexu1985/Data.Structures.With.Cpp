#include <iostream.h>

// include the Window class and WindowList class
#include "windlist.h"

// used to clear the input buffer to end of line 
void ClearEOL(void)
{
    char c;
    
    do
        cin.get(c);
    while (c != '\n');
}

void main(void)
{
    // list of available windows for the program
    WindowList windops;
    
    // window tiles
    String wtitle, itemText;
    
    // boolean that waits for user supplied quit response
    int done = 0, item;
    
    // run the simulation until user types 'q'  
    while(!done)
    {
        // print the menu options and get a user selection.
        windops.SelectItem(item,itemText);
        
        // if the user selects a number, activate that window
        if (item >= 6)
            windops.Activate(itemText[0] - '0');
            
        // otherwise select from the options 0 - 5
        // Call the method to process the request
        else
            switch(item)
            {
                case 0:     break;
                case 1:     windops.New();
                            break;
                case 2:     windops.Close();
                            break;
                case 3:     windops.CloseAll();
                            break;
                case 4:     cout << "New Window Title: ";
                            ClearEOL();
                            wtitle.ReadString();
                            windops.SaveAs(wtitle);
                            break;
                case 5:     done = 1;
                            break;
            }
    }
}

/*
<Run of Program 9.11>

New  Quit: n
New  Close  Close All  Save As  Quit  Untitled[0]: n
New  Close  Close All  Save As  Quit  Untitled[1]  Untitled[0]: s
New Window Title: one
New  Close  Close All  Save As  Quit  one[1]  Untitled[0]: 0
New  Close  Close All  Save As  Quit  Untitled[0]  one[1]: s
New Window Title: two
New  Close  Close All  Save As  Quit  two[0]  one[1]: n
New  Close  Close All  Save As  Quit  Untitled[2] two[0] one[1]:s
New Window Title: three
New  Close  Close All  Save As  Quit  three[2]  two[0]  one[1]: 0
New  Close  Close All  Save As  Quit  two[0]  three[2]  one[1]: c
New  Close  Close All  Save As  Quit  three[2]  one[1]: a
New  Quit: q
*/
