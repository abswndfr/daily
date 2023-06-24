#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1.1
// init bitmap after creating
// while(*str), not while(str)
#define ASCII_CODE_SIZE		128
bool isUnique(char* str)
{
	bool* found = (bool*)malloc(sizeof(bool) * ASCII_CODE_SIZE);

	if (found) {
		memset(found, 0, sizeof(bool) * ASCII_CODE_SIZE);
	}
	else {
		return false;
	}

	while (*str) {
		if (found[*str] == true) {
			return false;
		}
		found[*str] = true;
		str++;
	}

	return true;
}

//1.2
// is each character unique ? boolean type if yes, int type if no.
bool isPermutation(char* strA, char* strB)
{
	int* charBin = (int*)malloc(sizeof(int) * ASCII_CODE_SIZE);
	int lenA = strlen(strA);
	int lenB = strlen(strB);

	if (charBin) {
		memset(charBin, 0, sizeof(int) * ASCII_CODE_SIZE);
	}
	else {
		return false;
	}

	if ((lenA != lenB) || (lenA == 0) ) {
		return false;
	}

	while (*strA) {
		charBin[*strA]++;
		strA++;
	}

	while (*strB) {
		charBin[*strB]--;
		if (charBin[*strB] < 0) {
			return false;
		}
		strB++;
	}

	return true;
}

//1.4
// is null string a palindrome ? 
// reinit ptr after string reaches '/0' -> or use for instead while w/ str++
bool isPalindromePermutation(char* str)
{
	int* occurrence = (int*)malloc(sizeof(int) * ASCII_CODE_SIZE);
	int len = strlen(str);
	bool oddFound = false;

	if (occurrence) {
		memset(occurrence, 0, sizeof(int) * ASCII_CODE_SIZE);
	}
	else {
		return false;
	}

	// Counter
	//while (*str) {
	for(int i=0; i<len; i++) {
		occurrence[str[i]]++;
		//str++;	this will move ptr to '/0'
	}

	for (int i = 0; i < len; i++) {
		if ((occurrence[str[i]] & 1) != 0) {
			if (oddFound == true) {
				return false;
			}
			oddFound = true;
		}
	}

	return true;
}

#define MAX(A, B)		((A) > (B) ? (A) : (B))
#define ABS(A)			((A) > 0 ? (A) : (A) * (-1))

//1.5 char edit like insert, remove, or replace => same str?
// move next in one string only if lenA != lenB
// asdfjkl & asejkl : 2 edits away(replace & insert) -> needs 'continue'
bool isOneEditAway(char* strA, char* strB)
{
	int lenA = strlen(strA);
	int lenB = strlen(strB);

	bool mismatchFound = false;

	// same or +/-1
	if (ABS(lenA - lenB) > 1) {
		printf("%d %d\n", lenA, lenB);
		return false;
	}

	// count mismatches 
	while (*strA && *strB) {
		if (*strA != *strB) {
			printf("%c %c\n", *strA, *strB);
			if (mismatchFound == true) {
				return false;
			}

			mismatchFound = true;

			if (lenA > lenB) {
				strA++;
				continue;
			}
			else if (lenA < lenB){
				strB++;
				continue;
			}
			else {
				// same length : move both forward 
			}
		}
		
		strA++;
		strB++;
	}

	return true;
}

//1.6
// index should be the current one at the bottom of for loop. It will advance at the top of for loop.
char* string_compression(char* str)
{
	int len = strlen(str);
	char* res = (char*)malloc(sizeof(char) * len);
	int count;

	printf("%s\n", str);

	if (res) {
		memset(res, 0, sizeof(char) * len);
	}
	else {
		return NULL;
	}

	//          1      
	//0123456789012345
	//Hello, world!
	// 	i = 2, j = 3   -> i = 4
	// 	i = 2, j = 3~6 -> i = 7
	// aaa bbbbb c dddd ee fff k
	for (int i = 0; i < len; i++) {
		printf("%c", str[i]);
		count = 1;

		if (i == len - 1) {								// last charcter
			printf("%d ", count);
		} else {

			if (str[i] == str[i + 1]) {					// found repeating
				count = 2;
				int j;
				for (j = i + 1; j < len - 1; j++) {		// next one repeating ?
					if (str[j] == str[j + 1]) {
						count++;
					}
					else {
						break;							// no more repeating
					}
				}
				i = j;									// don't use i = j + 1. There's i++ above !!!
			}
			printf("%d ", count);
		}
	}

	return res;
}


