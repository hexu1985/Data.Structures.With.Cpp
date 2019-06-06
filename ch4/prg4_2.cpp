#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#pragma hdrstop

#include "video.h"      // video store data declarations
#include "aseqlist.h"   // include the SeqList class
    
// reads film inventory from disk
void SetupInventoryList(SeqList &inventoryList)
{
    ifstream filmFile;
    FilmData fd;
    
    // open the file with error checking
    filmFile.open("Films", ios::in | ios::nocreate);
    if (!filmFile)
    {
        cerr << "File 'films' not found!" << endl;
        exit(1);
    }  
    
    // read lines until EOF; insert film names in inventory list
    while(filmFile.getline(fd.filmName,32,'\n'))
        inventoryList.Insert(fd);
}

// cycle through inventory list and print film names
void PrintInventoryList(const SeqList &inventoryList) 
{
    int i; 
    FilmData fd;
    
    for (i = 0; i < inventoryList.ListSize(); i++)
    {
        fd = inventoryList.GetData(i);  // get film record 
        cout << fd.filmName <<endl;     // print film name 
    }
}

// cycle through customer list. print customer and film names
void PrintCustomerList(const SeqList &customerList)
{
    int i; 
    FilmData fd;
    
    for (i = 0; i < customerList.ListSize(); i++)
    {
        fd = customerList.GetData(i);   // get customer record
        cout << fd.customerName << " (" << fd.filmName
             << ")" << endl;
    }
}

void main(void)
{
    // the two data bases
    SeqList inventoryList, customerList;
    int i;
    
    // film inventory file
    FilmData  fdata;
    
    char customer[20];
    
    SetupInventoryList(inventoryList);  // read inventory file
    
    // process 4 customers, asking for name and film desired. if
    // the film is available, insert film record into customer
    // list and delete it from inventory list; otherwise,
    // indicate it is not available.
    for (i = 0; i < 4; i++)
    {
        cout << "Customer Name: ";
        cin.getline(customer,32,'\n');       // get customer name
        cout << "Film Request: ";
        cin.getline(fdata.filmName,32,'\n'); // get film request
        
        // check if film available. if so create customer record
        if (inventoryList.Find(fdata))
        {
            strcpy(fdata.customerName, customer);
            // insert in customer list.
            customerList.Insert(fdata);
            // delete from inventory list     
            inventoryList.Delete(fdata);
        }
        else
            cout << "Sorry! " << fdata.filmName
                 << " is not available." << endl;
    }
    cout << endl;
    
    // print the final customer and inventory lists.
    cout << "Customers Renting Films " << endl;
    PrintCustomerList(customerList);
    cout << endl;
    cout << "Films Remaining in Inventory:" << endl;
    PrintInventoryList(inventoryList);
}

/*
<Input file "Films">

War of the Worlds
Casablanca
Dirty Harry
Animal House
The Ten Commandments
Beauty and the Beast
Schindler's List
Sound of Music
La Strata
Star Wars

<Run of Program 4.2>

Customer Name: Don Baker
Film Request: Animal House
Customer Name: Teri Molton
Film Request: Beauty and the Beast
Customer Name: Derrick Lopez
Film Request: La Strata
Customer Name: Hillary Dean
Film Request: Animal House
Sorry! Animal House is not available.

Customers Renting Films
Don Baker (Animal House)
Teri Molton (Beauty and the Beast)
Derrick Lopez (La Strata)

Films Remaining in Inventory:
War of the Worlds
Casablanca
Dirty Harry
The Ten Commandments
Schindler's List
Sound of Music
Star Wars
*/
