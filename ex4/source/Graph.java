

import java.util.*;

public abstract class Graph<T extends Comparable<T>, L extends Comparable<L>> {
  protected Map<Node<T>, Map<Node<T>, Label<L>>> nodes;
  protected Map<Node<T>, Double> distances;
  protected Map<Node<T>, Node<T>> path;
  // Cache variables
  private int sizeCacheNode;
  private int sizeEdgeNode;
  private Set<Edge<T,L>> setCacheEdge;

  public Graph() {
    this.nodes = new HashMap<>();
    this.distances = new HashMap<>();
    this.path = new HashMap<>();
    this.sizeCacheNode = -1;
    this.sizeEdgeNode = -1;
    this.setCacheEdge = null;
  }

  public Graph(Set<Edge<T,L>> allData) {
    this();
    if (allData == null) {
      System.out.println("\nERROR: Miss some input, the class graph did not get the input \n");
      return;
    }

    for (Edge<T,L> new_edge : allData) {
      Node<T> source = new_edge.getSource();
      Node<T> destination = new_edge.getDestination();
      this.addNode(source);
      this.addNode(destination);
      this.addEdge(source, destination, new_edge.getLabel());
    }
  }

  // get methods
  public Set<Node<T>> getNodes() {
    if (nodes.size() == 0)
      return null;
    return nodes.keySet();
  }

  public Set<Edge<T,L>> getEdges() {
    if (nodes.size() == 0)
      return null;
    if (this.setCacheEdge != null)
      return this.setCacheEdge;

    this.setCacheEdge = new TreeSet<>();
    for (Map.Entry<Node<T>, Map<Node<T>, Label<L>>> node : nodes.entrySet()) {
      for (Map.Entry<Node<T>, Label<L>> edge : node.getValue().entrySet()) {
        this.setCacheEdge.add(new Edge<>(node.getKey(), edge.getKey(), edge.getValue()));
      }
    }
    return this.setCacheEdge;
  }

  public int getNodeSize() {
    if (this.sizeCacheNode > -1)
      return this.sizeCacheNode;
    return this.sizeCacheNode = nodes.size();
  }

  public int getEdgeSize() {
    if (this.sizeEdgeNode > -1)
      return this.sizeEdgeNode;
    this.sizeEdgeNode = 0;
    for (Map.Entry<Node<T>, Map<Node<T>, Label<L>>> node : nodes.entrySet()) {
      this.sizeEdgeNode += node.getValue().size();
    }
    return this.sizeEdgeNode;
  }

  // methods for tests
  // addNode
  public boolean addNode(T value) {
    return this.addNode(new Node<>(value));
  }

  public boolean addNode(Node<T> value) {
    if (value == null || value.getValue() == null)
      return false;
    this.sizeCacheNode = -1;
    value.setDistOriginNode(Double.MAX_VALUE);
    return nodes.putIfAbsent(value, new HashMap<>()) == null;
  }

  // addEgde
  public boolean addEdge(Edge<T,L> edge) {
    if (edge == null)
      return false;
    return this.addEdge(edge.getSource(), edge.getDestination(), edge.getLabel());
  }

  public boolean addEdge(T source, T destination, double weight, L label) {
    return this.addEdge(new Node<>(source), new Node<>(destination), new Label<>(label, weight));
  }

  public boolean addEdge(Node<T> source, Node<T> destination, Label<L> label) {
    if (source == null || source.getValue() == null || destination == null || destination.getValue() == null)
      return false;
    
    this.sizeEdgeNode = -1;
    this.setCacheEdge = null;

    if (nodes.containsKey(source) && nodes.containsKey(destination)) {
      return nodes.get(source).putIfAbsent(destination, label) == null;
    }
    return false;
  }

  // methods for dijkstra, get the next nodes
  public Set<Node<T>> getAdjentNodes(T value) {
    return this.getAdjentNodes(new Node<>(value));
  }

