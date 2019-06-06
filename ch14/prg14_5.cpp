#include <fstream.h>
#include <stdlib.h>
#pragma hdrstop

#include "keyval.h"     // iterator returns KeyValue objects
#include "dict.h"       // include the Dictionary class
#include "strclass.h"   // both key and value fields are Strings

// take a KeyValue object containing a word and
// its definition(s). print it
void PrintEntry(const KeyValue<String,String>& word)
{
    KeyValue<String,String> w = word;
    // word is followed by " - ", so word starts at print
    // position word length + 3
    int linepos = w.Key().Length() + 3;
    int i;
    
    // print word followed by " -". other blank from definition
    cout << w.Key() << " -";
    // print definition(s) on a sequence of 65 character lines
    while(!w.value.IsEmpty())
    {
        // determine if unprinted portion will fit within 65 char
        // line. compute index of the last character on the line
        if(w.value.Length() > 65-linepos)
        {
            // the string will not fit. move backward and find
            // first blank character. we will not split a word
            // between lines
            i = 64-linepos;
            while(w.value[i] != ' ')
                i--;
        }
        else
            // string fits on the line.
            i = w.value.Length()-1;
        // output the substring that fits on the line
        cout << w.value.Substr(0,i+1) << endl;
        // remove substring we just printed. prepare for new line
        w.value.Remove(0,i+1);
        linepos = 0;
    }
}

void main(void)
{
    // stream from which we read the data
    ifstream fin;
    String word, definition;
    // the dictionary
    Dictionary<String,String> wordDictionary("");
  
    // open the file "defs.dat" of words and their definitions
    fin.open("defs.dat",ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "The file 'defs.dat' is not found." << endl;
        exit(1);
    }

    // read a word and then a definition. using index operator,
    // insert the word and the definition or update the existing
    // definition by concatenating the current one
    while(fin >> word)
    {
        if (fin.eof())
            break;
		// reads blank following word
        definition.ReadString(fin);
        wordDictionary[word] += definition;
    }
    
    // declare an iterator to traverse the dictionary in order
    DictionaryIterator<String,String> dictIter(wordDictionary);

    // traverse dictionary. print each word and its definition(s)
    cout << "The dictionary is:" << endl << endl;
    for(dictIter.Reset();!dictIter.EndOfList();dictIter.Next())
    {
        PrintEntry(dictIter.Data());
        cout << endl;
    }
    
    wordDictionary.ClearList();
}

/*
<File "defs.dat">

program A list of the acts, speeches, pieces.
finish To bring to an end.
cause Anything producing an effect or result.
sextet A group of six performers. 
program A sequence of operations executed by a computer.
velocity Quickness of motion; swiftness.
cook To prepare by boiling, baking, frying, etc.
muff A cylindrical covering of fur to keep the hands warm.
banner A headline running across a newspaper page.
sextet A composition for six instruments.

<Run of Program 14.5>

The dictionary is:

banner - A headline running across a newspaper page.

cause - Anything producing an effect or result.

cook - To prepare by boiling, baking, frying, etc.

finish - To bring to an end.

muff - A cylindrical covering of fur to keep the hands warm.

program - A list of the acts, speeches, pieces. A sequence of
operations executed by a computer.

sextet - A group of six performers.  A composition for six
instruments.

velocity - Quickness of motion; swiftness.
*/
