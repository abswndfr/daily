// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
char* itoa(int val, char* buf, int base) {
	int i = 30;
	for (; val && i; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i + 1];
}
*/
//1.1
bool isUnique(char* str)
{
	// if ASCII,   
	bool bitmap[128];

	// fill zeros to bitmap
	memset(bitmap, 0, sizeof(bool) * 128);

	// get string length
	int len = strlen(str);

	// test if 
	for (int i = 0; i < len; i++) {
		if (bitmap[str[i]] == true) {
			printf("%c is duplicated\n", str[i]);
			return false;
		}
		bitmap[str[i]] = true;
	}

	return true;
}

//1.2
#define ASCII_CODE_SIZE		128

bool isPermutation(char *strA, char *strB)
{
	int lenA = strlen(strA);
	int lenB = strlen(strB);

	if ((lenA == 0) || (lenB == 0) || (lenA == lenB)) {
		return false;
	}

	// ASCii
	int bitmap[ASCII_CODE_SIZE];

	// clear bitmap with zeros
	memset(bitmap, 0, sizeof(int) * ASCII_CODE_SIZE);

	// get occurrence of each character of strA
	for (int i=0; i < lenA; i++) {
		bitmap[strA[i]]++;
	}

	// compare occurrence of each character of strB to strA
	for (int i = 0; i < lenB; i++) {
		bitmap[strB[i]]--;

		if (bitmap[strB[i]] < 0) {
			return false;
		}
	}
	return true;
}

//1.4
#define ASCII_CODE_SIZE		128

bool isPalindromePermutation(char* str)
{
	int len = strlen(str);
	int occurrence[ASCII_CODE_SIZE];
	bool odd_allowed = true;

	// clear frequency table
	memset(occurrence, 0, sizeof(int) * ASCII_CODE_SIZE);

	// Counter(str)
	for (int i = 0; i < len; i++) {
		occurrence[str[i]]++;
	}

	// check the occurrences are all even or only one odd.
	for (int i = 0; i < len; i++) {
		if ((occurrence[str[i]] & 1) != 0) {
			//printf("odd found with %c ", str[i]);
			if (odd_allowed == true) {
				odd_allowed = false;
				printf("\n");
			}
			else {
				//printf("more than once\n");
				return false;
			}
		}
	}

	return true;
}

//1.5 char edit like insert, remove, or replace => same str?
#define MAX(A, B)		(A > B ? A : B)
#define ABS(A)			(A > 0 ? A : -A)

bool isOneEditAway(char* strA, char* strB) 
{
	int lenA = strlen(strA);
	int lenB = strlen(strB);
	int diff_found = false;

	if (ABS(lenA - lenB) > 1) {
		return false;
	}

	if (lenA == lenB) {
		while (*strA) {
			printf("%c %c %d", *strA, *strB, diff_found);
			if (*strA != *strB) {
				printf("!\n");
				if (diff_found) {
					return false;
				}
				diff_found = true;
			}
			else {
				printf("\n");
			}
			strA++;
			strB++;
		}
	}

	return true;
}


//1.6
char* string_compression(char* str)
{

	int len = strlen(str);
	int count;

	for (int i = 0; i < len; i++) {
		printf("%c[%d]", str[i], i);
		if (i == len - 1) {
			printf("[%d] i=%d\n", 1, i);
			break;
		}

		// repeating
		if (str[i] == str[i + 1]) {		
			count = 2;
			for (int j = i + 2; j < len; j++) {
				if (str[i] == str[j]) {
					count++;
				}
				else {
					i = j - 1;
					break;
				}
			}
			printf("[%d] i=%d\n", count, i);
		}
		else { // not repeating
			printf("[%d]\n", 1);
			count = 1;
		}

	}

	return str;
}

//1.7 
// cw : transpose -> swap columns
// ccw: transpose -> reverse columns
/*
void rotate(vector<vector<int>>& matrix) {
	int n = matrix.size();
	int m = matrix[0].size();
	vector<vector<int>> temp(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			swap(matrix[i][j], matrix[j][i]);
		}
	}
	for (int i = 0; i < n; i++) {
		reverse(matrix[i].begin(), matrix[i].end());
	}
}*/

//1.8
/*1. Check if the first row and first column have any zeros, and set variables rowHasZero and columnHasZero.[We'll nullify the first row and first column later, if necessary.)
  2. Iterate through the rest of the matrix, setting matrix[i][0] and matri x[0][j] to zero whenever there's a zero in matri x [i] [j].
  3. Iterate through rest of matrix, nullifying row i if there's a zero in matri x [i ] [0] .
  4. Iterate through rest of matrix, nullifying column j if there's a zero inmatrix[0 ] [ j] ,
  5. Nullify the first row and first column, if necessary(based on values from Step 1).*/
