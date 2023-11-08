/*main_ex2.c*/

/*    
TO  COMPILE (aprire un terminale e posizionarsi nella cartella ex2)

make build/main_ex2 

TO RUN (bisogna avere nella cartella ex2 i file 'dictionary.txt' e 'correctme.txt')

build/main_ex2 dictionary.txt correctme.txt

GIT: (aprire un terminale e posizionarsi nella cartella ex2)

git pull

git add source/skip_list.c source/skip_list.h source/main_ex2.c source/test_main_ex2.c build/main_ex2 Makefile
git commit -m ""
git push
*/

#include "skip_list.h"
/*
 * Metodo per comparare due elementi, dato che nella applicazione vengono usati due file di testo il comparatore è appunto
 * string compare.
*/
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

/* 
 * Creiamo una skiplist inserendo come item le parole in dictionary.txt.
*/
SkipList* create_dictionary_skip_list(const char *file_path){
  int i = 0, num = 0;
  char word[1024];
  FILE *dictionary = fopen(file_path, "r");
  SkipList *list = create_empty_skip_list(string_compare);

  if(dictionary == NULL){
    printf("\nERROR: fp is NULL, impossible to open the file  %s\n",file_path);
    exit(EXIT_FAILURE);
    }

  while(fscanf(dictionary, "%s", word) != EOF) {
    num++;
  }

  rewind(dictionary);

  while(i < num){ //manpages
    fscanf(dictionary, "%s", word);
    insert_skip_list(list, strdup(word));
    //printf("\nword: %s", word);
    i++;
  }

  fclose(dictionary);

  return list;
}

/*
 *Metodo statico che identifica l'indice del primo elemento char da inserire nella parola da confrontare con dictionary.
*/
static int index_first_char(char *word) {
  int i = 0;
  while(!isalpha(word[i])) {
    if(word[i] == '\0')
      return -1;
    i++;
  }
  return i;
}

/*
 *Metodo statico che identifica l'indice di terminazione della parola da confrontare con dictionary.
*/
static int index_end_word(char *word) {
  int i = 0;
  while(isalpha(word[i])) {
    i++;
  }
  return i;
}

/*
 * Funzione che confronta ciascuna parola di correctme con le parole presenti in dictionary.
 * Questa funzione si occupa anche di leggere il file correct me, la lettura avviene carattere per carattere fino a incontrare 
 * un carattere non appartenente alla parola (spazi e punteggiatura).
*/
void check_correctme(SkipList *list, const char *file_path){
  char buffer[1024], word[1024];
  char *read_ptr;
  int buf_size = 1024,i, start, end;
  FILE *correctme;

  correctme = fopen(file_path, "r");

  if(correctme == NULL){
    printf("\nERROR: fp is NULL, impossible to open the file  %s\n",file_path);
    exit(EXIT_FAILURE);
  }

  printf("\n Parole not found:\n");

  while(fgets(buffer, buf_size, correctme) != NULL){
    read_ptr = buffer;
    while((start = index_first_char(read_ptr)) != -1) {
      read_ptr += start;
      end = index_end_word(read_ptr);
      i = 0;
      while(i < end) {
        word[i] = *read_ptr;
        i++;
        read_ptr++;
      }
      word[i] = '\0';
      if( (void *) search_skip_list(list, (void *) word) == NULL )
        printf("\n %s",word);
      
    }
  }
  
  fclose(correctme);
}

/*
 * Funzione main, unica cosa che fa è controllare che gli argomenti siano leciti, dopodichè lancia check la quale come primo 
 * parametro ha la lista creata con il file dictionary.
*/
int main(int argc, char const *argv[]) {

  /* txt files will be given by argv[1] and argv[2] */
  if(argc < 3){
    printf("Write: 'build/main_ex2 dictionary.txt correctme.txt'!!\n");
    exit(EXIT_FAILURE);
  }

  printf("\n \tINIZIO \n");

  check_correctme(create_dictionary_skip_list(argv[1]), argv[2]);

  printf("\n\n \tFINE \n");
  return 1;
}
