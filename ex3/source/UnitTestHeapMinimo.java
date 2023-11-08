/*
 * ESERCIZIO 3
 * 
 * Convenzioni per il linguaggio JAVA:
 * 
 * i package sono tutti in minuscolo senza separazione fra le parole
 * TheClass TheInterface classi e interface: tutto minuscolo tranne la primalettera della parola (CamelCase)
 * theMethod theVariable metodi e variabili: iniziano in minuscolo e proseguono in CamelCase
 * THE_CONSTANT costanti: tutto maiuscolo, parole separate da _ (SNAKE_CASE)
 */
/* 
package source;*/

import java.util.Comparator;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

//heap vuoto
//un elem Test dimensione
//test figlio dx e sx returno valore  assertEquals(3 , left...)
//extract min 
//decrease key

public class UnitTestHeapMinimo {
  static Comparator<Integer> comparator = new IntegerComparator();

	static class IntegerComparator implements Comparator<Integer> {
    @Override
    public int compare(Integer i1, Integer i2) {
      return i1.compareTo(i2);
    }
  }

  private Integer i1 = 57, i2 = 12, i3 = 19, i4 = 6, i5 = 41, i6 = 104, i7 = 18, i8 = 56, i9 = 5, i10 = 27, i11 = 3, i12 = 7, i13 = 15, i14 = 1, i15 = 2;
  
  HeapMinimo<Integer> heapMinimo = new HeapMinimo<Integer>(comparator);


  // creazione di uno heap minimo vuoto - O(1)
  @Test
  public void testNewHeap(){
    assertTrue( heapMinimo != null);
  }

  // inserimento di un elemento - O(log n)
  @Test
  public void testInsert(){
    heapMinimo.insert(i1);
    heapMinimo.insert(i2);
    assertEquals(i2, heapMinimo.extractMin());
  }


  // restituzione della dimensione dello heap - O(1)
  @Test
  public void testDimension_zeroEl(){
    assertTrue(0 == heapMinimo.dimension());
  }
  @Test
  public void testDimension_oneEl(){
    heapMinimo.insert(i6);
    assertTrue(1 == heapMinimo.dimension());
  }
  @Test
  public void testDimension_fourEl(){
    heapMinimo.insert(i1);
    heapMinimo.insert(i2);
    heapMinimo.insert(i3);
    heapMinimo.insert(i4);
    assertTrue(4 == heapMinimo.dimension());
  }


  // restituzione del genitore di un elemento - O(1)
  @Test
  public void testParentVal(){
    heapMinimo.insert(i1);
		heapMinimo.insert(i2);
		heapMinimo.insert(i3);
		heapMinimo.insert(i4);
		heapMinimo.insert(i5);
		heapMinimo.insert(i6);
		heapMinimo.insert(i7);
		heapMinimo.insert(i8);
		heapMinimo.insert(i9);
		heapMinimo.insert(i10);
		heapMinimo.insert(i11);
		heapMinimo.insert(i12);
		heapMinimo.insert(i13);
		heapMinimo.insert(i14);
		heapMinimo.insert(i15);
    assertEquals(i4, heapMinimo.parentVal(i10));
  }


  // restituzione del figlio sinistro di un elemento - O(1)
  @Test
  public void testLeftChildVal(){
    heapMinimo.insert(i1);
		heapMinimo.insert(i2);
		heapMinimo.insert(i3);
		heapMinimo.insert(i4);
		heapMinimo.insert(i5);
		heapMinimo.insert(i6);
		heapMinimo.insert(i7);
		heapMinimo.insert(i8);
		heapMinimo.insert(i9);
		heapMinimo.insert(i10);
		heapMinimo.insert(i11);
		heapMinimo.insert(i12);
		heapMinimo.insert(i13);
		heapMinimo.insert(i14);
		heapMinimo.insert(i15);
    assertEquals(i2, heapMinimo.leftChildVal(i9));
  }


  // restituzione del figlio destro di un elemento - O(1)
  @Test
  public void testRightChildVal(){
    heapMinimo.insert(i1);
		heapMinimo.insert(i2);
		heapMinimo.insert(i3);
		heapMinimo.insert(i4);
		heapMinimo.insert(i5);
		heapMinimo.insert(i6);
		heapMinimo.insert(i7);
		heapMinimo.insert(i8);
		heapMinimo.insert(i9);
		heapMinimo.insert(i10);
		heapMinimo.insert(i11);
		heapMinimo.insert(i12);
		heapMinimo.insert(i13);
		heapMinimo.insert(i14);
		heapMinimo.insert(i15);
    assertEquals(i11, heapMinimo.rightChildVal(i15));
  }


  // estrazione dell' elemento con valore minimo - O(log n)
  @Test
  public void testExtractMin(){
    heapMinimo.insert(i1);
		heapMinimo.insert(i2);
		heapMinimo.insert(i3);
		heapMinimo.insert(i4);
		heapMinimo.insert(i5);
		heapMinimo.insert(i6);
		heapMinimo.insert(i7);
		heapMinimo.insert(i8);
		heapMinimo.insert(i9);
		heapMinimo.insert(i10);
		heapMinimo.insert(i11);
		heapMinimo.insert(i12);
		heapMinimo.insert(i13);
		heapMinimo.insert(i14);
		heapMinimo.insert(i15);
    assertEquals(i14, heapMinimo.extractMin());
  }


  // diminuzione del valore di un elemento - O(log n)
  @Test
  public void testDecrease(){
    heapMinimo.insert(i1);
		heapMinimo.insert(i2);
		heapMinimo.insert(i3);
		heapMinimo.insert(i4);
		heapMinimo.insert(i5);
		heapMinimo.insert(i6);
		heapMinimo.insert(i7);
		heapMinimo.insert(i8);
		heapMinimo.insert(i9);
		heapMinimo.insert(i10);
		heapMinimo.insert(i11);
		heapMinimo.insert(i12);
		heapMinimo.insert(i13);
		heapMinimo.insert(i15);
    heapMinimo.decrease(i6, i14);
    assertEquals(i14, heapMinimo.extractMin());
    /*Non posso estrarre valore i6, posso solo estrarre dalla radice.*/
  }
  
}

