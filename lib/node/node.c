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
      children->size = 0;
      for (size_t j = 0; j < count; j++) {
        children->size += 1;
        children->values[j] = list[i].values[j];
      }

      return children;
    }
  }

  printf("Key : %d not found in list!\n", nodeKey);
  exit(0);
};

Node *searchNodeInGraph(Graph *graph, int key) {

  // Itération sur le graph pour checker si le node existe déjà
  for (size_t i = 0; i < graph->size; i++) {
    if (graph->nodes[i]->key == key) {
      printf("node key : %i has been found in graph\n", key);
      return graph->nodes[i];
    };
  };
  return NULL;
};

void createNode(Node *rootNode, Adjacent *list, size_t listSize, Graph *graph) {
  if (rootNode == NULL) {
    rootNode = malloc(sizeof(Node));
    rootNode->key = list[0].key;
    rootNode->childrenSize = 0;

    graph->nodes[graph->size++] = rootNode;
  }

  Children *childValues = getValuesInListByKey(list, listSize, rootNode->key);

  for (size_t i = 0; i < childValues->size; i++) {
    if (rootNode->key == 1)
      printf("rootNode: %d,  childValues[i] : %d\n", rootNode->key,
             childValues->values[i]);
  }

  // Itération sur les valeurs enfants pour les créer récursivement
  for (size_t i = 0; i < childValues->size; i++) {
    int childValue = childValues->values[i];

    if (rootNode->key == 1) {
      printf("childValues->size : %zu, i : %zu\n", childValues->size, i);
      printf("childValue for 1 : %d\n", childValue);
    }
    rootNode->children[i] = searchNodeInGraph(graph, childValue);

    if (rootNode->children[i] == NULL) {
      printf("Create child node : %i\n", childValue);

      Node *node = malloc(sizeof(Node));
      node->key = childValue;
      node->childrenSize = 0;

      graph->nodes[graph->size++] = node;
      rootNode->children[i] = node;
      createNode(node, list, listSize, graph);
    }
    rootNode->childrenSize += 1;
  }

  free(childValues);
}

Graph *initGraph(Adjacent *list, size_t listSize) {

  Graph *graph = malloc(sizeof(Graph) + (listSize * sizeof(Node *)));
  graph->size = 0;
  createNode(NULL, list, listSize, graph);

  return graph;
}