//1.7 
// cw : transpose -> swap columns
// ccw: transpose -> reverse columns
/*
void rotate(vector<vector<int>>& matrix) {

}*/

//1.8
bool zero_matrix(int** matrix, int len)
{
	return true;
}

//1.9
bool string_rotation(char* stra, char* strb)
{
	return true;
}



typedef struct _node {
	int data;
	struct _node* next;
} NODE;


void addList(NODE** pHead, int data)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));

	if (node) {
		node->data = data;
		node->next = *pHead;	
		*pHead = node;
	}
	else {
		//
	}
}

NODE* addList1(NODE** pHead, int data)
{
	return *pHead;
}

void printList(NODE* pNode)
{
	while (pNode) {
		printf("%d->", pNode->data);
		pNode = pNode->next;
	}
	printf("NULL\n");
}

//2.1
// NODE **pHead; -> *pHead->next (X) but (*pHead)->next (O)
// add list : newNode->next = *pHead, not *pHead->next unless pHead is a dummy
void remove_duplication(NODE* node)
{
	NODE *curr;
	NODE* prev;

	// out loop for the reference
	while (node) {
		// inner loop for the target	
		printf("%d-", node->data);
		prev = node;
		curr = node->next;

		while (curr) {
			printf("%d ", curr->data);
			if (node->data == curr->data) {
				// remove dup
				printf("    dup[%d]   ", curr->data);
				prev->next = curr->next;
			}
			else {
				// move forward
				prev = curr;
			}
			curr = curr->next;
		}

		printf("\n");
		node = node->next;
	}
}

//2.2
// 0 base or 1 base ? (is 1st to last a[n-1] or a[n-2] ?)
// missing index++;
NODE* returnKthToLast(NODE* node, int k)
{
	int len = 0;
	int index = 0;
	NODE* ptr = node;

	while (ptr) {
		len++;
		ptr = ptr->next;
	}
	printf("len:%d\n", len);

	if (k > len) return NULL;

	while (node) {
		if (k == len - index) {
			return node;
		}
		index++;
		node = node->next;
	}
}
/*
node* nthToLast(node* head, int k, int& i)
{
	if (head== NULL) {
		return NULL;
	}

	node* nd = nthToLast(head->next, k, i);

	i = i + 1;
	if (i == k) {
		return head;
	}

	return nd;
}

node* nthToLast(node* head, int k)
{
	int i = 0;
	return nthToLast(head, k, i);
} */


//2.3
bool delete_middle_node(NODE* node)
{
	if (node && node->next) {
		node->data = node->next->data;
		node->next = node->next->next;
		return true;
	}

	return false;
}

//2.4
// less.next can be null but less can never : 	temp = &less;	// less->next; while(temp) {}
NODE* partition(NODE* node, int x)
{
	NODE less;
	NODE more;
	NODE* temp;
	more.next = NULL;
	less.next = NULL;

	while (node) {
		temp = node->next;
		if (node->data < x) {
			node->next = less.next;
			less.next = node;
		}
		else {
			node->next = more.next;
			more.next = node;
		}
		node = temp;
	}

	printList(less.next);
	printList(more.next);

	temp = &less;	// less->next;
	while (temp && temp->next) {
		temp = temp->next;
	}

	temp->next = more.next;
	return less.next;
}

