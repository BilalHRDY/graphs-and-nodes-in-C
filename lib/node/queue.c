#include "queue.h"
#include "node.h"

void enqueue(Queue *q, Node *n) { q->nodes[q->size++] = n; };

Node *dequeue(Queue *q) {
  Node *first = q->nodes[q->index++];
  return first;
};