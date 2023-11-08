import static org.junit.Assert.*;
import org.junit.*;

public class UnitTestGraph {
  Graph<Character,Character> graph;

  @Before
  public void initializeClass() {
    graph = new NotOrientedGraph<>();

    graph.addNode('0');
    graph.addNode('1');
    graph.addNode('2');
    graph.addNode('3');
    graph.addNode('4');
    graph.addNode('5');
    graph.addNode('6');
    graph.addNode('7');

    graph.addEdge('0', '5', 0.8, 'a');
    graph.addEdge('4', '2', 1.0, 'b');
    graph.addEdge('6', '3', 3.9, 'c');
    graph.addEdge('2', '4', 4.0, 'd');
    graph.addEdge('3', '7', 4.6, 'e');
    graph.addEdge('4', '1', 2.6, 'f');
    graph.addEdge('5', '7', 3.1, 'g');
    graph.addEdge('6', '5', 4.0, 'h');
    graph.addEdge('2', '3', 0.4, 'i');
    graph.addEdge('1', '0', 4.3, 'j');
    graph.addEdge('3', '2', 14.0, 'k');
  }

  @Test
  public void AddNode() {
    assertFalse(graph.addNode('1'));
    assertFalse(graph.addNode((Character) null));
  }

  @Test
  public void AddEdge() {
    assertFalse(graph.addEdge(null));
    assertFalse(graph.addEdge('2', '4', 4.0, 'l'));
  }

  @Test
  public void RemoveNode() {
    assertTrue(graph.removeNode('1'));
    assertFalse(graph.removeNode((Character) null));
    assertFalse(graph.removeNode('8'));
  }

  @Test
  public void RemoveEdge() {
    assertTrue(graph.removeEdge('0', '5'));
    assertFalse(graph.removeEdge('0', '5'));
    assertFalse(graph.removeEdge((Character) null, (Character) null));
  }

}
