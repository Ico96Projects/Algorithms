/*mainino*//* 
package source;*/
import java.util.*;
public class MainHeapMinimo {
	static Comparator<Integer> comparator = new IntegerComparator();

	static class IntegerComparator implements Comparator<Integer> {
    @Override
    public int compare(Integer i1, Integer i2) {
      return i1.compareTo(i2);
    }
  }

	public static void main(String[] args) {
		HeapMinimo<Integer> heapMinimo = new HeapMinimo<Integer>(comparator);

		heapMinimo.insert(57);
		heapMinimo.insert(12);
		heapMinimo.insert(19);
		heapMinimo.insert(6);
		heapMinimo.insert(41);
		heapMinimo.insert(104);
		heapMinimo.insert(18);
		heapMinimo.insert(56);
		heapMinimo.insert(5);
		heapMinimo.insert(27);
		heapMinimo.insert(3);
		heapMinimo.insert(7);
		heapMinimo.insert(15);
		heapMinimo.insert(1);
		heapMinimo.insert(2);
		heapMinimo.printHeap();

		System.out.println("left di 1: "+heapMinimo.leftChildVal(1));

	
		System.out.println("\nEstratto: "+heapMinimo.extractMin());
		System.out.println("\ndopo extract:\n");
		heapMinimo.printHeap();
	
		System.out.println("right di 6: "+heapMinimo.rightChildVal(6));
	 
		heapMinimo.decrease(104, 4);
		System.out.println("\ndopo decrease:\n");
		heapMinimo.printHeap();

	}
}