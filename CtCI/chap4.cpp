#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MIN(A, B)		((A) < (B) ? (A) : (B))
#define MAX(A, B)		((A) > (B) ? (A) : (B))
#define ABS(A)			((A) > 0 ? (A) : (A) * (-1))


typedef struct _treeNode {
	int key;
	struct _treeNode* left;
	struct _treeNode* right;
	struct _treeNode* parent;		// for 4.6
} Node;

#define QUE_MAX	10
Node* queue[QUE_MAX];
int head;
int tail;
//int count = 0;

// passing by value of a pointer never gets newly allocated address. Pass it by reference, ie, **p, or "RETURN IT".
// call by reference
// malloc(sizeof(Node*)); (X)   malloc(sizeof(Node)); (O)
void insertNode(Node** root, int data)
{
	//Node* temp = *root;

	if (*root == NULL) {
		(*root) = (Node*)malloc(sizeof(Node));
		(*root)->key = data;
		(*root)->right = NULL;
		(*root)->left = NULL;
		(*root)->parent = NULL;
	}
	else {
		if (data < (*root)->key) {
			insertNode(&(*root)->left, data);
			if ((*root)->left) {
				(*root)->left->parent = *root;
			}
		}
		else {
			insertNode(&(*root)->right, data);
			if ((*root)->right) {
				(*root)->right->parent = *root;
			}
		}
	}
}

// base case for recursive calls !!!!!! 
void InOrder(Node* node)
{
	if (node) {
		InOrder(node->left);
		printf("%d[%d]->", node->key, node->parent == NULL ? 0 : node->parent->key);
		InOrder(node->right);
	}
}


void levelOrder(Node* node)
{
	head = 0;
	tail = 0;

	while (node) {
		printf("%d->", node->key);
		if (node->left) {
			queue[head++] = node->left;
		}

		if (node->right) {
			queue[head++] = node->right;
		}

		node = queue[tail++];
	}
	printf("\n");
}

//min depth
/*

			1				3
         /     \		 
       2		3			2
     /   \     /  \ 
	4	  5   6	   7		1	

							0
  */
int minDepth(Node* node)
{
	if (node == NULL) {
		return 0;
	}

	if ((node->left == NULL) && (node->right == NULL)) {
		return 1;
	}

	return MIN(minDepth(node->left), minDepth(node->right)) + 1;
}


//4.1 graph

//4.2
// input array needs to be sorted !!!!!
Node* createMinimalBST(int* arr, int start, int end)
{
	if (start > end) {
		return NULL;
	}

	int mid = (start + end) / 2;

	Node *node = (Node *)malloc(sizeof(Node));
	node->key = arr[mid];
	//node->left = NULL;
	//node->right = NULL;
	node->parent = NULL;

	node->left = createMinimalBST(arr, start, mid - 1);
	if (node->left) {
		node->left->parent = node;
	}
	node->right = createMinimalBST(arr, mid + 1, end);
	if (node->right) {
		node->right->parent = node;
	}

	return node;
}


//4.3

// Node	   : tree node  
// sllNode : list node  (=NODE)
typedef struct _sllNode {
	Node* treeNode;
	struct _sllNode* next;
} sllNode;

void addList(sllNode** pHead, Node* tNode)
{
}

void printList(sllNode* pNode)
{
	while (pNode) {
		printf("%d->", pNode->treeNode->key);
		pNode = pNode->next;
	}
	printf("NULL\n");
}

sllNode* listOfDepth[10];

void preOrderPerDepth(Node* node, int depth)
{
	if (node == NULL) {
		return;
	}

	sllNode* lNode = (sllNode*)malloc(sizeof(sllNode));
	if (listOfDepth[depth] == NULL) {
		lNode->next = NULL;
		lNode->treeNode = node;
	}
	else {
		lNode->next = listOfDepth[depth];
		lNode->treeNode = node;
	}
	listOfDepth[depth] = lNode;

	preOrderPerDepth(node->left, depth + 1);
	preOrderPerDepth(node->right, depth + 1);
}

sllNode** listOfDepths(Node* root)
{
	for (int i = 0; i < 10; i++) {
		listOfDepth[i] = NULL;
	}

	sllNode* lNode = (sllNode*)malloc(sizeof(sllNode));
	lNode->next = NULL;
	lNode->treeNode = root;
	listOfDepth[0] = lNode;

	preOrderPerDepth(root->left, 1);
	preOrderPerDepth(root->right, 1);

	return listOfDepth;
}


//4.4
int maxDepth(Node* node)
{
	if (node) {
		return MAX(maxDepth(node->left), maxDepth(node->right)) + 1;
	}
	else {
		return 0;
	}
}

bool balancedDepth(Node* node)
{
	if (node) {
		return ABS(maxDepth(node->left) - maxDepth(node->right)) < 2;
	}
	else {
		return true;
	}
}

//4.5   - leecode #98