  public Set<Node<T>> getAdjentNodes(Node<T> value) {
    if (nodes.size() == 0)
      return null;

    Set<Node<T>> adjentNodes = nodes.get(value).keySet();
    return adjentNodes;

  }

  // method for dijkstra, get the weight
  public double getEdgeWeight(T source, T destination) {
    return this.getEdgeWeight(new Node<>(source), new Node<>(destination));
  }

  public double getEdgeWeight(Node<T> source, Node<T> destination) {
    if (nodes.containsKey(source)) {
      Map<Node<T>, Label<L>> edges = nodes.get(source);
      if (edges.containsKey(destination)) {
        return edges.get(destination).getWeight();
      }
    }
    return -1.0;
  }

  // remove Node methods
  public boolean removeNode(T value) {
    return this.removeNode(new Node<>(value));
  }

  public boolean removeNode(Node<T> value) {
    if (value == null || value.getValue() == null)
      return false;
    this.sizeCacheNode = -1;

    for (Map.Entry<Node<T>, Map<Node<T>, Label<L>>> node : nodes.entrySet()) {
      if (node.getKey().equals(value))
        continue;
      node.getValue().remove(value);
    }
    return nodes.remove(value) != null;
  }

  // remove Edge methods
  public boolean removeEdge(Edge<T,L> edge) {
    if (edge == null)
      return false;
    return this.removeEdge(edge.getSource(), edge.getDestination());
  }

  public boolean removeEdge(T source, T destination) {
    return this.removeEdge(new Node<>(source), new Node<>(destination));
  }

  public boolean removeEdge(Node<T> source, Node<T> destination) {
    if (source == null || source.getValue() == null || destination == null || destination.getValue() == null)
      return false;

    this.sizeEdgeNode = -1;
    this.setCacheEdge = null;

    if (nodes.containsKey(source))
      return nodes.get(source).remove(destination) != null;
    return false;
  }

  public void dijkstra(Node<T> source, HeapMinimo<Node<T>> heapMin, Node<T> destination)  {
    Set<Node<T>> allNodes = this.getNodes();

    for(Node<T> n : allNodes){
      n.setDistOriginNode(Double.MAX_VALUE); 
      this.distances.put(n, Double.MAX_VALUE);
      this.path.put(n, null);
      //System.out.println(this.distances.get(n));
    }

    source.setDistOriginNode(0.0);
    this.distances.replace(source, 0.0);
    for(Node<T> n : allNodes){
      heapMin.insert(n);
    }
    while( heapMin.dimension() > 1) {
      Node<T> newNode = heapMin.extractMin();
      //System.out.print("\n "+heapMin.dimension()+"  we extracted " + newNode.getValue());
      
      for(Node<T> nodeAdjentOfNew : getAdjentNodes(newNode)) {
        double otherDistance = this.distances.get(newNode) + getEdgeWeight(newNode, nodeAdjentOfNew);
        
        if( otherDistance < this.distances.get(nodeAdjentOfNew) ) {
          //System.out.print(" ->if ");
          Node<T> tmp = nodeAdjentOfNew;
          this.distances.replace(nodeAdjentOfNew, otherDistance);
          this.path.replace(nodeAdjentOfNew, newNode);
          nodeAdjentOfNew.setDistOriginNode(otherDistance);
          heapMin.decrease(tmp, nodeAdjentOfNew);
        }
      }
    }
    System.out.println("\nDistanza da " + source.getValue() + " a " + destination.getValue() + " è: " + this.distances.get(destination)/1000 + " km");
    System.out.println("\nIl path minimo è:");
    
    ArrayList<Node<T>> list = new ArrayList<>();
    Node<T> temp = destination;
    while( temp!=null ){
      list.add(temp); 
      temp = this.path.get(temp); // dalla foglia (destination) alla radice (source)
    }
		Collections.reverse(list);
    for(int i = 0; i < list.size(); i++) {
      if(i!=0) System.out.print(" -> ");
      temp = list.get(i);
      System.out.print(temp.getValue());
    }
  }
}