bool zero_matrix(int** matrix, int len)
{
	bool firstlow, firstcol;
	int i, j;
	firstlow = firstcol = false;

	// 1
	for (i = 0; i < len; i++)
		if (matrix[i][0] == 0) { firstlow = true; break; }

	for (i = 0; i < len; i++)
		if (matrix[0][i] == 0) { firstcol = true; break; }
	// 2
	for (i = 1; i < len; i++)
	{
		for (j = 1; j < len; j++)
		{
			if (matrix[i][j] == 0)
			{
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}
	// 4
	for (i = 0; i < len; i++)
		if (matrix[0][i] == 0)
			for (j = 1; j < len; j++)
				matrix[j][i] = 0;
	// 3
	for (i = 0; i < len; i++)
		if (matrix[i][0] == 0)
			for (j = 1; j < len; j++)
				matrix[i][j] = 0;
	// 5
	if (firstlow)
		for (i = 0; i < len; i++)
			matrix[0][i] = 0;
	// 5
	if (firstcol)
		for (i = 0; i < len; i++)
			matrix[i][0] = 0;
	return true;
}

//1.9
bool string_rotation(char* stra, char* strb)
{
	//new strstr = stra+stra
	//isSubstring() is provided
	//if(isSubstring(strstr,strb)) => the result is what we want
	return true;
}

typedef struct _node {
	int data;
	struct _node* next;
	//bool visited;
} NODE;

void addList(NODE** pHead, int data)
{
	NODE* node = (NODE *)malloc(sizeof(NODE));

	if (node) {
		node->data = data;
		node->next = *pHead;
		*pHead = node;
	}
	else {
		exit(1);
	}
}

NODE* addList1(NODE** pHead, int data)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));

	if (node) {
		node->data = data;
		node->next = *pHead;
		*pHead = node;
	}
	else {
		exit(1);
	}
	return node;
}


void printList(NODE* pNode)
{
	while (pNode != NULL) {
		printf("%d->", pNode->data);
		pNode = pNode->next;
	}
	printf("NULL\n");
}



//2.1
void remove_duplication(NODE* node)
{
	NODE* prev;;
	NODE* temp;

	while (node) {
		prev = node;
		temp = node->next;
		while (temp) {
			//printf("%p %d %p %d\n", node, node->data, temp, temp->data);
			if (node->data == temp->data) {
				prev->next = temp->next;
				temp = temp->next;
			}
			else {
				prev = prev->next;
				temp = temp->next;
			}
		}
		//printf("\n");
		node = node->next;
	}
}

//2.2
void returnKthToLast(NODE* node, int k)
{
	NODE* temp = node;
	int len = 0;

	if (node == NULL) return;

	while (temp) {
		temp = temp->next;
		len++;
	}

	if (k + 1 > len) {
		printf("can't reach kth node\n");
	}

	temp = node;
	for (int i = 0; i < k; i++) {
		temp = temp->next;
	}

	printf("node at index %d is %d\n", k, temp->data);
}

//2.3
bool delete_middle_node(NODE* node)
{
	if ((node == NULL) || (node->next == NULL)) {
		return false;
	}

	node->data = node->next->data;
	node->next = node->next->next;

	return true;
}

//2.4
NODE* partition(NODE* node, int x)
{
	NODE less;
	NODE more;
	NODE* tmp;

	less.next = NULL;
	more.next = NULL;

	while (node) {
		tmp = node->next;

		// compare to x and move to less if less
		if (node->data < x) {
			node->next = less.next;
			less.next = node;
		}
		else { // move to more if more
			node->next = more.next;
			more.next = node;
		}

		node = tmp;
	}

	// merge less & more
	/*printf("\nmore: ");
	printList(more.next);
	printf("less: ");
	printList(less.next);*/

	tmp = less.next;
	while (tmp->next) {
		tmp = tmp->next;
	}
	tmp->next = more.next;

	//printList(less.next);

	return less.next;
}

