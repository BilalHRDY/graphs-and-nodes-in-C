#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int name;
  struct Node *children[2];
} Node;

typedef struct Graph {
  struct Node *nodes[5];
  int size;
} Graph;

typedef struct Adjacent {
  int key;
  int values[2];
} Adjacent;

int createNode(Node *rootNode, Adjacent *hashmap, size_t hashmapSize,
               Graph *graph) {
  int i = 0;
  int *childValues = NULL;
  size_t childCount = 0;
  printf("RootNode: %i\n", rootNode->name);

  // Itération sur la hashmap pour retrouver les valeurs enfants du node
  while (i != hashmapSize / sizeof(Adjacent)) {

    if (rootNode->name == hashmap[i].key) {
      printf("Key %i was found in hashmap\n", hashmap[i].key);

      childValues = hashmap[i].values;
      childCount = sizeof(hashmap[i].values) / sizeof(hashmap[i].values[0]);
      break;
    }
    i++;
  };

  if (childValues == NULL) {
    printf("Key not found in hashmap!\n");
    return -1;
  }

  // Itération sur les valeurs enfants pour les créer récursivement
  for (size_t i = 0; i < childCount; i++) {
    int childValue = childValues[i];
    printf("For rootNode : %i , child value : %i \n", rootNode->name,
           childValue);

    if (childValue == -1) {
      break;
    };

    bool nodeAlreadyExist = false;
    // Node *childNode = NULL;

    // Itération sur le graph pour checker si le node enfant existe déjà
    for (size_t j = 0; j < graph->size; j++) {
      if (graph->nodes[j]->name == childValue) {
        printf("child value : %i has been found in graph\n", childValue);
        nodeAlreadyExist = true;
        rootNode->children[i] = graph->nodes[j];
        break;
      };
    };

    if (!nodeAlreadyExist) {
      printf("Create child node : %i\n", childValue);

      Node *node = malloc(sizeof(Node));
      node->name = childValue;
      graph->nodes[graph->size++] = node;
      rootNode->children[i] = node;
      createNode(node, hashmap, hashmapSize, graph);
    }
  }
  return 0;
}

int initLinkedList(Adjacent *hashmap, Graph *graph, size_t hashmapSize) {

  Node *rootNode = malloc(sizeof(Node));
  rootNode->name = hashmap[0].key;

  graph->nodes[0] = rootNode;
  graph->size++;

  createNode(rootNode, hashmap, hashmapSize, graph);

  return 0;
}

int main() {
  sayHello("Alice");
  // Attention dans le cas où il a des sauts dans les index
  Adjacent hashmap[] = {{0, {1, -1}}, {1, {2, -1}}, {2, {0, -1}}};

  Graph graph = {0};
  initLinkedList(hashmap, &graph, sizeof(hashmap));
}

// Adjacent hashmap[] = {
//     {0, {1, 4}}, {1, {2, -1}}, {2, {-1, -1}}, {4, {-1, -1}}, {5, {-1, -1}}};
