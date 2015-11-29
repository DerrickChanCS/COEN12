/*
* Author: Derrick Chan
* Project 4: deque
* 2/19/15
* deque.c
*/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "deque.h"

typedef struct node
{
	int data;
	struct node* next;//next node in linked list
	struct node* prev;//prev node in linked list
}NODE;

struct deque
{
	int count;//number of items in deque
	NODE* head;//head of deque
};

/*
*Big O; O(1)
*Return a pointer to a new node
*/
NODE* createNode(int x)
{
	NODE* no = malloc(sizeof(NODE));
	assert(no != NULL);

	no->data = x;
	no->next = NULL;
	no->prev = NULL;
	return no;
}

/*
*Big O: O(1)
*Return a pointer to a new deque
*/
DEQUE* createDeque()
{
	DEQUE* dq = malloc(sizeof(DEQUE));
	assert(dq != NULL);

	dq->count = 0;
	dq->head = createNode(0);
	dq->head->next = dq->head;//set head next to itself
	dq->head->prev = dq->head;//set head prev to itself

	return dq;
}
/*
*Big O: O(1)
*Deallocate memory associated with the node pointed to by no
*/
void destroyNode(NODE *no)
{
	assert(no != NULL);
	free(no);
}

/*
*Big O: O(n)
*Deallocate memory associated with the deque pointed to by dp
*/
void destroyDeque(DEQUE *dp)
{
	assert(dp != NULL);
	NODE* n = dp->head->next;//first node is the head
	while(n != dp->head)//if there are items in the deque
	{
		n = n->next;//set the node to the next one
		destroyNode(n->prev);//destroy the previous node
	}//exits loop when n is the head
	
	destroyNode(n);//destroy the head
	free(dp);
}

/*
*Big O: O(1)
*Return the number of items in the deque pointed to by dp
*/
int numItems(DEQUE *dp)
{
	return dp->count;
}

/*
*Big O: O(1)
*Inserts a new node in between two existing nodes
*/
void insertNode(NODE* first, NODE* second, int x)
{
	NODE* new = createNode(x);
	first->next = new;//the node after first is the new node
	new->next = second;//the node after new is the second node
	new->prev = first;//the node before new is the first node
	second->prev = new;//the node before the second is the new node
}
/*
*Big O: O(1)
*Removes and destroyes a node from a deque and returns the data in the node
*/
int removeNode(NODE* remove)
{
	int data = remove->data;//retrieves the data in the remove node
	remove->prev->next = remove->next;//the next pointer for the node before remove is set to the node after remove
	remove->next->prev = remove->prev;//the prev pointer for the node after remove is set to the node before remove
	destroyNode(remove);
	return data;
}

/*
*Big O: O(1)
*Add x as the first item in the deque pointed to by dp
*/
void addFirst(DEQUE *dp, int x)
{
	insertNode(dp->head, dp->head->next, x);//inserts a new node inbetween head and head->next
	dp->count++;
}
/*
*Big O: O(1)
*Add x as the last item in the deque pointed to by dp
*/
void addLast(DEQUE *dp, int x)
{
	insertNode(dp->head->prev, dp->head, x);//inserts a new node inbetween head->prev and head
	dp->count++;
}

/*
*Big O: O(1)
*Remove and return the first item in the deque pointed to by dp; the deque must not be empty
*/
int removeFirst(DEQUE *dp)
{
	assert(dp->count > 0);
	dp->count--;
	return removeNode(dp->head->next);
}

/*
*Big O: O(1)
*Remove and return the last item in the deque pointed to by dp; the deque must not be empty
*/
int removeLast(DEQUE *dp)
{
	assert(dp->count > 0);
	dp->count--;	
	return removeNode(dp->head->prev);
}

/*
*Big O: O(1)
*Return the first item in the deque pointed to by dp; the deque must not be empty
*/
int getFirst(DEQUE *dp)
{
	assert(numItems(dp) > 0);
	return dp->head->next->data;
}

/*
*Big O: O(1)
*Return the last item in the deque pointed to by dp; the deque must not be empty
*/
int getLast(DEQUE *dp)
{
	assert(numItems(dp)>0);
	return dp->head->prev->data;
}
