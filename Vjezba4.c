#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>


typedef struct node {
	int coef;
	int exp;
	struct node* nextNode;
}_node;

typedef struct node* Node;

Node createList();
int addToListEnd(Node, Node);
int addBeforeNode(Node, Node,Node);
int addAfterNode(Node,Node);
Node allocateNode(int, int);
Node readListFromFile(char*);
Node addNodeToList(Node,int, int);
void printNode(Node node);
void printList(Node head);
Node sumLists(Node, Node);
Node mulLists(Node, Node);
int deleteList(Node);
int deleteNode(Node);
int main() {
	Node lista = readListFromFile("polinomi.txt");
	Node lista2 = readListFromFile("polinomi2.txt");
	printf("list1-----------------\n");
	printList(lista);
	printf("list2--------------\n");
	printList(lista2);
	Node sumList = sumLists(lista, lista2);
	printf("sumirana lista-----------\n");
	printList(sumList);
	printf("multi lista-----------\n");
	Node multList = mulLists(lista, lista2);
	printList(multList);
	deleteList(lista);
	deleteList(lista2);
	deleteList(sumList);
	deleteList(multList);
	system("pause");
	return 0;
}
Node allocateNode(int coef, int exp) {
	Node node = NULL;

	node = (Node)malloc(sizeof(_node));
	
	if (node != NULL) {
		node->coef = coef;
		node->exp = exp;
		node->nextNode = NULL;
		
		return node;
	}
	printf("malloc failed");
	return NULL;
}
Node createList() {
	Node head = NULL;
	head = allocateNode(0,0);
	
	return head;
}
Node addNodeToList(Node head,int coef, int exp) {
	if (head == NULL || (coef == 0 && exp == 0)) {
		printf("args are useless,returning null");
		return NULL;
	}
	Node node = allocateNode(coef,exp);
	if (node == NULL)return NULL;
	Node nodeptr = head->nextNode;
	while (nodeptr != NULL) {
		if (nodeptr->exp > exp) {
			nodeptr = nodeptr->nextNode;
		}
		else if (nodeptr->exp == exp) {
			nodeptr->coef = node->coef + nodeptr->coef;
			return node;
		}
		else {
			if (addBeforeNode(head,nodeptr, node) != 0) {
				printf("sum ting wong");
				return NULL;
			}
			return node;
		}
	}

	if (addToListEnd(head, node) != 0) {
		printf("error");
		return NULL;
	}
	return node;

}
int deleteNode(Node node) {
	if (node != NULL) {
		free(node);
		return 0;
	}
	printf("node was null");
	return -1;
}
int deleteList(Node head) {

	if (head == NULL) {
		printf("head is null");
		return -1;
	}
	
	Node nodeToDelete = NULL;
	Node nodeptr = head->nextNode;

	deleteNode(head);

	while (nodeptr != NULL) {
		nodeToDelete = nodeptr;
		nodeptr = nodeptr->nextNode;
		deleteNode(nodeToDelete);
	}
	return 0;
}
void printList(Node head) {
	if (head == NULL) {
		printf("head is null");
		return;
	}
	Node nodeptr = NULL;
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

void printNode(Node node) {
	if (node != NULL) {
		printf("%dX^%d\n", node->coef, node->exp);
		return;
	}
	else printf("Node is NULL.\n");
}
int addToListEnd(Node head, Node nodeToAdd) {
	if (head == NULL || nodeToAdd == NULL) {
		printf("head or node is NULL");
		return -1;
	}
	Node nodeptr = head;
	while (nodeptr->nextNode != NULL) {
		nodeptr = nodeptr->nextNode;
	}
	nodeptr->nextNode = nodeToAdd;
	nodeToAdd->nextNode = NULL;
	return 0;

}
int addBeforeNode(Node head,Node node, Node nodeToAdd) {
	if (node == NULL || nodeToAdd == NULL||head==NULL) {
		printf("one of the arguments is null");
		return -1;
	}
	Node nodeptr = head;
	while (nodeptr->nextNode != NULL) {
		if (nodeptr->nextNode == node) {
			nodeptr->nextNode = nodeToAdd;
			nodeToAdd->nextNode = node;
			return 0;
		}
		nodeptr = nodeptr->nextNode;
	}

	return -1;
}
int addAfterNode(Node afterNode, Node nodeToAdd) {
	if (afterNode == NULL || nodeToAdd == NULL) {
		printf("shits broke yo");
		return -1;
	}
	nodeToAdd->nextNode = afterNode->nextNode;
	afterNode->nextNode = nodeToAdd;
	return 0;
}
Node readListFromFile(char* fileName) {
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("failed to open file\n");
		return NULL;
	}
	Node list = createList();
	if (list == NULL)return NULL;
	int coef = 0;
	int	exp = 0;
	int ret =0;
	while (ret=fscanf(fp,"%d %d",&coef,&exp)) {
		if (ret == 1) {
			addNodeToList(list, coef, 0);
		}
		else if(ret==2){
			addNodeToList(list, coef, exp);
		}
		else {
			
			break;
		}
	}
	fclose(fp);
	return list;
}

Node sumLists(Node list1, Node list2) {
	Node sumList = createList();
	Node list1ptr = list1->nextNode;
	Node list2ptr = list2->nextNode;
	if (list1ptr == NULL)return list2;
	if (list2ptr == NULL)return list1;
	while (list1ptr != NULL&&list2ptr!=NULL	) {
		if (list1ptr->exp == list2ptr->exp) {
			addNodeToList(sumList, list1ptr->coef + list2ptr->coef, list1ptr->exp);
			list1ptr = list1ptr->nextNode;
			list2ptr = list2ptr->nextNode;
		}
		if (list1ptr->exp < list2ptr->exp) {
			addNodeToList(sumList, list1ptr->coef, list1ptr->exp);
			list1ptr = list1ptr->nextNode;

		}
		else {
			addNodeToList(sumList, list2ptr->coef, list2ptr->exp);
			list2ptr = list2ptr->nextNode;

		}
	}
	while (list1ptr != NULL) {
		addNodeToList(sumList, list1ptr->coef, list1ptr->exp);
		list1ptr = list1ptr->nextNode;

	}
	while (list2ptr != NULL) {
		addNodeToList(sumList, list2ptr->coef, list2ptr->exp);
		list2ptr = list2ptr->nextNode;

	}
	return sumList;
}
Node mulLists(Node list1, Node list2) {
	Node mulList = createList();
	Node list1ptr = list1->nextNode;
	Node list2ptr = list2->nextNode;
	if (list1ptr == NULL)return list2;
	if (list2ptr == NULL)return list1;
	while (list1ptr != NULL) {
		while (list2ptr != NULL) {
			addNodeToList(mulList, list1ptr->coef * list2ptr->coef, list1ptr->exp + list2ptr->exp);
			list2ptr = list2ptr->nextNode;
		}
		list2ptr = list2->nextNode;
		list1ptr = list1ptr->nextNode;
	}
	return mulList;

}
