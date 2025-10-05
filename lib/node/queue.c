#include "queue.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

Queue *enqueue(Queue *q, Node *n) {
  if (q->tail == q->maxSize) {
    q->maxSize *= 2;
    q = realloc(q, sizeof(Queue) + q->maxSize * sizeof(Node));
  }

  q->nodes[q->tail++] = n;
  return q;
};

Node *dequeue(Queue *q) {
  if (q->tail == 0) {
    printf("The queue is empty!\n");
    exit(0);
  }
  Node *first = q->nodes[0];
  q->nodes[0] = NULL;

  for (size_t i = 0; i < q->tail; i++) {
    if (i == q->tail - 1) {
      q->nodes[i] = NULL;
      break;
    }
    q->nodes[i] = q->nodes[i + 1];
  }
  q->tail--;
  return first;
};