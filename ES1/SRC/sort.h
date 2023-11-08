#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

/*------------METHODS------------*/

int binary_search( void **subarray, void *item, int low, int high);

void binary_insertion_sort(unsigned int length_array, void **array);

int partition_high(void **array, int low, int high);
int partition_low(void **array, int low, int high);
int partition_rand(void **array, int low, int high);

void quick_sort (void **array, int low, int high);

void initialize_sorting(unsigned int length_array, const char *sorting_algorithm, void **array, int (*this_compare)(void *, void *));
