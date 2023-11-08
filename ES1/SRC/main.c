/*ESERCIZIO 1
* Libreria che mette a disposizione due algoritmi, Quick Sort e Binary Insertion Sort.
* Non fare una classe, semplicemente algoritmi devono essere generici, non per un tipo specifico.
* "void**" array di puntatori generici. In input (non da tastiera ma puntatore a funzione) criterio di come ordinare i dati.
* Due algoritmi diversi, da linea di comando utilizzatore della libreria andrà a specificare quale dei due vuole usare.
* Quick Sort --> scegliere pivot casualmente (ANALIZZARE LE DIVERSE SCELTE) e scambiarlo con primo (o ultimo) elemento e 
*                utilizzare algoritmo canonico visto a lezione.
* Binary Insertion Sort --> come insertion sort visto a lezione ma anzichè scandire linearmente la struttura operare una 
*                           ricerca dicotomica fino a trovare l'unica posizione possibile in cuio inserire.
*                           In ogni caso shiftare verso dx gli elementi fuori posto è obbligatorio.
* Non usare tutti i 20mln di record in un colpo solo. Fare più file .csv di dimensioni diverse (10k, 100k, 500k, 1mln, ...) e 
* osservare il comportamento degli algoritmi al crescere delle dimensioni (COSTRUIRE GRAFICI E ANALIZZARLI NELLA RELAZIONE 
* ASSIEME ALLA SPIEGAZIONE DI COME ABBIAMO STRUTTURATO L'INPUT E MOTIVANDO LA NOSTRA SCELTA.).
* Mi aspetto che al crescere delle dimensioni del file aumenti il tempo.
* Criterio di ordinamento --> confronto rispetto a F1, se non basta confronto rispetto a F2, se ancora non basta F3 e se a 
*                            questo punto ancora non so differenziarli allora sono uguali e quindi prima uno o l'altro è
*                            indifferente.
*                            Questi criteri(almeno 3) sono definiti nell'applicazione ed funzione passata per puntatore.
*                            (guardare "precedes_record_string_field") 
*
*
* Convenzioni per il linguaggio C:
*   THE_MACRO     THE_CONSTANT
*   macro e costanti: tutto maiuscolo, parole separate da _ (SNAKE_CASE)
*
*   TheType       TheStruct         
*   tipi e struct: tutto minuscolo tranne la prima lettera della parola (CamelCase)
*
*   the_function()                 
*   funzioni: tutto minuscolo, parole separate da _ (SNAKE_CASE)
*/

#include "sort.h"

#define FILE_TO_STORE_SORTED_ARRAY "result.csv"
#define FILE_TO_STORE_DATA "data.csv"

/*    
TO  COMPILE (aprire un terminale e posizionarsi nella cartella ES1)

gcc -std=c89 -pedantic -Wall SRC/main.c SRC/sort.c SRC/sort.h -o EXE/esercizio_1

TO RUN (bisogna avere nella cartella ES1 il file record.csv)

EXE/esercizio_1 records.csv

GIT: (aprire un terminale e posizionarsi nella cartella ES1)

git pull

git add dati_per_relazione.xlsx Relazione.docx SRC/unit_test.c SRC/main.c SRC/sort.c SRC/sort.h EXE/unit_test.exe EXE/esercizio_1
git commit -m ""
git push
*/
unsigned int length_array;
/*ATTENZIONE! limit serve per limitare la dimensione del file .csv in modo da capire come cambiano i tempi in base alla dimensione*/
unsigned int limit = 5000000;
/*	struct for records in the file (record.csv)	*/
struct record {
	int id;
	int integer;
	char *string;
	double floating_point;
};

/* 
corrispondono all'ordine di importanza di ordinamento dei campi
  esempio: se vogliamo ordinare sui int
            f_1 = int_compare
            f_2 = string_compare
            f_3 = double_compare
*/
int (*f_1)(void *, void *) = NULL;
int (*f_2)(void *, void *) = NULL;
int (*f_3)(void *, void *) = NULL;

void print_array(void **array){
  unsigned int i = 0;
  struct record *this_record;
  while ( i < length_array && array[i]!=NULL) {
    this_record = (struct record *)array[i];
    printf(" %d : ", this_record->id );
    printf(" %s ", this_record->string );
    printf(" %d ", this_record->integer );
    printf(" %f ", this_record->floating_point );
    i++;
    printf("\n");
  }
}

void free_mem(void **array){
  unsigned int i=0;
  struct record *this_record;
  while( i < length_array && array[i]!=NULL){
    this_record = (struct record *)array[i];
    free(this_record->string);
    free(array[i]);
    i++;
    }
  free(array);
}

