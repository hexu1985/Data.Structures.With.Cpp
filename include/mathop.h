#ifndef INFIX_MATH_OPERATIONS
#define INFIX_MATH_OPERATIONS

// list of constants specifying specific error messages  
const int OperatorExpected = 0,
          OperandExpected = 1,
          MissingLeftParenthesis = 2,
          MissingRightParenthesis = 3,
          InvalidInput = 4;
          
// labels designating the parentheses characters 
const char leftparenthesis  = '(',
           rightparenthesis = ')';

// a class that handles operators on the operator stack
class MathOperator
{
    private:
        // operator and its two precedence values
        char op;
        int inputprecedence;
        int stackprecedence;
        
    public:
        // constructors; includes default constructor and a 
        // constructor that initializes the object
        MathOperator(void);
        MathOperator(char ch);
        
        // member functions handling operator on the stack
        int operator>= (MathOperator a) const;
        void Evaluate (Stack<float> &OperandStack);
        char GetOp(void);
};

// default constructor
MathOperator::MathOperator(void)
{}

// constructor that assigns operator and precedences values
MathOperator::MathOperator(char ch)
{
    op = ch;    // assign operator
    switch(op)
    {
        // '+' and '-' have input/stack precedence 1
        case '+':   
        case '-':   inputprecedence = 1;
                    stackprecedence = 1;
                    break;
                                
        // '*' and '/' have input/stack precedence 2
        case '*':   
        case '/':   inputprecedence = 2;
                    stackprecedence = 2;
                    break;
                            
        // '(' has input precendence 3, stack precedence -1
        case '(':   inputprecedence = 3;
                    stackprecedence = -1;
                    break;
                            
        // ')' has input/stack precedence 0
        case ')':   inputprecedence = 0;
                    stackprecedence = 0;
                    break;
    }
}
        
// overload the >= operator by comparing stackprecedence of
// the current object with inputprecedence of a. used when
// reading an operator to determine whether operators
// on the stack should be evaluated before pushing the new
// operator on the stack. 
int MathOperator::operator>= (MathOperator a) const
{
    return stackprecedence >= a.inputprecedence;
}
        
// evaluate operator for the current object. First pop two
// operands from the operand stack, then execute operator and
// push the result back onto the operand stack.   
void MathOperator::Evaluate (Stack<float> &OperandStack)
{
    float operand1 = OperandStack.Pop(); // get left operand
    float operand2 = OperandStack.Pop(); // get right operand
            
    // evaluate operator and push result back on the stack
    switch (op)                          // select operation
    {
        case '+' :  OperandStack.Push(operand2 + operand1);
                    break;
                            
        case '-':   OperandStack.Push(operand2 - operand1);
                    break;
                            
        case '*':   OperandStack.Push(operand2 * operand1);
                    break;
                
        case '/':   OperandStack.Push(operand2 / operand1);
                    break;
    }
}

// return operator associated with current object        
char MathOperator::GetOp(void)
{
    return op;
}

#endif // INFIX_MATH_OPERATIONS

