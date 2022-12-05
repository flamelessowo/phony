class BinaryTree {
  
  Node root;

  public BinaryTree() {
    this(0);
  }

  public BinaryTree(int val) {
    root = new Node(val);
  }

  private Node addRecursive(Node current, int value) {
    if (current == null) {
      return new Node(value);
    }

    if (value < current.value) {
      current.left = addRecursive(current.left, value);
    } else if (value > current.value) {
      current.right = addRecursive(current.right, value);
    } else {
      return current;
    }
    return current;
  }

  public void add(int value) {
    root = addRecursive(root, value);
  }

  private boolean containsNodeRecursive(Node current, int value) {

    if (current == null) {
      return false;
    } 
    
    if (value == current.value) {
      return true;
    }
    return value < current.value
      ? containsNodeRecursive(current.left, value)
      : containsNodeRecursive(current.right, value);
  }

  public boolean containsNode(int value) {
    return containsNodeRecursive(root, value);
  }

  private int findSmallestValue(Node root) {
    return root.left == null ? root.value : findSmallestValue(root.left);
  }

  private Node deleteRecursive(Node current, int value) {
    if (current == null) {
      return null;
    }

    if (value == current.value) {
      if (current.left == null && current.right == null) {
        return null;
      }
      if (current.right == null) {
        return current.left;
      }
      if (current.left == null) {
        return current.right;
      }

    }
    if (value < current.value) {
      current.left = deleteRecursive(current.left, value);
      return current;
    }
    current.right = deleteRecursive(current.right, value);
    return current;
  }
}
