/*skip_list.c*/
/*
 *MAX_HEIGHT ------> numero massimo possibile di puntatori che ogni nodo potrebbe avere
 *size ------> numero effettivo di puntatori in un determinato nodo
 *max_level ------> massimo attuale tra i vari size (in un dato istante)
*/

#include "skip_list.h"

/*
 *Creazione di un singolo nodo. Prende come parametri in ingresso valore (key) e il livello (size) estratto random.
 *Array di next inizialmente deve puntare a tutti null. Poi i collegamenti corretti saranno fatti in fase di inserimento.
*/
Node* create_node(void *item, int lvl){
	Node *new = (Node*)malloc(sizeof(Node));
	new->next = (Node**)malloc(lvl * sizeof(Node*));
	new->size = lvl;
	new->item = item;

	return new;
}

/*
 *Creazione della lista vuota. Inizialmente è un solo nodo head di item void, max_level = size = 1 e Node.next inizialmente tutti void.
 *L'argomento 'comp_func' indica la funzione di comparazione degli elementi che andranno a costituire la lista.
*/
SkipList* create_empty_skip_list(int (*comp_func)(void * i_1, void * i_2)){
	SkipList *new = (SkipList*) malloc(sizeof(SkipList));
	
	if(comp_func==NULL){
		perror("function compare is null");
		exit(EXIT_FAILURE);
	}

	new->head = create_node(NULL, 1);
	new->max_level = 1;
	new->compare = comp_func;
	
	return new;
}

/*
 *Funzione probabilistica che decide la size di ogni nuovo nodo. Più è basso il livello più è alta la probabilità
*/
int random_level(){
	int lvl = 1;
  // random() returns a random value in [0...1)
  while ( (random() /(double)RAND_MAX ) < 0.5 && lvl < MAX_HEIGHT){
    lvl++;
  }  
  return lvl;
}
/*lvl  probabilità
	1			1/2
	2			1/4
	3			1/8
	..		...
	n 		1/2^n			*/

/*
 * Funzione che aggiorna l'altezza dell'array next di head ogni qualvolta viene inserito un nodo con altezza maggiore di quella 
 * impostata fino in quel momento.
*/
void update_head_size(SkipList *list, int size) {
	Node *new_h = create_node(NULL, size);
	Node *prev_h;
	int j = 0;

	while(j < size) {
		if(j < list->max_level) 
			new_h->next[j] = (list->head)->next[j];
		else 
			new_h->next[j] = NULL;

		j++;
	}
	list->max_level = size;
	prev_h = list->head;
	list->head = new_h;
	free(prev_h->next);
	free(prev_h);
}

/*
 * Funzione che inserisce un nuovo nodo nella skiplist. Se il nuovo nodo ha size maggiore di max_level quest'ultimo viene aggiornato.
 * Al termine dell'inserimento ovviamente la skiplist rimane ordinata e il nuovo nodo è stato inserito in posizione corretta.
*/
void insert_skip_list(SkipList *list, void *itm) {
	int k;
	Node *new = create_node(itm, random_level());

	if (new->size > list->max_level)
		update_head_size(list, new->size);

  Node *x = list->head;
  for(k = list->max_level - 1; k >= 0; k--) {
  	if(x->next[k] == NULL || list->compare(new->item, (x->next[k])->item)) {
  		if(k < new->size) {
  			new->next[k] = x->next[k];
  			x->next[k] = new;
  		}
  	}
  	else {
  		x = x->next[k];
  		k++;
  	}
  }
}

/*
 * Funzione che cerca un elemento all'interno della skiplist.
 * Se esiste e se in posizione trovata è presente proprio l'elemento desiderato allora ritorna tale elemento.
 * Ritorna nil altrimenti.
*/
void* search_skip_list(SkipList *list, void *itm){
	if(list == NULL) {
		fprintf(stderr, "Error, list null in search!\n");
		exit(EXIT_FAILURE);
	}
	if(itm == NULL) {
		fprintf(stderr, "Error, item null in search!\n");
		exit(EXIT_FAILURE);
	}
	Node *x = list->head;
	int i = (int) list->max_level-1;

  while( i >= 0 ){
   	while ( x->next[i]!=NULL && list->compare((x->next[i])->item, itm)){
      x = x->next[i];
    }
    i--;
  }

  if( (list->compare((x->next[i+1])->item, itm) == 0) && (list->compare(itm, (x->next[i+1])->item) == 0) )
    return itm;
  else
    return NULL;
}

/*
 * Deallocazione di tutte le strutture della lista e dei nodi nonchè tutte le informazioni ad esse associate. 
*/
void delete_skip_list(SkipList *list){
	Node *x;

	while( list->head != NULL ){
		x = list->head;
		list->head = (list->head)->next[0];
		free(x->next);
		free(x);
	}
	free(list);
}