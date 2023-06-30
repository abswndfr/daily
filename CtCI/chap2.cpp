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
	while(pNode) {	
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
	if (node == NULL) {
		return;
	}

	NODE* curr = NULL;
	NODE* prev = NULL;

	// out loop for the reference
	while (node) {
		// inner loop for the target	
		printf("%d-", node->data);
		prev = node;
		curr = node->next;

		while (curr) {
			printf("%d", curr->data);			// prev -> temp -> temp.next
			if (node->data == curr->data) {
				// remove dup
				printf("* ", node->data);
				prev->next = curr->next;
			} else {
				// move forward
				printf("  ");
				prev = prev->next;
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
// slow & fast approach
//		  		  51-44-32-27-11-nil		: k = 2
//		 k    :   2  1  0  	  		 
//		 fast :   .  .  *  *  *  *
//		 slow :   *  *  *  X
//
// len - k approach 
// i		:  0  1  2  3  4  5  6		k = 2, len = 7
// len - k	:              *
// node     :  1  2  3  4  5
NODE* returnKthToLast(NODE* node, int k)
{
#if 1
	int len = 0;
	NODE* tmp = node;

	while (tmp) {
		len++;
		tmp = tmp->next;
	}

	for (int i = 0; i < len - k; i++) {
		node = node->next;
	}

	return node;
#else 
	NODE* fast = node;
	NODE* slow = node;

	while (fast) {  
		printf("%d: f%d s%d\n", k, fast->data, slow->data);
		if (k>0) {
			k--;			
		}
		else {
			slow = slow->next;	// this will advance ptr one more than last - k
		}

		fast = fast->next;
	}

	return slow;
#endif
}


//2.3
bool delete_middle_node(NODE* node)
{
	/*if ((node == NULL) || (node->next == NULL)) {
		return false;
	}
	return true;
	*/
	// node -> node.next -> node.next.next
	if (node && node->next) {
		node->next = node->next->next;		
		return true;
	}

	return false;
}


//2.4
// less.next can be null but less can never : 	temp = &less;	// less->next; while(temp) {}
// temp = node->next; ... node = temp; (O)   node = temp->next; (X)
NODE* partition(NODE* node, int x)
{
	NODE less;
	NODE more;
	NODE* temp = NULL;

	more.next = NULL;
	less.next = NULL;

	while (node) {
		temp = node->next;
		// node -> node.next -> node.next.next
		if (node->data < x) {
			node->next = less.next;
			less.next = node;
		}
		else {
			node->next = more.next;
			more.next = node;
		}
		node = temp;	// ->next;  !!!!!
	}

	//printList(less.next);
	//printList(more.next);

	temp = &less;
	while (temp && temp->next) {
		temp = temp->next;
	}

	temp->next = more.next;

	return less.next;
}


//2.5
// advance pointer to struct :  node = node->next;  not node++;
// dont' overwrite to head : head->data = sum;
// don't forget to advance node pointers for A & B.
NODE* sumList(NODE* nodeA, NODE* nodeB)
{
	NODE* res = NULL;
	NODE* temp;
	int sum;
	int carry = 0;	

	while (nodeA || nodeB || carry) {
		sum = 0;

		if (nodeA) {
			sum += nodeA->data;
			nodeA = nodeA->next;
		}

		if (nodeB) {
			sum += nodeB->data;
			nodeB = nodeB->next;
		}
		sum += carry;
		carry = sum / 10;

		temp = (NODE*)malloc(sizeof(NODE));
		temp->data = sum % 10; 
		temp->next = res;
		res = temp;
	}

	return res;
}


//2.6
bool palindrome(NODE* node)
{
	NODE* ptr = node;		// org list
	NODE* rHead = NULL;		// reversed list
	NODE* temp;				// temp. node

	while (ptr) {
		temp = (NODE*)malloc(sizeof(NODE));
		temp->data = ptr->data;
		temp->next = rHead;
		rHead = temp;
		ptr = ptr->next;
	}

	printList(rHead);

	while (node) {
		if (rHead->data != node->data) {
			return false;
		}
		rHead = rHead->next;
		node = node->next;
	}

	return true;
}



int main()
{
	NODE* head = NULL;

	int arr[] = { 2,1,2,3,2,4 };
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
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
	headA = returnKthToLast(headA, 2);
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
	int e[] = { 9,7,6,7 };
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
	//int f[] = { 1,2,3,4,5 };
	int f[] = { 1,2,3,2,1 };
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
