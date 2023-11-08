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
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

//heap vuoto
//un elem Test dimensione
//test figlio dx e sx returno valore  assertEquals(3 , left...)
//extract min 
//decrease key

public class MainUnitTest {

  public static void main(String[] args) {
    
    Result result = JUnitCore.runClasses(UnitTestHeapMinimo.class);

    for (Failure failure : result.getFailures()) {
      System.out.println(failure.toString());
    }

    if (result.wasSuccessful() == true) 
      System.out.println("\nAll Test PASSED\n");
    else 
      System.out.println("\nSome Test FAILED\n");
  }
}