//2.5
// advance pointer to struct :  node = node->next;  not node++;
// dont' overwrite to head : head->data = sum;
NODE* sumList(NODE* nodeA, NODE* nodeB)
{
	NODE* head = (NODE*)malloc(sizeof(NODE));
	NODE* result = head;
	int sum = 0;
	int carry = 0;

	if (head) {
		head->next = NULL;
	}
	else {
		return NULL;
	}

	while (nodeA || nodeB || carry) {
		if (nodeA) {
			sum = nodeA->data;
			nodeA = nodeA->next;
		}

		if (nodeB) {
			sum += nodeB->data;
			nodeB = nodeB->next;
		}
		sum += carry;

		carry = sum / 10;
		sum = sum % 10;
		//printf("sum:%d carry:%d\n", sum, carry);

		// next place digit
		NODE* node = (NODE*)malloc(sizeof(NODE));
		node->data = sum;
		node->next = head->next;

		head->next = node;
	}
	
	return result->next;
}

//2.6
bool palindrome(NODE* node)
{
	NODE revHead;
	NODE* head = node;

	revHead.next = NULL;

	while (node) {
		NODE *newNode = (NODE*)malloc(sizeof(NODE));

		newNode->data = node->data;
		newNode->next = revHead.next;
		revHead.next = newNode;
		node = node->next;
	}

	printList(revHead.next);

	while (head) {
		//printf("%d %d .. ", revHead.next->data, head->data);
		if (revHead.next->data != head->data) {
			//printf("false\n");
			return false;
		}
		//printf("\n");

		revHead.next = revHead.next->next;
		head = head->next;
	}

	return true;
}



typedef struct _treeNode {
	int key;
	struct _treeNode* left;
	struct _treeNode* right;
	struct _treeNode* parent;
} Node;


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


void InOrder(Node*node)
{
	if (node) {
		InOrder(node->left);
		printf("%d[%d] ", node->key, node->parent != NULL ? node->parent->key : NULL);
		InOrder(node->right);
	}
}


#define QUE_MAX	10
Node* queue[QUE_MAX];
int head = 0;
int tail = 0;
//int count = 0;

void levelOrder(Node* node)
{
	//Node* node = NULL;
	//queue[head++] = root;				// push(root);
	//node = queue[tail++];				// node = pop();
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
// need to be sorted !!!!!
Node* createMinimalBST(int* arr, int start, int end) 
{
	if (end < start) {
		return NULL;
	}

	int mid = (start + end) / 2;

	Node *node = (Node *)malloc(sizeof(Node));
		
	node->key = arr[mid];
	node->left = createMinimalBST(arr, start, mid - 1);
	node->right = createMinimalBST(arr, mid + 1, end);

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

#if 0
Node* link_of_depth(Tree* t, TreeList* tl, int depth)
{
	cur;

	return 
}
#endif

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

	return (ABS(left - right) <= 1) ;
}


//4.5 - leecode #98
int left = -100;
int right=  100;
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
bool isValidBST(Node *root, int left, int right)
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
int inOrderSuccessor(Node *node)
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
	} else if (onLeft && !onRight) {
		//printf("p & q on left: start from %d\n", root->left->key);
		lowestCommonAncestor(root->left, p, q);
	} else if (!onLeft && onRight) {
		//printf("p & q on right: start from %d\n", root->right->key);
		lowestCommonAncestor(root->right, p, q);
	}
	else {
		printf("error!\n");
	}
}

//4.9 BST sequence


//4.10 subtree
//T1, T2, T2 is sub of T2??
//1. T1==T2 then T1.left==T2.left && T1.right==T2.right
//2. T1!=T2 then T1.left==T2 or T1.right T2 => one of them matching then goto #1








//4.11 rondom node


//4.12 path sum



void printBin(unsigned int a)
{
	for (int i = 6; i >= 0; i--)
		printf("%d", (a & (1 << i)) >> i);
	printf("  ");
}


int countOnes(unsigned int a)
{
	int count = 0;
	/*
		for (int i = 0;i < 32; i++) {
			if (a & (1 << i)) {
				count++;
			}
		}*/
		/*
			while (a) {
				if(a & 1) {
					count++;	// count += a & 1;
				}
				a = a >> 1;
			}
		*/
	while (a) {
		a = a & (a - 1);
		count++;
	}

	return count;
}

