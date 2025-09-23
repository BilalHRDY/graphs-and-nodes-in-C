#include "lib/node/node.h"
#include <stdio.h>

int main() {
  // Attention dans le cas où il a des sauts dans les index
  Adjacent list[] = {{0, {1, 3}}, {1, {2, -1}}, {2, {0, -1}}, {3, {-1, -1}}};

  Graph *graph = initGraph(list, sizeof(list) / sizeof(list[0]));

  for (size_t i = 0; i < graph->size; i++) {
    printf("node %d\n", graph->nodes[i]->key);
  };
}

// Adjacent hashmap[] = {
//     {0, {1, 4}}, {1, {2, -1}}, {2, {-1, -1}}, {4, {-1, -1}}, {5, {-1, -1}}};
