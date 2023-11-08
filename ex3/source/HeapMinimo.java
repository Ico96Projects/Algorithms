/*
 * ESERCIZIO 3
 * 
 * Si implementi una libreria che realizza la struttura dati Heap Minimo
 * La struttura dati deve:
 *  - rappresentare internamente lo heap tramite un vettore (e' possibile usare anche altre strutture interne di supporto, se necessarie)
 *  - consentire un numero qualunque e non noto a priori di elementi dello heap
 *  - essere generica per quanto riguarda il tipo degli elementi dello heap
 *  - essere generica per quanto riguarda il criterio di confronto fra elementi dello heap
 *  
 * 
 * Convenzioni per il linguaggio JAVA:
 * 
 * i package sono tutti in minuscolo senza separazione fra le parole
 * TheClass TheInterface classi e interface: tutto minuscolo tranne la primalettera della parola (CamelCase)
 * theMethod theVariable metodi e variabili: iniziano in minuscolo e proseguono in CamelCase
 * THE_CONSTANT costanti: tutto maiuscolo, parole separate da _ (SNAKE_CASE)
 */
/*
GIT: (aprire un terminale e posizionarsi nella cartella ex3)

git pull

git add source/HeapMinimo.java source/UnitTestHeapMinimo.java source/MainUnitTest.java source/MainHeapMinimo.java
git commit -m ""
git push
*/
/* 
package source;*/
import java.util.*;


  /**
   * It represents a minum heap structure based on array. Elements in the heap are always ordered according
   * to a criterion specified by a compare method at creation time.
   * @author pitaccolo_Pochettino
   * @param <T>: type of the ordered array elements
   */

public class HeapMinimo<T> {
  private ArrayList<T> array;
  private Comparator<T> comparator;
  private Hashtable<T, Integer> hashTable;
  private Integer size; //dimensione logica
 
  // creazione di uno heap minimo vuoto - O(1)
  public HeapMinimo(Comparator<T> comparator) {
    this.array = new ArrayList<T>();
    this.comparator = comparator;
    this.hashTable = new Hashtable<T, Integer>();
    this.size = 0;
  }

  // restituzione della dimensione dello heap - O(1)
  public int dimension() {
    return this.size;
  }

  // restituzione del genitore di un elemento - O(1)
  //INDICE
  public int parentInd(int pos) {
    if (pos <= 2)
      return 0;
    return (pos - 1) / 2;
  }
  // restituzione del genitore di un elemento - O(1)
  //VALORE
  public T parentVal(T elem) {
    Integer i = hashTable.get(elem);
    return this.array.get(parentInd(i));
  }

  // restituzione del figlio sinistro di un elemento - O(1)
  //INDICE
  public int leftChildInd(int pos) {
    if ((2 * pos) + 1 > size) {
      return pos;
    }
    else {
      return (2 * pos) + 1;
    }
  }
  // restituzione del figlio sinistro di un elemento - O(1)
  //VALORE
  public T leftChildVal(T parent) {
    Integer i = leftChildInd(hashTable.get(parent));
    return this.array.get(i);
  }

  // restituzione del figlio destro di un elemento - O(1)
  //INDICE
  public int rightChildInd(int pos) {
    if ((2 * pos) + 2 > size) {
      return pos;
    }
    return (2 * pos) + 2;
  }
  // restituzione del figlio destro di un elemento - O(1)
  //VALORE
  public T rightChildVal(T parent) {
    Integer i = rightChildInd(hashTable.get(parent));
    return this.array.get(i);
  }

  // inserimento di un elemento - O(log n)
  public void insert(T element) {
    if (hashTable.get(element) == null) {
      (this.array).add(size, element);
      (this.hashTable).put(element, size);
      while (parentVal(element) != null && (this.comparator).compare(element, parentVal(element)) < 0) {
        swap(element, parentVal(element));
      }
      this.size++;
    }
  }

  // estrazione dell' elemento con valore minimo - O(log n)
  public T extractMin() {
    if (size <= 0){
      System.out.println("extractMin: element does not exists");
      return null;
    }
    T element = (this.array).get(0);
    (this.array).set(0, (this.array).get(size - 1));
    size--;
    hashTable.remove(element);
    hashTable.replace(array.get(0), 0);
  
    this.heapify(0);
    return element;
  }

  // diminuzione del valore di un elemento - O(log n)
  public void decrease(T old_el, T new_el) {
    Integer i = hashTable.get(old_el);
    array.set(i, new_el);
    hashTable.remove(old_el);
    hashTable.put(new_el, i);

    while (parentVal(new_el) != null && comparator.compare(parentVal(new_el), new_el) > 0) {
      swap(new_el, parentVal(new_el));
    }
  }

  // funzionwe ausiliaria che scambia due elementi dello heap.
  private void swap(T first, T second) {
    Integer i = hashTable.get(first);
    Integer j = hashTable.get(second);

    (this.hashTable).replace(second, j, i);
    (this.hashTable).replace(first, i, j);

    T tmp = array.get(i);

    (this.array).set(i, array.get(j));
    (this.array).set(j, tmp);
  }

  // funzione ausiliaria per ripristinare la corretta struttura dello heap minimo a seguito dell'estrazione del minimo.
  private void heapify(int i) {
    T element = array.get(i);

    int min = hashTable.get(minimum(element, minimum(rightChildVal(element), leftChildVal(element))));
    if (min != i) {
      swap(element, array.get(min));
      heapify(min);
    }
  }

  //confronta due elementi per determinarne il minimo.
  private T minimum(T el1, T el2) {
    if ((el1 == null) && (el2 != null))
      return el2;
    if((el1 != null) && (el2 == null))
      return el1;
    if ((el1 == null) && (el2 == null))
      return el1;
    if(comparator.compare(el1, el2) < 0)
      return el1;
    else
      return el2;
  }

  public void printHeap() {
    for(int i = 0; i < this.dimension()/2; i++) {
      System.out.println("Parent: "+ array.get(i)+
                          "\tLeft_Child: "+ array.get(leftChildInd(i))+
                          "\tRight_Child: "+ array.get(rightChildInd(i)));
      System.out.println();
    }
  }
}



