
/*Za dvije sortirane liste L1 i L2(mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna :
a) L1unijaL2,
b) L1presjekL2.
Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.
*/

#define _CRT_SECURE_NO_WARNINGS
#define maxFn (100);
#include<stdio.h>
#include<stdlib.h>

typedef struct _node {
struct _node* nextNode;
int elem;
}NODE;

typedef struct _node* Pos;

Pos createList();
Pos allocateNode();
int addBeforeNode(Pos, Pos, Pos);
int addAfterNode(Pos, Pos);
Pos readListFromConsole();
Pos readListFromFile(char*);
int addToList(Pos,Pos);
int addToListEnd(Pos,Pos);
void printList(Pos);
Pos listUnion(Pos, Pos);
Pos listIntersection(Pos, Pos);
void deleteList(Pos);

int main() {
Pos lista = readListFromFile("elem.txt");
printList(lista);
Pos lista2 = readListFromFile("elem2.txt");
printList(lista2);
printf("union\n");
Pos list3 = listUnion(lista, lista2);
printList(list3);
Pos list4 = listIntersection(lista, lista2);
printf("presjek\n");
printList(list4);
system("pause");
return 0;
}
Pos createList() {
Pos head = NULL;
head = allocateNode();
if (head != NULL) {
return head;
}
printf("malloc failed");
return NULL;
}
Pos allocateNode() {
Pos node = NULL;
node = (Pos)malloc(sizeof(NODE));
if (node != NULL) {
node->nextNode = NULL;
return node;
}
return NULL;
}
Pos readListFromConsole() {
Pos node = NULL;
Pos list = createList();
int num = 0;
int ret = 0;
int term=0;
while (term != -1) {
printf("type in a nubmer, -1 leaves\n");
ret=scanf("%d", &num);
if (num == -1)break;
if (ret == 1) {
node = allocateNode();
if (node == NULL)return NULL;
node->elem = num;
addToList(list,node);
}
else {
printf("error on input");
}
}
return list;
}
Pos readListFromFile(char* fileName)
{
int ret = 0;
int tempElem = 0;
Pos list = createList();
FILE* fp = NULL;
fp = fopen(fileName, "r");
if (fp == NULL)return NULL;
while (ret != -1) {
ret = fscanf(fp, "%d", &tempElem);
if (ret == 1) {
Pos node = allocateNode();
node->elem = tempElem;
addToList(list, node);
}
if (ret == 0) {
printf("ret is 0\n");
}
}
fclose(fp);
return list;
}
int addToList(Pos head,Pos node) {
	Pos nodeptr = head->nextNode;
	if (!head || !node)return -1;
	while (nodeptr) {
		if (nodeptr->elem < node->elem) {
			nodeptr = nodeptr->nextNode;
		}
		else if (nodeptr->elem == node->elem) {
			return 1;
	}
		else {
			addBeforeNode(head, nodeptr, node);
			return 0;
		}
	}
	addToListEnd(head, node);
	return 0;
}
int addToListEnd(Pos head,Pos node)
{
if (!head||!node)return -1;
Pos nodeptr = head;
while (nodeptr->nextNode != NULL) {
nodeptr = nodeptr->nextNode;
}
nodeptr->nextNode = node;
return 0;
}
int addBeforeNode(Pos head, Pos node, Pos nodeToAdd) {
if (head == NULL || node == NULL || nodeToAdd == NULL)return - 1;
Pos nodeptr = head;
while (nodeptr->nextNode != NULL) {
if (nodeptr->nextNode == node) {
nodeToAdd->nextNode = node;
nodeptr->nextNode = nodeToAdd;
return 0;
}
nodeptr = nodeptr->nextNode;
}
return -1;
}
int addAfterNode(Pos node, Pos nodeToAdd) {
if (node == NULL || nodeToAdd == NULL) {
printf("error");
return -1;
}
nodeToAdd->nextNode = node;
node->nextNode = nodeToAdd;
return 0;
}
void printList(Pos head) {
if (head == NULL) {
printf("head is null");
return;
}
Pos nodeptr = head->nextNode;
while (nodeptr) {
printf("node number: %d\n", nodeptr->elem);
nodeptr = nodeptr->nextNode;
}
return;
}

Pos listIntersection(Pos l1, Pos l2)
{
Pos l1ptr = l1->nextNode;
Pos l2ptr = l2->nextNode;
Pos list = createList();
while (l1ptr && l2ptr) {
	if (l1ptr->elem == l2ptr->elem) {
		Pos node = allocateNode();
		node->elem = l1ptr->elem;
		addToList(list, node);
		l1ptr = l1ptr->nextNode;
		l2ptr = l2ptr->nextNode;
	}
	else if (l1ptr->elem > l2ptr->elem) {
		l2ptr = l2ptr->nextNode;
	}
	else {
		l1ptr=l1ptr->nextNode;
	}
}

return list;
}

Pos listUnion(Pos l1, Pos l2)
{
	if (!l1 || !l2)return NULL;
	Pos list = createList();
	if (!list)return NULL;
	Pos l1ptr = l1->nextNode;
	Pos l2ptr = l2->nextNode;

	while (l1ptr) {
		Pos node = allocateNode();
		node->elem = l1ptr->elem;
		if (addToList(list, node) < 0) {
			printf("error adding to list");
		}
		l1ptr = l1ptr->nextNode;
	}
	while (l2ptr) {
		Pos node = allocateNode();
		node->elem = l2ptr->elem;
		
		if (addToList(list, node) < 0) {
			printf("error adding to list");
		}
		l2ptr = l2ptr->nextNode;
	}
	return list;
}

void deleteList(Pos head)
{
	if (!head)return;
	Pos nodeptr = head;
	Pos nodeToDelete = NULL;
	while (nodeptr != NULL) {
		nodeToDelete = nodeptr;
		nodeptr = nodeptr->nextNode;
		free(nodeToDelete);
	}
}