int type_compare(void *first, void *second){
  int result;

  result = f_1(first, second);
  if( result == 0 ){
    result = f_2(first, second);
      if( result == 0 ){
        result = f_3(first, second);
      }
  }
  return result;
}

int int_compare(void *first_v, void *second_v){
  struct record *first  = (struct record *)first_v;
  struct record *second = (struct record *)second_v;
  if(first == NULL && second == NULL)
    return 0;
  if (first == NULL) 
    return -1;
  if (second == NULL)
    return 1;

  if (first->integer > second->integer)
    return 1;
  if (first->integer < second->integer)
    return -1;
  return 0;
  }

int string_compare(void *first_v, void *second_v){
  struct record *first  = (struct record *)first_v;
  struct record *second = (struct record *)second_v;
  if(first == NULL && second == NULL)
    return 0;
  if (first == NULL)
    return -1;
  if (second == NULL)
    return 1;

  return strcasecmp(first->string, second->string);
  }

int double_compare(void *first_v, void *second_v){
  struct record *first  = (struct record *)first_v;
  struct record *second = (struct record *)second_v;
  if(first == NULL && second == NULL)
    return 0;
  if (first == NULL) 
    return -1;
  if (second == NULL)
    return 1;

  if (first->floating_point > second->floating_point)
    return 1;
  if (first->floating_point < second->floating_point)
    return -1;
  return 0;
  }

