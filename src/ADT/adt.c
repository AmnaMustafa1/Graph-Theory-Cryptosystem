#include "adt.h"
#include <stdlib.h>
#include <stdio.h>

void createGraph(Graph* graf, int x) {
    graf->matrix = (int**)malloc(x * sizeof(int*));
    if (graf->matrix != NULL) {
        graf->len = x;
        for (int i = 0; i < x; i++) {
            graf->matrix[i] = (int*)malloc(x * sizeof(int));
            if (graf->matrix[i] == NULL) {
                printf("Failed to allocate row %d in graph\n", i);
                exit(1); // terminate if allocation fails
            }
            for (int j = 0; j < x; j++) {
                graf->matrix[i][j] = 0;
            }
        }
    } else {
        printf("Failed to allocate graph matrix\n");
        exit(1); // terminate if allocation fails
    }
}

void keyAppend(keyList* keyL, Key keyG) {
    keyList p1 = (keyList)malloc(sizeof(KeyMsg));
    if (p1 != NULL) {
        p1->info = keyG;
        p1->next = NULL;
        if (*keyL == NULL) {
            *keyL = p1;
        } else {
            keyList p = *keyL;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = p1;
        }
    } else {
        printf("Failed to allocate KeyMsg\n");
        exit(1);
    }
}

void graphAppend(graphList* grafL, Graph grafVal) {
    graphList g1 = (graphList)malloc(sizeof(GraphMsg));
    if (g1 != NULL) {
        g1->graf = grafVal;
        g1->next = NULL;
        if (*grafL == NULL) {
            *grafL = g1;
        } else {
            graphList g = *grafL;
            while (g->next != NULL) {
                g = g->next;
            }
            g->next = g1;
        }
    } else {
        printf("Failed to allocate GraphMsg\n");
        exit(1);
    }
}

void displayGraph(Graph g) {
    for (int i = 0; i < g.len; i++) {
        for (int j = 0; j < g.len; j++) {
            printf("%d ", g.matrix[i][j]);
        }
        printf("\n");
    }
}