bool isValidBST(Node* root)
{
	bool left;
	bool right;

	if (root == NULL) {
		return true;
	}

	if (root->left && !(root->key > root->left->key)) {
		return false;
	}

	if (root->right && !(root->key < root->right->key)) {
		return false;
	}

	left = isValidBST(root->left);
	right = isValidBST(root->right);

	return left && right;
}

//4.6 successor
		/*
						20
					  /	  \
					8*	   22
				  /  \
				 4    12
					 /  \
					10*	 14*

		   case #1. 8 -> 10  : 8  has right subtree and the minumum of right subtree is 10.
		   case #2. 10-> 12  : 10 doesn't have a right subtree, but the left child of its parent node, 12.
		   case #3. 14-> 20  : 14 doesn't have a right subtree, and it's right child of its parent node, 12. (8 is first left child to 20 while going up)
		   case #4. 22-> NULL: no untraversed parent -> just return NULL  */
		   //				4			// 2 -> 3
		   //			  /	  \			// 4 -> 6
		   //			2	   7		// 3 -> 4 *
		   //		     \    /  \		// 6 -> 7
		   //		      3* 6	  8*	// 8 -> NULL *
Node* inOrderSuccessor(Node* node)
{
	// root	   -> min of right C		; same as 3rd case
	// left C  -> parent
	// parent  -> min of right C
	// right C -> right 1st node as left child, then parent to that.
	// end     -> NULL
	if (node->right) {
		Node* temp = node->right;
		while (temp->left) {
			temp = temp->left;
		}
		return temp;
	}
	else if (node->parent->left == node) {
		return node->parent;
	}
	else {
		while (node->parent) {
			if (node->parent->right != node) {
				return node->parent;
			}
			node = node->parent;
		}
	}

	return NULL;
}


//4.7 topology sort


//4.8 lowest common ancestor
// if(root == node) instead of if(root->key == node->key) in case it's not BST
bool isNodeFound(Node* root, Node* node)
{
/*
	if ((root == NULL) || (node == NULL)) {
		return false;
	}

	if (root->key == node->key) {
		return true;
	}
*/
	if (root == NULL) {
		return false;
	}

	if (root == node) {
		return true;
	}

	return isNodeFound(root->left, node) || isNodeFound(root->right, node);
}

Node* lowestCommonAncestor(Node* root, Node* p, Node* q)
{
	if ((root == NULL) || (root == p) || (root == q)) {
		return root;
	}

	bool left = isNodeFound(root->left, p);
	bool right = isNodeFound(root->right, q);

	if (left && right) {
		return root;
	}

	if (left) {
		return lowestCommonAncestor(root->left, p, q);
	}
	else {
		return lowestCommonAncestor(root->right, p, q);
	}
}


//4.9 BST sequence



/*
	t1	t2
	n	n		T
	-	n		T
	n	-		F
	-	-		continue

	1. T1==T2 then T1.left==T2.left && T1.right==T2.right
	2. T1!=T2 then T1.left==T2 or T1.right T2 => one of them matching then goto #1
*/
//4.10
// Early returning upon t1.key != t2.key evades matching subtree below. #385
// Returning upon child == null avoids reporting true/false #380~381
bool isSubTree(Node* t1, Node* t2)
{
	bool left = false;
	bool right = false;

	if (t2 == NULL) {
		return true;
	}

	if (t1 == NULL) {
		return false;
	}

	if (t1->key == t2->key) {
		left = isSubTree(t1->left, t2->left);
		right = isSubTree(t1->right, t2->right);
	}


	if (left && right) {
		return true;
	}

	return isSubTree(t1->left, t2) || isSubTree(t1->right, t2);
}



//4.11 rondom node


//4.12 path sum



