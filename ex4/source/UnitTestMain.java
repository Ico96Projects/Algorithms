
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

class UnitTestMain {

  public static void main(String[] args) {
    
    Result result = JUnitCore.runClasses(UnitTestGraph.class);

    for (Failure failure : result.getFailures()) {
      System.out.println(failure.toString());
    }

    if (result.wasSuccessful() == true) 
      System.out.println("\nAll Test PASSED\n");
    else 
      System.out.println("\nSome Test FAILED\n");
  }

}
