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
int count = 0;

// passing by value of a pointer never gets newly allocated address. Pass it by reference, ie, **p, or "RETURN IT".
// call by reference
// malloc(sizeof(Node*)); (X)   malloc(sizeof(Node)); (O)
// Node *node = *root ->  node is not root !!!!!  *node = temp wouldn't update root
void insertNode(Node** root, int data)
{
	if (root == nullptr) {
		printf("...\n");
		return;
	}
	/*
		Node* node = *root;

		if (node) {
			if (data < node->key) {
				insertNode(&node->left, data);
			}
			else {
				insertNode(&node->right, data);
			}
		}*/
	if (*root) {
		if (data < (*root)->key) {
			insertNode(&(*root)->left, data);
			(*root)->left->parent = *root;
		}
		else {
			insertNode(&(*root)->right, data);
			(*root)->right->parent = *root;
		}
	}
	else {
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->key = data;
		temp->left = nullptr;
		temp->right = nullptr;
		temp->parent = nullptr;

		//node = temp;
		*root = temp;
	}
}


// base case for recursive calls !!!!!! 
void InOrder(Node* node)
{
	if (node) {
		InOrder(node->left);
		printf("%d(%d)->", node->key, node->parent == nullptr ? 0 : node->parent->key);
		InOrder(node->right);
	}
}


int enqueue(Node* node)
{
	queue[tail++] = node;
	count++;
	return count;
}

Node* dequeue()
{
	Node* node;

	if (count > 0) {
		node = queue[head++];
		count--;
		return node;
	}
	else {
		return nullptr;
	}
}

// don't enqueue null node
void levelOrder(Node* node)
{
	head = 0;
	tail = 0;

	while (node) {
		printf("%d(%d)->", node->key, node->parent == nullptr ? 0 : node->parent->key);

		if (node->left) {
			enqueue(node->left);
		}
		if (node->right) {
			enqueue(node->right);
		}

		node = dequeue();
	}
	printf("nullptr\n");
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
	if (node == nullptr) {
		return 0;
	}

	return MIN(minDepth(node->left), minDepth(node->left)) + 1;
}



//4.1 graph


//4.2
// input array needs to be sorted !!!!!
Node* createMinimalBST(int* arr, int start, int end)
{
	Node* node = nullptr;

	if (start <= end) {
		int mid = (start + end) / 2;

		node = (Node*)malloc(sizeof(Node));
		node->key = arr[mid];
		node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;

		node->left = createMinimalBST(arr, start, mid - 1);
		if (node->left) {
			node->left->parent = node;
		}
		node->right = createMinimalBST(arr, mid + 1, end);
		if (node->right) {
			node->right->parent = node;
		}
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
	lNode->treeNode = tNode;
	if (*pHead) {
		lNode->next = *pHead;
	}
	else {
		lNode->next = nullptr;
	}
	*pHead = lNode;
}

void printList(sllNode* pNode)
{
	while (pNode) {
		printf("%d->", pNode->treeNode->key);
		pNode = pNode->next;
	}
	printf("\n");
}

sllNode* listOfDepth[10];


void preOrderPerDepth(Node* node, int depth)
{
	if (node == nullptr) {
		return;
	}

	addList(&listOfDepth[depth], node);

	preOrderPerDepth(node->left, depth + 1);
	preOrderPerDepth(node->right, depth + 1);
}

sllNode** listOfDepths(Node* root)
{
	for (int i = 0; i < 10; i++) {
		listOfDepth[i] = nullptr;
	}

	preOrderPerDepth(root, 0);

	return listOfDepth;
}


//4.4
int maxDepth(Node* node)
{
	if (node == nullptr) {
		return 0;
	}

	return MAX(maxDepth(node->left), maxDepth(node->right)) + 1;
}

bool balancedDepth(Node* node)
{
	if (node == nullptr) {
		return true;
	}

	return ABS(maxDepth(node->left) - maxDepth(node->right)) <= 1;
}


//4.5   - leecode #98
bool isValidBST(Node* root)
{
	bool left;
	bool right;

	if (root == nullptr) {
		return true;
	}

	if (root->left && !(root->left->key < root->key)) {
		return false;
	}

	if (root->right && !(root->right->key > root->key)) {
		return false;
	}

	return isValidBST(root->left) || isValidBST(root->right);
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
	Node* temp;

	if (node->right) {
		node = node->right;
		while (node->left) {
			node = node->left;
		}
		return node;
	}

	//if (node->parent && node == node->parent->left) {
	//	return node->parent;
	//}

	//if (node->parent && node == node->parent->right) {
	//	node = node->parent;

		while (node->parent && node == node->parent->right) {
			node = node->parent;
		}

		return node->parent;
	//}

	//return node;
}




//4.7 topology sort


//4.8 lowest common ancestor
// if(root == node) instead of if(root->key == node->key) in case it's not BST
bool isNodeFound(Node* root, Node* node)
{
	if (root == nullptr) {
		return false;
	}

	if (root->key == node->key) {
		return true;
	}
	else {
		return isNodeFound(root->left, node) || isNodeFound(root->right, node);
	}
}

Node* lowestCommonAncestor(Node* root, Node* p, Node* q)
{
	bool left;
	bool right;

	if (root == nullptr) return root;
	if (root == p) return root;
	if (root == q) return root;

	left = isNodeFound(root->left, p);
	right = isNodeFound(root->right, q);

	if (left && right) return root;

	if (left) {
		return lowestCommonAncestor(root->left, p, q);
	}

	if (right) {
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
// Early returning upon t1.key != t2.key evades matching subtree below. #385
// Returning upon child == null avoids reporting true/false #380~381
bool isSubTree(Node* t1, Node* t2)
{
	if (t2 == nullptr) {
		return true;
	}

	if (t1 == nullptr) {
		return false;
	}

	if (t1->key == t2->key) {
		return isSubTree(t1->left, t2->left) && isSubTree(t1->right, t2->right);
	}
	else {
		return isSubTree(t1->left, t2) || isSubTree(t1->right, t2);
	}
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
	Node* rootA = nullptr;

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
	Node* rootB = nullptr;
	int arrB[] = { 4, 7, 2, 1, 6, 8, 3 };
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
	Node* rootD = nullptr;

	//int arrD[] = { 4, 7, 2, 1, 6, 8 };
	int arrD[] = { 1, 2, 4, 6, 7, 8 };
	for (int i = 0; i < sizeof(arrD) / sizeof(int); i++) {
		insertNode(&rootD, arrD[i]);
	}
	InOrder(rootD);		// 1 2 4 6 7 8
	printf("\n\n");

	printf("4.4 balanced : %d\n", balancedDepth(rootD));



	// 4.5 valid BST
	Node* rootE = nullptr;

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

	printf("2 -> %d\n", inOrderSuccessor(rootF->left)->key);			// 2 -> 3
	printf("4 -> %d\n", inOrderSuccessor(rootF)->key);					// 4 -> 6
	printf("3 -> %d\n", inOrderSuccessor(rootF->left->right)->key);		// 3 -> 4
	printf("6 -> %d\n", inOrderSuccessor(rootF->right->left)->key);		// 6 -> 7
	printf("8 -> %d\n\n", inOrderSuccessor(rootF->right->right));		// 8 -> NULL

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