//2.5
NODE* sumList(NODE* nodeA, NODE* nodeB)
{
	NODE* ptr = (NODE*)malloc(sizeof(NODE));
	NODE* tmp = ptr;

	int carry = 0;

	while ((nodeA != NULL) || (nodeB != NULL) || (carry > 0)) {
		int sum = 0;

		if(nodeA) printf("nodeA : %d ", nodeA->data);
		if(nodeB) printf("nodeB : %d ", nodeB->data);

		if (nodeA != NULL) {
			sum += nodeA->data;
			nodeA = nodeA->next;
		}

		if (nodeB != NULL) {
			sum += nodeB->data;
			nodeB = nodeB->next;
		}

		sum += carry;
		carry = sum / 10;

		printf(" %d\n", carry);

		NODE* New = (NODE*)malloc(sizeof(NODE));
		New->data = sum % 10;
		New->next = NULL;

		tmp->next = New;
		tmp = tmp->next;
	}

	return ptr->next;
}

//2.6
bool palindrome(NODE* node)
{
	NODE* head = node;
	NODE* reverse = (NODE*)malloc(sizeof(NODE));
	NODE* tmp;

	reverse->next = NULL;

/*
	head     -> n1 -> n2 -> n3 -> null

	revserse -> n1 -> null
	revserse -> n2 -> n1 -> null
	revserse -> n3 -> n2 -> n1 -> null
*/
	while (node) {
		NODE* New = (NODE*)malloc(sizeof(NODE));
		New->data = node->data;
		New->next = reverse->next;

		reverse->next = New;
		node = node->next;
	}

	//printList(reverse->next);
	reverse = reverse->next;
	//printList(reverse);

	node = head;

	while (node) {
		//printf("%d %d\n", node->data, reverse->data);
		if (node->data != reverse->data) {
			return false;
		}
		node = node->next;
		reverse = reverse->next;
	}

	return true;
}

//2.7
bool intersection(NODE* nodea, NODE* nodeb)
{
	//1. if we know lenght then can find start node with same length => compare node till finding same node.
	//2. reverse each nodes and compare from first node whether same or not.
	return true;
}

//2.8
NODE* loopDetection(NODE* node)
{
	NODE* fast = node;
	NODE* slow = node;
	bool detected = false;

	while (fast && slow) {
		if (fast->next == NULL) break;
		if (fast->next->next == NULL) break;

		slow = slow->next;
		fast = fast->next->next;

		if (fast->data == slow->data) {
			detected = true;
			break;
		}
	}

	if (!detected) {
		return NULL;
	}

	slow = node;

	while (slow->data != fast->data) {
		slow = slow->next;
		fast = fast->next;
	}

	return slow;
}

//tree struct
typedef struct _tree {
	int data;
	struct _tree* left;
	struct _tree* right;
	struct _tree* next;
}Tree;

//4.2
Tree* minimal_tree(int* arry, int s, int e)
{
	int mid;
	Tree* root;
	if (s < e) return NULL;
	mid = (s + e) / 2;
	root = (Tree*)malloc(sizeof(Tree));
	root->data = arry[mid];
	root->left = minimal_tree(arry, s, mid - 1);
	root->right = minimal_tree(arry, mid + 1, e);
	return root;
}


//4.3
#define MAX 128
typedef struct _treelist
{
	Tree* t;
	int dep;
	struct _treelist* next;
} TreeList;

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
}

//4.4
int max_depth(Tree* t, int depth)
{
	int left, right;
	if (t == NULL) return depth - 1;
	left = max_depth(t->left, depth + 1);
	right = max_depth(t->right, depth + 1);
	return left > right ? left : right;
}

bool balanced_depth(Tree* t)
{
	int depl, depr;
	if (t == NULL) true;
	depl = max_depth(t->left, 1);
	depr = max_depth(t->right, 1);
	if (abs(depl - depr) > 1) return false;
	if (!balanced_depth(t->left)) return false;
	if (!balanced_depth(t->right)) return false;
	return true;
}

//4.5
bool valid_btree(Tree* t)
{
	if (t == NULL) return true;
	
	if (t->left)
	{
		if (t->left->data > t->data) return false;
	}
	
	if (t->right)
	{
		if (t->right->data < t->data) return false;
	}
	
	if (!valid_btree(t->left)) return false;
	if (!valid_btree(t->right)) return false;
	return true;
}

//4.10 Check Subtree
//T1, T2, T2 is sub of T2??
//1. T1==T2 then T1.left==T2.left && T1.right==T2.right
//2. T1!=T2 then T1.left==T2 or T1.right T2 => one of them matching then goto #1



void printBin(unsigned int a)
{
	for (int i = 31; i >= 0; i--)
		printf("%d", (a & (1 << i)) >> i);
	printf("  ");
}

