#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX(A, B)		((A) > (B) ? (A) : (B))
#define ABS(A)			((A) > 0 ? (A) : (A) * (-1))


typedef struct _treeNode {
	int key;
	struct _treeNode* left;
	struct _treeNode* right;
	struct _treeNode* parent;
	struct _treeNode* next;
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
void insertNode(Node** root, int data)
{
	Node* node = *root;

	if (node == NULL) {
		node = (Node*)malloc(sizeof(Node));
		if (node) {
			node->key = data;
			node->left = NULL;
			node->right = NULL;
			node->parent = NULL;
			*root = node;
		}
	}
	else {
		if (data > node->key) {
			insertNode(&node->right, data);
			node->right->parent = *root;
		}
		else {
			insertNode(&node->left, data);
			node->left->parent = *root;
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
		InOrder(node->right);
	}
}



void levelOrder(Node* node)
{
	//Node* node = NULL;
	//queue[head++] = root;				// push(root);
	//node = queue[tail++];				// node = pop();
	head = 0;
	tail = 0;
	while (node) {
		printf("%d ", node->key);

		if (node->left) {
			queue[head++] = node->left;		// push(node->left);
		}

		if (node->right) {
			queue[head++] = node->right;	// push(node->right);
		}

		node = queue[tail++];			// node = pop();
	}
}

//min depth
#define MIN(A, B)	(A < B ? A : B)

int minDepth(Node* node)
{
	int left = 100000;
	int right = 100000;

	if (node == NULL) {
		return 0;
	}

	if ((node->left == NULL) && (node->right == NULL)) {
		return 1;
	}

	if (node->left) left = minDepth(node->left);
	if (node->right) right = minDepth(node->right);

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
	//printf("s:%d e:%d -> ", start, end);
	if (end < start) {
		//printf("end\n");
		return NULL;
	}

	int mid = (start + end) / 2;

	Node* node = (Node*)malloc(sizeof(Node));

	node->key = arr[mid];
	node->parent = NULL;
	//printf("%d[%d]\n", arr[mid], mid);

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
//#define MAX 128
typedef struct _tree {
	int data;
	struct _tree* left;
	struct _tree* right;
	struct _tree* next;
}Tree;

typedef struct _treelist
{
	Tree* t;
	int dep;
	struct _treelist* next;
} TreeList;
/*
TreeList* link_of_depth(Tree* t, TreeList* tl, int depth)
{
	TreeList* cur, * tmp;
	if (t == NULL) return NULL;
	cur = tl;
	while (cur)
	{
		if (cur->dep == depth) break;
		cur = cur->next;
	}
	if (cur == NULL)
	{
		cur = (TreeList*)malloc(sizeof(TreeList));
		cur->t = t;
		cur->dep = depth;
		cur->next = NULL;
		tmp = tl;
		while (tmp->next) tmp = tmp->next;
		tmp->next = cur;
	}
	else
	{
		t->next = cur->t->next;
		cur->t = t;
	}
	link_of_depth(t->right, tl->next, depth + 1);
	link_of_depth(t->left, tl->next, depth + 1);
	return cur;
}

TreeList* setlink(Tree* t)
{
	TreeList* tl;
	if (t == NULL) return NULL;
	tl = (TreeList*)malloc(sizeof(TreeList));
	tl->t = NULL;
	tl->dep = 1;
	tl->next = NULL;
	return link_of_depth(t, tl, tl->dep);
}*/


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

sllNode *listOfDepth[10];

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
	int left = 0;
	int right = 0;

	if (node == NULL) {
		return 0;
	}

	/*if ((node->left == NULL) && (node->right == NULL)) {
		return 1;
	}*/

	left = maxDepth(node->left);
	right = maxDepth(node->right);

	return MAX(left, right) + 1;
}

bool balanced_depth(Node* node)
{
	int left = maxDepth(node->left);
	int right = maxDepth(node->right);

	//printf("l:%d r:%d abs(l-r):%d\n", left, right, ABS(left - right));

	return (ABS(left - right) <= 1);
}


//4.5 - leecode #98
int left = -100;
int right = 100;
int count = 0;

#if 1
bool isValidBST(Node* root)
{
	bool result = true;

	if (root == NULL) {
		return true;
	}

	if ((root->left) && (root->key <= root->left->key)) {
		return false;
	}

	if ((root->right) && (root->key >= root->right->key)) {
		return false;
	}

	if (!(isValidBST(root->left))) {
		return false;
	}

	if (!(isValidBST(root->right))) {
		return false;
	}

	return true;
}
#else
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
		   //		      3* 6	  8		// 8 -> NULL *


#if 1 // with parent link
int inOrderSuccessor(Node* node)
{
	int prevKey;
	Node* temp;

	if (node == NULL) {
		return NULL;
	}
	printf("%d->", node->key);

	// case #1 : 
	if (node->right) { // find min on the right subtree
		temp = node->right;
		while (temp) {
			prevKey = temp->key;
			temp = temp->left;
		}
		return prevKey;
	}
	else {
		// is the node left child of its parent ?
		temp = node->parent;
		while (temp && (node == temp->right)) {
			node = temp;
			temp = temp->parent;
		}
		if (temp) {
			return temp->key;
		}
	}
	return NULL;
}
#else // without parent link


#endif


//4.7 topology sort


//4.8 lowest common ancestor
bool isNodeFound(Node* root, Node* node)
{
	//printf("%p %p->", root, node);
	if (root == NULL) {
		//printf("----------------%d not found\n", node->key);
		return false;
	}
	//printf("%d %d\n", root->key, node->key);

	if (root == node) {
		//printf("----------------%d found\n", node->key);
		return true;
	}

	bool result = false;

	result = isNodeFound(root->left, node);
	result |= isNodeFound(root->right, node);

	return result;
}

Node* lowestCommonAncestor(Node* root, Node* p, Node* q)
{
	bool onLeft = false;
	bool onRight = false;

	if (!root || root == p || root == q) {	// !!!!!! 
		return root;
	}

	onLeft = isNodeFound(root->left, p);
	onRight = isNodeFound(root->right, q);
	//printf("L:%d    R:%d\n", onLeft, onRight);

	if (onLeft && onRight) {
		//printf("LCA %d found\n", root->key);
		return root;
	}
	else if (onLeft && !onRight) {
		//printf("p & q on left: start from %d\n", root->left->key);
		lowestCommonAncestor(root->left, p, q);
	}
	else if (!onLeft && onRight) {
		//printf("p & q on right: start from %d\n", root->right->key);
		lowestCommonAncestor(root->right, p, q);
	}
	else {
		printf("error!\n");
	}
}

//4.9 BST sequence


//4.10 subtree
/*
boolean containsTree(TreeNode t1, TreeNode t2) {
	if (t2 == null) return true; 		// The empty tree is always a subtree
	return subTree(t1, t2);
}

boolean subTree(TreeNode r1, TreeNode r2) {
	if (r1 == null) {
		return false; 					// big tree empty & subtree still not found.
	}
	else if (r1.data == r2.data && matchTree(r1, r2)) {
		return true;
	}
	return subTree(rl.left, r2) || subTree(rl.right, r2);
}

boolean matchTree(TreeNode rl, TreeNode r2) {
	if (rl == null && r2 == null) {
		return true; 					// nothing left in the subtree
	}
	else if (rl == null || r2 == null) {
		return false; 					// exactly tree is empty, therefore trees don't match
	}
	else if (rl.data != r2.data) {
		return false; 					// data doesn't match
	}
	else {
		return matchTree(rl.left, r2.left) && matchTree(rl.right, r2.right);
	}
}*/

/*
	t1	t2
	n	n		T
	-	n		T
	n	-		F
	-	-		continue
*/

bool isSubTree(Node* t1, Node* t2)
{
	if (t2 == NULL) {
		return true;
	}
	else if (t1 == NULL) {
		return false;
	}

	if (t1->key == t2->key && isSubTree(t1->left, t2->left) && isSubTree(t1->right, t2->right)) {
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

	int arrB[] = { 4, 7, 2, 1, 6, 8 };
	//for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
	for (int i = 0; i < 5; i++) {
		insertNode(&rootB, arrB[i]);
	}
	InOrder(rootB);		// 1 2 4 6 7 8

	printf("min depth:%d\n", minDepth(rootB));

	// 4.2 minimal binary tree
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

	printf("4.4 balanced : %d\n", balanced_depth(rootD));



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

	printf("%d\n", inOrderSuccessor(rootF->left));			// 2 -> 3
	printf("%d\n", inOrderSuccessor(rootF));				// 4 -> 6
	printf("%d\n", inOrderSuccessor(rootF->left->right));	// 3 -> 4
	printf("%d\n", inOrderSuccessor(rootF->right->left));	// 6 -> 7
	printf("%d\n", inOrderSuccessor(rootF->right->right));	// 8 -> NULL

	//~4.7 topology sort
	//4.8 LCA
		//				4
		//			  /	  \
		//			2	   7
		//		  /       /  \
		//		1        6    8
	Node* rootG = NULL;

	int arr[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		insertNode(&rootG, arr[i]);
	}
	InOrder(rootG);		// 1 2 4 6 7 8
	printf("\n\n");

	// 2 & 8
	printf("4.8 LCA %d for %d & %d\n\n", lowestCommonAncestor(rootG, rootG->left, rootG->right->right)->key, rootG->left->key, rootG->right->right->key);

	// 2 & 1
	printf("4.8 LCA %d for %d & %d\n\n", lowestCommonAncestor(rootG, rootG->left, rootG->left->left)->key, rootG->left->key, rootG->left->left->key);

	// 7 & 6
	printf("4.8 LCA %d for %d & %d\n\n", lowestCommonAncestor(rootG, rootG->right, rootG->right->left)->key, rootG->right->key, rootG->right->left->key);

	// 6 & 8
	printf("4.8 LCA %d for %d & %d\n\n", lowestCommonAncestor(rootG, rootG->right->left, rootG->right->right)->key, rootG->right->left->key, rootG->right->right->key);


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
