/*    
TO  COMPILE (aprire un terminale e posizionarsi nella cartella ex2)
make build/test_main_ex2

TO RUN 
build/test_main_ex2
*/

/*
I seguenti metodi sono interni alla libreria e non vanno testati
  - Node* create_node(void *item, int lvl);
  - int random_level();

Questo metodo non può essere testato:
  - void delete_skip_list(SkipList *list);

Faremo il testing di questi tre metodi:
  - SkipList* create_empty_skip_list(int (*comp_func)(void *, void *));
  - void insert_skip_list(SkipList *list, void *itm);
  - void* search_skip_list(SkipList *list, void *itm);

*/

#include "skip_list.h"
#define NUM_METHODS 3

int num_tests[NUM_METHODS];
char *(name_methods[NUM_METHODS]);
int *(results[NUM_METHODS]);
char **(print[NUM_METHODS]);
int index_method;
int count;


int string_compare(void *first_v, void *second_v){
  char *first  = (char *)first_v;
  char *second = (char *)second_v;

  if(first_v == NULL) {
    printf("ERROR! First paramater to compare is null");
    exit(EXIT_FAILURE);
  }
  if(second_v == NULL) {
    printf("ERROR! Second paramater to compare is null");
    exit(EXIT_FAILURE);
  }
  
  if(strcasecmp(first, second) < 0)
    return 1;
  return 0;
}

/*-------------------------------tests--start--here--------------------------------------------------*/
/*
SkipList* create_empty_skip_list(int (*comp_func)(void *, void *));

void insert_skip_list(SkipList *list, void *itm);

void* search_skip_list(SkipList *list, void *itm);
*/

void test_create_empty_skip_list(){
  int res=0;
  SkipList *list = create_empty_skip_list(string_compare);
  if( list->head->next!=NULL  &&
      list->head->size==1  &&
      string_compare((void *)list->head->item,(void *)"Head")==0  &&
      list->max_level==1  &&
      list->compare == string_compare)
  {
    res=1;
  }

  if ( res==1 ) {
    results[index_method][0]=1;
    count++;
  } else {
    results[index_method][0]=-1;
  }
  delete_skip_list(list);
}



void insert_into_empty_skip_list(){
  int res=0;
  SkipList *list = create_empty_skip_list(string_compare);
  insert_skip_list(list, (void *)"a");

  if( string_compare((void *)list->head->next[0]->item,(void *)"a")==0 )
    res=1;
  
  if ( res==1 ) {
    results[index_method][0]=1;
    count++;
  } else {
    results[index_method][0]=-1;
  }
  delete_skip_list(list);
}

void insert_first_node(){
  int res=0;
  SkipList *list = create_empty_skip_list(string_compare);
  insert_skip_list(list, (void *)"c");
  insert_skip_list(list, (void *)"b");
  insert_skip_list(list, (void *)"a");

  if( string_compare((void *)list->head->next[0]->item,(void *)"a")==0 )
    res=1;

  if ( res==1 ) {
    results[index_method][1]=1;
    count++;
  } else {
    results[index_method][1]=-1;
  }
  delete_skip_list(list);
}

void insert_middle_node(){
  int res=0;
  
  SkipList *list = create_empty_skip_list(string_compare);
  insert_skip_list(list, (void *)"c");
  insert_skip_list(list, (void *)"a");
  insert_skip_list(list, (void *)"b");

  if( string_compare((void *)list->head->next[0]->next[0]->item,(void *)"b")==0 )
    res=1;

  if ( res==1 ){
    results[index_method][2]=1;
    count++;
  } else {
    results[index_method][2]=-1;
  }
  delete_skip_list(list);
}

void insert_last_node(){
  int res=0;
  SkipList *list = create_empty_skip_list(string_compare);
  insert_skip_list(list, (void *)"a");
  insert_skip_list(list, (void *)"b");
  insert_skip_list(list, (void *)"c");

  if(string_compare((void *)list->head->next[0]->next[0]->next[0]->item,(void *)"c")==0)
    res=1; 
  
  if ( res==1 ) {
    results[index_method][3]=1;
    count++;
  } else {
    results[index_method][3]=-1;
  }
  delete_skip_list(list);
}

void test_insert_skip_list(){
  int rand_test, i=0;

  while( i < num_tests[index_method] ){
    do{/* randomizzo l'ordine dei test */
      rand_test = rand()%num_tests[index_method];
    }while(results[index_method][rand_test]!=0);

    switch(rand_test){
      case 0:
        insert_into_empty_skip_list();
        break;
      case 1:
        insert_first_node();
        break;
      case 2:
        insert_middle_node();
        break;
      case 3:
        insert_last_node();
        break;
      default:
        break;
    }
    i++;
  }
}