int countOnes(unsigned int a)
{
	int count = 0;

	while (a) {
		//count += a & 1;
		//a = a >> 1;
		a = a & (a - 1);
		count++;
	}

	return count;
}

//5.1
unsigned int bitInsert(unsigned int a, unsigned int b, int i, int j)
{
	// 6 : 100_0000			1<<6+1 - 1 = 111_1111 
	// 2 :      100			1<<2   - 1 =       11 
	// ^                                 111_1100
	// ~								 11111000_0011	
	int mask = ~(((1 << (j + 1)) - 1) ^ ((1 << i) - 1));
	a = a& mask;
	a |= b<<i;

	printBin(a);

	return a;
}

//5.4
unsigned int bigSmallFromGiven(unsigned int a)
{
	int n = countOnes(a);

	int big = 0;
	int small = 0;

	bool firstOneFound = false;

	//-------------------- biggest -------------------- 
	// step 1 : set right most non trailing zero
	int bit = 1;	// 2^0
	big = a;
	while (bit < (sizeof(int) * 8)) {
		// find 1st one
		if (big & bit) {
			firstOneFound = true;
		}

		// find 1st zero after 1s and set
		if (firstOneFound) {
			if (!(big & bit)) {
				big |= bit;
				break;
			}
		}

		bit = bit << 1;
	}

	// step 2 : clear all 1s after the new 1.
	int right = big & (bit - 1);
	big = big ^ right;

	// step 3 : add all cleared 1s except one to the right most
	int right_n = countOnes(right) - 1;
	right = 0;
	for (int i = 0; i < right_n; i++) {
		right += 1 << i;
	}
	big = big + right;

	//-------------------- smallest --------------------
	for (int i = 0; i < n; i++) {
		small += 1 << i;
	}
	printf("a:%d -> big:%d small:%d ", a, big, small);

	return n;
}

//5.6
int conversion(int a, int b)
{
	int t, count;
	t = a ^ b;
	count = 0;

	while (t)
	{
		t = t & (t - 1);	
		count++;
	}

	return count;
}

//8.1
int triple_step(int n)
{
	if (n < 0) return 0;
	if (n == 0) return 1;
	return triple_step(n - 1) + triple_step(n - 2) + triple_step(n - 3);
}

int triple_steps(int n)
{
	if (n < 1) return 0;
	if (n == 1) return 1;
	if (n == 2) return 2;
	if (n == 3) return 4;
	return triple_step(n - 1) + triple_step(n - 2) + triple_step(n - 3);
}


//8.2
int arr[3][3];

//-1:block, 0:can move, >1 :visited
bool robotInGrid(int row, int col, int step)
{
	// off limit
	if (!(row < 3) || !(col < 3)) {
		printf("%d %d: fail\n", row, col);
		return false;
	}

	// obstacle
	if (arr[row][col] == -1) {
		printf("%d %d: fail\n", row, col);
		return false;
	}

	// already visited
	if (arr[row][col] > 0)
	{
		if (arr[row][col] > step) arr[row][col] = step;
		printf("%d %d: pass\n", row, col);
		return true;
	}

	if (arr[row][col] == 0) arr[row][col] = step;

	//todo : check range whether row, col can be exceed or not
	if (!robotInGrid(row + 1, col, step + 1)) {
		printf("%d %d: fail\n", row, col);
		//return false;
	}

	if (!robotInGrid(row, col + 1, step + 1)) {
		printf("%d %d: fail\n", row, col);
		//return false;
	}

	return true;
}

void printArray(int* data, int r)
{
	for (int j = 0; j < r; j++)
		printf("%d ", data[j]);
	printf("\n");
}

//8.4
//int list[10] = { -1, };
//int idx = 0;
#include <math.h>
void pow_set(int set_size)
{
	unsigned int pow_set_size = pow(2, set_size);
	int counter, j;

	for (counter = 0; counter < pow_set_size; counter++) {
		printf("{");
		for (j = 0; j < set_size; j++) {
			if (counter & (1 << j)) {
				printf("%d", j+1);
			}
		}
		printf("}\n");
	}
}

#if 0
void pow_set(int n)

