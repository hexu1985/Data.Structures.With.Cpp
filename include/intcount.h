struct IntegerCount
{
	// number is the key, count number times key has occurred
	int number;
	long count;
};

// compare two IntegerCount records by key field

int operator< (IntegerCount x, IntegerCount y)
{
	return x.number < y.number;
}

int operator== (IntegerCount x, IntegerCount y)
{
	return x.number == y.number;
}
