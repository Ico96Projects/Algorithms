/*skip_list.h*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

#define MAX_HEIGHT 100

typedef struct _SkipList SkipList;
typedef struct _Node Node;

struct _SkipList {
  Node *head;
  int max_level;
  int (*compare)(void*, void*);
  /*nel main compare sarà string_compare*/
};

struct _Node {
  Node **next;
  int size;
  void *item;
};


/*---------- METHODS ----------*/
/*
Node* create_node(void *item, int lvl);

int random_level();
*/
void insert_skip_list(SkipList *list, void *itm);

SkipList* create_empty_skip_list(int (*comp_func)(void *, void *));

void* search_skip_list(SkipList *list, void *itm);

void delete_skip_list(SkipList *list);