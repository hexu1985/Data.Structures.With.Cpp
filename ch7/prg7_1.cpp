#include <iostream.h>
#pragma hdrstop

// includes template based sequential search and a sequential
// search function specific to C++ strings
#include "utils.h"

// declaration of Student and "==" for Student
#include "student.h"

void main()
{
    // three different array types
    int     list[10] = {5, 9, 1, 3, 4, 8, 2, 0, 7, 6};
    Student studlist[3] = {{1000, 3.4},{1555, 2.6},{1625, 3.8}};
    char    *strlist[5] = {"zero","one","two","three","four"};
    
    int     i, index;
    // this record is used as key to search array studlist
    Student studentKey = {1555, 0};
    
    if ((i = SeqSearch(list,10,8)) >= 0)
        cout << "Item 8 is found at index " << i << endl;
    else
		cout << "Item 8 is not found" << endl;
		
    index = SeqSearch(studlist, 3, studentKey);     
    cout << "Student 1555 has gpa " << studlist[index].gpa
    	 << endl;

    cout << "String 'two' is at index "
    	 << SeqSearch(strlist,5,"two") << endl;
}

/*
<Run of Program 7.1>
Item 8 is found at index 5
Student 1555 has gpa 2.6
String 'two' is at index 2
*/
