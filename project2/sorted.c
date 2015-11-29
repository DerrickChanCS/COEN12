/*
* Author: Derrick Chan
* Date: 1/26/15
* Last Modified: 2/1/15
* Version 1.0.0
* Sorted.c
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "set.h"

struct set
{
	int count;
	int maxElements;
	char **elts;

};

SET* createSet(int maxElts)//Function to create an sorted set
{
	SET *sp = malloc(sizeof(SET));//Allocates memory for struct
	assert(sp!=NULL);

	sp->count = 0;//Initializes members
	sp->maxElements = maxElts;
	
	sp->elts = malloc(maxElts * sizeof(char*));
	assert(sp->elts != NULL);
	return sp;
}

/*
* Big O: O(n)
* Frees all the memory associated with the set
*/
void destroySet(SET *sp)
{
	assert(sp!=NULL);
	for(int i = 0; i < sp->count; i++)//Frees the memory in the array
		free(sp->elts[i]);
	free(sp->elts);//Frees the array
	free(sp);//Frees the pointer
}

/*
* Big O: O(1)
*/
int numElements(SET *sp)
{
	return sp->count;//returns number of elements in sp
}

/*
* Big O: O(logn)
* Returns the index of the element. If element is not in array, returns location where it should be.
*/
int findElement(SET *sp, char *elt, bool* found)
{
	*found = false;
	int low = 0;
	int high = sp->count-1;
	int mid = 0;

	if(sp->count == 0)//If there are no elements in the array
		return 0;

	//If there are elements
	while(low <= high)
	{
		mid = (low + high)/2;
		int comp = strcmp(sp->elts[mid], elt);//Saves the value of the comparison between sp->elts[mid] and elt
		if(comp == 0) //If they are the same
		{
			*found = true;//sets the value to true if found
			return mid;
		}
		else if(comp < 0)//If the elt is to the right of mid
			low = mid + 1;
		else//If the elt is to the left of mid
			high = mid - 1;
	}
	found = false;//sets the value to false if not found
	return low;//The index of the elt. If the elt is not in the array, low is the index elt would be
}

/*
* Big O: O(logn)
* Returns true if set has the element. False if not in the set.
*/
bool hasElement(SET *sp, char *elt)
{
	bool found;
	findElement(sp, elt, &found);//Returns a bool corresponding to if the element is in the set or not
	return found;
}

/*
* Big O: O(n)
* Returns true if function successfully added in the element. False if not in the set.
*/
bool addElement(SET *sp, char *elt)
{
	bool found;
	int index = findElement(sp, elt, &found);
	if(found == true)//Element is in the set. Did not add elt
		return false;
	else
	{
		for(int i = sp->count; i > index; i--)//Shifts all the elements [index, count) right one slot
		{
			sp->elts[i] = sp->elts[i-1];
		}	
	}
	sp->elts[index] = strdup(elt);//Inserts elt into sp->elts[index]
	sp->count++;//increments the number of elments in sp

	return true;	
}

/*
* Big O: O(n)
* Returns true if function successfully removes the element. False if not successful.
*/
bool removeElement(SET *sp, char *elt)
{
	bool found;
	int index = findElement(sp, elt, &found);//Returns the index the element is at
	if(index >= 0)//If the element is in the set
	{
		free(sp->elts[index]);//free the memeory
		for(int i = index; i < sp-> count - 1; i++)//Shifts all elements [index + 1, count) left one slot
		{
			sp->elts[i] = sp->elts[i+1];
		}
		sp->count--;
	}
	return found;
}
