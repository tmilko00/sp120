/*Definirati strukturu osoba (ime, prezime, godina roðenja)
i napisati program koji:
a)dinamièki dodaje novi element na poèetak liste,
b)ispisuje listu,
c)dinamièki dodaje novi element na kraj liste,
d)pronalazi element u listi (po prezimenu)
e)briše odreðeni element iz liste
U zadatku se ne smiju koristiti globalne varijable.*/

//Prethodnom zadatku dodati funkcije:
//a) dinamicki dodaje novi element iza odredenog elementa, 
//b) dinamicki dodaje novi element ispred odredenog elementa, 
//c) sortira listu po prezimenima osoba,
//d) upisuje listu u datoteku,
//e) cita listu iz datoteke. 


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

typedef struct _node* Pozicija;

_osoba* allocateOsoba();
Pozicija allocateNode();
Pozicija createList();
int addToListEnd(Pozicija head);//returns >=0 if successful
int addToListStart(Pozicija head);//returns >=0 if successful 
void printList(Pozicija head);
void printNode(Pozicija node);
Pozicija findByName(Pozicija head);
int removeNodeFromList(Pozicija head, Pozicija node);
void deleteList(Pozicija head);
void addAfterNode(Pozicija);

int main(int argc, char* argv[]) {
	int ret = 0;
	Pozicija list = NULL;
	list= createList();
	Pozicija trazi = NULL;
	addToListStart(list);
	addToListEnd(list);
	addToListStart(list);
	printList(list);
	trazi = findByName(list);
	printf("nakon trazenja\n");
	printNode(trazi);
	removeNodeFromList(list,trazi);
	printf("lista nakon brisanja\n");
	printList(list);
	deleteList(list);

	return 0;
}

_osoba* allocateOsoba() {
	int ret = 0;
	_osoba* osobaptr= NULL;
	osobaptr = (_osoba*)malloc(sizeof(_osoba));
	if (osobaptr != NULL) {
		while (ret != 3) {
			printf("Upisi Ime, Prezime, Godinu rodjenja\n");
			ret = scanf("%s %s %d", osobaptr->ime, osobaptr->prezime, &osobaptr->godinaRodenja);
			if (ret != 3)printf("Krivo uneseni podatci\n");
		}
		return osobaptr;
	}
	else return NULL;
}
Pozicija allocateNode() {
	Pozicija newNode = NULL;
	newNode = (Pozicija)malloc(sizeof(NODE));
	if (newNode != NULL) {
		return newNode;
	}
	else return NULL;
}

Pozicija createList() {
	Pozicija head = NULL;
	head = allocateNode();
	if (head != NULL) {
		head->nextNode = NULL;
		return head;
	}
	else return NULL;
}

int addToListEnd(Pozicija head) {

	Pozicija node = NULL;
	Pozicija nodeptr = NULL;
	_osoba* novaOsoba = NULL;

	node = allocateNode();
	novaOsoba = allocateOsoba();

	if (node != NULL) {
		node->osoba = *novaOsoba;
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

int addToListStart(Pozicija head) {
	
	Pozicija node =NULL;
	_osoba* novaOsoba = NULL;

	node = allocateNode();
	novaOsoba = allocateOsoba();

	if ((node != NULL) && (head!=NULL)) {
		node->osoba = *novaOsoba;
		node->nextNode = head->nextNode;
		head->nextNode = node;
		return 0;
	}
	else return -1;
}

void printList(Pozicija head) {

	Pozicija nodeptr = NULL;
	nodeptr = head;
	if (nodeptr->nextNode != NULL) {
		while (nodeptr->nextNode != NULL) {
			nodeptr = nodeptr->nextNode;
			printNode(nodeptr);
		}
	}
	else printf("Error, no nodes");
}

void printNode(Pozicija node) {
	if (node != NULL) {
		printf("%s %s %d\n", node->osoba.ime, node->osoba.prezime, node->osoba.godinaRodenja);
	}
	else printf("Node is NULL.\n");
}


Pozicija findByName(Pozicija head) {
	int ret = 0;
	Pozicija nodeptr = head;
	char prezime[MAX_CHAR] = {0};
	if (nodeptr->nextNode != NULL) {
		printf("Upisi prezime osobe koju trazis\n");
		while (ret != 1) {
			ret = scanf("%s", prezime);
			if (ret != 1)printf("Need 1 argument\n");
		}
		while (nodeptr->nextNode != NULL) {
			nodeptr = nodeptr->nextNode;
			if (strcmp(nodeptr->osoba.prezime, prezime) == 0) {
				return nodeptr;
			}
		}
		return NULL;
	}
	else return NULL;
}
int removeNodeFromList(Pozicija head, Pozicija node) {
	if (head == NULL||node==NULL) return -1;
	
	Pozicija nodeptr = head;
	Pozicija elemBefore = NULL;
	if (nodeptr != NULL) {
		while (nodeptr->nextNode != NULL) {
			elemBefore = nodeptr;
			nodeptr = nodeptr->nextNode;
			if (nodeptr == node) {
				elemBefore->nextNode = nodeptr->nextNode;
				free(node);
				return 0;
			}
		}
		return -1;
	}
	else {
		printf("No nodes\n");
		return -1;
	}
		

}

void deleteList(Pozicija head) {
	Pozicija nodeptr = head;
	Pozicija nodeToClear = NULL;
	if (nodeptr != NULL) {
		while (nodeptr->nextNode != NULL) {
			nodeToClear = nodeptr;
			nodeptr = nodeptr->nextNode;
			free(nodeToClear);
		}
		free(nodeptr);
	}
	else printf("List head is NULL\n");
}
void addAfterNode(Pozicija node) {
	Pozicija newNode = NULL;
	_osoba* newOsoba = NULL;
	newNode = allocateNode();
	newOsoba = allocateOsoba();
	if (node != NULL && newNode != NULL) {
		newNode->osoba = *newOsoba;
		newNode->nextNode = node->nextNode;
		node->nextNode = newNode;
	}
	else printf("node is null");
}