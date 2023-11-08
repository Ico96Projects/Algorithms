# dal carattere '#' fino a fine riga, il testo dentro il Makefile e`
# un commento
# flags per la compilazione
CFLAGS = -Wall -g
# target ovvero nome dell'eseguibile che si intende produrre
TARGET1 = build/main_ex2
TARGET2 = build/test_main_ex2
# object files necessari per produrre l'eseguibile
OBJ1    = source/skip_list.o source/main_ex2.o
OBJ2    = source/skip_list.o source/test_main_ex2.o

# Si sfrutta la regola implicita per la produzione dei file oggetto in
# $(OBJ)
#
# Le "variabili" del Makefile sono espanse con $(NOME_VAR). Quindi
# scrivere
#
# $(TARGET): $(OBJ)
#

$(TARGET1): $(OBJ1)
	$(CC) $(OBJ1) $(LDFLAGS) -o $(TARGET1)
$(TARGET2): $(OBJ2)
	$(CC) $(OBJ2) $(LDFLAGS) -o $(TARGET2)

# solitamente il target "all" e` presente. con questa funzionalità compilo tutto 
all: $(TARGET1) $(TARGET2)

