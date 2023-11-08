#include "sort.h"

/*global variables*/
int (*compare)(void *, void *) = NULL;

/*implementazione della ricerca dicotomica:*/
int binary_search (void **array, void *item, int low, int high) {
  int mid;

  if (high <= low )
    /*(condizione boolean) ? istr_se_true : istr_se_false*/
    return ( compare( item, array[low] ) > 0 ) ? (low + 1) : low; /* item > array[low] */
  mid = (low + high) / 2;

  if ( compare(item, array[mid]) == 0 ) /* item == array[mid] */
    return mid + 1;

  if ( compare( item, array[mid] ) > 0 ) /* item > array[mid] */
    return binary_search(array, item, mid + 1, high);

  return binary_search(array, item, low, mid - 1);
}

/*implementazione dell'algoritmo di ordinamento basato su una versione modificata di insertion sort.
 *Questa versione sfrutta la ricerca dicotomica per andare a trovare la corretta posizione.
*/
void binary_insertion_sort (unsigned int length_array, void **array) {
  int index_item, i=1, j;
  void *selected;

  while ( i < length_array ){
    j = i - 1;
    selected = array[i];
    index_item = binary_search(array, selected, 0, j);

    while (j >= index_item && array[j+1]!=NULL){ /*shifta a dx per fare spazio all'elemento da inserire*/
      array[j + 1] = array[j];
      j--;
    }
    /*qui j+1 = index_item*/
    array[j + 1] = selected; /*j+1 perchè j viene decrementato una volta ancora dopo aver trovato la giusta posizione.*/
    i++;
  }
} 

/*implementazione di partition impostando come perno l'elemento finale dell'array passato come argomento.*/
int partition_high(void **array, int low, int high) {
  void *temp;
  int i, j;
  void *pivot;
  int choice = high;

  pivot = array[choice];
  i = low - 1;

  for(j = low; j < high; j++) {
    if (compare(array[j], pivot) <= 0) {
      i++;
      temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }
  temp = array[i + 1];
  array[i + 1] = array[high];
  array[high] = temp;

  return i + 1;
}

/*implementazione di partition impostando come perno l'elemento iniziale dell'array passato come argomento.*/
int partition_low(void **array, int low, int high) {
  void *pivot = array[low];
  int i = low + 1, j = high + 1;
  void *temp;

  while (i <= j) {
    if(array[i] <= pivot) {
      i++;
    }
    else {
      if(array[j] > pivot) {
        j--;
      }
      else {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
      }
    }
  }/*a questo punto avremo j == i - 1*/
  temp = array[low];
  array[low] = array[j];
  array[j] = temp;
  return j;
}

/*implementazione di partition impostando come perno un elemento casuale compreso tra inizio e fine dell'array passato come argomento.*/
int partition_rand(void **array, int low, int high) {
  void *temp, *pivot;
  int i, j;
  int val = low + rand() % (high - low);

  temp = array[val];
  array[val] = array[high];
  array[high] = temp;

  pivot = array[high];
  i = low - 1;

  for(j = low; j < high; j++) {
    if (compare(array[j], pivot) <= 0) {
      i++;
      temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }
  temp = array[i + 1];
  array[i + 1] = array[high];
  array[high] = temp;

  return i + 1;
}


void quick_sort (void **array, int low, int high){
  if (low < high) {
    int p;
    /*scommentare la scelta che si desidera per il perno:*/
    p = partition_high(array, low, high); 
/*  p = partition_low(array, low, high);  */
/*  p = partition_rand(array, low, high); */ 
    quick_sort(array, low, p -1);
    quick_sort(array, p + 1, high);
  }
}

void initialize_sorting(unsigned int length_array, const char *sorting_algorithm, void **array, int (*this_compare)(void *, void *) ){
  
  if(length_array!=0 && length_array!=1 && array != NULL){

    compare = this_compare;
    if ( compare == NULL ) {
      perror("\nERROR : we have no compare function\n");
      exit(EXIT_FAILURE);
    }

    if( strcmp(sorting_algorithm, "binary_insertion_sort") == 0 )
      binary_insertion_sort(length_array, array);
    
    else if( strcmp(sorting_algorithm, "quick_sort") == 0 )
      quick_sort(array, 0, length_array - 1);

    else
      printf("\n\n we don't provide the following sorting algorithm:   %s", sorting_algorithm);
  }

}