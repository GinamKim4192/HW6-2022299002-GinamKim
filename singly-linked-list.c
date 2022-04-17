#include<stdio.h>
#include<stdlib.h>


/*자기참조 구조체 Node 초기화
  key는 해당 Node의 값이며,
  link는 해당 Node의 다음 주소를 가르킨다.
  (다음 주소는 물리적으로 연결된 것이 아닌,
  논리적으로 연결된 주소이다.)*/
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

/*단일연결리스트 시작 구조체 초기화*/
typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	printf("[----- [김기남]  [2022299002] -----]\n");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode구조체를 동적할당 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	// node하나를 동적할당. 해당 node에 key값 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	/*headNode가 NULL일 경우,
	연결리스트가 아직 만들어지지 않을 것으로
	headNode의 연결로 key값을 가진 node를 연결함.*/
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	// node하나를 동적할당함.
	// 해당 node에 key값을 할당.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	/* headNode의 연결된 값이 NULL일 경우,
	 아직 연결리스트가 생성된것이 아니므로 신규 node가
	 처음이자 마지막 노드가 되는것임.
	*/ 
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	/*반복문을 돌며 NULL값이 나올때까지 link를 따라감.
	  NULL값이 나온 노드가 연결리스트의 마지막 노드임*/
	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	// listNode 하나를 동적할당.
	// 해당 listNode에 key값을 할당.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	/*새로운 node는 headNode의 link를 할당받으며
	  headNode는 새로운 node로 연결.*/
	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	/* headNode가 NULL값인 경우,
	생성된 연결리스트가 없으므로 종료*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	/*headNode가 NULL값인 경우,
 	  연결리스트가 없는 것이므로 종료.*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* headNode부터 link가 NULL값이 될때까지 접근함
	   NULL값을 가진 노드가 마지막 노드임. */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* 반복문에서 최종할당된 마지막 위치를 메모리할당을 해제하며
	   그 이전 노드의 link를 NULL로 변경함. */
	trail->link = NULL;
	free(n);

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/*headNode가 NULL값인 경우,
 	  연결리스트가 없는 것이므로 종료.*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	/*headNode에 기존 연결된 노드를 대신
	  기존 연결된 노드의 다음 노드를 headNode에 할당함.*/
	listNode* n = h->first;

	h->first = n->link;
	/*연결이 끊긴 노드 메모리할당해제*/
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	/*headNode가 NULL값인 경우,
 	  연결리스트가 없는 것이므로 종료.*/
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;
	/* n, trail, middle의 값을 서로 할당해주며,
	   n(맨처음 headNode의 link로 연결된)이 NULL이 될때까지 반복하며
	   역순으로 재배치함.*/
	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

