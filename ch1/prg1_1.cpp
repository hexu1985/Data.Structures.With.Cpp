#include <iostream.h>

const float PI = 3.14152;
const float FencePrice = 3.50;
const float ConcretePrice = 0.50;

// declare Circle class with data and method declarations
class Circle
{
    private:
        // data member radius is a floating point number
        float   radius;
        
    public:
        // constructor                
        Circle(float r);
        
        // measurement functions
        float Circumference() const;
        float Area() const;
};

// class implementation

// constructor initializes the radius data member
Circle::Circle(float r): radius(r)
{ }

// return circumference
float Circle::Circumference() const
{
    return 2 * PI * radius;
}
        
// return area 
float Circle::Area() const
{
    return PI * radius * radius;
}

void main ()
{
    float radius;
    float FenceCost, ConcreteCost; 

    // set fixed point output with 2 decimal places
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    // prompt for and input radius
    cout << "Enter the radius of the pool: ";
    cin >> radius;

    // declare the Circle objects
    Circle Pool(radius);
    Circle PoolRim(radius + 3);       
     
    // Compute the cost of the Fence and output its value
    FenceCost = PoolRim.Circumference() * FencePrice;
    cout << "Fencing Cost is $" << FenceCost << endl;
    
    //  Compute the cost of the Concrete and output its value
    ConcreteCost = (PoolRim.Area() - Pool.Area())*ConcretePrice;
    cout << "Concrete Cost is $" << ConcreteCost << endl;
}

/*
<Run of Program 1.1>

Enter the radius of the pool: 40
Fencing Cost is $945.60
Concrete Cost is $391.12
*/
