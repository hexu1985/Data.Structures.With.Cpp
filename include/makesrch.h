#ifndef SEARCHTREE
#define	SEARCHTREE

#include "bstree.h"
#include "random.h"

void MakeSearchTree(BinSTree<int> &T, int type)
{
	int i, randint;
	int arr0[6] = {30, 20, 45, 5, 10, 40},  
		arr1[8] = {50, 20, 45, 70, 10, 60, 90, 30};
	RandomNumber rnd;
	
	switch(type)
	{
		case 0:
			for (i = 0; i < 6; i++)
				T.Insert(arr0[i]);
			break;
			
		case 1:
			for (i = 0; i < 8; i++)
				T.Insert(arr1[i]);
			break;
			
		case 2:
			for (i = 0; i < 15; i++)
			{
				randint = rnd.Random(90) + 10;
				T.Insert(randint);
			}
			break;
	}
}

#endif	// SEARCHTREE