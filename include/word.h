#include <iostream.h>
#include <ctype.h>
#include <iomanip.h>


#include "link.h"      // LinkedList obj holds line numbers 
#include "strclass.h"  // a text word is stored as a String

class Word
{
   private:
      // wordText is word of text, count is its frequency
      String wordText;
      int count;
      
      // the line count is shared amoung all Word objects
      static int lineno;
      
      // last line number where word occurred. used to know
      // when to insert a line number into lineNumbers
      int lastLineNo;
      LinkedList<int> lineNumbers;
   
   public:
      // constructor
      Word(void);
      
      // public class operations
      void CountWord (void);
      String& Key(void);
      
      // comparison operators used by BinSTree class
      int operator== (const Word& w) const;
      int operator< (const Word& w) const;
      
      // Word stream operators
      friend istream& operator>> (istream& istr, Word& w);
      friend ostream& operator<< (ostream& ostr, Word& w);
};

// constructor. set count to 0 and lastLineNo to 0
Word::Word(void): count(0), lastLineNo(0)
{}

// record the occurrence of a word
void Word::CountWord (void)
{
   // increment the word's occurrence count
   count++;
   
   // if this is the first time the word has occurred or
   // it has occurred on a new line, insert it into the
   // list and change lastLineNo to the current line
   if (count == 1 || lastLineNo != lineno)
   {
      lineNumbers.InsertRear(lineno);
      lastLineNo = lineno;
   }
}

// return the text of the word
String& Word::Key(void)
{
   return wordText;
}

// comparison operators use wordText as the key

int Word::operator== (const Word& w) const
{
   return wordText == w.wordText;
}

int Word::operator< (const Word& w) const
{
   return wordText < w.wordText;
}

// input a Word object from a stream
istream& operator>> (istream& istr, Word& w)
{
   // read characters from istr into wd
   char c, wd[20];
   int   i = 0;

   // skip leading whitespace and non-alphabetic characters
   while (istr.get(c) && !isalpha(c))
      // if end of line is found, increment line number count
      if ( c == '\n')
         w.lineno++;
         
   // if not at end of file, read the word
   if (!istr.eof())
   {  
      // convert first char of word to lowercase. assign to wd
      c = tolower(c);
      wd[i++] = c;
      
      // read consecutive alphabetic or numeric characters and
      // convert each to lower case
      while (istr.get(c) && (isalpha(c) || isdigit(c)))
         wd[i++] = tolower(c);
         
      // null terminate the C++ string wd
      wd[i] = '\0';
      
      // if newline after current word, save for next word
      if (c == '\n')
         istr.putback(c);

      // set wd to wordText, count to 0, lastLineNo to lineno 
      w.wordText = wd;
      w.count = 0;
      w.lastLineNo = w.lineno;
   }
   
   // flush any pre-existing queue elements and return
   w.lineNumbers.ClearList();
   return istr;
}

// output a Word object to a stream
ostream& operator<< (ostream& ostr, Word& w)
{  
   // output the word
   ostr << w.wordText;
   
   // output count right justified with leading '.' characters
   ostr.fill('.');
   ostr << setw(25-w.wordText.Length()) << w.count << ": ";
   ostr.fill(' ');      // set fill char back to blank
   
   // traverse the list and print the line numbers
   for(w.lineNumbers.Reset(); !w.lineNumbers.EndOfList(); 
                                        w.lineNumbers.Next())
      ostr << w.lineNumbers.Data() << "    ";
   ostr << endl;
   
   return ostr;
}

// lineno is current line number of the document. it is
// a private static data member of Word. as such, it is
// shared among all Word objects
int Word::lineno = 1;
