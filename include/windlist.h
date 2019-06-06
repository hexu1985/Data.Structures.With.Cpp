#include <iostream.h>
#include <ctype.h>

// include the String and LinkedList classes
#include "strclass.h"
#include "link.h"

// class that contains information for an individual window
class Window
{
    private:
      // window data includes its title and its index in
      // the table of available windows
      String windowTitle;
      int windowNumber;
        
    public:
      // constructors
      Window(void);
      Window(const String& title, int wnum);
        
      // data access methods 
      void ChangeTitle(const String& title);
      int GetWindowNumber(void);
        
      // overloaded operators
      int operator== (const Window& w);
      friend ostream& operator<< (ostream& ostr,
                                        const Window& w);
};

// default constructor
Window::Window(void)
{}

// constructor that initializes the title and window number
Window::Window(const String& title, int wnum):
        windowTitle(title), windowNumber(wnum)
{}

// rename the window
void Window::ChangeTitle(const String& title)
{
    windowTitle = title;
}

// get the window number
int Window::GetWindowNumber(void)
{
    return windowNumber;
}

// overload equality by comparing the window numbers
int Window::operator== (const Window& w)
{
    return windowNumber == w.windowNumber;
}

// overload output to print the window in the format title[#]
ostream& operator<< (ostream& ostr, const Window& w)
{
    ostr << "  " << w.windowTitle << '[' << w.windowNumber << ']';
    return ostr;
}

// linked list storage structure that holds Window objects  
class WindowList
{
    private:
        // list of active windows       
        LinkedList<Window> windList;
        
        // list of available windows and number of open windows
        int windAvail[10];
        int windCount;
        
        // functions to get and free windows     
        int GetWindowNumber(void);
        int FindAndDelete(Window& wind);
        
        // print list of open windows
        void PrintWindowList(void);
        
    public:
        // constructor
        WindowList(void);
        
        // window menu methods
        void New(void);
        void Close(void);                 // close front window
        void CloseAll(void);              // close all windows
        void SaveAs(const String& name);  // change name
        void Activate(int windownum);     // activate windownum
        
        // simulate the menu manager
        void SelectItem(int& item, String& name);
};

// constructor; initialize number of active windows to 0
 WindowList::WindowList(void)
{
    windCount = 0;
    for(int i=0;i < 10;i++)
        windAvail[i] = 1;
}

// get first free window from available window list 
int WindowList::GetWindowNumber(void)
{
    for(int i=0;i < 10;i++)
        // if it is available, select it
        // set the window to be unavailable. 
        if (windAvail[i])
        {
            windAvail[i] = 0;
            break;
        }
    return i;           // return window index
}

// print window information for all active windows
void WindowList::PrintWindowList(void)
{    
    for(windList.Reset(); !windList.EndOfList(); 
                                    windList.Next())
        cout << windList.Data();
}

// get a new window and give it the name 'untitled'
void WindowList::New(void)
{
    // check if a window is available.  if not quietly return
    if (windCount == 10)
    {
        cerr << "No more windows available until one is closed.\n";
        return;
    }
    
    // get a new 'Untitled' window by calling GetWindowNumber
    Window win("Untitled", GetWindowNumber());
    
    // make it active by inserting it in the front of the list
    windList.InsertFront(win);
    windCount++;
}

// close the current active window and delete the Window object
void WindowList::Close(void)
{
    int winNum;
    
    windList.Reset();       // move to front of list
    winNum = windList.Data().GetWindowNumber();
   
    // delete the Window record associated with the current window 
    windList.DeleteFront();
    
    // make the closed window available for future use
    windAvail[winNum] = 1;
    windCount--;            // decrement number of active windows
}

// close all of the current active windows
void WindowList::CloseAll(void)
{

    // close all windows by clearing the list and making all 
    // windows available
    windList.ClearList();
    windCount = 0;
    for(int i=0;i < 10;i++)
        windAvail[i] = 1;
}

// rename the front or active window
void WindowList::SaveAs(const String& name)
{
    
    windList.Reset();       // move to front of list
    windList.Data().ChangeTitle(name);
}

// 
int WindowList::FindAndDelete(Window& wind)
{ 
    int retval;

    // cycle through the list search for wind
    for(windList.Reset();!windList.EndOfList();windList.Next())
        // window "==" operator compares window numbers
        // break loop if have a match
        if(wind == windList.Data())
            break;
    // have window numbers matched?
    if(!windList.EndOfList())    
    {
        // assign wind, delete record and return 1 (success)
        wind = windList.Data();
        windList.DeleteAt();
        retval = 1;
    }
    else
        retval = 0;       // return 0 (failure)
    return retval;
}

void WindowList::Activate(int windownum)
{
    Window win("Dummy Name", windownum);

    if (FindAndDelete(win))
        windList.InsertFront(win);
    else
        cerr << "Incorrect window number.\n";
}

void WindowList::SelectItem(int& item, String& name)
{
    char selectchar, s[2];

    cout << "New";
    if (windCount > 0)
    {
        cout << "  Close";
        cout << "  Close All";
        cout << "  Save As";
    }
    cout << "  Quit";
    if(windCount > 0)
        PrintWindowList();
    cout << ": ";

    cin >> selectchar;
    selectchar = tolower(selectchar);
    if (isdigit(selectchar))
    {
        item = 6 + selectchar - '0';
        s[0] = selectchar;
        s[1] = 0;
        name = s;
    }
    else
        switch(selectchar)
        {
            case 'n':   item = 1;
                        name = "New";
                        break;
                
            case 'c':   item = 2;
                        name = "Close";
                        break;
                
            case 'a':   item = 3;
                        name = "Close All";
                        break;
                
            case 's':   item = 4;
                        name = "Save As";
                        break;
                
            case 'q':   item = 5;
                        name = "Quit";
                        break;
                        
            default:    cerr << "Not a valid menu selection." << endl;
                        item = 0;
                        break;
        }
}

