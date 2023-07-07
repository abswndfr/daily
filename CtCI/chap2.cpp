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
// prev should point to one node behind !
void remove_duplication(NODE* node)
{
	NODE* prev;
	NODE* curr;

	while (node) {
		prev = node;
		curr = node->next;
		while (curr) {		
			if(node->data == curr->data) {
				prev->next = curr->next;
			}
			else {
				prev = prev->next;
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
	NODE* head = node;
	int len = 0;
	int count = 0;

	while (node) {
		node = node->next;
		len++;
	}

	while (head) {
		if (count == len - k) {
			break;
		}
		head = head->next;
		count++;
	}

	return head;
}

//2.3
// X -> B -> C  => B -> C
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
	NODE* head = node;
	NODE* temp;

	less.next = NULL;
	more.next = NULL;

	while (head) {
		temp = head->next;
		if (head->data < x) {
			head->next = less.next;
			less.next = head;		
		}
		else {
			head->next = more.next;
			more.next = head;
		}
		head = temp;
	}

	printList(less.next);
	printList(more.next);

	temp = &less;
	while (temp->next) {
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
	NODE* res = NULL;
	NODE* temp;
	int carry = 0;
	int sum;

	while (nodeA || nodeB || carry) {
		sum = 0;
		temp = (NODE*)malloc(sizeof(NODE));
		temp->next = res;
		res = temp;

		if (nodeA) {
			sum = nodeA->data;
			nodeA = nodeA->next;
		}

		if (nodeB) {
			sum += nodeB->data;
			nodeB = nodeB->next;
		}
	
		sum += carry;

		temp->data = sum % 10;
		carry = sum / 10;
	}

	return res;
}

//2.6
bool palindrome(NODE* node)
{
	NODE* rev = NULL;
	NODE* head = node;

	while (head) {
		NODE* temp = (NODE*)malloc(sizeof(NODE));
		temp->data = head->data;
		temp->next = rev;
		rev = temp;
		head = head->next;
	}
	
	printList(rev);
	printList(node);

	while (node) {
		if (node->data != rev->data) {
			return false;
		}
		node = node->next;
		rev = rev->next;
	}

	return true;
}



int main()
{
	NODE* head = NULL;

	printf("\n2.1\n");
	int arr[] = { 2,1,2,3,2,4 };
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
		//printList(head);
		addList(&head, arr[i]);
	}
	printList(head);

	// 2.1
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
	headA = returnKthToLast(headA, 3);
	printf("kth node:%d\n", headA->data);


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
	printf("\nsumlist   ");
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
