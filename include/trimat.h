#ifndef TRIMAT_CLASS
#define TRIMAT_CLASS

#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>

// maximum number of upper triangular entries and rows
const int ELEMENTLIMIT = 325;
const int ROWLIMIT = 25;

class TriMat
{
    private:
        // private data members for data storage
        int rowTable[ROWLIMIT];	// starting index of rows in M
        int n;					// row/column size
        double M[ELEMENTLIMIT];	// stores upper elements

    public:
        // constructor. no default parameters
        TriMat(int matsize);
        
        // matrix element access methods                   
        void PutElement (double item, int i, int j);
        double GetElement(int i,int j) const;
        
        // matrix arithmetic operations 
        TriMat AddMat(const TriMat& A) const;
        double DetMat(void) const;
        
        // matrix I/O operations
        void ReadMat(void);
        void WriteMat(void) const;
        
        // get matrix dimension
        int GetDimension(void) const;
};
  
  
// initialize n and rowTable
TriMat::TriMat(int matsize)
{
    int storedElements = 0;	// accumulates the stored entries
            
    // terminate program if matsize exceeds ROWLIMIT
    if (matsize > ROWLIMIT)
    {
        cerr << "The matrix cannot exceed size " << ROWLIMIT <<
                "x " << ROWLIMIT << endl;
        exit(1);
    }

    n = matsize;
    
    // set up the table
    for(int i = 0; i < n; i++)
    {
        rowTable[i] = storedElements;
        storedElements += n - i;
    }
}

// return the matrix dimension n
int TriMat::GetDimension(void) const
{
    return n;
}

// stores matrix item [i,j] in the array M
void TriMat::PutElement (double item, int i, int j)
{
    // terminate program if element indices are out of range
    if ((i < 0 || i >= n) || (j < 0 || j >= n))
    {
        cerr << "PutElement: index out of range 0 to "
             << (n-1) << endl;
        exit (1);
    }
    // all elements below the diagonal are ignored
    if (j >= i)
            M[rowTable[i] + j-i] = item;
}

// retrieves matrix item [i,j] from the array M
double TriMat::GetElement(int i,int j) const
{
    // terminate program if element indices are out of range
    if ((i < 0 || i >= n) || (j < 0 || j >= n))
    {
        cerr << "PutElement: index out of range 0 to "
             << (n-1) << endl;
        exit (1);
    }
    if (j >= i)
        // retrieve entry if above diagonal
        return M[rowTable[i] + j-i];
    else
    	// entry is 0 if below diagonal
        return 0;
}

// reads matrix elements by rows. client must enter
// all n x n elements 
void TriMat::ReadMat(void)
{
    double item;
    int i, j;

    for (i = 0; i < n; i++)			// scan rows
        for (j = 0; j < n; j++)		// for each row scan columns
        {
            cin >> item;			// Read matrix element[i,j]
            PutElement(item,i,j);	// stores the element
        }
}

// writes matrix elements row by row
void  TriMat::WriteMat(void) const
{
    int i,j;

    // fixed-point output, 3 decimal places, include trailing 0's
    cout.setf(ios::fixed);
    cout.precision(3);
    cout.setf(ios::showpoint);

    for (i = 0; i < n; i++)
    {
        for  (j = 0; j < n; j++)
            cout << setw(7) << GetElement(i,j);
        cout << endl;
    }
}

// returns sum of A and current object. current obj not changed.
TriMat TriMat::AddMat(const TriMat& A) const
{
    int i, j;
    double itemCurrent, itemA;
    TriMat B(A.n);  // B will be the sum.

    for (i = 0; i < n; i++)		// cycle through the rows
    {
        for (j = i; j < n; j++)	// skip entries below diagonal
        {
            itemCurrent = GetElement(i,j);
            itemA = A.GetElement(i,j);
            B.PutElement(itemCurrent + itemA, i, j);
        }
    }
    return B;
}

// determinant of current object
double TriMat::DetMat(void) const
{
    double val = 1.0;

    // determinant is product of items on diagonal 
    for (int i = 0; i < n; i++)
        val *= GetElement(i,i);
    return val;
}

#endif  // TRIMAT_CLASS
