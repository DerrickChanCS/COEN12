struct node{
	int data;
	struct node* left;
	struct node* right;
}
typedef struct node NODE;


void foo(struct node* pCur)
{
	if(pCurr!=NULL)
	{
		foo(pCurr->next);
		print(pCur->data);
	}
	/*
	prints backwards for a linked list
	prints last item first
	*/
}

void postOrder(NODE* np)
{
	if(np == NULL)
		return;
	postOrder(np->left);
	postOrder(np->right);
	printf("%d\n", np->data); 
}
void inOrder(NODE* np)
{
	if(np == NULL)
		return;
	inOrder(np->left);
	printf("%d\n", np->data);
	inOrder(np->right);
}
void preOrder(NODE* np)
{
	if(np == NULL)
		return;
	printf("%d\n", np->data);
	preOrder(np->left);
	preOrder(np->right);
}
int height(NODE* np)
{
	if(np == NULL)
		return 0;
	int leftHeight = height(np->left);
	int rightHeight = height(np->right);
	
	return(1 + (leftHeight > rightHeight ? leftHeight:rightHeight))
	//ternary lol
	/*
	if(leftHeight>rightHeight)
		return 1+leftHeight;
	else
		return 1+rightHeight;
	*/
}

void foo(struct node* pCur)
{
	if(pCurr != NULL)
	{
		foo(pCurr->left);
		print(pCur->data);
		foo(pCurr->right);
	}
	/*
	for trees
	PLR -> ABDECF
	LPR -> DBEAFC
	LRP -> DEBFCA
	a->b, c
	b->d, e
	c->f, null
	inorder LPR
	postorder LRP

	*/

}

bool find(NODE* root, int x)
{	/* //recursive
	if(root == NULL) 
		return false;
	if( x == root-> data)
		return true;
	if(x < root-> data) 
		return find(root->left, x);
	return find(root->right, x);
	*/
	while(root != NULL)
	{
		if(x < root->data)
			root = root->left;
		else if(x > root->data)
			root = root->right;
		else
			return true;
	}
	return false;
}

int minimum(NODE* np)
{
	/*
	assert(np!=NULL);
	if(np->left != null)
		return minimum(np->left);
	return np->data;
	*/
	assert(np!=NULL)
	while(np->left != NULL)
	{
		np = np->left;
	}
	return np->data;
}





/*
Binary Search Tree
left tree <= parent <= right tree


*/
