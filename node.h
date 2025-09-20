#ifndef UTILS_H
#define UTILS_H

typedef struct Node {
  int name;
  struct Node *children[2];
} Node;

typedef struct Graph {
  struct Node *nodes[5];
  int size;
} Graph;

typedef struct Adjacent {
  int key;
  int values[2];
} Adjacent;

typedef struct Queue Queue;

void enqueue(Queue q, Node n);

#endif