{
	int i, j;
	printArray(list, 10);

	if (n < 0) return;

	if (n == 0) {
		list[idx++] = 0;
		return;
	}

	pow_set(n - 1);

	i = idx;

	for (j = 0; j < idx; j++, i++)
	{
		list[i] = list[j] + n;
	}
	idx = j;
}
#endif
/*
start:0  index:0     						... 0 0 0 0					10 0 0 0

	start:1  index:1 						...10 0 0 0					10 20 0 0

		start:2  index:2     				...10 20 0 0	10 20		10 30 0 0
		start:3  index:2     				...10 30 0 0	10 30		10 40 0 0
		start:4  index:2 					...10 40 0 0	10 40		20 40 0 0

	start:2  index:1 						...20 40 0 0				20 30 0 0

		start:3  index:2     				...20 30 0 0	20 30		20 40 0 0
		start:4  index:2     				...20 40 0 0	20 40		30 40 0 0

	start:3  index:1     					...30 40 0 0				30 40 0 0

		start:4  index:2     				...30 40 0 0	30 40
*/
void combinationUtil(int *arr, int *data, int start, int end, int index, int r)
{
	//printf("start:%d index:%d     ...", start, index);
	//printArray(data, 4);

	// base case
	if (index == r) {
		printArray(data, r);
		return;
	}

	//for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
	for (int i = start; i <= end; i++) {
		data[index] = arr[i];
		//printArray(data, 4);
		combinationUtil(arr, data, i + 1, end, index + 1, r);
	}
}

void printCombination(int* arr, int n, int r)
{
	int data[10];	// subarray

	for (int j = 0; j < 10; j++)
		data[j] = 0;

	combinationUtil(arr, data, 0, n - 1, 0, r);
}

