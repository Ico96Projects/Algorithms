

import java.util.*;

public class DirectGraph<T extends Comparable<T>, L extends Comparable<L>> extends Graph<T,L> {

  public DirectGraph() {
    super();
  }

  public DirectGraph(Set<Edge<T,L>> allData) {
    super(allData);
  }

  // this make a direct graph
  public boolean isDirect() {
    return true;
  }

}
