import java.util.Objects;

public class Node<T> {
  private T value;
  private double distOriginNode;  //for dijkstra, (distanza da sorgente)

  public Node(T value) {
    this.value = value;
  }

  // get methods
  public T getValue() {
    return this.value;
  }

  public double getDistOriginNode() {
    return this.distOriginNode;
  }
  
  public void setDistOriginNode(double d) {
    this.distOriginNode = d;
  }

  // check if two nodes are equals (similar to Edge)
  @SuppressWarnings("unchecked")
  public boolean equals(Object toCheck) {
    if (toCheck == this)
      return true;
    if (toCheck == null || (getClass() != toCheck.getClass()))
      return false;

    Node<T> nodeToCheck = (Node<T>) toCheck;
    return Objects.equals(value, nodeToCheck.value);
  }

  // calculate hashcode
  public int hashCode() {
    return this.value.hashCode();
  }

}
