#include "node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Children {
  size_t size;
  int values[];
} Children;

Children *getValuesInListByKey(Adjacent *list, size_t listSize, int nodeKey) {

  for (size_t i = 0; i < listSize; i++) {
    if (nodeKey == list[i].key) {

      int count = 0;
      for (size_t j = 0; j < MAX_CHILDREN; j++) {
        if (list[i].values[j] == -1) {
          break;
        }
        count++;
      }

      Children *children = malloc(sizeof(Children) + count * sizeof(int));
      children->size = count;
      for (size_t j = 0; j < count; j++) {
        children->values[j] = list[i].values[j];
      }

      return children;
    }
  }

  printf("Key : %d not found in list!\n", nodeKey);
  exit(0);
};

Node *searchNodeInGraph(Graph *graph, int key) {
  for (size_t i = 0; i < graph->size; i++) {
    if (graph->nodes[i]->key == key) {
      return graph->nodes[i];
    };
  };
  return NULL;
};

Node *createNode(int key, Adjacent *list, size_t listSize, Graph *graph) {

  Node *existing = searchNodeInGraph(graph, key);
  if (existing != NULL)
    return existing;

  Children *childValues = getValuesInListByKey(list, listSize, key);

  Node *node = malloc(sizeof(Node) + childValues->size * sizeof(Node *));
  node->key = key;
  node->childrenSize = 0;

  graph->nodes[graph->size++] = node;

  for (size_t i = 0; i < childValues->size; i++) {
    int childKey = childValues->values[i];
    Node *child = createNode(childKey, list, listSize, graph);
    node->children[i] = child;
    node->childrenSize++;
  }

  free(childValues);
  return node;
}

Graph *initGraph(Adjacent *list, size_t listSize) {

  Graph *graph = malloc(sizeof(Graph) + (listSize * sizeof(Node *)));
  graph->size = 0;
  createNode(list[0].key, list, listSize, graph);

  return graph;
}

void freeGraph(Graph *graph) {
  for (size_t i = 0; i < graph->size; i++) {
    free(graph->nodes[i]);
  }
  free(graph);
}
