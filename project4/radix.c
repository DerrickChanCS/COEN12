/*
* Author: Derrick Chan
* Project 4: radix
* 2/19/15
* radix.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "deque.h"

/*
* Big O: O(n)
* Takes the data from the radix and puts the data back into the deque
*/
void combineRadix(DEQUE* rad[], DEQUE* dp)
{
	for(int i = 0; i< 10; i++)
	{
		while(numItems(rad[i]) != 0)//if there are items in the i bucket
		{
			int x = removeFirst(rad[i]);//remove the item from radix and add it back into the main deque
			addLast(dp, x);
		}
	
	}
}

/*
*Big O: O(n)
*Returns a sorted deque pointer
*/
DEQUE* radix(DEQUE* dp)
{
	DEQUE* rad[10];
	for(int i = 0; i< 10; i++)//Initialize 10 deques
	{
		rad[i] = createDeque();
	}
	int high = 0;
	while(numItems(dp) != 0)//this loop puts data into radix buckets and figures out highest number
	{
		int cur = removeFirst(dp);//takes the first item from the deque
		if(cur > high)
			high = cur;//figures out the highest number
		addLast(rad[cur%10], cur);//adds the data value to the correct bucket
	}
	combineRadix(rad, dp);
	int pow = 1;
	while(high/(pow* 10) > 0)//tests for the most significant digit
	{
		pow = pow*10;
		while(numItems(dp) != 0)//while there are items in the deque
		{
			int cur = removeFirst(dp);
			addLast(rad[(cur/pow)%10], cur);//put the data into the correct bucket
		}
		combineRadix(rad, dp);//put the data back into the main deque
	}
	for(int i = 0; i < 10; i++)
	{
		destroyDeque(rad[i]);
	}
	return dp;
}

int main()
{
	DEQUE* dp = createDeque();
	printf("\nInsert a negative number to initiate radix sort\n");
	while(1)
	{
		int n;
		printf("Please insert a number: ");
		scanf("%i", &n);
		if(n > 0)
			addLast(dp, n);
		else
			break;
	}
	dp = radix(dp);
	printf("Sorted using radix sort: ");
	while(numItems(dp) != 0)
	{
		printf("%d", removeFirst(dp));
		if(numItems(dp) != 0)
			printf(", ");
	}
	printf("\n\n");
	destroyDeque(dp);
	return 0;
}
