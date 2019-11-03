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

typedef struct osoba{
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
int addToListEnd(Pozicija,Pozicija);//returns >=0 if successful
int addToListStart(Pozicija head);//returns >=0 if successful 
void printList(Pozicija head);
void printNode(Pozicija node);
Pozicija findByName(Pozicija head);
int removeNodeFromList(Pozicija head, Pozicija node);
void deleteList(Pozicija head);
void addAfterNode(Pozicija);
void addBeforeNode(Pozicija,Pozicija);
int sortList(Pozicija);
int countListElements(Pozicija);
Pozicija mergeSort(Pozicija);
Pozicija merge(Pozicija, Pozicija);
Pozicija findRightSide(Pozicija,int);
Pozicija findLeftSide(Pozicija, Pozicija);
int printListToFile(Pozicija,char*);
int readListFromFile(Pozicija, char*);

int main(int argc, char* argv[]) {
	int ret = 0;
	Pozicija list = NULL;
	Pozicija trazi = NULL;
	/*list= createList();
	addToListStart(list);
	addToListEnd(list,NULL);
	addToListStart(list);
	printList(list);
	printf("-------prije sorta\n");
	printList(list);
	sortList(list);
	printf("--------nakon sortanja\n");
	printList(list);
	printListToFile("potato", list);
	*/
	printf("Prije sorta\n\n");
	Pozicija novilist = createList();
	readListFromFile(novilist, "./studentinew.txt");
	printList(novilist);
	printf("\nNakon sorta\n\n");
	sortList(novilist);
	printList(novilist);
	printListToFile(novilist,"./studenti_print.txt");
//	trazi = findByName(list);
	//printf("nakon trazenja\n");
	//printNode(trazi);
	//removeNodeFromList(list,trazi);
	//printf("lista nakon brisanja\n");
	//printList(list);
	deleteList(novilist);
	
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

int addToListEnd(Pozicija head, Pozicija nodeToAdd) {

	Pozicija node = NULL;
	Pozicija nodeptr = NULL;
	Pozicija newNode = allocateNode();
	_osoba* novaOsoba = NULL;
	if (nodeToAdd == NULL) {
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
	}
	else {
		newNode->nextNode = NULL;
		newNode->osoba = nodeToAdd->osoba;
		nodeptr = head;
		while (nodeptr->nextNode != NULL) {
				nodeptr = nodeptr->nextNode;
		}
		nodeptr->nextNode =newNode;

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
	nodeptr = head->nextNode;
	if (nodeptr == NULL) {
		printf("Error, no nodes");
		return;
	}
	while (nodeptr != NULL) {
		printNode(nodeptr);
		nodeptr = nodeptr->nextNode;
	}
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
void addBeforeNode(Pozicija head,Pozicija node) {
	Pozicija nodeptr = head;
	Pozicija newNode = NULL;
	newNode = allocateNode();
	if (newNode == NULL) {
		printf("cant allocate new node");
		return;
	}
	if (head == NULL || node == NULL) {
		printf("nodes are null");
		return;
	}
	while (nodeptr->nextNode != NULL) {
		if (nodeptr->nextNode == node) {
			nodeptr->nextNode = newNode;
			newNode->nextNode = node;
			return;
		}
		nodeptr = nodeptr->nextNode;
	}

}
int countListElements(Pozicija head)
{
	
	if (head == NULL) {
		printf("head is null");
		return -1;
	}
	int numOfElements = 0;
	Pozicija element = head->nextNode;
	if (element == NULL) {
		printf("no items in list");
		return 0;
	}
	while (element != NULL) {
		numOfElements++;
		element = element->nextNode;
	}
	return numOfElements;
}

int sortList(Pozicija head) {
	if (head == NULL) return -1;
	Pozicija sortedList = NULL;
	sortedList = mergeSort(head);
	head->nextNode = sortedList->nextNode;
	return 0;
	
}
Pozicija mergeSort(Pozicija head) {
	if (head == NULL) return NULL;
	Pozicija lSide = head;
	Pozicija rSide = NULL;
	int	numOfElem = countListElements(head);
	if (numOfElem == 0) {
		printf("List has 0 elements");
		return head;
	}
	else if (numOfElem == 1) {
		head->nextNode->nextNode = NULL;
		//printf("list leng 1");
		//printList(head);
		return head;
	}
	rSide = findRightSide(head,numOfElem/2);
	lSide = findLeftSide(head, rSide);
	lSide = mergeSort(lSide);
	rSide = mergeSort(rSide);
	//printf("prije mergea lside i rside\n\n");
	//printList(lSide);
	//printList(rSide);
	return merge(lSide, rSide);
}
Pozicija merge(Pozicija lSide, Pozicija rSide) {
	Pozicija lIter = lSide->nextNode;
	Pozicija rIter = rSide->nextNode;
	//printf("UMERGE liter\n");
	//printList(lSide);
	//printf("UMERGE riter\n");
	//printList(rSide);
	Pozicija list = createList();
	while (lIter != NULL) {
		if (rIter != NULL) {
			if (strcmp(lIter->osoba.prezime, rIter->osoba.prezime) < 0) {
				addToListEnd(list,lIter);
				lIter = lIter->nextNode;
			}
			else {
				addToListEnd(list,rIter);
				rIter = rIter->nextNode;
				
			}
		}
		else {
			addToListEnd(list, lIter);
			lIter = lIter->nextNode;
		}
	}
	while (rIter != NULL) {
		addToListEnd(list,rIter);
		rIter = rIter->nextNode;
	}
	//printf("LISTNAKRAJUPRIJERETURNA\n");
	//printList(list);
	return list;
}
Pozicija findRightSide(Pozicija head,int nodePos) {
	if (head->nextNode == NULL) return head;
	if (nodePos == 0)return head;
	int currNode = 0;
	Pozicija list = createList();
	Pozicija prevNode = NULL;
	Pozicija nodeptr = head->nextNode;
	while (nodeptr != NULL) {
		if (currNode == nodePos) {
			prevNode->nextNode = NULL;
			list->nextNode = nodeptr;
			return list;
		}
		currNode++;
		prevNode = nodeptr;
		nodeptr=nodeptr->nextNode;
	}
	return list;
}
Pozicija findLeftSide(Pozicija head, Pozicija lastNode) {
	Pozicija nodeptr = NULL;
	nodeptr = head;
	if (nodeptr->nextNode == NULL)return head;
	while (nodeptr != NULL) {
		if (nodeptr->nextNode==lastNode) {
			nodeptr->nextNode = NULL;
		}
		nodeptr = nodeptr->nextNode;
	}
	return head;
}
int printListToFile(Pozicija head,char* fileName) {
	FILE* fp = NULL;
	Pozicija nodeptr = head->nextNode;
	if (nodeptr != NULL) {
		fp = fopen(fileName, "w");
		if (fp != NULL) {
			while (nodeptr != NULL) {
				fprintf(fp, "%s %s %d\n", nodeptr->osoba.ime, nodeptr->osoba.prezime, nodeptr->osoba.godinaRodenja);
				nodeptr = nodeptr->nextNode;
			}
			fclose(fp);
			return 0;
		}
		return -1;
	}
	return -1;
}
int readListFromFile(Pozicija head, char* fileName) {
	FILE* fp = NULL;
	Pozicija nodeToAdd = NULL;
	char str[256] = { 0 };
	if (head != NULL) {
		fp = fopen(fileName, "r");
		if (fp == NULL)return-1;
		while (fgets(str,sizeof(str),fp)){
			nodeToAdd = allocateNode();
			sscanf(str,"%s %s %d",nodeToAdd->osoba.ime,nodeToAdd->osoba.prezime,&nodeToAdd->osoba.godinaRodenja);
			addToListEnd(head, nodeToAdd);
			nodeToAdd = NULL;
		}
		fclose(fp);
		return 0;
	}
	return -1;
}
