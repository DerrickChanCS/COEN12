#include <stdio.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"

#include <string.h>

#define PARENT(x) ((x-1)/2)
#define LEFT(x) ((x*2)+1)
#define RIGHT(x) ((x*2)+2)


struct tree  *heap[257]; //used to store a heap. The tree leaves hold count values
struct tree *node[257]; //used to store the count value for each ASCII value. Index corresponds to ASCII value
//For example index 97 corresponds to the count of the letter a 
int heapSize = 0;

/*
* Big O: O(logn)
* Helper function. Helps the insert function insert an element into the heap and maintain the heap structure
* Moves the element up through the heap to the proper location
*/
void siftUp(int index)
{
	if(index != 0)//if the element is not at the top of the heap
	{
		int parentIndex = PARENT(index);//Figure out what is the parent of the element you are trying to fix
		if (getData(heap[parentIndex]) > getData(heap[index]))//if the parent is greater than the node you are trying to fix
		{
			struct tree  *tmp = heap[parentIndex]; //Save the value of the parent 
			heap[parentIndex] = heap[index];//Move the node you are trying to fix as its parent
			heap[index] = tmp;//Move the parent to the index of the node you are trying to fix
			siftUp(parentIndex);//Sift up the node to ensure heap structure is preserved
		}
	}
}

/*
* Big O: O(logn)
* Helper function. Helps the remove function maintain the heap structure
* Moves the element downt hrough the heap to the proper location
*/
void siftDown(int index)
{
	int leftChildIndex = LEFT(index); //gets the index of the left child of the element you are trying to fix
	int rightChildIndex = RIGHT(index); // get the index of the right child  of the element you are tyring to fix
	int minIndex; //holds the index of the child with the lower index
	struct tree* tmp; //holds the value of an element for switching
	
	if (rightChildIndex >= heapSize) //if the right child does not exist
	{
		if (leftChildIndex >= heapSize) //if the left child does not exist
			return; //returns nothing. Base case. Node has no children
		else
			minIndex = leftChildIndex; //the min value is leftChild because right child does not exist
	}
	
	//Favors shifting left because if the leftChild is less than or equal to rightChild, it will return leftChild index
	//Will favor swapping left
	else//Both children exist. FAVORS SHIFTING LEFT
	{
		if (getData(heap[leftChildIndex]) <= getData(heap[rightChildIndex])) //If the leftChild is less than or equal to rightChild
			minIndex = leftChildIndex;//the min value is leftChild
		else//if the rightChild is less than the leftChild
			minIndex = rightChildIndex;//the min value is rightChild
	}
	/*
	//FAVORS SHIFTING RIGHT
	//Favors shifting right because if the rightChild is less than or equal to leftChild, it will return rightChild index.
	//The node will then swap with the rightChild index
	else //Both children exist. FAVORS SHIFTING RIGHT
	{
		if (getData(heap[rightChildIndex]) <= getData(heap[leftChildIndex])) //If the rightChild is less than or equal to leftChild
			minIndex = rightChildIndex;//the min value is rightChild
		else//if the leftChild is less than the rightChild
			minIndex = leftChildIndex;//the min value is leftChild
	}
	*/
	if (getData(heap[index]) > getData(heap[minIndex])) //if the data at index is greater than the the minValue of the children
	{
		//switches the parent with the min value
		tmp = heap[minIndex];//holds the minvalue
		heap[minIndex] = heap[index];//parent to minvalue
		heap[index] = tmp;//minvalue to parent
		siftDown(minIndex);//check to make sure the parent is the proper position
	}
}

/*
* Big O: Best Case O(1)
* Average/Worst Case O(logn)
* Function to insert elements in a priority queue minimum binary heap
* Function will be order 1 if it does not need to shift elements upward
*/
void insert(struct tree* value)
{
	heap[heapSize] = value; //Inserts element at last index of binary heap to preserve heap structure
	siftUp(heapSize); //Ensures the data value is in proper place in binary heap
	heapSize++;
}

/*
* Big O: O(logn)
* Function to remove the top of the binary heap
*/
struct tree* removeMin()
{
	struct tree* min = heap[0]; //saves the minimum value
	heap[0] = heap[heapSize - 1]; //puts the last value in the heap at the top of the binary heap
	heapSize--;
	if(heapSize  > 0)//If there is more than one element in the binary heap
		siftDown(0);//sift the top down to find proper place in binary heap
	return min;
}

/*
* Big O: O(logn)
* Traverses up the binary heap then traverses back down to print out the character codes
*/
void code(struct tree* start)
{
	struct tree* parent = getParent(start); //parent of the node you start at
	if(start == NULL || parent == NULL)//base case
		return;//recurse up until you get to the top of the huffman tree
	else
	{
		code(parent);//go up a level on the tree
		if(start == getLeft(parent))//If the start node is the leftChild of parent
			printf("0");
		else
			printf("1");
	}
}


int main(int argc, char *argv[])
{
	int counts[257];	
	if(argc != 3)
	{
		printf("improper input\n");
		return 1;
	}
	FILE *in = fopen(argv[1], "r");
	if(in == NULL)
	{	
		printf("bad file name\n");
		return 2;
	}

	//set the values of aray to 0
	for(int i = 0; i < 257; i++)
	{
		counts[i] = 0;
	}

	//reads in characters
	int c = fgetc(in);
	while(c != EOF)
	{
		counts[c] += 1;
		c = fgetc(in);
	}

	//create heap
	//insert end of file marker
	node[256] = createTree(0, NULL, NULL);
	insert(node[256]);

	for(int i = 0; i < 257; i++)
	{
		//if the ASCII character appeared
		if(counts[i] != 0)
		{
			//create a new tree node
			node[i] = createTree(counts[i], NULL, NULL);
			insert(node[i]);
		}
	}	
	
	//constructing huffman tree
	while(heapSize > 1)
	{	
		//remove two lowest values, put them into a node, put the new node into the binary heap
		struct tree* left = removeMin();
		struct tree* right = removeMin();
		struct tree *tmp = createTree((getData(left) + getData(right)), right, left);
		insert(tmp);
	}

	for(int i = 0; i < 257; i++)
	{
		//print out the count and the codes of the ASCII characters
		if (node[i]!=NULL) {
			if(isprint(i))
				printf("'%c': %i ", i, getData(node[i]));
			else
				printf("%03o: %i ", i, getData(node[i]));
			code(node[i]);
			printf("\n");
		}
	}

	pack(argv[1], argv[2], node);//zip the file
	destroyTree(heap[0]);
	return 0;
}