void** load_array(const char *file_path){
  struct record *this_record;
  unsigned int i=0;
  char *read_line_p, *string_tmp, buffer[1024];
  int buf_size = 1024;
  void **array_to_sort;
  FILE *fp;
  length_array = 1000;

  printf("\n Loading data from file %s", file_path);
  fp = fopen(file_path,"r");

  if(fp == NULL){
    printf("\nERROR: fp is NULL, impossible to open the file  %s\n",file_path);
    exit(EXIT_FAILURE);
    }
  array_to_sort = malloc(sizeof(void*)* length_array);

  while((fgets(buffer, buf_size, fp) != NULL) && (i < limit)){

    if( length_array == i ){ /* dynamic array */
      length_array = length_array * 2;
      array_to_sort = realloc (array_to_sort, sizeof(void*) * length_array );
      }

    read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
    if(read_line_p == NULL){
      printf("\n\n struct allocated = %d",i);
      printf("\nERROR : unable to allocate memory for the read line");
      exit(EXIT_FAILURE);
      }   
    strcpy(read_line_p, buffer); 

    this_record = malloc(sizeof(struct record));
    if(this_record == NULL){
      printf("\n\n struct allocated = %d",i);
      printf("\nERROR : unable to allocate memory for the struct record");
      exit(EXIT_FAILURE);
      }  
    /* set all values */
    this_record->id = atoi(strtok(read_line_p,","));
    string_tmp = strtok(NULL, ",");
    this_record->string = malloc((strlen(string_tmp) + 1) * sizeof(char));
    strcpy(this_record->string, string_tmp);
    this_record->integer = atoi(strtok(NULL,","));
    this_record->floating_point = atof(strtok(NULL,"\n"));

    if(this_record->string == NULL){
      printf("\n\n struct allocated = %d",i);
      printf("\nERROR : unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
      }
    array_to_sort[i] = (void *) this_record;
    free(read_line_p);
    i++;
    }
  fclose(fp);
  length_array = (unsigned int) i;
  printf("\n Read of file ended, allocated  %d  elements", length_array );
  return array_to_sort;
}

void write_file(void **array) {
  FILE *fp;
  int i = 0;
  struct record *this_record;
  char line[60], int_buf[20], float_buf[20];

  fp = fopen(FILE_TO_STORE_SORTED_ARRAY,"w");
  if(fp == NULL){
    printf("\nERROR: fp is NULL, impossible to open the file  %s\n",FILE_TO_STORE_SORTED_ARRAY);
    exit(EXIT_FAILURE);
  }
  while ( i < length_array && array[i]!=NULL) {
    this_record = (struct record *)array[i];
    sprintf(line, "%d", this_record->id);
    sprintf(int_buf, "%d", this_record->integer);
    sprintf(float_buf, "%f", this_record->floating_point);

    strcat(line, ", ");
    strcat(line, this_record->string);
    strcat(line, ", ");
    strcat(line, int_buf);
    strcat(line, ", ");
    strcat(line, float_buf);
    strcat(line, "\n");
    fwrite(line, 1, strlen(line), fp);
    i++;
/*
    fprintf(fp, "%d, %s, %d, %f\n", this_record->id, this_record->string, this_record->integer, this_record->floating_point);
*/
  }

  fclose(fp);
}


long sort_execute(const char *file_path, const char *sorting_algorithm) {
  clock_t start, end;
  void **array;

  start = clock();
  array = load_array(file_path);
  end = clock();
  
  printf ("  in  %ld  milliseconds",(end-start)*1000/CLOCKS_PER_SEC);
  
  start = clock();
  initialize_sorting(length_array, sorting_algorithm, array, type_compare);
  end = clock();
/*
  print_array(array);
*/
  write_file(array);

  free_mem(array);

  return ( (end-start)*1000 / CLOCKS_PER_SEC );
}


int main(int argc, char const *argv[]) {
  long time;
  int field_mode=0;
  char repeat;

  if (argc < 2) {
    printf("ERROR: Miss some input\n");
    exit(EXIT_FAILURE);
  }
/*
  raccolta_dati(argv[1],"binary_insertion_sort");
  raccolta_dati(argv[1],"quick_sort");
*/
  do{
    printf("\n ---------------------------------------------------------------------");
    printf("\n definire in base a quale campo principale ordinare i record: \n\t 1->int \n\t 2->string \n\t 3->double\n");
    do{
      printf("\n input: ");
      scanf("%d", &field_mode);
      if( field_mode != 1 && field_mode != 2 && field_mode != 3 )
        printf(" il valore inserito ( %d ) non e' valido!\n", field_mode);
    } while(field_mode != 1 && field_mode != 2 && field_mode != 3);

    switch(field_mode){
      
      case 1:
        printf("\n\n---------START SORTING INT FIELD");
        printf("\n   Priorita' di ordinamento: int, string, floating_point\n");
        f_1 = int_compare;
        f_2 = string_compare;
        f_3 = double_compare;
        break;

      case 2:
        printf("\n\n---------START SORTING STRING FIELD");
        printf("\n   Priorita' di ordinamento: string, floating_point, int\n");
        f_1 = string_compare;
        f_2 = double_compare;
        f_3 = int_compare;
        break;

      case 3:
        printf("\n\n---------START SORTING FLOATING POINT FIELD");
        printf("\n   Priorita' di ordinamento: floating_point, int, string\n");
        f_1 = double_compare;
        f_2 = int_compare;
        f_3 = string_compare;
        break;

      default:
        printf("\nERRORE field_mode\n");
        exit(EXIT_FAILURE);
        break;
    }

    /*scommentare codice in base a quale algoritmo di ordinamento si desidera utilizzare:*/
 
    time = sort_execute(argv[1],"binary_insertion_sort");
    printf ("\n\n  Time of sorting field using binary_insertion_sort;   %ld  milliseconds \n",time);
/*
    time = sort_execute(argv[1],"quick_sort");
    printf ("\n\n  Time of sorting using quick_sort;  %ld  milliseconds \n",time);
*/


    printf("\n\n Si desidera rieseguire l'ordinamento? [ input y per yes ]  ");
    scanf("%s", &repeat);
  }while(repeat=='y');

  printf("\n------------------------\n\t FINE \n------------------------\n");
  return (EXIT_SUCCESS);
}















void raccolta_dati(const char *file_path, const char *sorting_algorithm){
  int i = 0, max, increment;
  long time;
  FILE *fp;

  /* Segue la raccolta dati al cambiare della dimensione dell'array */
  while( i < 3){
    printf("----------------------------------");
    if(i == 0){
      printf(" INT FIELD");
      f_1 = int_compare;
      f_2 = string_compare;
      f_3 = double_compare;
    }
    if(i == 1){
      printf(" STRING FIELD");
      f_1 = string_compare;
      f_2 = double_compare;
      f_3 = int_compare;
    }
    if(i == 2){
      printf(" FLOATING POINT FIELD");
      f_1 = double_compare;
      f_2 = int_compare;
      f_3 = string_compare;
    }

    if(strcmp(sorting_algorithm, "quick_sort")==0){
      limit = 1000000;
      max = 20000000;
      increment = 1000000;
    }
    if(strcmp(sorting_algorithm, "binary_insertion_sort")==0){
      limit = 50000;
      max = 900000;
      increment = 50000;
    }

    while (limit <= max){   /* circa da qui la simulazione dura più di 10 minuti */
      
      time = sort_execute( file_path, sorting_algorithm );
      printf ("\n  Time of sorting field using %s;   %ld  milliseconds \n", sorting_algorithm, time);

      fp = fopen(FILE_TO_STORE_DATA, "w");
      if(fp == NULL){
        printf("\nERROR: fp is NULL, impossible to open the file  %s\n", FILE_TO_STORE_DATA);
        exit(EXIT_FAILURE);
      }
      fprintf(fp, "%d, %ld\n", limit, time);
      fclose(fp);
      
      limit = limit + increment;
    }
    i++;
  }
}