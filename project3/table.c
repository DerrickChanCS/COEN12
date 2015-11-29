/* Author: Derrick Chan
* Date: 2/2/2015
* Last Modified: 2/10/15
* Version 1.0.0
* Unsorted.c
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "set.h"

#define FLAG_EMPTY 0 //If the slot is empty
#define FLAG_FULL 1 //If there is data in the slot
#define FLAG_TOMB -1 //If there is data in the slot, but is deleted
struct set //creates a struct named set
{
	int count;//Number of elements in set
	int maxElements;//Maximum number of elements a set can hold
	char **elts;//Data set holds
	int *flags;//Determines if slot in the array is filled
};

SET* createSet(int maxElts)//Function to create a hashed set
{
	SET *sp = malloc(sizeof(SET)); //Allocate memory for set
	assert(sp!=NULL);

	sp->count = 0; 
	sp->maxElements = maxElts;
	
	sp->elts = malloc(maxElts * sizeof(char*)); //Allocate memory for strings
	assert(sp->elts != NULL);

	sp->flags = malloc(maxElts * sizeof(int));//Allocate memory for flags
	assert(sp->flags != NULL);
	
	for(int i =0; i < maxElts; i++)//Initializes each slot in flag to empty
	{
		sp->flags[i] = FLAG_EMPTY;
	}
	return sp;
}

/* Big O: O(n)
* Frees all memory associated with set
*/
void destroySet(SET *sp)
{
	assert(sp!=NULL);
	for(int i = 0; i < sp->maxElements; i++)
	{
		if(sp->flags[i] != FLAG_EMPTY)//If there is data at the index
			free(sp->elts[i]);//Frees the memory in the array
	}
	free(sp->elts);//Free the data array
	free(sp->flags);//Free the flag array
	free(sp);//Free the pointer
}

/*Big O: O(1);
* Returns number of elements of sp
*/
int numElements(SET *sp)
{
	return sp->count;
}

/* Big O: O(n)
* Returns the hash index for a string
*/
unsigned hashString(char* s)
{
	unsigned hash = 0;

	while(*s != '\0')
		hash = 31 * hash + *s++;
	//printf("Hash is %i", hash);
	return hash;
}

/*Big O: O(n)
* Returns the index of the element. Returns -1 if element is not found
*/
int findElement(SET *sp, char *elt, bool* found)
{
	assert(elt != NULL);
	if(elt == NULL)
		return false;
	*found = false;
	unsigned home = hashString(elt) % sp->maxElements;
	int  hash = home;
	int available = -1;
	int flag;
	do
	{
		flag = sp->flags[hash];//gets the value at hash
	
		if(flag == FLAG_EMPTY)
		{
			if(available != -1) //if there is a tombstone, return index of tomb
				return available;
			return hash;//Return the index to insert the data element to if the data slot is empty
		}
		if(flag == FLAG_TOMB)
		{
			if(available == -1)//If the flag is a tomb and available has not been changed
			{
				//Ensures that it gets the first tombstone after the home location if home location is occupied.
				available = hash;
			}
		}
		if(flag == FLAG_FULL)
		{	
			if(strcmp(sp->elts[hash], elt) == 0)//if the flag is full and the strings match
			{	
				*found = true;//set the found bool to true
				return hash;//return the index it was found at
			}
		}
		hash = (hash+1) % sp->maxElements;//Increments the hash by 1 each time. Linear probing
	}
	while(hash != home );//will loop through entire array until it returns back to home location or finds a matching index/empty index
	
	if(available == -1)//if the element was not found.
		available = hash;//returns the home location of the string
	return available;
	
}

/*Big O: O(n)
* Returns true if set has an element. False if not found.
*/
bool hasElement(SET *sp, char *elt)
{
	bool found;
	findElement(sp, elt, &found);
	return found;
}

/*Big O: O(n)
* Returns true if function successfully adds an element. False if not added.
*/
bool addElement(SET *sp, char *elt)
{
	bool found;
	int index = findElement(sp, elt, &found);//index it should be inserted at
	if(sp->count < sp->maxElements)
	{
		if(found == false)//if findElement is false
		{
			sp->elts[index] = strdup(elt); //inserts string at index
			sp->flags[index] = FLAG_FULL; //sets flag at index to full
			sp->count++; //increment the number of elements in the hash set
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
	bool found;
	int index = findElement(sp, elt, &found);//Find an element
	if(found)//If element is in the array
	{
	//	free(sp->elts[index]);
		sp->flags[index] = FLAG_TOMB;//sets the flag to a tomb at index
		sp->count--;//decrement the number of elements in the hash set
		return true;
	}
	return false;
}