//5.1
unsigned int bitInsert(unsigned int a, unsigned int b, int i, int j)
{
	int mask = ((1 << j) - 1) ^ ((1 << i) - 1);
	return a & (~mask) | (b << i);
}

//5.4
/*
13  12  11  10  9  8  7  6  5  4  3  2  1  0
---------------------------------------------
 1   1   0   1  1  0  0  1  1  1  1  1  0  0
					  ^
 1   1   0   1  1  0  1  1  1  1  1  1  0  0

 1   1   0   1  1  0  1  0  0  0  0  0  0  0
						 ^  ^  ^  ^  ^  ^  ^
 1   1   0   1  1  0  1  0  0  0  1  1  1  1
								  ^  ^  ^  ^
	int c = a;
	int c0 = 0;
	int c1 = 0;

	while (((c & 1) == 0) && (c != 0)) {	// trailing zero
		c0++;
		c >>= 1;
	}

	while ((c & 1) == 1) {					// non trailing ones
		c1++;
		c >>= 1;
	}

	printf("c0:%d c1:%d\n", c0, c1);
	// If there is no bigger number with the same no. of 1's
	if (c0 + c1 == 31 || c0 + c1 == 0)
		return -1;

	// position of rightmost non-trailing zero
	int p = c0 + c1;

	// Flip rightmost non-trailing zero
	a |= (1 << p);

	// Clear all bits to the right of p
	a &= ~((1 << p) - 1);

	// Insert (c1-1) ones on the right.
	a |= (1 << (c1 - 1)) - 1;

	return a;

 13  12  11  10  9  8  7  6  5  4  3  2  1  0
 ---------------------------------------------
 1   0   0    1  1  1  1  0  0  0  0  0  1  1
					   ^
 1   0   0    1  1  1  0  0  0  0  0  0  0  0
										^  ^
 1   0   0    1  1  1  0  1  1  1  0  0  0  0
						  ^  ^  ^

	int temp = a;
	int c0 = 0;
	int c1 = 0;

	// count 1s
	while ((temp & 1) == 1) {
		c1++;
		temp = temp >> 1;
	}

	if (temp == 0) {
		return -1;
	}

	// count 0s except leading 0s
	while (((temp & 1) == 0) && (temp != 0)) {
		c0++;
		temp = temp >> 1;
	}

	// position of rightmost non-trailing one.
	int p = c0 + c1;

	// clears from bit p onwards
	a = a & ((~0) << (p + 1));

	// Sequence of (c1+1) ones
	int mask = (1 << (c1 + 1)) - 1;

	a = a | mask << (c0 - 1);

	return a;
*/
unsigned int bigSmallFromGiven(unsigned int a)
{
/* 1  1  0  1  1  0  0  1  1  1  1  1  0  0
   1  1  0  1  1  0  1  1  1  1  1  1  0  0
   1  1  0  1  1  0  1  0  0  0  1  1  1  1 */
	//-- closet bigger number
	// find the right most non trailing zero and set to it
	bool oneFound = false;
	int bit = 0;
	int temp = a;
	int count = 0;

	while (bit < 32) {
		// find 1 first
		if (temp & (1 << bit)) {
			oneFound = true;
		}

		// then find 0 
		if (oneFound) {
			if (!(temp & (1 << bit))) {
				temp |= 1 << bit;
				break;
			}
			count++;
		}
		bit++;
	}

	// clear after the 1st one and then set count - 1
	temp = temp & ~((1 << bit) - 1);
	for (int i = 0; i < count - 1; i++) {
		temp |= 1 << i;
	}


/* 1  0  0  1  1  1  1  0  0  0  0  0  1  1
   1  0  0  1  1  1  0  0  0  0  0  0  0  0
   1  0  0  1  1  1  0  1  1  1  0  0  0  0 */

	//-- closet smaller number
	// find the right most non trailing one and set it
	int zeroFound = false;
	bit = 0;
	temp = a;
	count = 0;

	printBin(temp);

	while (bit < 32) {
		// find 0 first
		if (!(temp & (1 << bit))) {
			zeroFound = true;
		}

		// then find 1 and clear the bit
		if (zeroFound) {
			if (temp & (1 << bit)) {
				temp &= ~(1 << bit);
				break;
			}
		}
		else {
			count++;
		}
		bit++;
	}
	printf("..%d..", count);
	printBin(temp);

	// clear after the flipped bit and then set count + 1
	temp = temp & ~((1 << bit) - 1);
	printBin(temp);
	for (int i = 0; i < count + 1; i++) {
		temp |= 1 << (bit - i - 1);
	}
	printBin(temp);

	return temp;
}

