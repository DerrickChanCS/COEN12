#include <stdio.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"

#include <string.h>

#define PARENT(x) ((x-1)/2)
#define LEFT(x) ((x*2)+1)
#define RIGHT(x) ((x*2)+2)

#define LEFTFAVOR
#define PREI

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

#ifdef LEFTFAVOR
	else//Both children exist. FAVORS SHIFTING LEFT
	{
		if (getData(heap[leftChildIndex]) <= getData(heap[rightChildIndex])) //If the leftChild is less than or equal to rightChild
			minIndex = leftChildIndex;//the min value is leftChild
		else//if the rightChild is less than the leftChild
			minIndex = rightChildIndex;//the min value is rightChild
	}
#else
	//FAVORS SHIFTING RIGHT
	else //Both children exist. FAVORS SHIFTING RIGHT
	{
		if (getData(heap[rightChildIndex]) <= getData(heap[leftChildIndex])) //If the rightChild is less than or equal to leftChild
			minIndex = rightChildIndex;//the min value is rightChild
		else//if the leftChild is less than the rightChild
			minIndex = leftChildIndex;//the min value is leftChild
	}
#endif

	if (getData(heap[index]) > getData(heap[minIndex])) //if the data at index is greater than the the minValue of the children
	{
		//switches the parent with the min value
		tmp = heap[minIndex];//holds the minvalue
		heap[minIndex] = heap[index];//parent to minvalue
		heap[index] = tmp;//minvalue to parent
		siftDown(minIndex);//check to make sure the parent is the proper position
	}
}


void insert(struct tree* value)
{
	heap[heapSize] = value;
	siftUp(heapSize);
	heapSize++;
}

struct tree* removeMin()
{
	struct tree* min = heap[0];
	heap[0] = heap[heapSize - 1];
	heapSize--;
	if(heapSize  > 0)
		siftDown(0);
	return min;
}

void code(struct tree* start)
{
	struct tree* parent = getParent(start);
	if(start == NULL || parent == NULL)
		return;
	else
	{
		code(getParent(start));
		if(start == getLeft(parent))
			printf("0");
		else
			printf("1");
	}
}

//DIE
void printVal(int ascii) {
	if(isprint(ascii))
			printf("'%c'", ascii);
		else
			printf("%03o", ascii);
}

//DIE
void heapDump() {
	printf("\n----- %i -----\n", heapSize);
	for(int i = 0; i < heapSize; i++)
	{
		int count = getData(heap[i]);
		char* ascii = getAscii(heap[i]);
		//if(isprint(ascii))
			printf("'%s': %i\n", ascii, count);
		//else
		//	printf("%03o: %i\n", ascii, count);
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

	for(int i = 0; i < 257; i++)
	{
		counts[i] = 0;
	}

	int c = fgetc(in);
	while(c != EOF)
	{
		counts[c] += 1;
		c = fgetc(in);
	}
	//create heap
#ifdef PREI
	node[256] = createTree(0, NULL, NULL);
	setAscii(node[256], "400"); //DIE
	insert(node[256]);
#endif

	for(int i = 0; i < 257; i++)
	{
		
		if(counts[i] != 0)
		{
			char foo[2] = {'*', '\0'};
			if (isprint(i)) {
				if(i==' ') foo[0] = '_';
				else foo[0] = i;
			}
			node[i] = createTree(counts[i], NULL, NULL);
			setAscii(node[i], strdup(foo)); //DIE
			insert(node[i]);
		}
	}	

#if !defined PREI
	node[256] = createTree(0, NULL, NULL);
	setAscii(node[256], "400"); //DIE
	insert(node[256]);
#endif

	heapDump(); //DIE

	while(heapSize > 1)
	{
		/*
		printf("the heap before remove two lowest \n");
		for(int i = 0; i < heapSize; i++)
		{
		//	printf("index %d: \n", i);
			printf("Index is %d: ", i);
			printf("Parent is: %d, ", getData(heap[i]));
			if(LEFT(i) < heapSize)
				printf("left child is: %d, ", getData(heap[LEFT(i)]));
			if(RIGHT(i) < heapSize)
				printf("right child is: %d, ", getData(heap[RIGHT(i)]));
			if(LEFT(i) >= heapSize && RIGHT(i) >= heapSize)
				printf("no children");
			printf("\n");
		}
		printf("\n");
		*/
	
		struct tree* left = removeMin();
		struct tree* right = removeMin();
		printf("Remove %s\n", getAscii(left)); //DIE
		printf("Remove %s\n", getAscii(right)); //DIE
	//	printf("left is %d and right is %d new combined is %d\n", getData(left), getData(right), getData(left) + getData(right));
	//	insert(createTree((getData(left) + getData(right)), left, right));
		struct tree *tmp = createTree((getData(left) + getData(right)), right, left);
		char foo[100];
		strcpy(foo, getAscii(left));
		strcat(foo, getAscii(right));
		setAscii(tmp, strdup(foo));
		insert(tmp);
		
		heapDump(); //DIE
	}

	printf("\n==========\n");
	for(int i = 0; i < 257; i++)
	{
		if (node[i]!=NULL) {
			if(isprint(i))
				printf("'%c': %i ", i, getData(node[i]));
			else
				printf("%03o: %i ", i, getData(node[i]));
			code(node[i]);
			printf("\n");
		}
		//printf("heap value is %i \n", getData(heap[i]));
		//destroyTree(heap[i]);
	}

	pack(argv[1], argv[2], node);
	destroyTree(heap[0]);
	return 0;
}
