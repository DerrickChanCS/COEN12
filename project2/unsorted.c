/* Author: Derrick Chan
* Date: 1/26/2015
* Last Modified: 2/1/15
* Version 1.0.0
* Unsorted.c
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "set.h"

struct set //creates a struct named set
{
	int count;//Number of elements in set
	int maxElements;//Maximum number of elements a set can hold
	char **elts;//Data set holds

};

SET* createSet(int maxElts)//Function to create an unsorted set
{
	SET *sp = malloc(sizeof(SET)); //Allocate memory for set
	assert(sp!=NULL);

	sp->count = 0; 
	sp->maxElements = maxElts;
	
	sp->elts = malloc(maxElts * sizeof(char*)); //Allocate memory for strings
	assert(sp->elts != NULL);
	return sp;
}

/* Big O: O(n)
* Frees all memory associated with set
*/
void destroySet(SET *sp)
{
	assert(sp!=NULL);
	for(int i = 0; i < sp->count; i++)
		free(sp->elts[i]);//Frees the memory in the array
	free(sp->elts);//Free the array
	free(sp);//Free the pointer
}

/*Big O: O(1);
* Returns number of elements of sp
*/
int numElements(SET *sp)
{
	return sp->count;
}

/*Big O: O(n)
* Returns the index of the element. Returns -1 if element is not found
*/
int findElement(SET *sp, char *elt)
{
	for(int i = 0 ; i < sp->count; i++)//Loops through entire set
	{
		if(strcmp(elt, sp->elts[i]) == 0)//compares if the strings are the same.
			return i;
	}
	return -1;
}

/*Big O: O(n)
* Returns true if set has an element. False if not found.
*/
bool hasElement(SET *sp, char *elt)
{
	if(findElement(sp, elt) == -1)
		return false;
	
	return true;
}

/*Big O: O(n)
* Returns true if function successfully adds an element. False if not added.
*/
bool addElement(SET *sp, char *elt)
{
	if(sp->count < sp->maxElements)
	{
		if(!hasElement(sp, elt))//if hasElement is false
		{
			sp->elts[sp->count] = strdup(elt);//adds the element at last index
			sp->count++;//increment the count
			return true;
		}
	}

	return false;
}

/*Big O: O(n)
* Returns true if function succesfully removes an element. False if not removed.
*/
bool removeElement(SET *sp, char *elt)
{
	int index = findElement(sp, elt);//Find an element
	if(index >= 0)//If element is in the array
	{
		free(sp->elts[index]);
		sp->elts[index] = sp->elts[--sp->count];//Set the element at index to the last element in array and decrement
		return true;
	}
	return false;
}
