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
#if 1
// call by value
/*Node* insertNode(Node* root, int data)
{
	if (root == NULL) {
		root = (Node*)malloc(sizeof(Node));
		if (root) {
			root->key = data;
			root->left = NULL;
			root->right = NULL;
			root->parent = NULL;
		}
	}
	else {
		if (root->key < data) {
			root->right = insertNode(root->right, data);
			root->right->parent = root;
		}
		else {
			root->left = insertNode(root->left, data);
			root->left->parent = root;
		}
	}

	return root;
}*/
// call by reference
// malloc(sizeof(Node*)); (X)   malloc(sizeof(Node)); (O)
void insertNode(Node** root, int data)
{
	Node* node = *root;

	if (node == NULL) {
		//node = (Node*)malloc(sizeof(Node*));
		node = (Node*)malloc(sizeof(Node));
		node->key = data;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		*root = node;
	}
	else {
		if (node->key > data) {
			insertNode(&node->left, data);
			node->left->parent = node; // *root; 
		}
		else {
			insertNode(&node->right, data);
			node->right->parent = node; // *root;
		}
	}
}
#else
void createBST(Node** root, int* arr, int start, int end)
{
	Node* node = *root;

	if (start >= end) {
		return;
	}
	else {

		arr[start];

	}
}
#endif


