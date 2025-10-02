#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

#define MAX_CHILDREN 3

typedef struct Node {
  int key;
  int childrenSize;
  struct Node *children[];
} Node; // size = 4 + 4 (padding) + 2 * 8 = 24 octets

typedef struct Graph {
  size_t size;
  struct Node *nodes[];
} Graph; // size = 8 * 5 + 4 = 44 octets

typedef struct Adjacent {
  int key;
  int values[MAX_CHILDREN];
} Adjacent;

typedef struct Queue Queue;

void enqueue(Queue q, Node n);

Graph *initGraph(Adjacent *list, size_t listSize);

#endif
