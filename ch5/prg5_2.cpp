#include <iostream.h>
#pragma hdrstop

typedef int DataType;

#include "astack.h"

// print integer num in base B
void MultibaseOutput(long num, int B)
{
    // stack holds base B digits left to right
    Stack S;
    
    // extract base B digits right to left and push on stack S
    do
    {
        S.Push(int(num % B));    // convert to int and push on stack
        num /= B;                // remove right most digit
    } while (num != 0);          // continue until all digits computed
    
    while (!S.StackEmpty())  // flush the stack
        cout << S.Pop();
}

void main(void)
{
    long num;                // decimal number
    int  B;                  // base
    
    // read 3 positive numbers and the desired base 2 <= B <= 9
    for(int i=0;i < 3;i++)
    {
        cout << "Enter non-negative decimal number and base "
             << "(2<=B<=9): ";
        cin >> num >> B;
        cout << num << " base " << B << " is ";
        MultibaseOutput(num, B);
        cout << endl;
    }
}

/*

<Run of Program 5.2>

Enter non-negative decimal number and base (2<=B<=9): 72 4
72 base 4 is 1020
Enter non-negative decimal number and base (2<=B<=9): 53 2
53 base 2 is 110101
Enter non-negative decimal number and base (2<=B<=9): 3553 8 
3553 base 8 is 6741
*/
