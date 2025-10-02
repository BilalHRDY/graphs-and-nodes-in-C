#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

#define MAX_CHILDREN 3

typedef struct Node {
  int key;
  int childrenSize;
  struct Node *children[];
} Node;

typedef struct Graph {
  size_t size;
  struct Node *nodes[];
} Graph;

typedef struct Adjacent {
  int key;
  int values[MAX_CHILDREN];
} Adjacent;

typedef struct Queue Queue;

void enqueue(Queue q, Node n);

Graph *initGraph(Adjacent *list, size_t listSize);

void freeGraph(Graph *graph);

#endif
