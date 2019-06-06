#include <iostream.h>
#include <ctype.h>
#pragma hdrstop

#include "spooler.h"

void main(void)
{
    // the print spooler object 
    Spooler spool;
    int jnum, jobno = 0, rempages;
    char response = 'C';
    PrintJob J;
    
    for (;;)
    {
        // print choices.  can check/list only if jobs present
        if (spool.NumberOfJobs() != 0)
            cout << "Add(A)   List(L)   Check(C)   Quit(Q) ==> ";
        else
            cout << "Add(A)   Quit(Q) ==> ";
        cin >> response;
        // convert response to uppercase
        response = toupper(response);
        
        // action dictated by the response
        switch(response)
        {
            //  add a new job with next number used as id; read
            //  file name and the number of pages. 
            case 'A':   
                J.number = jobno;
                jobno++;
                cout << "File name: ";
                cin >> J.filename;
                cout << "Number of pages: ";
                cin >> J.pagesize; 
                spool.AddJob(J);
                break;
                        
            //  Print info for each remaining printer job
            case 'L':   
                spool.ListJobs();
                break;
                        
            // input job id; scan list with this key. indicate if
            // job complete or number of remaining pages to print
            case 'C':   
                cout << "Enter job number: ";
                cin >> jnum;
                rempages = spool.CheckJob(jnum);
                if (rempages > 0)
                    cout << "Job is in the queue. " << rempages
                         << " pages remain to be printed\n";
                else
                    cout << "Job has completed\n";
                break;
    
            // exit the switch and test for input 'Q'
            case 'Q':   
                break;
                        
            // indicate an invalid request and redraw the menu
            default:    
                cout << "Invalid spooler command.\n";
                break;
        }
        if (response == 'Q')
            break;
        cout << endl;
    }
}

/*
<Run of Program 9.8>

Add (A)   Quit (Q) ==> a
File name: notes
Number of pages: 75

Add (A)   List(L)   Check (C)   Quit (Q) ==> a
File name: paper
Number of pages: 25

Add (A)   List(L)   Check (C)   Quit (Q) ==> l
Job 0: notes   19 pages remaining
Job 1: paper   25 pages remaining

Add (A)   List(L)   Check (C)   Quit (Q) ==> c
Enter job number: 1
Job is in the queue. 20 pages remain to be printed

Add (A)   List(L)   Check (C)   Quit (Q) ==> l
Print queue is empty

Add (A)   Quit (Q) ==> q
*/
