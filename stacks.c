#include <stdlib.h>
#include <stdio.h>

typedef struct sllnode {
    int data;
    struct sllnode *next;
} sllnode;

typedef struct sllstack {
    int size;
    sllnode *top;
} sllstack;

typedef struct arraystack {
    int topIndex, capacity, size, values[50];
} arraystack;

sllnode *makeNode(int data) {
    sllnode *newNode = malloc(sizeof(sllnode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
};

// initialize the stack.
sllstack *makesllStack() {
    sllstack *newStack = malloc(sizeof(sllstack));
    newStack->top = NULL;
    newStack->size = 0;
    return newStack;
};

void push(sllstack *s, int data) {
    // if there's no stack, you  cant push.
    if (s == NULL) return;

    // make the new node
    sllnode *newNode = makeNode(data);
    // assign the top if null
    if (s->top == NULL)
        s->top = newNode;
    // else reroute and change top, connect newnode to old top.
    else {
        newNode->next = s->top;
        s->top = newNode;
    };

    // increment the size, new node was added
    s->size++;
};

// popping off of a stack of only positive integers (hence -1 return if invalid.)
int pop(sllstack *s) {
    // check if there's something to remove or a stack
    if (s == NULL || s->top == NULL) return -1;
    
    // store return value, top of stack
    int retval = s->top->data;
    // set a pointer to the old top for freeing.
    sllnode *oldTop = s->top;

    // slide the top over to the next element (could be null)
    s->top = s->top->next;

    // free the old top.
    free(oldTop);

    // decrement size since a node was removed.
    s->size--;

    // return the old top value.
    return retval;
};

void freesllStack(sllstack *stack) {
    if (stack == NULL) return;
    sllnode *c = stack->top, *n;
    while (c != NULL) {
        n = c->next;
        free(c);
        c = n;
    };
};

arraystack *makeArrayStack() {
    arraystack *newStack = malloc(sizeof(arraystack));
    newStack->topIndex = '?'; // this should be -1 or 0... it depends what they ask you. disregard this '?'
    newStack->capacity = newStack->size = 0;
    return newStack;
};


void pushTopIndexNegative1(arraystack *stack, int data) {
    if (stack == NULL || stack->topIndex == stack->capacity-1) return;
    stack->topIndex++;
    stack->values[stack->topIndex] = data;
    stack->size++;
};

void pushTopIndex0(arraystack *stack, int data) {
    if (stack == NULL || stack->topIndex == stack->capacity) return;
    stack->values[stack->topIndex] = data;
    stack->topIndex++;
    stack->size++;
};

int popTopIndexNegative1(arraystack *stack) {
    if (stack == NULL || stack->topIndex == -1) return -1;
    int retval = stack->values[stack->topIndex];
    stack->topIndex--;
    stack->size--;
    return retval;
};

int popTopIndex0(arraystack *stack) {
    if (stack == NULL || stack->topIndex == 0) return -1;
    stack->topIndex--;
    int retval = stack->values[stack->topIndex];
    stack->size--;
    return retval;
};

int isEmptyArrayStack(arraystack *stack) {
    return stack->size == 0;
};

/*

INVERT ARRAY

Given an array of n integers, invert the array in a left to right manner.
For example: [1,2,3,4] ---> [3,4,1,2] and [1,2,3] --> [3,2,1] and [1,2,3,4,5,6] --> [4,5,6,1,2,3]

1 4 2 3

*/

void invertArray(int *array, int n) {
    int l = 0, r = n-1;
    sllstack *stack = makesllStack();

    while (l < r) {
        push(stack, array[l++]);
        push(stack, array[r--]);
    };

    l = 0;
    r = n-1;

    while (l < r) {
        array[l++] = pop(stack);
        array[r--] = pop(stack);
    };

    freesllStack(stack);

};


int main () {

    int array1[] = { 1,2,3,4 },
        array2[] = { 1,2,3 },
        array3[] = { 1,2,3,4,5,6 },
        array4[] = { 1,2,3,4,5,6,7,8,9,10 },
        array5[] = { 10,9,8,7,6,5,4,3,2,1 };

    invertArray(array1, 4);
    invertArray(array2, 3);
    invertArray(array3, 6);
    invertArray(array4, 10);
    invertArray(array5, 10);


    for (int x = 0; x < 4; ++x)
        printf("%d ", array1[x]);
    printf("\n");

    for (int x = 0; x < 3; ++x)
        printf("%d ", array2[x]);
    printf("\n");

    for (int x = 0; x < 6; ++x)
        printf("%d ", array3[x]);
    printf("\n");

    for (int x = 0; x < 10; ++x)
        printf("%d ", array4[x]);
    printf("\n");

    for (int x = 0; x < 10; ++x)
        printf("%d ", array5[x]);
    printf("\n");

    return 0;
}