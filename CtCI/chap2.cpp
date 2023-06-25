#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
//                  () [] -> . 
//                  ! ~ ++ -- + - * (type) sizeof)
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



int main()
{
	NODE* head = NULL;

	int arr[] = { 1,1,3,2,4 };
	for (int i = 0; i < 5; i++) {
		//printList(head);
		addList(&head, arr[i]);
	}
	printList(head);

// 2.1
	remove_duplication(head);
	printList(head);

	NODE* headA = NULL;
	int a[] = { 11,27,32,44,51 };
	for (int i = 0; i < 5; i++) {
		addList(&headA, a[i]);
	}
	printList(headA);

// 2.2
	headA = returnKthToLast(headA, 2);
	printf("2.2 kth node:%d", headA->data);	


// 2.3
	NODE* headB = NULL;
	int b[] = { 11,27,32,44,51 };
	for (int i = 0; i < 5; i++) {
		addList(&headB, b[i]);
	}
	printList(headB);


	delete_middle_node(head->next->next);
	printList(head);

// 2.4
	NODE* headC = NULL;
	int c[] = { 3,5,8,6,10,1,2 };
	for (int i = 0; i < 7; i++) {
		addList(&headC, c[i]);
	}
	printList(headC);


	printf("2.4 partition   ");
	printList(partition(head, 3));


// 2.5
	NODE* nodeD = NULL;
	int d[] = { 2,4,3 };
	for (int i = 0; i < 3; i++) {
		addList(&nodeD, d[i]);
	}

	NODE* nodeE = NULL;
	int e[] = { 9,7,6,4 };
	//int b[] = { 5,2,3 };
	for (int i = 0; i < 4; i++) {
		addList(&nodeE, e[i]);
	}


	printList(nodeD);
	printList(nodeE);
	printf("2.5 sumlist   ");
	printList(sumList(nodeD, nodeE));

// 2.6
	NODE* headF = NULL;
	//int c[] = { 1,2,3,4,5 };
	int f[] = { 1,2,3,2,1 };
	for (int i = 0; i < 5; i++) {
		addList(&headF, f[i]);
	}
	printList(headF);
	printf("2.6 palindrome: %d\n", palindrome(headF));

/*
//TODO  no cycle generated
	NODE* nodeG = NULL;
	NODE* temp;

	int a[] = { 3,5,4,3,2,1 };
	for (int i = 0; i < 6; i++) {
		temp = addList1(&nodeG, a[i]);
	}	
	printList(nodeA);

// 2.7 intersection


// 2.8
	NODE* headF = NULL;
	nodeH = (loopDetection(nodeH));

	if (nodeH) {
		printf("%d", nodeH->data);
	}
	else {
		printf("not detected\n");
	}
*/
	return 0;
}
