#include "queue.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

Queue *initQueue() {
  Queue *q = malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
};

void enqueue(Queue *q, Node *n) {
  Item *item = malloc(sizeof(Item));
  item->node = n;
  item->next = NULL;
  if (q->head == NULL) {
    q->head = item;
  } else {
    q->tail->next = item;
  }
  q->tail = item;
};

Node *dequeue(Queue *q) {
  if (q->head == NULL) {
    printf("The queue is empty!\n");
    exit(0);
  }

  Node *head = q->head->node;

  q->head = q->head->next;
  if (q->head == NULL) {
    q->tail = NULL;
  }
  return head;
};