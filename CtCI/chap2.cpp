#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _node {
	int data;
	struct _node* next;
} NODE;


void addList(NODE** pHead, int data)
{
	NODE* node;

	node = (NODE*)malloc(sizeof(NODE));
	node->data = data;
	node->next = *pHead;
	*pHead = node;
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
	NODE* prev;
	NODE* curr;

	while (node) {
		prev = node;
		curr = node->next;

		while (curr) {
			if (node->data == curr->data) {
				prev->next = curr->next;
			}
			else {
				prev = curr;
			}
			curr = curr->next;
		}
		node = node->next;
	}
}

//2.2
// 0 base or 1 base ? (is 1st to last a[n-1] or a[n-2] ?)
// missing index++;
NODE* returnKthToLast(NODE* node, int k)
{
	int count = 0;
	NODE *slow = node;
	while (node && (count != k)) {node = node->next; count++; }
	while (node) { node = node->next; slow = slow->next; }
	return slow;
}


//2.3
bool delete_middle_node(NODE* node)
{
	NODE* temp;

	if (node->next == NULL) {
		return false;	
	}
	else {
		node->data = node->next->data;
		node->next = node->next->next;
	}

	return true;
}

//2.4
// less.next can be null but less can never : 	temp = &less;	// less->next; while(temp) {}
NODE* partition(NODE* node, int x)
{
	NODE less;
	NODE more;
	NODE *temp;

	less.next = NULL;
	more.next = NULL;

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

	temp = &less;
	while (temp) {
		if (temp->next) {
			temp = temp->next;
		}
		else {
			temp->next = more.next;
			break;
		}
	}

	return less.next;
}

//2.5
// advance pointer to struct :  node = node->next;  not node++;
// dont' overwrite to head : head->data = sum;
NODE* sumList(NODE* nodeA, NODE* nodeB)
{

	NODE* node;
	NODE* head = NULL;

	int carry = 0;
	int sum;

	while (nodeA || nodeB || carry) {
		sum = 0;

		//printf("%d + %d (%d) = ", nodeA->data, nodeB->data, carry);

		node = (NODE*)malloc(sizeof(NODE));
		node->next = head;
		head = node;

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
		sum %= 10;

		node->data = sum;
		//printList(head);
	}

	//  h
	//  1 -> 2 -> 3 -> null
	//  3 -> 2 -> 1 -> null
	//  n
	printList(head);

	//NODE* node;
	NODE* rev = NULL;

	while (head) {
		node = head->next;
		head->next = rev;
		rev = head;
		head = node;
	}

	return rev;
}

//2.6
bool palindrome(NODE* node)
{
	NODE* rev = NULL;
	NODE* temp;
	NODE* org = node;
/*
	while (node) {
		temp = node->next;
		node->next = rev;
		rev = node;
		node = temp;
	}*/

	while (node) {
		temp = (NODE*)malloc(sizeof(NODE));
		temp->data = node->data;
		temp->next = rev;
		rev = temp;	
		node = node->next;
	}

	//printList(org);
	printList(rev);

	while (org) {
		if (org->data != rev->data) {
			return false;
		}
		org = org->next;
		rev = rev->next;
	}

	return true;
}



int main()
{
	NODE* head = NULL;

	int arr[] = { 2,1,2,3,2,4 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		//printList(head);
		addList(&head, arr[i]);
	}
	printList(head);

	// 2.1
	printf("\n2.1\n");
	remove_duplication(head);
	printList(head);

	printf("\n2.2\n");
	NODE* headA = NULL;
	int a[] = { 11,27,32,44,51 };
	for (int i = 0; i < 5; i++) {
		addList(&headA, a[i]);
	}
	printList(headA);

	// 2.2
	int k = 3;
	headA = returnKthToLast(headA, k);
	printf("kth(%d) node:%d\n", k, headA->data);


	// 2.3
	printf("\n2.3\n");
	NODE* headB = NULL;
	int b[] = { 11,27,32,44,51 };
	for (int i = 0; i < 5; i++) {
		addList(&headB, b[i]);
	}
	printList(headB);

	delete_middle_node(headB->next->next);
	printList(headB);

	// 2.4
	printf("\n2.4\n");
	NODE* headC = NULL;
	int c[] = { 3,5,8,6,10,1,2 };
	for (int i = 0; i < 7; i++) {
		addList(&headC, c[i]);
	}
	printList(headC);
	printList(partition(headC, 3));

	// 2.5
	printf("\n2.5\n");
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
	printf("\nsumlist \n");
	printList(sumList(nodeD, nodeE));

	// 2.6
	printf("\n2.6\n");
	NODE* headF = NULL;
	int f[] = { 1,2,3,4,5 };
	//int f[] = { 1,2,3,2,1 };
	for (int i = 0; i < 5; i++) {
		addList(&headF, f[i]);
	}
	printList(headF);
	printf("palindrome: %d\n", palindrome(headF));

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
