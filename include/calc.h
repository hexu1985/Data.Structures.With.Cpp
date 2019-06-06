#include <iostream.h>
#include <math.h>
#pragma hdrstop

enum Boolean {False, True};
typedef double DataType;        // calculator accepts real data
#include "astack.h"             // include Stack class

class Calculator
{
    private:
        // private members: calculator stack and operators
        Stack S;                // holds operands
    
        void Enter(double num);
        Boolean GetTwoOperands(double& opnd1, double& opnd2);
        void Compute(char op);

    public:
        // constructor
        Calculator(void);
        
        // evaluate an expression and clear calculator
        void Run(void);
        void Clear(void);
};

// store data value on the stack
void Calculator::Enter(double num)
{
    S.Push(num);
}

// fetch operands from stack and assign value to parameters.
// print message and return False if two operands not present
Boolean Calculator::GetTwoOperands(double& opnd1, double& opnd2)
{
    if (S.StackEmpty())         // check for presence of operand
    {
        cerr << "Missing operand!" << endl;
        return False;
    }
    opnd1 = S.Pop();            // fetch right-hand operand
    if (S.StackEmpty())
    {
        cerr << "Missing operand!" << endl;
        return False;
    }
    opnd2 = S.Pop();            // fetch left-hand operand
    return True;
}

// evaluate an operation
void Calculator::Compute(char op)
{
    Boolean result;
    double operand1, operand2;

    // fetch two operands and identify success or failure
    result = GetTwoOperands(operand1, operand2);

    // if success, evaluate the operator and push value on stack
    // otherwise, clear calculator stack. check for divide by 0.
    if (result == True)
        switch(op)
        {
            case '+':   S.Push(operand2+operand1);
                        break;
                        
            case '-':   S.Push(operand2-operand1);
                        break;
                        
            case '*':   S.Push(operand2*operand1);
                        break;
                        
            case '/':   if (operand1 == 0.0)
                        {
                            cerr << "Divide by 0!" << endl;
                            S.ClearStack();
                        }
                        else
                            S.Push(operand2/operand1);
                        break;
                        
            case '^':   S.Push(pow(operand2,operand1));
                        break;
        }
    else
        S.ClearStack();         // error! clear calculator
}

Calculator::Calculator(void)
{}
                
// read chars and evaluate a postfix expression. stop on '='.
void Calculator::Run(void)
{
    char c;
    double newoperand;
            
    while(cin >> c, c != '=')   // read until '=' (Quit)
    {
        switch(c)
        {
            case '+':           // check possible operators
            case '-':
            case '*':
            case '/':
            case '^':
                Compute(c);     // have operator; evaluate it
                break;

            default:            
                // not operator, must be operand; put char back
                cin.putback(c);
                // read the operand and store it on the stack
                cin >> newoperand;
                Enter(newoperand);
                break;
        }
    }
    // answer stored on top of stack. print using Peek
    if (!S.StackEmpty())
        cout << S.Peek() << endl;
}

// clear operand stack
void Calculator::Clear(void)
{
    S.ClearStack();
}
