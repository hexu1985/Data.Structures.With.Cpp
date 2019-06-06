#include "random.h"

class Dice
{
    private:
        // member data
        int  diceTotal;                 // sum of the two die
        int  diceList[2];                // listing of the two die faces
        
        // random number generator class used for dice toss
        RandomNumber rnd;
        
    public:
        // constructor
        Dice(void);
        
        // dice handling methods    
        void Toss(void);
        int Total(void) const;
        void DisplayToss(void) const;   
};  

// constructor. let random number generator use automatic seeding
Dice::Dice(void)
{}
        
// toss and determine dietotal
void Dice::Toss(void)
{   
    diceTotal = 0;
    for (int i = 0; i < 2; i++)
    {
        diceList[i] = rnd.Random(6) + 1;
        diceTotal = diceTotal + diceList[i];
    }
}

// return the value of dietotal
int Dice::Total(void) const
{   
    return diceTotal;
}

// print the dice faces
void Dice::DisplayToss(void) const
{   
    for (int i = 0; i < 2; i++)
        cout << diceList[i] << "  ";
}

