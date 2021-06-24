#ifndef PILHA_ENCADEADA_H
#define PILHA_ENCADEADA_H

typedef int elem;

typedef struct node_ Node;
typedef struct stack_ Stack;

Stack* CreateStack();
int GetNumElements(Stack *stack);
int IsEmptyStack(Stack *stack);
int AddElemStack(Stack *stack, elem e);
int Pop(Stack *stack, elem *e);
Node* SearchElemStack(Stack *stack, elem e, int *error);
int PrintStack(Stack *stack);
int GetNumElem(Stack *stack);
int FreeStack(Stack *stack);

#endif
