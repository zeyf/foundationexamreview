#include <stdlib.h>
#include <stdio.h>

typedef struct sllnode {
    int data;
    struct sllnode *next;
} sllnode;

// dynamically allocates a linked list node
sllnode *makeNode(int data) {
    sllnode *newNode = malloc(sizeof(sllnode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
};

// inserts to the front / head of the linked list a new node.
sllnode *insertFront(sllnode *head, int data) {
    sllnode *newNode = makeNode(data);
    if (head == NULL) return newNode;    
    newNode->next = head;
    return newNode;
};

// inserts to the tail / back of a linked list a new node.
sllnode *insertTail(sllnode *head, int data) {
    sllnode *newNode = makeNode(data), *c = head;
    if (head == NULL) return newNode;

    while (c->next != NULL)
        c = c->next;
    c->next = newNode;

    return head;
};


/*
PROBLEM: Minimal of most frequent.
Topics: Linked Lists / Recursion / Frequency Arrays

Given a singly linked list with positive integers from [1, 10000], return the minimum value of the greatest frequencies.
If the linked list is empty, return -1.
For example, if a linked list is: 8 -> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x
The answer would be 1.

The frequencies are as follows: 8 appears 1 time, 1 appears 2 times, 3 appears 2 times, 4 appears 2 times, and 6 appears 2 times.
The most frequent are { 1, 3, 4, 6 }, and min({1,2,4,6}) = 1.

typedef struct node {
    int data;
    struct node *next;
} node;

int minOfMaxFrequency(sllnode *head, int frequencies[10001]) {



};

*/



















/*
Approach:
- If head is null, return -1, we have an empty list.

We must account for every node and it's corresponding value, so increment the frequency of head->data.

- If we hit head->next == NULL, at the end of the list. Therefore, we can return head->data to compare against the previous node.

From this point, we have fully accounted for every value in the linked list and its frequency while ascending in the recursion.
Now, we can do the calculations as we descend back the recursive calls towards the head.

Store the subResult -- the result that the recursion has. It will store the best answer succeeding a given node in the linked list.

Then, compare the frequency of the given subResult value from the linked list with that of the current head->data.
Take the one with the higher frequency.
If they have the same frequency, take the minimal of the two. It can be the case that they are the same frequency and same value.
This will still be handled implicitly on the false case of the ternary return statement.


Walk through:
 0 1 2 3 4 5 6 7 8      10000
[0,0,0,0,0,0,0,0,0, .... 0]

====================================

v
8 -> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,0,0,0,0,0,0,0,1, .... 0]

     v
8 -> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,1,0,0,0,0,0,0,1, .... 0]

         v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,1,0,1,0,0,0,0,1, .... 0]

              v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,1,0,1,1,0,0,0,1, .... 0]

                   v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,1,0,1,1,0,1,0,1, .... 0]

                        v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,1,0,1,1,0,2,0,1, .... 0]

                             v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,1,0,1,2,0,2,0,1, .... 0]

                                  v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,2,0,1,2,0,2,0,1, .... 0]

                                       v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

 0 1 2 3 4 5 6 7 8      10000
[0,2,0,2,2,0,2,0,1, .... 0]

// Above is the final state of the frequency array... now we descend towards the head and compare.

                                  v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x

frequencies[1] == frequencies[3] --> return 1

                             v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x
frequencies[4] == frequencies[1] --> return 1

                        v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x
frequencies[6] == frequencies[1] --> return 1

                   v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x
frequencies[6] == frequencies[1] --> return 1

              v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x
frequencies[4] == frequencies[1] --> return 1

         v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x
frequencies[3] == frequencies[1] --> return 1

    v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x
frequencies[1] == frequencies[1] --> return 1

    v
8-> 1 -> 3 -> 4 -> 6 -> 6 -> 4 -> 1 -> 3 -> x
frequencies[8] < frequencies[1] --> return 1

*/
int minOfMaxFrequency(sllnode *head, int frequencies[10001]) {
    if (head == NULL) return -1;

    frequencies[head->data]++;
    if (head->next == NULL) return head->data;
    
    int subResult = minOfMaxFrequency(head->next, frequencies);
    if (frequencies[subResult] > frequencies[head->data])
        return subResult;
    else if (frequencies[subResult] < frequencies[head->data])
        return head->data;
    
    return head->data > subResult ? subResult : head->data;
};


int main () {



    return 0;
}