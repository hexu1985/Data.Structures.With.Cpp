#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#pragma hdrstop

#include "hash.h"
#include "strclass.h"
#include "strfreq.h"

void main(void)
{
    // read the strings from stream fin
    ifstream fin;
    NameRecord rec;
    String token;
    HashTable<NameRecord> HF(101,hash);
    
    fin.open("strings.dat", ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "Could not open \"strings.dat\"!" << endl;
        exit(1);
    }

    while(fin >> rec.name)
    {
        // look for string in table; if present, update count
        if (HF.Find(rec))
        {
            rec.count += 1;
            HF.Update(rec);
        }
        else
        {
            rec.count = 1;
            HF.Insert(rec);
        }
    }
    
    // print the strings and their frequency
    HashTableIterator<NameRecord> hiter(HF);
    
    for(hiter.Reset();!hiter.EndOfList();hiter.Next())
    {
        rec = hiter.Data();
        cout << rec.name << ": " << rec.count << endl;
    }
}

/*
<File "strings.dat">

Columbus Washington Napoleon Washington Lee Grant
Washington Lincoln Grant Columbus Washington

<Run of Program 14.2>

Lee: 1
Washington: 4
Lincoln: 1
Napoleon: 1
Grant: 2
Columbus: 2
*/
