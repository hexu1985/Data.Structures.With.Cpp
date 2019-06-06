#include <iostream.h>

class Rectangle
{
    private: 
        // length and width of the rectangle object
        float length,width; 
    public:
        // constructor
        Rectangle(float l = 0, float w = 0);
        
        // methods to retrieve and modify private data
        float GetLength(void) const;
        void  PutLength(float l);
        float GetWidth(void) const;
        void  PutWidth(float w);
        
        // compute and return rectangle measurements
        float Perimeter(void) const;
        float Area(void) const;
};


// constructor. assign l to length and w to width
Rectangle::Rectangle (float l, float w) : length(l), width(w)
{}

// return the length of the rectangle
float Rectangle::GetLength (void) const
{
    return length;
}

// allow client to assign new value l to length of the rectangle
void Rectangle::PutLength (float l)
{
    length = l;
}

// return the width of the rectangle
float Rectangle::GetWidth (void) const
{
    return width;
}

// allow client to assign new value w to width of the rectangle
void Rectangle::PutWidth (float w)
{
    width = w;
}

// compute and return the perimeter of the rectangle
float Rectangle::Perimeter (void) const
{
    return 2.0 * (length + width);  // return rectangle perimeter
}

// compute and return the area of the rectangle
float Rectangle::Area (void) const  // return area of rectangle
{
    return length*width;
}

void main(void)
{
    // cost of siding and molding are constants
    const float sidingCost = 2.00, moldingCost = 0.50;
    
    // initially, selections are not complete
    int completedSelections = 0;
    
    // option from menu selected by user
    char  doorOption;
    
    // length/width and door cost
    float glength, gwidth, doorCost;
    // total cost includes door,siding,molding
    float totalCost;           
    
    cout << "Enter the length and width of the garage: ";
    cin >> glength >> gwidth;
    
    // create garage object with user supplied dimensions.
    // create door object with default dimensions.
    Rectangle garage(glength,gwidth);
    Rectangle door;


    while (!completedSelections)
    {
        cout << "Enter 1-4 or 'q' to quit" << endl << endl;
        cout << "Door 1 (12 by 8; $380)    "
             << "Door 2 (12 by 10; $420)" << endl;
        cout << "Door 3 (16 by 8; $450)    "
             << "Door 4 (16 by 10; $480)" << endl;
        cout << endl;
        
        cin >> doorOption;

        if (doorOption == 'q')
            completedSelections = 1;    // terminate loop
        else
        {
            switch (doorOption)
            {
                case '1': door.PutLength(12);   // 12x8 ($380)
                          door.PutWidth(8);
                          doorCost = 380; 
                          break;
                    
                case '2': door.PutLength(12);   // 12x10 ($420)
                          door.PutWidth(10);
                          doorCost = 420;
                          break;
                    
                case '3': door.PutLength(16);   // 16x8 ($450)
                          door.PutWidth(8);
                          doorCost = 450;
                          break;
                            
                case '4': door.PutLength(16);   // 16x10 ($480)
                          door.PutWidth(10);
                          doorCost = 480 ;
                          break;
            }
            totalCost = doorCost +
                moldingCost*(garage.Perimeter()+door.Perimeter())
                + sidingCost*(garage.Area()-door.Area());
            cout << "Total cost of door, siding, and molding: $"
                 << totalCost << endl << endl;
        }
    }
}

/*
<Run of Program 3.1>

Enter the length and width of the garage: 20 12
Select the door by number or 'q' to quit

Door 1 (12 by 8; $380)    Door 2 (12 by 10; $420)
Door 3 (16 by 8; $450)    Door 4 (16 by 10; $480)

1
Total cost of door, siding, and molding is $720

Select the door by number or 'q' to quit

Door 1 (12 by 8; $380)    Door 2 (12 by 10; $420)
Door 3 (16 by 8; $450)    Door 4 (16 by 10; $480)

q
*/