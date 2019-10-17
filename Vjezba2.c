/*Definirati strukturu osoba (ime, prezime, godina roðenja)
i napisati program koji:
a)dinamièki dodaje novi element na poèetak liste,
b)ispisuje listu,
c)dinamièki dodaje novi element na kraj liste,
d)pronalazi element u listi (po prezimenu)
e)briše odreðeni element iz liste
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_CHAR (100)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	char ime[MAX_CHAR];
	char prezime[MAX_CHAR];
	int godinaRodenja;
}_osoba;

typedef struct _node {
	struct _node* nextNode;
	_osoba osoba;
}NODE;

NODE* createList(_osoba osoba);
int addToListEnd(NODE* head, _osoba osoba);//returns >=0 if successful
NODE* addToListStart(NODE* head, _osoba osoba); //returns new head node
void printList(NODE* head);
void printNode(NODE* node);
NODE* findByName(NODE* head, char* prezime);
NODE* removeNodeFromList(NODE* head, NODE* node);//returns new/old head if deleted node was head/not
void deleteList(NODE* head);

int main(int argc, char* argv[]) {

	_osoba o1 = { "Pero","Djetlic",20 };
	_osoba o2 = { "Mate","Bakic",80 };
	_osoba o3 = { "Luka","Lokvic",60 };
	NODE* list = createList(o1);
	char prezime[MAX_CHAR] = "Bakic";
	NODE* newHead = addToListStart(list, o2);
	addToListEnd(newHead, o3);
	NODE* item = findByName(newHead, prezime);
	printNode(item);
	printf("cijela lista:\n");
	printList(newHead);
	newHead=removeNodeFromList(newHead, item);
	printf("lista nakon izbrisanog clana\n");
	printList(newHead);
	deleteList(newHead);

	return 0;
}

NODE* createList(_osoba osoba) {
	NODE* node = (NODE*)(malloc(sizeof(NODE)));
	if (node != NULL) {
		node->osoba = osoba;
		node->nextNode = NULL;
		return node;
	}
	else return NULL;
}

int addToListEnd(NODE* head, _osoba osoba) {

	NODE* node = (NODE*)(malloc(sizeof(NODE)));
	NODE* nodeptr = NULL;
	if (node != NULL) {
		node->osoba = osoba;
		node->nextNode = NULL;
		nodeptr = head;
		while (nodeptr->nextNode != NULL) {
			nodeptr = nodeptr->nextNode;
		}
		nodeptr->nextNode = node;
		return 0;
	}
	return -1;
}

NODE* addToListStart(NODE* prevHead, _osoba osoba) {

	NODE* node = (NODE*)(malloc(sizeof(NODE)));
	if (node != NULL) {
		node->osoba = osoba;
		node->nextNode = prevHead;
		return node;
	}
	else return NULL;
}

void printList(NODE* head) {

	NODE* nodeptr = head;
	if (head != NULL) {
		while (nodeptr->nextNode != NULL) {
			printf("Osoba %s %s %d\n", nodeptr->osoba.ime, nodeptr->osoba.prezime, nodeptr->osoba.godinaRodenja);
			nodeptr = nodeptr->nextNode;
		}
		//print last item
		printf("Osoba %s %s %d\n", nodeptr->osoba.ime, nodeptr->osoba.prezime, nodeptr->osoba.godinaRodenja);
	}
	else printf("Error, got NULL as node head\n");
}

void printNode(NODE* node) {
	if (node != NULL) {
		printf("%s %s %d\n", node->osoba.ime, node->osoba.prezime, node->osoba.godinaRodenja);
	}
	else printf("Node is NULL.\n");
}


NODE* findByName(NODE* head, char* prezime) {

	NODE* nodeptr = head;
	if (nodeptr != NULL) {
		while (nodeptr->nextNode != NULL) {
			if (strcmp(nodeptr->osoba.prezime, prezime) == 0) {
				return nodeptr;
			}
			nodeptr = nodeptr->nextNode;
		}
		//check last element
		if (strcmp(nodeptr->osoba.prezime, prezime) == 0) {
			return nodeptr;
		}
		else return NULL;
	}
	else return NULL;
}
NODE* removeNodeFromList(NODE* head, NODE* node) {
	NODE* nodeptr = head;
	NODE* newHead = NULL;
	if ((head != NULL) && (node != NULL)) {
		if (head == node) {
			newHead = head->nextNode;
			free(head);
			return newHead;
		}
		else {
			while (nodeptr->nextNode != node) {
				nodeptr = nodeptr->nextNode;
				//nesto je fked sa ovin redon iznad ja msn
			}
			if (nodeptr->nextNode == node) {
				nodeptr->nextNode = node->nextNode;
				free(node);
				return head;
			}
			else {
				printf("No node");
				return head;
			}
		}
	}
	else return head;
}

void deleteList(NODE* head) {
	NODE* nodeptr = head;
	NODE* nodeToClear = NULL;
	if (nodeptr != NULL) {
		while (nodeptr->nextNode != NULL) {
			nodeToClear = nodeptr;
			nodeptr = nodeptr->nextNode;
			free(nodeToClear);
		}
		free(nodeptr);
	}
	else printf("List head is NULL");
}