//5.6
int conversion(int a, int b)
{
	int t;
	int	count = 0;

	t = a ^ b;

	while (t) {
		t = t & (t - 1);
		count++;
	}

	return count;
}

//prime
bool prime(int n)
{
/*
	for () {
	
	
	}
*/
	return true;
}

bool find_prime(int n)
{
	return true;
}

//memcpy
char* mymemcpy(char* src, char* desc, int size)
{
	return desc;
}




//10.1
/*
void sorted_merge(int* a, int* b, int la, int lb)
{
	int size = la + lb - 1;
	la--;
	lb--;

	while (lb >= 0) {
		if (a[la] > b[lb]) {
			a[size--] = a[la--];
		} else {
			a[size--] = b[lb--];
		}
	}
}
void sorted_merge(int* a, int* b, int lastA, int lastB)
{
	int indexA = lastA - 1;	
	int indexB = lastB - 1;
	int indexMerged = lastB + lastA - 1;
		
	while (indexB >= 0) {
		if (indexA >= 0 && (a[indexA] > b[indexB])) {
			a[indexMerged] = a[indexA];
			indexA--;
		}
		else {
			a[indexMerged] = b[indexB];
			indexB--;
		}
		indexMerged--;
	}
}*/

void sorted_merge(int* a, int* b, int lastA, int lastB)
{

	int index = lastA + lastB - 1;
	int indexA = lastA - 1;
	int indexB = lastB - 1;

	while ((indexA >= 0) && (indexB >= 0)) {
		if (a[indexA] > b[indexB]) {
			a[index] = a[indexA];
			indexA--;
		}
		else {
			a[index] = b[indexB];
			indexB--;
		}
		index--;
	}

	if (indexB > 0) {
		for (; indexB >= 0; indexB--) {
			a[index] = b[indexB];
			index--;
		}
	}
}




#if 0
//2.7
bool intersection(NODE* nodea, NODE* nodeb)
{
	return true;
}

//2.8
NODE* loopDetection(NODE* node)
{
	return slow;
}

//tree struct
typedef struct _tree {
}Tree;

typedef struct _treelist
{
} TreeList;



//8.1
int triple_step(int n)
{
	return ...
}

int triple_steps(int n)
{
	return ...
}



//8.2
int arr[3][3];

//-1:block, 0:can move, >1 :visited
bool robotInGrid(int row, int col, int step)
{
	return true;
}

void printArray(int* data, int r)
{
	for (int j = 0; j < r; j++)
		printf("%d ", data[j]);
	printf("\n");
}

//8.4
#include <math.h>
void pow_set(int set_size)
{
}

void combinationUtil(int *arr, int *data, int start, int end, int index, int r)
{
}

void printCombination(int* arr, int n, int r)
{
}

void swap(char* x, char* y)
{
}

void permute(char* a, int l, int r)
{
}

//8.5
int multiply(int a, int b)
{
	return a;
}
#endif


