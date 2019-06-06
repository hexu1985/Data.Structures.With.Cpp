#ifndef EXCHANGE_SORT
#define EXCHANGE_SORT

template <class T>
void ExchangeSort(T a[], int size)
{
    int i, j;
    T temp;
    
    for (i = 0; i < size-1; i++)
        for (j = i+1; j < size; j++)
            if (a[j] < a[i])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
}

#endif  // EXCHANGE_SORT