void search_into_empty_skip_list(){
  int res=0;
  char *obj="a";
  SkipList *list = create_empty_skip_list(string_compare);

  if( NULL==search_skip_list(list, (void *)obj) )
    res=1;

  if ( res==1 ) {
    results[index_method][0]=1;
    count++;
  } else {
    results[index_method][0]=-1;
  }
  delete_skip_list(list);
}

void search_first_node(SkipList *list){
  int res=0;

  if( string_compare( (void *)search_skip_list(list, (void *)"a" ) , (void *)"a")==0 )
    res=1;

  if ( res==1 ) {
    results[index_method][1]=1;
    count++;
  } else {
    results[index_method][1]=-1;
  }
  delete_skip_list(list);
}

void search_middle_node(SkipList *list){
  int res=0;

  if( string_compare( (void *)search_skip_list(list, (void *)"b" ), (void *)"b")==0 )
    res=1;

  if ( res==1 ) {
    results[index_method][2]=1;
    count++;
  } else {
    results[index_method][2]=-1;
  }
  delete_skip_list(list);
}

void search_last_node(SkipList *list){
  int res=0;

  if( string_compare( (void *)search_skip_list(list, (void *)"c" ), (void *)"c")==0 )
    res=1;

  if ( res==1 ) {
    results[index_method][3]=1;
    count++;
  } else {
    results[index_method][3]=-1;
  }
  delete_skip_list(list);
}

void test_search_skip_list(){
  int rand_test, i=0;
  SkipList *list = create_empty_skip_list(string_compare);
  insert_skip_list(list, (void *)"a");
  insert_skip_list(list, (void *)"b");
  insert_skip_list(list, (void *)"c");

  while( i < num_tests[index_method] ){
    do{/* randomizzo l'ordine dei test */
      rand_test = rand()%num_tests[index_method];
    }while(results[index_method][rand_test]!=0);

    switch(rand_test){
      case 0:
        search_into_empty_skip_list();
        break;
      case 1:
        search_first_node(list);
        break;
      case 2:
        search_middle_node(list);
        break;
      case 3:
        search_last_node(list);
        break;
      default:
        break;
    }
    i++;
  }
}



void print_all(){
  int index_me=0, index_test;

  while( index_me < NUM_METHODS ){
    index_test=0;
    printf("\n METHOD -> %s",name_methods[index_me]);
    while( index_test < num_tests[index_me] ){
      if ( results[index_me][index_test]==1 ) 
        printf("\n test case %s array   \tpassed", print[index_me][index_test]);
      else
        printf("\n test case %s array   \tNOT passed", print[index_me][index_test]);
      index_test++;
    }
    printf("\n");
    index_me++;
  }
  printf("\n\n");
}



int main(int argc, char const *argv[]) {
  int tot_tests=0, i=0;

  index_method=0;
  count=0;

  name_methods[0]="create_empty_skip_list";
  num_tests[0] = 1;
  name_methods[1]="insert_skip_list";
  num_tests[1] = 4;
  name_methods[2]="search_skip_list";
  num_tests[2] = 4;

  for(i=0; i<NUM_METHODS; i++){
    results[i] = (int*)malloc(sizeof (int) *num_tests[i]);
    print[i] = (char**)malloc(sizeof(char*)*num_tests[i]);
  }

  i=0;
  while( i < NUM_METHODS ){

    do{/* randomizzo l'ordine dei metodi da testare */
      index_method = rand()%NUM_METHODS;
    }while(results[index_method][0]!=0);

    tot_tests+=num_tests[index_method];

    switch(index_method){
      case 0:
        test_create_empty_skip_list();
        print[0][0]="create skip_list";
        break;
      case 1:
        test_insert_skip_list();
        print[1][0]="insert into empty skip_list";
        print[1][1]="insert first node";
        print[1][2]="insert middle node";
        print[1][3]="insert last node";
        break;
      case 2:
        test_search_skip_list();
        print[2][0]="search into an empty skip_list";
        print[2][1]="search first node";
        print[2][2]="search middle node";
        print[2][3]="search last node";
        break;
      default:
        break;
      }
    i++;
  }

  print_all();
/*
  if( count != tot_tests )
    print_all();
*/
  for(i=0; i<NUM_METHODS;i++){
    free(results[i]);
    free(print[i]);
  }

  return 0;
}