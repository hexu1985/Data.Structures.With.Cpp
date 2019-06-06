#include <iostream.h>
#include <fstream.h>
#prama hdrstop

// SeqList class inherited from List. includes SeqListIterator
#include "seqlist2.h"

// record that holds the sales person's id no and units sold
struct SalesPerson
{
    int idno;
    int units;
};

// operator == compares employees by id no
int operator == (const SalesPerson& a, const SalesPerson &b)
{
    return a.idno == b.idno;
}

// take id as a key and scan the list. add the units sold by
// employee with id number == id.  print final information
void PrintTotalSales(SeqList<SalesPerson>& L, int id)
{
    // declare a SalesPerson variable and initialize fields
    SalesPerson  salesP = {id, 0};
    
    // declare the sequential list iterator and use it to
    // scan the list
    SeqListIterator<SalesPerson> iter(L);
    
    for(iter.Reset();!iter.EndOfList();iter.Next())
        // if a match with id occurs, add the number of units
        if (iter.Data() == salesP)
            salesP.units += (iter.Data()).units;
            
    // print the sales person's id and total units sold
    cout << "Sales person " << salesP.idno 
         << "    Total Units Sold " << salesP.units << endl;
}

void main(void)
{
    // lists will contain SalesPerson records and employee id
    SeqList<SalesPerson> salesList;
    SeqList<int> idList;        
    
    ifstream salesFile;     // file containing input data
    SalesPerson salesP;     // variable holding input

    // open the input file
    salesFile.open("sales.dat", ios::in | ios::nocreate);
    if (!salesFile)
    {
        cerr << "File 'sale.dat' not found!";
        exit(1);
    }

    // read data in form  'idno   units' to end of file
    while (!salesFile.eof())
    {
        // read data fields and insert into SeqList salesList
        salesFile >> salesP.idno >> salesP.units;
        salesList.Insert(salesP);
        // if id not in idlist, add it 
        if (!idList.Find(salesP.idno))
            idList.Insert(salesP.idno);
    }
    
    // set up iterators for the two lists
    SeqListIterator<int> idIter(idList);
    SeqListIterator<SalesPerson> salesIter(salesList);
    
    // scan the id list and use each entry as a parameter to
    // the function PrintTotalSales that adds up the total
    // number of units sold by the employee 
    for(idIter.Reset();!idIter.EndOfList();idIter.Next())
        PrintTotalSales(salesList, idIter.Data());
}

/*

<File 'Sales.dat'>
300     40
100     45
200     20
200     60
100     50
300     10
400     40
200     30
300     10

<Run of Program 12.4>

Sales person 300    Total Units Sold 70
Sales person 100    Total Units Sold 95
Sales person 200    Total Units Sold 110
Sales person 400    Total Units Sold 40
*/
