/*    
TO  COMPILE (aprire un terminale e posizionarsi nella cartella ES1)

gcc -std=c89 -pedantic -Wall SRC/unit_test.c SRC/sort.c SRC/sort.h -o EXE/unit_test

TO RUN

EXE/unit_test

*/

#include "sort.h"
#define LENGTH 10
#define NUM_TESTS 4
#define NUM_SORTING_METHODS 2

int results[NUM_SORTING_METHODS][NUM_TESTS];
char *(print[NUM_TESTS]);
int index_method=0;
int count=0;
char *(sorting_algorithm[NUM_SORTING_METHODS]);

struct test {
  int num;
};


/* creo il metodo compare_integer, lavoreremo con array di int */
int compare_integer(void *first_v, void *second_v){
  struct test *first  = (struct test *) first_v;
  struct test *second = (struct test *) second_v;
  if(first_v == NULL && second_v == NULL)
    return 0;
  if (first_v == NULL) 
    return -1;
  if (second_v == NULL)
    return 1;

  if ( first->num > second->num )
    return 1;
  if ( first->num < second->num )
    return -1;
  return 0;
  }


/* questo metodo controlla che l'output della libreria sia uguale all'expected */
int check_output(void **expected, void **output, unsigned int length_array){
  int i=0;

  if( expected==NULL && output==NULL )
    return 1;
  
  while( i < length_array ){
    if( compare_integer( expected[i], output[i]) != 0 )
      return -1;
    i++;
  }
  return 1;
}

void print_arrays(void **expected, void **output, unsigned int length_array){
  int i=0;
  struct test *exp, *out;

  printf("\n\tarray->\ti     expected  output");
  while(i < length_array){
    exp = (struct test *) expected[i];
    out = (struct test *) output[i];
    printf("\n\t\t%d  \t  %d  \t   %d", i, exp->num, out->num);
    i++;
  }
}


void free_arrays(void **expected, void **output, unsigned int length_array){
  int i=0;
  while(i < length_array){
    free(expected[i]);
    free(output[i]);
    i++;
  }
}
/*-------------------------------tests--start--here--------------------------------------------------*/

/* controllo passando array NULL */
void test_sort_null_array(){
  unsigned int length_array = 0;
  void **output=NULL, **expected=NULL;

  initialize_sorting(length_array, sorting_algorithm[index_method], output, compare_integer);

  if ( check_output( expected, output, length_array)==1 ) {
    results[index_method][0]=1;
    count++;
  } else {
    results[index_method][0]=-1;
  }
}


/* controllo passando array con length=1 */
void test_sort_length_1_array(){
  unsigned int length_array=1;
  void *(output[1]), *(expected[1]);
  struct test *tmp1,*tmp2;
  tmp1 = (struct test*) malloc(sizeof(struct test));
  tmp2 = (struct test*) malloc(sizeof(struct test));
  tmp1->num = 3;
  tmp2->num = 3;
  output[0] = (void *) tmp1;
  expected[0] = (void *) tmp2;

  initialize_sorting(length_array, sorting_algorithm[index_method],(void**) output, compare_integer);

  if ( check_output( (void**)expected, (void**)output, length_array)==1 ) {
    results[index_method][1]=1;
    count++;
  } else {
    results[index_method][1]=-1;
  }
  free_arrays( expected, output, length_array);
}


/* controllo passando array ordinato */
void test_sort_ordered_array(){
  unsigned int length_array=LENGTH;
  int i=0;
  void *(output[LENGTH]), *(expected[LENGTH]);
  struct test *tmp1, *tmp2;

  while( i < length_array ){
    tmp1 = (struct test*) malloc(sizeof(struct test));
    tmp2 = (struct test*) malloc(sizeof(struct test));
    tmp1->num = i;
    tmp2->num = i;
    output[i] = (void *) tmp1;
    expected[i] = (void *) tmp2;
    i++;
  }
  initialize_sorting(length_array, sorting_algorithm[index_method],(void**) output, compare_integer);

  if ( check_output( (void**)expected, (void**)output, length_array)==1 ) {
    results[index_method][2]=1;
    count++;
  } else {
    results[index_method][2]=-1;
  }
  free_arrays( expected, output, length_array);
}


/* controllo passando array randomico da ordinare */
void test_sort_random_array(){
  unsigned int length_array=LENGTH;
  int i=0, random_index;
  void *(output[LENGTH]), *(expected[LENGTH]);
  struct test *tmp1, *tmp2, *scambio;

  while( i < length_array ){
    tmp1 = (struct test*) malloc(sizeof(struct test));
    tmp2 = (struct test*) malloc(sizeof(struct test));
    tmp1->num = i;
    tmp2->num = i;
    output[i] = (void *) tmp1;
    expected[i] = (void *) tmp2;
    i++;
  }
  i=0; /*randomizzo l'array output*/
  while( i < length_array ){
    random_index = rand()%length_array;
    scambio = output[i];
    output[i] = output[random_index];
    output[random_index] = scambio;
    i++;
  }
  initialize_sorting(length_array, sorting_algorithm[index_method],(void**) output, compare_integer);

  if ( check_output( (void**)expected, (void**)output, length_array)==1 ) {
    results[index_method][3]=1;
    count++;
  } else {
    results[index_method][3]=-1;
  }
  free_arrays( expected, output, length_array);
}




void print_all(){
  int index_me=0, index_test=0;

  while( index_me < NUM_SORTING_METHODS ){
    index_test=0;
    printf("\nSORT -> %s",sorting_algorithm[index_me]);
    while( index_test < NUM_TESTS ){
      if ( results[index_me][index_test]==1 ) 
        printf("\n test case %s array   \tpassed",print[index_test]);
      else 
        printf("\n test case %s array   \tNOT passed",print[index_test]);
      index_test++;
    }
    printf("\n");
    index_me++;
  }
  printf("\n\n");
}

int main(int argc, char const *argv[]) {
  int index_test=0, rand_test=0;
  sorting_algorithm[0] = "binary_insertion_sort";
  sorting_algorithm[1] = "quick_sort";

  print[0] ="null";
  print[1] ="length=1";
  print[2] ="ordered";
  print[3] ="randomised";

  while( index_method < NUM_SORTING_METHODS ){
    index_test=0;
    while( index_test < NUM_TESTS ){
      do{/* randomizzo l'ordine dei test */
        rand_test = rand()%NUM_TESTS;
      }while(results[index_method][rand_test]!=0);

      switch(rand_test){
        case 0:
          test_sort_null_array();
          break;
        case 1:
          test_sort_length_1_array();
          break;
        case 2:
          test_sort_ordered_array();
          break;
        case 3:
          test_sort_random_array();
          break;
        default:
          break;
        }
      index_test++;
    }
    index_method++;
  }

  if( count != NUM_TESTS*NUM_SORTING_METHODS )
    print_all();
  return 0;
}