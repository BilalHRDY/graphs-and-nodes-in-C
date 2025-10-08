#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include <stdbool.h>
#include <stddef.h>

#define QUEUE_MAX_SIZE 2

typedef struct Item {
  struct Node *node;
  struct Item *next;
} Item;
typedef struct Queue {
  Item *head;
  Item *tail;
} Queue;

Queue *initQueue();
void enqueue(Queue *q, Node *n);
Node *dequeue(Queue *q);
bool isEmpty(Queue *q);

#endif
