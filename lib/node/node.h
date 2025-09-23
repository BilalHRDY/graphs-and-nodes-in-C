#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

typedef struct Node {
  int key;
  struct Node *children[2];
} Node; // size = 4 + 4 (padding) + 2 * 8 = 24 octets

typedef struct Graph {
  struct Node *nodes[5];
  int size;
} Graph; // size = 8 * 5 + 4 = 44 octets

typedef struct Adjacent {
  int key;
  int values[2];
} Adjacent;

typedef struct Queue Queue;

void enqueue(Queue q, Node n);

Graph *initGraph(Adjacent *list, size_t listSize);

#endif