void InOrder(Node* node)
{
	if (node) {
		InOrder(node->left);
		printf("%d[%d] ", node->key, node->parent != NULL ? node->parent->key : NULL);
		//printf("%d ", node->key);
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
int minDepth(Node* node)
{
	int left = 10000000;	// 10000000
	int right = 10000000; 	// 10000000

	if (node == NULL) {
		return 0;
	}

	if ((node->left == NULL) && (node->right == NULL)) {
		return 1;
	}

	if (node->left) {
		left = minDepth(node->left);
	}

	if (node->right) {
		right = minDepth(node->right);
	}

	return MIN(left, right) + 1;
}

/*
int minDepth(Node* node)
{
	int left = 1000;
	int right = 1000;

	if (node == NULL) {
		return 0;
	}
	else if ((node->left == NULL) && (node->right == NULL)) {
		printf("%d\n", node->key);
		return 1;
	}
	else {
		printf("%d\n", node->key);
	}

	if (node->left) {
		left = minDepth(node->left);
	}

	if (node->right) {
		right = minDepth(node->right);
	}

	return MIN(left, right) + 1;
}
*/

//4.1 graph

//4.2
// input array needs to be sorted !!!!!
Node* createMinimalBST(int* arr, int start, int end)
{
	// TODO
	if (end < start) {
		return NULL;
	}

	int mid = (start + end) / 2;

	Node* node = (Node*)malloc(sizeof(Node));

	node->key = arr[mid];
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
	sllNode* lNode = (sllNode*)malloc(sizeof(sllNode));

	if (lNode) {
		lNode->treeNode= tNode;
		lNode->next = *pHead;
		*pHead = lNode;
	}
	else {
		//
	}
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

	if (listOfDepth[depth] == NULL) {
		listOfDepth[depth] = (sllNode *)malloc(sizeof(sllNode) * pow(2, depth));
		listOfDepth[depth]->treeNode = node;	// head node
		listOfDepth[depth]->next = NULL;
		printf("%d[%d]_\n", node->key, depth);
	}
	else {
		addList(&(listOfDepth[depth]), node);
		printf("%d[%d]+\n", node->key, depth);
	}

	//printf("%d[%d]->", node->key, depth);
	preOrderPerDepth(node->left, depth + 1);
	preOrderPerDepth(node->right, depth + 1);		
}

sllNode** listOfDepths(Node* root)
{
	Node *node = root;

	for (int i=0; i < 10; i++) {
		listOfDepth[i] = NULL;
	}

	//listOfDepth[0] = (sllNode*)malloc(sizeof(sllNode*));
	//listOfDepth[0]->treeNode = root;
	//printf("list created for depth %d with key %d\n", 0, root->key);

	preOrderPerDepth(root, 0);
	printf("NULL\n");
	return listOfDepth;
}

/*	depth first
	while (node) {
		printf("%d ", node->key);
		if (node->left) {
			queue[head++] = node->left;
		}
		if (node->right) {
			queue[head++] = node->right;
		}
		node = queue[tail++];
	}
	printf("\n\n\n\n\n\n");
	//addList(&head, data);
*/

//4.4
int maxDepth(Node* node)
{
	if (node == NULL) {
		return 0;
	}

	return MAX(maxDepth(node->left), maxDepth(node->right)) + 1;
}

bool balancedDepth(Node* node)
{
	int left;
	int right;

	if (node == NULL) {
		return true;
	}

	left = maxDepth(node->left);
	right = maxDepth(node->right);

	printf("l:%d r:%d\n", left, right);

	return ABS(left - right) < 2;
}




//4.5   - leecode #98
#if 1
bool isValidBST(Node* root)
{
	if (root == NULL) {
		return true;
	}

	printf("%d->", root->key);

	if ((root->left) && !(root->left->key < root->key)) {
		return false;
	}

	if ((root->right) && !(root->right->key > root->key)) {
		return false;
	}

	return isValidBST(root->left) && isValidBST(root->right);
}
#else
int left = -1000000;
int right = 1000000;
int count = 0;

// neetcode 
bool isValidBST(Node* root, int left, int right)
{
	bool result = true;

	if (root == NULL) {
		return true;
	}

	// test code to fail
	if (count++ == 3) {
		root->key = 0;
	}
	printf("%4d %4d %4d\n", left, root->key, right);

	if (!((root->key > left) && (root->key < right))) {
		return false;
	}

	return (isValidBST(root->left, left, root->key) && isValidBST(root->right, root->key, right));
}
#endif

//4.6
/*
	#1  check arr[i] < arr[i+1]	after inorder traversal
	#2	def valid(node, left, right):
			if not node: return True
			if not (node.val < right and node.val > left): return False
			return valid(node.left, left, node.val) and valid(node.right, node.val, right)

		return valid(root, float("-inf"), float("inf")) */
		/*
		#if 0
		int inOrderResult[] = {0,0,0,0,0,0,0,0,0,0};
		int index = 0;

		void inOrderTraverse(Node* node)
		{
			if (node == NULL) {
				return;
			}

			inOrderTraverse(node->left);
			inOrderResult[index++] = node->key;
			inOrderTraverse(node->right);
		}

		bool isValidBST(Node* root)
		{
			inOrderTraverse(root);
			// fail case !
			//inOrderResult[3] = 0;
			printf("\n");

			for (int i = 0;i < index-1; i++) {
				printf("%d %d\n", inOrderResult[i], inOrderResult[i+1]);
				if (inOrderResult[i] >= inOrderResult[i+1]) {
					return false;
				}
			}
			printf("\n");

			return true;
		}
		#else
		int prevKey = -1;

		bool inOrderTraverse(Node* node)
		{
			if (node == NULL) {
				return true;
			}

			inOrderTraverse(node->left);
			printf("%2d %2d\n", prevKey, node->key);
			if (prevKey > node->key) {
				return false;
			}
			prevKey = node->key;
			inOrderTraverse(node->right);
		}

		bool isValidBST(Node* root)
		{
			bool result = inOrderTraverse(root);

			return result;
		}
		#endif
		*/


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
	Node* prev = NULL;

	if (node == NULL) {
		return node;
	}
	printf("%d->", node->key);

	// has right child 
	if (node->right) {
		// find min node on the right subtree
		node = node->right;
		while (node) {
			prev = node;
			node = node->left;
		}
		return prev;
	}
	else {
		while (node->parent && node->parent->right == node) {
			node = node->parent;
		}
		return node->parent;
	}

	return NULL;
}




//4.7 topology sort


//4.8 lowest common ancestor
bool isNodeFound(Node* root, Node* node)
{
	if (root == NULL) {
		return false;
	}

	if (root == node) {
		return true;
	}
	else {
		return isNodeFound(root->left, node) || isNodeFound(root->right, node);
	}
}

Node* lowestCommonAncestor(Node* root, Node* p, Node* q)
{
	bool left = false;
	bool right = false;

	if ((root == NULL) || (root == p) || (root == q)) {
		return root;
	}

	left = isNodeFound(root->left, p);
	right = isNodeFound(root->right, q);

	// p & q are on both sides
	if (left && right) {
		return root;
	}

	// p & q are on either side
	if (left) {
		return lowestCommonAncestor(root->left, p, q);
	}
	else {
		return lowestCommonAncestor(root->right, p, q);
	}

	return NULL;
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
bool isSubTree(Node* t1, Node* t2)
{
	bool result = false;

	if (t2 == NULL) {
		return true;
	}

	if (t1 == NULL) {	// t2 != NULL 
		return false;
	}

	if ((t1->key == t2->key) && isSubTree(t1->right, t2->right) && isSubTree(t1->left, t2->left)) {
		return true;
	}

	return isSubTree(t1->left, t2) || isSubTree(t1->right, t2);;
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
	int arrB[] = { 4, 7, 2, 1, 6, 8 };
	//for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {		// minDepth : 3
	//for (int i = 0; i < 3; i++) {								// minDepth	: 3
	for (int i = 0; i < 3; i++) {								// minDepth	: 2
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
	InOrder(t1);		// 1 2 4 6 7 8
	printf("\n");

	int arr2[] = { 7, 6, 8 };
	for (int i = 0; i < sizeof(arr2) / sizeof(int); i++) {
		insertNode(&t2, arr2[i]);
	}
	InOrder(t2);		// 6 7 8
	printf("\n\n");

	printf("4.10 t2 is t1's subtree:%d\n", isSubTree(t1, t2));

	//4.11 random node


	//4.12 path sum

	return 0;
}
