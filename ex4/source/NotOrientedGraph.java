

import java.util.*;

public class NotOrientedGraph<T extends Comparable<T>, L extends Comparable<L>> extends Graph<T,L> {

  public NotOrientedGraph() {
    super();
  }

  public NotOrientedGraph(Set<Edge<T,L>> allData) {
    super(allData);
  }

  // this make a not oriented graph
  public boolean isDirect() {
    return false;
  }

  // get methods
  public int getEdgeSize() {
    return super.getEdgeSize() / 2;
  }

  // add Edge methods
  public boolean addEdge(Edge<T,L> edge) {
    if (edge == null)
      return false;
    return super.addEdge(edge.getSource(), edge.getDestination(), edge.getLabel())
        && super.addEdge(edge.getDestination(), edge.getSource(), edge.getLabel());
  }

  public boolean addEdge(T source, T destination, Label<L> label) {
    return super.addEdge(new Node<>(source), new Node<>(destination), label)
        && super.addEdge(new Node<>(destination), new Node<>(source), label);
  }

  public boolean addEdge(Node<T> source, Node<T> destination, Label<L> label) {
    return super.addEdge(source, destination, label) 
        && super.addEdge(destination, source, label);
  }

  // remove Edge methods
  public boolean removeEdge(Edge<T,L> edge) {
    if (edge == null)
      return false;
    return super.removeEdge(edge.getSource(), edge.getDestination())
        && super.removeEdge(edge.getDestination(), edge.getSource());
  }

  public boolean removeEdge(Node<T> source, Node<T> destination) {
    return super.removeEdge(source, destination) 
        && super.removeEdge(destination, source);
  }

}
