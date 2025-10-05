#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include <stddef.h>

#define QUEUE_MAX_SIZE 2

typedef struct Queue {
  size_t maxSize;
  size_t tail;
  struct Node *nodes[];
} Queue;

Queue *enqueue(Queue *q, Node *n);
Node *dequeue(Queue *q);

#endif
