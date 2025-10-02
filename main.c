#include "lib/node/node.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Tester avec des sauts dans les indexes
  Adjacent list[] = {{0, {1, 2, -1}},
                     {1, {3, 4, -1}},
                     {2, {3, -1}},
                     {3, {-1, -1}},
                     {4, {-1, -1}}};

  // Adjacent list[] = {
  //     {0, {1, 2, -1}},
  //     {1, {2, -1, -1}},
  //     {2, {-1, -1, -1}},
  // };

  Graph *graph = initGraph(list, sizeof(list) / sizeof(Adjacent));
  printf("\n");

  char buffer[256];

  size_t pos = 0;

  for (size_t i = 0; i < graph->size; i++) {
    printf("node %d\n", graph->nodes[i]->key);
    pos += snprintf(buffer + pos, sizeof(buffer) - pos, "node : %d ",
                    graph->nodes[i]->key);

    printf("childrenSize: %d\n", graph->nodes[i]->childrenSize);

    for (size_t j = 0; j < graph->nodes[i]->childrenSize; j++) {

      char *str = "children : ";
      if (j > 0) {
        str = "";
      }
      pos += snprintf(buffer + pos, sizeof(buffer) - pos, "%s %d ", str,
                      graph->nodes[i]->children[j]->key);
    }
    pos += snprintf(buffer + pos, sizeof(buffer) - pos, "\n");
  };

  printf("%s\n", buffer);

  for (size_t i = 0; i < graph->size; i++) {
    free(graph->nodes[i]); // libère chaque Node
  }
  free(graph); // libère le Graph
}

// Adjacent hashmap[] = {
//     {0, {1, 4}}, {1, {2, -1}}, {2, {-1, -1}}, {4, {-1, -1}}, {5, {-1, -1}}};
// {0, {1, 3}}, {1, {2, -1}}, {2, {0, -1}}, {3, {-1, -1}}};

/* Une structure avec un FAM dans la heap

#include <stddef.h>
#include <stdio.h>

typedef struct Graph {
    int size;
    int numbers[];
} Graph;

int main() {

printf("sizeof(Graph) : %zu",sizeof(Graph)); // 4 octets, on ne compte pas le
tableau

Graph *g = malloc(2*(sizeof(Graph) + sizeof(int)));

g->size = 1;
g->numbers[0] = 2;

g = g+1; // le pointeur ne se décale que de 4 octets
g->size = 3;
g->numbers[0] = 4;

}
*/

/* Une structure avec un FAM dans la stack (à éviter)

typedef struct Graph {
    int size;
    int numbers[];
} Graph;

int main() {

printf("sizeof(Graph) : %zu",sizeof(Graph)); // 4 octets, on ne compte pas le
tableau Graph g;

g.size = 1;
g.numbers[0] = 2;

int a = 3; // 'a' est la même adresse que g.numbers[0]
}

*/

/* Une structure dans la stack avec un pointeur vers un tableau dans la heap

typedef struct Graph {
    int size;
    int *numbers;
} Graph;


int main() {

printf("sizeof(Graph) : %zu",sizeof(Graph)); // 8 + 8 octets
Graph g;

g.size = 1;
g.numbers = malloc(4 + 4);

g.numbers[0] = 2;
g.numbers[1] = 3;

g.numbers = g.numbers + 1;

printf("g.numbers[0] : %d",g.numbers[0]); // 3

g.numbers[2] = 4; // erreur car pas de mémoire initialisée à cet index
}
*/

/* Une structure dans la heap avec un pointeur vers un tableau

typedef struct Graph {
    int size;
    int *numbers;
} Graph;


int main() {

printf("sizeof(Graph) : %zu",sizeof(Graph));
Graph *g = malloc(sizeof(Graph)); // 16 octets

g->size = 1;
g->numbers = malloc(4 + 4);

g->numbers[0] = 2;
g->numbers[1] = 3;

g->numbers = g->numbers+1;

printf("g.numbers[0] : %d",g->numbers[0]);


g->numbers[2] = 4; // erreur car pas de mémoire initialisée à cet index

}

On a un pointeur de la stack qui pointe vers la structure dans la heap,
la structure a elle-même un pointeur qui pointe vers un tableau de int

*/

/* Une structure dans la heap contenant un tableau de pointeurs vers des
tableaux de int

typedef struct Graph {
    int size;
    int *numbers[];
} Graph;


int main() {

printf("sizeof(Graph) : %zu",sizeof(Graph)); // 8 octets : 4 int + 4 padding
Graph *g = malloc((sizeof(Graph) + sizeof(int*) + + sizeof(int*)));

g->size = 1;

g->numbers[0] = malloc(4);
g->numbers[1] = malloc(4);

*(g->numbers[0]) = 2;
*(g->numbers[1]) = 3;

}

g = g + 1;  // le pointeur est décalé de 8 octets

printf("*(g->numbers[0]) : %d", *(g->numbers[0]) ); // 3

*/