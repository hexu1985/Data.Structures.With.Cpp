#include <iostream.h>
#include <string.h>

// reverse first and last name and separate them
// with a comma. copy result to newName.
void ReverseName(char *name, char *newName)
{
    char *p;
        
    // search for first blank in name and replace with NULL char
    p = strchr(name,' ');       
    *p = 0;
    
    // copy last name to newName, append ", " and
    // concatenate first name  
    strcpy(newName,p+1);
    strcat(newName,", ");
    strcat(newName,name);
    
    // replace the NULL char with the original blank
    *p = ' ';
}
    
void main(void)
{
    char name[32], newName[32];
    int  i;
    
    // read and process three names
    for (i = 0; i < 3; i++)
    {
        cin.getline (name,32,'\n');
        ReverseName(name,newName);
        cout << "Reversed name: " << newName << endl << endl;
    }
}

/*
<Run of Program 2.1>

Abraham Lincoln
Reversed Name: Lincoln, Abraham

Debbie Rogers
Reversed Name: Rogers, Debbie

Jim Brady
Reversed Name: Brady, Jim
*/