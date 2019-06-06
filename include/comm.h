// determine the number of committees with k members that
// can be chosen from n persons
int comm (int n, int k)
{
    // stopping condition; too few persons 
    if (k > n)    
        return 0;
    // stopping condition; committee of the whole or 0 members
    else if (n == k || k == 0)
        return 1;
    else
        // recursive step: all committes without person A
        // + all committees that include person A
        return comm(n-1,k) + comm(n-1,k-1);
}
