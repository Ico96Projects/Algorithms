/*
 * ESERCIZIO 4
 * 
 * Convenzioni per il linguaggio JAVA:
 * 
 * i package sono tutti in minuscolo senza separazione fra le parole
 * 
 * TheClass TheInterface classi e interface: tutto minuscolo tranne la prima
 * lettera della parola (CamelCase)
 * 
 * theMethod theVariable metodi e variabili: iniziano in minuscolo e proseguono
 * in CamelCase
 * 
 * THE_CONSTANT costanti: tutto maiuscolo, parole separate da _ (SNAKE_CASE)
 */
/*
GIT: (aprire un terminale e posizionarsi nella cartella ES4/source_code)

git pull

git add Main.java Label.java Graph.java DirectGraph.java NotOrientedGraph.java Edge.java Node.java UnitTestMain.java UnitTestGraph.java HeapMinimo.java
git commit -m ""
git push


TO RUN: (with libraries junit in the classpath)

javac Main.java Edge.java Node.java Graph.java DirectGraph.java NotOrientedGraph.java

java Main italian_dist_graph.csv

*/

import java.util.*;
import java.io.*;

public class Main {
 
  static Comparator<Node<String>> comparator = new NodeComparator();

	static class NodeComparator implements Comparator<Node<String>> {
    @Override
    public int compare(Node<String> n1, Node<String> n2) {

      if (n1.getDistOriginNode() == n2.getDistOriginNode())
        return 0;

      if (n1.getDistOriginNode() > n2.getDistOriginNode())
        return 1;

      return -1;
    }
  }


  public static void main(String[] args) {

    if (args.length < 1) {
      System.out.println("\nERROR: Miss some input\n");
      System.exit(1);
    }
    System.out.println("\n\nReading file  " + args[0] + " ...");

    Set<Edge<String,Double>> allData = readData(args[0]);
    if (allData == null) {
      System.out.println("\nData file not found\n");
      System.exit(1);
    }
    System.out.println("\tFile read successfully \n\nInitializing graph ...");

    Graph<String,Double> grafo = new DirectGraph<>(allData);
  //Graph<String> grafo = new NotOrientedGraph<>(allData);

    // è consigliato per l'implementazione di gestire il grafo come fosse non orientato
    for (Edge<String,Double> new_edge : allData) {
      Node<String> source = new_edge.getSource();
      Node<String> destination = new_edge.getDestination();
      grafo.addEdge(destination, source, new_edge.getLabel());
    }

    System.out.println("\tThe graph created has " + grafo.getNodeSize() + " nodes");
    System.out.println("\tThe graph created has " + grafo.getEdgeSize() + " edges");
    
    Set<Node<String>> allNodes = grafo.getNodes();
    Node<String> origin = null;
    String input = null;
    Console console = System.console();
    do{
      input = console.readLine("\n\nEnter City of departure : ");
      for(Node<String> n : allNodes){
        if(input.compareTo(n.getValue())==0)
          origin = n;
      }
      if (origin==null)
        System.out.println("\nThe city chosen is not on our map\n");
    } while(origin==null);

    Node<String> dest = null;
    do{
      input = console.readLine("\nEnter City of destination : ");
      for(Node<String> n : allNodes){
        if(input.compareTo(n.getValue())==0)
        dest = n;
      }
      if (dest==null)
        System.out.println("\nThe city chosen is not on our map\n");
    } while(dest==null);

    grafo.dijkstra(origin, new HeapMinimo<Node<String>>(comparator), dest);

    System.out.println("\n\n");
  }

  // read the file
  public static Set<Edge<String, Double>> readData(String fileName) {
    Set<Edge<String, Double>> Data = null;

    File fd = new File(fileName);
    try (BufferedReader br = new BufferedReader(new FileReader(fd))) {
      Data = new HashSet<>();
      String line;
      while ((line = br.readLine()) != null) {
        String params[] = line.split(",");
        Edge<String, Double> edgeToAdd = new Edge<String, Double>(params[0], params[1], new Label<Double>(Double.parseDouble(params[2]), Double.parseDouble(params[2])));
        Data.add(edgeToAdd);
      }
    } catch (Exception e) {
    }
    return Data;
  }

}
