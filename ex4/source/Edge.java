

import java.util.Objects;

public class Edge<T extends Comparable<T>, L extends Comparable<L>> implements Comparable<Edge<T,L>> {
  private final Label<L> label;
  private final Node<T> source;
  private final Node<T> destination;

  //per testing:
  public Edge(T source, T destination, Label<L> label) {
    this(new Node<>(source), new Node<>(destination), label);
  }

  /*costruttore:*/
  public Edge(Node<T> source, Node<T> destination, Label<L> label) {
    this.source = source;
    this.destination = destination;
    this.label = label;
  }

  // get methods
  public Node<T> getSource() {
    return this.source;
  }

  public Node<T> getDestination() {
    return this.destination;
  }

  public double getWeight() {
    return this.label.getWeight();
  }

  public Label<L> getLabel() {
    return this.label;
  }

  // calculate hashcode
  public int hashCode() {
    return source.hashCode() + (this.destination.hashCode());
  }

  // check if two edges are equals (similar to Node)
  @SuppressWarnings("unchecked")
  public boolean equals(Object toCheck) {
    if (toCheck == this)
      return true;
    if (toCheck == null || (getClass() != toCheck.getClass()))
      return false;

    Edge<T,L> edgeToCheck = (Edge<T,L>) toCheck;
    return Objects.equals(this.source, edgeToCheck.source) && Objects.equals(this.destination, edgeToCheck.destination);
  }

  // compare weight for dijkstra
  public int compareTo(Edge<T,L> edge) {
    if (edge.getWeight() >= this.getWeight())
      return -1;
    return 1;
  }

}