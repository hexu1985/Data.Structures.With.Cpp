#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#pragma hdrstop

// record that declares a dancer
struct Person
{
    char  name[20];
    char  sex;                          // 'F'(female) 'M'(male)
};

// queue holds a list of Person objects
typedef Person DataType;

#include "aqueue.h"

void main(void)
{
    // two queues to separate male and female dancers
    Queue maleDancers, femaleDancers;
    
    Person p;
    char blankseparator;
    
    // input file for the dancers;  
    ifstream fin;

    // open the file and check that the file exists
    fin.open("dance.dat");
    if (!fin)
    {
        cerr << "Unable to open file" << endl;
        exit (1);
    }
        
    // read input line that includes sex, name, and age
    while(fin.get(p.sex))               // terminate on eof
    {
        fin.get(blankseparator);        // clear blank
        fin.getline(p.name,20,'\n');
        // insert into correct queue
        if (p.sex == 'F')
            femaleDancers.QInsert(p);
        else
            maleDancers.QInsert(p);
     }
     
    // set a dancing pair by getting partners from two queues;
    // quit when the male or female queue is empty 
    cout << "The dancing partners are: " << endl << endl;
    while (!femaleDancers.QEmpty() && !maleDancers.QEmpty())
    {
        p = femaleDancers.QDelete();
        cout << p.name << "  ";         // announce female dancer
        p = maleDancers.QDelete();
        cout << p.name << endl;         // announce male dancer
     }
     cout << endl;
     
     
    // if either queue has unselected dancer(s), announce the
    // name of the first person in line
    if (!femaleDancers.QEmpty())
    {
        cout << "There are " << femaleDancers.QLength()
             << " women waiting for the next round." << endl;
        cout << femaleDancers.QFront().name
             << " will be the first to get a partner." << endl;
    }
    else if (!maleDancers.QEmpty())
    {
        cout << "There are " << maleDancers.QLength()
             << " men waiting for the next round." << endl;
        cout << maleDancers.QFront().name
             << " will be the first to get a partner." << endl;
    }
}

/*
<File "dance.dat">

M George Thompson
F Jane Andrews
F Sandra Williams
M Bill Brooks
M Bob Carlson
F Shirley Granley
F Louise Sanderson
M Dave Evans
M Harold Brown
F Roberta Edwards
M Dan Gromley
M John Gaston

<Run of Program 5.4>

The dancing partners are:

Jane Andrews  George Thompson
Sandra Williams  Bill Brooks
Shirley Granley  Bob Carlson
Louise Sanderson  Dave Evans
Roberta Edwards  Harold Brown

There are 2 men waiting for the next round.
Dan Gromley will be the first to get a partner.
*/
