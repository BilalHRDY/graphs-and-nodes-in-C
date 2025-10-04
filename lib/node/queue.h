#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include <stddef.h>

#define QUEUE_MAX_SIZE 5

typedef struct Queue {
  size_t maxSize;
  size_t tail;
  size_t head;
  struct Node *nodes[QUEUE_MAX_SIZE];
} Queue;

void enqueue(Queue *q, Node *n);
Node *dequeue(Queue *q);

#endif
