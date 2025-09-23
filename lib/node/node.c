#include "node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Children {
  int children[2];
} Children;

Children getValuesInListByKey(Adjacent *list, size_t listSize, int nodeKey) {

  for (size_t i = 0; i < listSize; i++) {
    if (nodeKey == list[i].key) {
      Children children;
      memcpy(children.children, list[i].values, sizeof(children.children));
      return children;
    }
  }

  printf("Key not found in list!\n");
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
    graph->nodes[graph->size++] = rootNode;
  }

  Children childValues = getValuesInListByKey(list, listSize, rootNode->key);

  // Itération sur les valeurs enfants pour les créer récursivement
  for (size_t i = 0;
       i < sizeof(childValues.children) / sizeof(childValues.children[0]);
       i++) {
    int childValue = childValues.children[i];
    printf("For rootNode : %i , child value : %i \n", rootNode->key,
           childValue);

    if (childValue == -1) {
      break;
    };

    rootNode->children[i] = searchNodeInGraph(graph, childValue);

    if (rootNode->children[i] == NULL) {
      printf("Create child node : %i\n", childValue);

      Node *node = malloc(sizeof(Node));
      node->key = childValue;
      graph->nodes[graph->size++] = node;
      rootNode->children[i] = node;
      createNode(node, list, listSize, graph);
    }
  }
}

Graph *initGraph(Adjacent *list, size_t listSize) {

  Graph *graph = malloc(sizeof(Graph));
  graph->size = 0;

  createNode(NULL, list, listSize, graph);

  return graph;
}