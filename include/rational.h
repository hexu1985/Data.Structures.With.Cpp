#ifndef RATIONAL_CLASS
#define RATIONAL_CLASS

#include <iostream.h>
#include <stdlib.h>

class Rational
{
   private:
      // defines a rational number as numerator/denominator
      long num, den;

	  // private constructor used by arithmetic operators.
	  // handles large numerators or denominators
	  Rational(long num, long denom);
	  
      // Rational utility functions
	  void Standardize(void);
	  long gcd(long m, long n) const;

   public:
	  // constructors handle conversion:
	  // int->Rational, double->Rational
	  Rational(int num=0, int denom=1);
	  Rational(double x);
   
      // rational input/output
      friend istream& operator>> (istream& istr,
                                  Rational &r);
      friend ostream& operator<< (ostream& ostr,
                                  const Rational& d);
  
      // binary operators: add, subtract, multiply, divide
      Rational operator+ (Rational r) const; 
      Rational operator- (Rational r) const; 
      Rational operator* (Rational r) const; 
      Rational operator/ (Rational r) const; 

      // unary minus (change sign)
      Rational operator- (void) const;

      // relational operators
      int operator< (Rational r) const;
      int operator<= (Rational r) const;
      int operator== (Rational r) const;
      int operator!= (Rational r) const;
      int operator> (Rational r) const;
      int operator>= (Rational r) const;
      
      // conversion operator: Rational to double
      operator double(void) const;
      
      // utility methods
	  long GetNumerator(void) const;
      long GetDenominator(void) const;
      void Reduce(void);
};

// Rational form is (+/-)numerator/denominator. denominator
// is always positive in standard form
void Rational::Standardize(void)
{  
   if (den < 0)
   {
      // make denominator >= 0 and and absorb sign
      // in the numerator
      den = -den;
      num = -num;
   }
}

// computes the GCD of m and n. Use to reduce fraction
long Rational::gcd(long m, long n) const
{
   long remainder = m % n;
   while (remainder > 0) 
   {
      m = n;
      n = remainder;
      remainder = m % n;
   }
   return n;
}

// constructor. form the rational number num/den. if used with
// default value of den=1, converts/ an integer to a Rational
Rational::Rational(int p, int q): num(p), den(q)
{
   if (den == 0)
   {
      cerr << "A Zero denominator is invalid" << endl;
      exit(1);
   }
}

Rational::Rational(long p, long q): num(p), den(q)
{
   if (den == 0)
   {
      cerr << "A Zero denominator is invalid" << endl;
      exit(1);
   }
}

// constructor. approximate the double value x
// as a Rational number
Rational::Rational(double x)
{
   double val1, val2;
   
   // move decimal pt of x 8 pos to the right
   val1 = 100000000L*x;
   // move decimal pt of x 7 pos to the right
   val2 = 10000000L*x;
   // val1-val2 = 90,000,000 * x; by truncating
   // to a long, throw away the fractional part.
   // approx x by numerator/90,000,000
   num = long(val1-val2);
   den = 90000000L;
   // reduce to lowest terms
   Reduce();
}

// overload stream input operator. input in form P/Q
istream& operator >> (istream& istr, Rational& r)
{
   char c;  // reads the separator '/'

   // as a friend, ">>" can access numerator/denominator of r
   istr >> r.num >> c >> r.den;
   // terminate if denominator is 0
   if (r.den == 0)
   {
      cerr << "A Zero denominator is invalid\n";
      exit(1); 
   }
   
   // put r in standard form
   r.Standardize();
   return istr;
}

// overload stream output operator. output in form P/Q 
ostream& operator << (ostream& ostr, const Rational& r)
{
   // as a friend, ">>" can access numerator/denominator of r
   ostr << r.num << '/' << r.den;
   return ostr;
}

// Rational addition
Rational Rational::operator+ (Rational r) const
{
   return Rational(num*r.den + den*r.num, den*r.den);
}

// Rational subtraction
Rational Rational::operator- (Rational r) const
{
   return Rational(num*r.den - r.num*den, den*r.den);
}

// Rational multiplication
Rational Rational::operator* (Rational r) const
{
   return Rational(num*r.num, den*r.den);
}

// Rational division
Rational Rational::operator/ (Rational r) const
{
   Rational temp = Rational(num*r.den, den*r.num);
   
   // make sure denominator is positive
   temp.Standardize();
   return temp;
}
      
// Rational negation
Rational Rational::operator- (void) const
{
   return Rational(-num, den);
}

// relational "less than"
int Rational::operator< (Rational r) const
{
   return num*r.den < r.num*den;
}

// relational "less than or equal to"
int Rational::operator<= (Rational r) const
{
   return num*r.den <= r.num*den;
}

// relational "equal"
int Rational::operator== (Rational r) const
{
   return num*r.den == den*r.num;
}

// relational "not equal"
int Rational::operator!= (Rational r) const
{
   return num*r.den != r.num*den;
}

// relational "greater than"
int Rational::operator> (Rational r) const
{
   return num*r.den > r.num*den;
}

// relational "greater than or equal to"
int Rational::operator>= (Rational r) const
{
   return num*r.den >= r.num*den;
}

// convert Rational to a double
Rational::operator double(void) const
{
   return double(num)/den;
} 

// return the numerator of the Rational object
long Rational::GetNumerator(void) const
{
   return num;
} 

// return demoninator of the Rational object
long Rational::GetDenominator(void) const
{
   return den;
}

// put the Rational object in lowest terms
void Rational::Reduce(void)
{
   long bigdivisor, tempnumerator;
   
   // tempnumerator is the absolute value of the numerator
   tempnumerator = (num < 0) ? -num : num;

   if (num == 0)
      den = 1;    // standardize to 0/1
   else
   {
      // find GCD of the postive numbers
      // tempnumerator, denominator
      bigdivisor = gcd(tempnumerator, den);
      
      // if bigdivisor == 1, Rational already in lowest 
      // terms; otherwise, divide numerator and denominator
      // by their largest common divisor
      if (bigdivisor > 1) // don't divide if gcd is 1
      {
         num /= bigdivisor;
         den /= bigdivisor;
      }
   }
}

#endif   // RATIONAL_CLASS
