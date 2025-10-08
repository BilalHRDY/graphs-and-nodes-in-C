#include "../node/node.h"
#include "../node/queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool routeBetweenNodes(Node *src, Node *dst) {
  Queue *q = initQueue();

  Node *current = src;
  enqueue(q, current);

  while (!isEmpty(q)) {
    current = dequeue(q);

    if (current->key == dst->key) {
      printf("true : src %d dst %d\n", src->key, dst->key);
      return true;
    }
    for (size_t i = 0; i < current->childrenSize; i++) {
      enqueue(q, current->children[i]);
    }
  }
  free(current);
  free(q);

  printf("false : src %d dst %d\n", src->key, dst->key);

  return false;
}