int main()
{
	char astr[] = "asdfjkl";
	char bstr[] = "asefjkl";	// asefjkl
	char cstr[] = "aaabbbbbcddddeefffk"; // aaabbbbbcddddeefffk

/*
// 1.1
	if (isUnique(cstr)) {
		printf("no dup found\n");
	}
	else {
		printf("dup found\n");
	}

// 1.2
	if (isPermutation(astr, bstr)) {
		printf("permutation\n");
	}
	else {
		printf("not permutation\n");
	}

// 1.4
	if (isPalindromePermutation(bstr)) {
		printf("permutation of palindrome\n");
	}
	else {
		printf("not permutation of palindrome\n");
	}

// 1.5
	if (isOneEditAway(astr, bstr)) {
		printf("one\n");
	}
	else {
		printf("more than one\n");
	}

// 1.6
	printf("%s", string_compression(cstr));

	NODE* head = NULL;

	int a[] = { 1,1,3,2,4 };
	for (int i = 0; i < 5; i++) {
		//printList(head);
		addList(&head, a[i]);
	}
	printList(head);

// 2.1
	remove_duplication(head);
	printList(head);

	NODE* head = NULL;
	int a[] = { 11,27,32,44,51 };
	for (int i = 0; i < 5; i++) {
		addList(&head, a[i]);
	}
	printList(head);

// 2.2
	head = returnKthToLast(head, 2);
	printf("kth node:%d", head->data);	


	NODE* head = NULL;
	int a[] = { 11,27,32,44,51 };
	for (int i = 0; i < 5; i++) {
		addList(&head, a[i]);
	}
	printList(head);

// 2.3
	delete_middle_node(head->next->next);
	printList(head);

	NODE* head = NULL;
	int a[] = { 3,5,8,6,10,1,2 };
	for (int i = 0; i < 7; i++) {
		addList(&head, a[i]);
	}
	printList(head);

// 2.4
	printList(partition(head, 3));


	NODE* nodeA = NULL;
	int a[] = { 2,4,3 };
	for (int i = 0; i < 3; i++) {
		addList(&nodeA, a[i]);
	}

	NODE* nodeB = NULL;
	int b[] = { 9,7,6,4 };
	//int b[] = { 5,2,3 };
	for (int i = 0; i < 4; i++) {
		addList(&nodeB, b[i]);
	}

// 2.5
	printList(nodeA);
	printList(nodeB);
	printList(sumList(nodeA, nodeB));

// 2.6
	NODE* head = NULL;
	//int c[] = { 1,2,3,4,5 };
	int c[] = { 1,2,3,2,1 };
	for (int i = 0; i < 5; i++) {
		addList(&head, c[i]);
	}
	printList(head);
	printf("%d\n", palindrome(head));

//TODO  no cycle generated
	NODE* nodeA = NULL;
	NODE* temp;

	int a[] = { 3,5,4,3,2,1 };
	for (int i = 0; i < 6; i++) {
		temp = addList1(&nodeA, a[i]);	
	}	
	printList(nodeA);

// 2.7 intersection


// 2.8
	nodeA = (loopDetection(nodeA));

	if (nodeA) {
		printf("%d", nodeA->data);
	}
	else {
		printf("not detected\n");
	}


// 5.1
	printBin(bitInsert(0b10000000000, 0b10011, 2, 6));
	printBin(bitInsert(0b10010110001, 0b1000, 3, 6));


// 5.4																B		S
	printf("count:%d\n", bigSmallFromGiven(5));		//  5: 0101		0110	0011		
	printf("count:%d\n", bigSmallFromGiven(9));		//  9: 1001		1010	0110		
	printf("count:%d\n", bigSmallFromGiven(11));	// 11: 1011		1101	0111			
	printf("count:%d\n", bigSmallFromGiven(13948));	


// 5.6		29 (or: 11101), 15 (or: 01111) -> 2	
	printf("%d %d -> %d\n", 29, 15, conversion(29,15));
	

// 8.2
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr[i][j] = 0;
		}
	}
	arr[1][1] = -1;

	if (robotInGrid(0, 0, 0)) {
		printf("pass\n");
	}
	else {
		printf("fail\n");
	}

// 8.4
	pow_set(3);

// 8.5
	printf("%d\n", multiply(10, 20));


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

// 10.1
	int b[5] = { 1, 3,12,14,25 };
	int a[20] = { 7,11,13,14,15 };

	sorted_merge(a, b, 5, 5);

	for (int i = 0; i < 20; i++) {
		printf("%3d ", a[i]);

		if ((i+1) % 10 == 0) printf("\n");
	}

// permutation
	char s[] = "ABC";
	int n = strlen(s);
	permute(s, 0, n - 1);

// combination
	int comb[4] = { 10,20,30,40 };
	printCombination(comb, 4, 2);	

// prime
	printf("%d\n", find_prime(7));

// BST 
	//				4
	//			  /	  \		
	//			2	   7
	//		  /       /  \	
	//		1        6    8
	Node* root = NULL;

	int arr[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		//root = insertNode(root, arr[i]);
		insertNode(&root, arr[i]);
	}
	InOrder(root);		// 1 2 4 6 7 8
	printf("\n");
	levelOrder(root);	// 4 2 7 1 6 8
	printf("\n");

// minimum depth
	Node* root = NULL;

	int arr[] = { 4, 7, 2, 1, 6, 8 };
	//for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
	for (int i = 0; i < 5 ; i++) {
		insertNode(&root, arr[i]);
	}
	InOrder(root);		// 1 2 4 6 7 8

	printf("min depth:%d\n", minDepth(root));


// 4.2 minimal binary tree
	int sorted_arr[] = { 1, 2, 4, 6, 7, 8 };
	Node *root = createMinimalBST(sorted_arr, 0, 5);

	InOrder(root);		// 1 2 4 6 7 8
	printf("\n");

//4.3



//4.4
	Node* root = NULL;
	
	//int arr[] = { 4, 7, 2, 1, 6, 8 };
	int arr[] = { 1, 2, 4, 6, 7, 8 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		insertNode(&root, arr[i]);
	}
	InOrder(root);		// 1 2 4 6 7 8
	printf("\n");

	printf("balanced : %d\n", balanced_depth(root));


// 4.5 valid BST
	Node* root = NULL;
	
	int arr[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		insertNode(&root, arr[i]);
	}
	InOrder(root);		// 1 2 4 6 7 8
	printf("\n");

	//bool result = isValidBST(root, left, right);	// neetcode
	bool result = isValidBST(root);
	printf("result:%d\n", result);

//4.6
	//				4
	//			  /	  \		
	//			2	   7
	//		     \    /  \	
	//		      3  6    8
	Node* root = NULL;
	
	int arr[] = { 4, 7, 2, 3, 6, 8 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		insertNode(&root, arr[i]);
	}
	InOrder(root);		// 2 3 4 6 7 8
	printf("\n");

	levelOrder(root);	// 4 2 7 3 6 8
	printf("\n");

	printf("%d\n", inOrderSuccessor(root->left));			// 2 -> 3
	printf("%d\n", inOrderSuccessor(root));					// 4 -> 6
	printf("%d\n", inOrderSuccessor(root->left->right));	// 3 -> 4
	printf("%d\n", inOrderSuccessor(root->right->left));	// 6 -> 7
	printf("%d\n", inOrderSuccessor(root->right->right));	// 8 -> NULL

//~4.7 topology sort
//4.8 LCA
	//				4
	//			  /	  \		
	//			2	   7
	//		  /       /  \	
	//		1        6    8
	Node* root = NULL;

	int arr[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		insertNode(&root, arr[i]);
	}
	InOrder(root);		// 1 2 4 6 7 8
	printf("\n");

	// 2 & 8
	printf("LCA %d for %d & %d\n\n", lowestCommonAncestor(root, root->left, root->right->right)->key, root->left->key, root->right->right->key);

	// 2 & 1
	printf("LCA %d for %d & %d\n\n", lowestCommonAncestor(root, root->left, root->left->left)->key, root->left->key, root->left->left->key);

	// 7 & 6
	printf("LCA %d for %d & %d\n\n", lowestCommonAncestor(root, root->right, root->right->left)->key, root->right->key, root->right->left->key);

	// 6 & 8
	printf("LCA %d for %d & %d\n\n", lowestCommonAncestor(root, root->right->left, root->right->right)->key, root->right->left->key, root->right->right->key);
*/

//4.9 BST seq


//4.10 subtree


//4.11 random node


//4.12 path sum


	return 0;
}
