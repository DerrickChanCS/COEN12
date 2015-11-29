#include <stdlib.h>
#include "tree.h"

typedef struct tree
{
	struct tree* right;
	struct tree* left;
	struct tree* parent;
	int data;

}TREE;


struct tree *createTree(int data, struct tree *left, struct tree *right)//return a pointer to a new tree with the specified left and right subtrees and data for its root
{
	TREE* newTree = malloc(sizeof(TREE));
	newTree->data = data;
	setLeft(newTree, left);
	setRight(newTree, right);
	return newTree;
}
void destroyTree(struct tree *root)//deallocate memory for the entire subtree pointed to by root
{
	if(root == NULL)
		return;
	else
	{
		destroyTree(root->left);
		destroyTree(root->right);
		free(root);
	}

}

/*
* Big O: O(1)
*return the data in the root of the subtree pointed to by root
*/
int getData(struct tree *root)
{
	return root->data;
}

/*
* Big O: O(1)
* return the left subtree of the subtree pointed to by root
*/
struct tree *getLeft(struct tree *root)
{
	return root->left;
}

/*
* Big O: O(1)
* return the right subtree of the subtree pointed to by root
*/
struct tree *getRight(struct tree *root)
{
	return root->right;
}

/*
* Big O: O(1)
* return the parent tree of the subtree pointed to by root
*/
struct tree *getParent(struct tree *root)
{
	
	return root->parent;
}

/*
* Big O: O(1)
* update the left subtree of root
*/
void setLeft(struct tree *root, struct tree *left)
{
	root->left = left;
	if(left != NULL)
		root->left->parent = root;
}

/*
* Big O: O(1)
* update the right subtree of root
*/
void setRight(struct tree *root, struct tree *right)
{
	root->right = right;
	if(right != NULL)
		root->right->parent = root;
}