void swap(char* x, char* y)
{
	char temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

/*
B-l:0 i:0 ABC								0		A
	B-l:1 i:1 ABC							1,1			AB
	 -l:2 i:2_________________________ABC					ABC
	A-l:1 i:1 ABC

	B-l:1 i:2 ACB							1,2			AC
	 -l:2 i:2_________________________ACB					ACB
	A-l:1 i:2 ABC
A-l:0 i:0 ABC

B-l:0 i:1 BAC								1		B
	B-l:1 i:1 BAC							1,1			BA
	 -l:2 i:2_________________________BAC					BAC
	A-l:1 i:1 BAC

	B-l:1 i:2 BCA							1,2			BC
	 -l:2 i:2_________________________BCA					BCA
	A-l:1 i:2 BAC
A-l:0 i:1 ABC

B-l:0 i:2 CBA								2		C
	B-l:1 i:1 CBA							1,1			CB
	 -l:2 i:2_________________________CBA					CBA
	A-l:1 i:1 CBA
	B-l:1 i:2 CAB							1,2			CA
	 -l:2 i:2_________________________CAB					CAB
	A-l:1 i:2 CBA
A-l:0 i:2 ABC
*/
void permute(char* a, int l, int r)
{
	int i;
	if (l == r) {
		printf(" -l:%d i:%d_________________________%s\n", l, r, a);
	}
	else
	{
		for (i = l; i <= r; i++)
		{
			swap((a + l), (a + i));	printf("B-l:%d i:%d %s\n", l, i, a);
			permute(a, l + 1, r);
			swap((a + l), (a + i)); printf("A-l:%d i:%d %s\n", l, i, a);
		}
	}
}

//8.5
int multiply(int a, int b)
{
	/*
		int product = 0;
		while (b > 0)
		{
			product = product + a;
			b--;
		}
		return product;
	*/
	int t;
	if (a < b)
	{
		t = b;
		b = a;
		a = t;
	}
	while (b)
	{
		if (b & 1)
		{
			t = a + a;
			a = t;
		}
		b >> 1;
	}
	return a;
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
*/
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
}

//prime
bool prime(int n)
{
	int i;
	if (n < 2) false;
	for (i = 2; i < n / 2; i++)
	{
		if (n % i == 0) return false;
	}
	return true;
}

bool find_prime(int n)
{
	char* list;
	int i, j;

	if (n < 2) false;

	list = (char*)malloc(sizeof(int) * (n + 1));

	memset(list, 1, sizeof(int) * (n + 1));

	for (i = 2; i * i <= n; i++) {

		if (list[i]) {

			for (j = i; j <= n; j += i) {
				list[j] = false;
			}
		}
	}
	//if list[i]==true => i is prime
	free(list);
	return true;
}

//min depth
int min_depth(Tree* node, int depth)
{
	int left, right;
	if (node == NULL) return depth - 1;
	left = min_depth(node->left, depth + 1);
	right = min_depth(node->right, depth + 1);
	return (left < right) ? left : right;
}

//memcpy
char* mymemcpy(char* src, char* desc, int size)
{
	char* tmps, * tmpd;
	if (desc<src || desc>(src + size))
	{
		memcpy(src, desc, size);
	}
	else
	{
		tmps = src + size;
		tmpd = desc + size;
		while (tmps >= src && tmpd >= desc)
		{
			*tmpd-- = *tmps--;
		}
	}
	return desc;
}


int main()
{
	char astr[] = "asdfjkl";
	char bstr[] = "asefjkk";	// asefjkl
	char cstr[] = "aaabbbbbcddddeefffk"; // aaabbbbbcddddeefffk

	/*
	if (isUnique(cstr)) {
		printf("no dup found\n");
	}
	else {
		printf("dup found\n");
	}

	if (isPermutation(astr, bstr)) {
		printf("permutation\n");
	}
	else {
		printf("not permutation\n");
	}

	if (isPalindromePermutation(bstr)) {
		printf("permutation of palindrome\n");
	}
	else {
		printf("not permutation of palindrome\n");
	}

	if (isOneEditAway(astr, bstr)) {
		printf("ok\n");
	}
	else {
		printf("nok\n");
	}

	printf("%s", string_compression(cstr));

	NODE *head = NULL;
	int a[] = { 1,1,3,2,4 };
	for (int i = 0; i < 5; i++) {
		//printList(head);
		addList(&head, a[i]);
	}
	printList(head);

	remove_duplication(head);
	printList(head);


	NODE* head = NULL;
	int a[] = { 11,27,32,44,51 };
	for (int i = 0; i < 5; i++) {
		addList(&head, a[i]);
	}
	printList(head);

	returnKthToLast(head, 2);

	NODE* head = NULL;
	int a[] = { 11,27,32,44,51 };
	for (int i = 0; i < 5; i++) {
		addList(&head, a[i]);
	}
	printList(head);

	delete_middle_node(head->next->next->next);
	printList(head);

	NODE* head = NULL;
	int a[] = { 3,5,8,6,10,1,2 };
	for (int i = 0; i < 7; i++) {
		addList(&head, a[i]);
	}
	printList(head);

	partition(head, 5);


	NODE* nodeA = NULL;
	int a[] = { 2,4,3 };
	for (int i = 0; i < 3; i++) {
		addList(&nodeA, a[i]);
	}

	NODE* nodeB = NULL;
	int b[] = { 9,7,6,4 };
	for (int i = 0; i < 4; i++) {
		addList(&nodeB, b[i]);
	}

	printList(nodeA);
	printList(nodeB);
	printList(sumList(nodeA, nodeB));

	NODE* nodeA = NULL;
	int a[] = { 1,2,3,4,5 };
	//int a[] = { 1,2,3,2,1 };
	for (int i = 0; i < 5; i++) {
		addList(&nodeA, a[i]);
	}
	printList(nodeA);
	printf("%d\n", palindrome(nodeA));

//TODO  no cycle generated
	NODE* nodeA = NULL;
	NODE* temp;

	int a[] = { 3,5,4,3,2,1 };
	for (int i = 0; i < 6; i++) {
		temp = addList1(&nodeA, a[i]);	
	}	
	printList(nodeA);

	nodeA = (loopDetection(nodeA));

	if (nodeA) {
		printf("%d", nodeA->data);
	}
	else {
		printf("not detected\n");
	}

	printf("%d\n", bitInsert(0b10000000000, 0b10011, 2, 6));
	printf("%d\n", bitInsert(0b10010110001, 0b1000, 3, 6));

	printf("count:%d\n", bigSmallFromGiven(5));	
	printf("count:%d\n", bigSmallFromGiven(11));	

	printf("%d\n", multiply(10, 20));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr[i][j] = 0;
		}
	}
	arr[1][1] = -1;
*/

if (robotInGrid(0, 0, 0)) {
		printf("pass\n");
	}
	else {
		printf("fail\n");
	}

	/*
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	int a[20] = { 1, 3,12,14,25 }; 
	int b[5]  = { 7,11,13,14,15 };

	sorted_merge(a, b, 5, 5);

	for (int i = 0; i < 20; i++) {
		printf("%d ", a[i]);

		if ((i+1) % 10 == 0) printf("\n");
	}

	int comb[4] = { 10,20,30,40 };
	printCombination(comb, 4, 2);	

	char s[] = "ABC";
	int n = strlen(s);
	permute(s, 0, n - 1);

	pow_set(3);
*/


	//printf("%d\n", find_prime(7));

	return 0;
}

