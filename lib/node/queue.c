#include "queue.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

void enqueue(Queue *q, Node *n) { q->nodes[q->tail++] = n; };

Node *dequeue(Queue *q) {
  if (q->head == q->tail) {
    printf("The queue is empty!\n");
    exit(0);
  }
  Node *first = q->nodes[q->head++];
  return first;
};