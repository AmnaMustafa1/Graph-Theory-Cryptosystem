#ifndef ADT_H
#define ADT_H

#include "boolean.h"

// ------------------- Graph Structure -------------------
typedef struct graph {
    int **matrix;
    int len;
} Graph;

// ------------------- Key Structure -------------------
typedef struct key {
    int first;
    int last;
} Key;

// ------------------- Linked Lists -------------------
typedef struct keyMsg {
    Key info;
    struct keyMsg* next;
} KeyMsg;

typedef KeyMsg* keyList;

typedef struct graphMsg {
    Graph graf;
    struct graphMsg* next;
} GraphMsg;

typedef GraphMsg* graphList;

// ------------------- Message Structure -------------------
typedef struct message {
    int len;
    graphList gList;
} Message;

// ------------------- Function Prototypes -------------------
void createGraph(Graph* graf, int x);
void keyAppend(keyList* keyL, Key keyG);
void graphAppend(graphList* grafL, Graph grafVal);
void displayGraph(Graph g);

#endif // ADT_H

