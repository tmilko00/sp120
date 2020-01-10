/*

Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i povratak u prethodni direktorij.
Toènije program treba preko menija simulirati korištenje DOS naredbi: 1-"md", 2 -"cd dir", 3 -"cd..",4 -"dir"i5 –izlaz
 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX (50)
typedef struct _stack {
    struct _node* node;
    struct _stack* nextNode;
}SNODE;
typedef struct _stack* SPos;
typedef struct _node {
    struct _node* nextNode;
    struct _node* child;
    char name[MAX];
}
NODE;
 
typedef struct _node* Pos;
 
Pos createList();
void tree(Pos root,int);
SPos createStack();
SPos allocateSNode(Pos);
Pos push(SPos stack, SPos nodeToPush);
Pos pop(SPos stack);
Pos deleteNode(SPos stacknode);
Pos allocateNode(char*);
int addBeforeNode(Pos, Pos, Pos);
int addAfterNode(Pos, Pos);
int addToList(Pos, Pos);
int addToListEnd(Pos, Pos);
void deleteList(Pos);
void printStack(SPos);
void md(SPos,char*);
void cd(SPos,char* param);
int main() {
    Pos root = createList();
    SPos stack = createStack();
    Pos rootNode = allocateNode("C:");
    addToList(root,rootNode);
    push(stack, allocateSNode(rootNode));
    char* na = "loptata";
    md(stack,na);
    cd(stack, na);
    md(stack, "kunpir");
    md(stack, "motok");
    cd(stack, "kunpir");
    tree(root,0);
    printStack(stack);
    cd(stack, "..");
    printStack(stack);
   
    system("pause");
    return 0;
}
Pos createList() {
    Pos head = NULL;
    head = allocateNode(NULL);
    if (head != NULL) {
        return head;
    }
    printf("malloc failed");
    return NULL;
}
void tree(Pos root, int time) {
    Pos nodeptr = root->nextNode;
    for (int i = 0;i < time;i++) {
        printf(" ");
    }
    printf("%s \n",nodeptr->name);
    if (nodeptr->child!=NULL) {
        tree(nodeptr->child,time+1);
    }
    while (nodeptr->nextNode != NULL) {
        for (int i = 0;i < time;i++) {
            printf(" ");
        }
        printf("%s \n",nodeptr->nextNode->name);
        nodeptr = nodeptr->nextNode;
    }
    return;
}
void printStack(SPos stack){
    if(stack->nextNode != NULL) {
        printStack(stack->nextNode);
    }
    if (stack->node) {
        printf("%s/",stack->node->name);
        return;
    }
    printf("\n");
}
void cd(SPos stack,char* param) {
    Pos nodeptr = stack->nextNode->node;
    if (strcmp(param,"..")==0) {
        if (strcmp(stack->nextNode->node->nextNode->name, "C:") == 0) {
            printf("this is root");
        }
        else {
            pop(stack);
            return;
        }
    }
    else{
        nodeptr = nodeptr->child;
        while (strcmp(nodeptr->name, param) != 0) {
            nodeptr = nodeptr->nextNode;
        }
        if (strcmp(nodeptr->name, param) == 0) {
            push(stack, allocateSNode(nodeptr));
            return;
        }
        printf("no dir like that");
        return;
    }
}
void md(SPos stack,char* name) {
    if (stack) {
        if (stack->nextNode->node->child == NULL) {
            Pos child = createList();
            addToList(child, allocateNode(name));
            stack->nextNode->node->child = child;
        }
        else {
            addToList(stack->nextNode->node->child, allocateNode(name));
 
        }
        return;
 
    }
}
SPos createStack() {
    SPos head = NULL;
    head = allocateSNode(NULL);
    if (head != NULL) {
        return head;
    }
    printf("malloca fail");
    return NULL;
}
SPos allocateSNode(Pos nodeToAdd) {
    SPos node = NULL;
    node = (SPos)malloc(sizeof(SNODE));
    if (node != NULL) {
        node->nextNode = NULL;
        if (nodeToAdd) {
            node->node = nodeToAdd;
            return node;
        }
        node->node = NULL;
        return node;
    }
    return NULL;
}
Pos push(SPos stack,SPos nodeToPush) {
    if (stack&&nodeToPush) {
        nodeToPush->nextNode = stack->nextNode;
        stack->nextNode = nodeToPush;
        return nodeToPush->node;
 
    }
    return NULL;
}
Pos pop(SPos stack) {
    SPos nodeToPop = stack->nextNode;
    stack->nextNode = nodeToPop->nextNode;
    Pos delN=deleteNode(nodeToPop);
    return delN;
}
Pos deleteNode(SPos stacknode) {
    if (stacknode) {
        Pos node = stacknode->node;
        free(stacknode);
        return node;
    }
    return NULL;
}
Pos allocateNode(char* name) {
    Pos node = NULL;
    node = (Pos)malloc(sizeof(NODE));
    if (node != NULL) {
        node->nextNode = NULL;
        node->child = NULL;
        if (name!=NULL) {
            //node->name = name;
            strcpy(node->name,name);
        }
        return node;
    }
    return NULL;
}
int addToList(Pos head, Pos node) {
    Pos nodeptr = head->nextNode;
    if (!head || !node) return -1;
    while (nodeptr) {
        if (nodeptr->name == node->name) {
            printf("that dir already exists at this lvl\n");
            return 0;
        }
        else if (strcmp(nodeptr->name, node->name) < 0) {
            nodeptr = nodeptr->nextNode;
        }
        else {
            addBeforeNode(head,nodeptr, node);
            return 0;
        }
    }
    addToListEnd(head, node);
    return 0;
}
int addToListEnd(Pos head, Pos node) {
    if (!head || !node) return -1;
    Pos nodeptr = head;
    while (nodeptr->nextNode != NULL) {
        nodeptr = nodeptr->nextNode;
    }
    nodeptr->nextNode = node;
    return 0;
}
int addBeforeNode(Pos head, Pos node, Pos nodeToAdd) {
    if (head == NULL || node == NULL || nodeToAdd == NULL) return -1;
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
 
 
void deleteList(Pos head) {
    if (!head) return;
    Pos nodeptr = head;
    Pos nodeToDelete = NULL;
    while (nodeptr != NULL) {
        nodeToDelete = nodeptr;
        nodeptr = nodeptr->nextNode;
        free(nodeToDelete);
    }
}
*/