int main()
{
	// BST
		//				4
		//			  /	  \
		//			2	   7
		//		  /       /  \
		//		1        6    8
	Node* rootA = NULL;

	int arrA[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arrA) / sizeof(int); i++) {
		//root = insertNode(root, arr[i]);
		insertNode(&rootA, arrA[i]);
	}
	printf("inorder  ");
	InOrder(rootA);		// 1 2 4 6 7 8
	printf("\nlevel order  ");
	levelOrder(rootA);	// 4 2 7 1 6 8
	printf("\n");

	// minimum depth
	Node* rootB = NULL;
	int arrB[] = { 4, 7, 2, 1, 6, 8, 3};
	//int arrB[] = { 1, 2, 3, 4, 5, 6, 8 };						// minDepth : 1
	for (int i = 0; i < sizeof(arrB) / sizeof(int); i++) {		// minDepth : 3
	//for (int i = 0; i < 3; i++) {								// minDepth	: 3
	//for (int i = 0; i < 3; i++) {								// minDepth	: 2
		insertNode(&rootB, arrB[i]);
	}
	InOrder(rootB);		// 1 2 4 6 7 8

	printf("min depth:%d\n", minDepth(rootB));

	// 4.2 minimal binary tree
	printf("\n4.2  ");
	int sorted_arrA[] = { 1, 2, 4, 6, 7, 8 };
	Node* rootC = createMinimalBST(sorted_arrA, 0, 5);

	InOrder(rootC);		// 1 2 4 6 7 8
	printf("\n4.3\n");



	//4.3 list of depths
	Node* node3 = NULL;

	int arr3[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arr3) / sizeof(int); i++) {
		insertNode(&node3, arr3[i]);
	}
	InOrder(node3);		// 1 2 4 6 7 8
	printf("\n");

	sllNode** pHead = NULL;
	pHead = listOfDepths(node3);

	for (int i = 0; i < 4; i++) {
		printList(pHead[i]);
	}

	printf("\n\n");


	//4.4
	Node* rootD = NULL;

	int arrD[] = { 4, 7, 2, 1, 6, 8 };
	//int arrD[] = { 1, 2, 4, 6, 7, 8 };
	for (int i = 0; i < sizeof(arrD) / sizeof(int); i++) {
		insertNode(&rootD, arrD[i]);
	}
	InOrder(rootD);		// 1 2 4 6 7 8
	printf("\n\n");

	printf("4.4 balanced : %d\n", balancedDepth(rootD));



	// 4.5 valid BST
	Node* rootE = NULL;

	int arrE[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arrE) / sizeof(int); i++) {
		insertNode(&rootE, arrE[i]);
	}
	InOrder(rootE);		// 1 2 4 6 7 8
	printf("\n");

	//bool result = isValidBST(root, left, right);	// neetcode
	bool result = isValidBST(rootE);
	printf("\n4.5 valid BST:%d\n", result);

	//4.6
		//				4
		//			  /	  \
		//			2	   7
		//		     \    /  \
		//		      3  6    8
	printf("\n4.6\n");
	Node* rootF = NULL;

	int arrF[] = { 4, 7, 2, 3, 6, 8 };
	for (int i = 0; i < sizeof(arrF) / sizeof(int); i++) {
		insertNode(&rootF, arrF[i]);
	}
	printf("in order : ");
	InOrder(rootF);		// 2 3 4 6 7 8
	printf("\nlevel order : ");
	levelOrder(rootF);	// 4 2 7 3 6 8						// ????
	printf("\n");

	printf("%d\n", inOrderSuccessor(rootF->left)->key);			// 2 -> 3
	printf("%d\n", inOrderSuccessor(rootF)->key);				// 4 -> 6
	printf("%d\n", inOrderSuccessor(rootF->left->right)->key);	// 3 -> 4
	printf("%d\n", inOrderSuccessor(rootF->right->left)->key);	// 6 -> 7
	printf("%d\n\n", inOrderSuccessor(rootF->right->right));		// 8 -> NULL

	//~4.7 topology sort
	//4.8 LCA
		//				4
		//			  /	  \
		//			2	   7
		//		  /       /  \
		//		1        6    8
	Node* rootG = NULL;

	printf("\n4.8\n");
	int arr[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		insertNode(&rootG, arr[i]);
	}
	InOrder(rootG);		// 1 2 4 6 7 8
	printf("\n\n");

	// 2 & 8
	printf("LCA %d for %d & %d\n\n", lowestCommonAncestor(rootG, rootG->left, rootG->right->right)->key, rootG->left->key, rootG->right->right->key);

	// 2 & 1
	printf("LCA %d for %d & %d\n\n", lowestCommonAncestor(rootG, rootG->left, rootG->left->left)->key, rootG->left->key, rootG->left->left->key);

	// 7 & 6
	printf("LCA %d for %d & %d\n\n", lowestCommonAncestor(rootG, rootG->right, rootG->right->left)->key, rootG->right->key, rootG->right->left->key);

	// 6 & 8
	printf("LCA %d for %d & %d\n\n", lowestCommonAncestor(rootG, rootG->right->left, rootG->right->right)->key, rootG->right->left->key, rootG->right->right->key);


	//4.9 BST seq


	//4.10 subtree
		//				4
		//			  /	  \
		//			2	   7
		//		  /       /  \
		//		1        6    8
	Node* t1 = NULL;
	Node* t2 = NULL;

	int arr1[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arr1) / sizeof(int); i++) {
		insertNode(&t1, arr1[i]);
	}
	printf("\n\n4.10 \n");
	InOrder(t1);		// 1 2 4 6 7 8
	printf("\n");

	int arr2[] = { 7, 6, 8 };
	for (int i = 0; i < sizeof(arr2) / sizeof(int); i++) {
		insertNode(&t2, arr2[i]);
	}
	InOrder(t2);		// 6 7 8
	printf("\n\n");

	printf("t2 is t1's subtree:%d\n", isSubTree(t1, t2));

	//4.11 random node


	//4.12 path sum

	return 0;
}
