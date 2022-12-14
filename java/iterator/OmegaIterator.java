import java.util.*;

class TestIterator<T> {
  public String[] arr = {"a", "b", "o", "b", "a"};

  public CustomIterable<T> getIterator() {
    return new OmegaIterator<T>();
  }

  private class OmegaIterator<T> implements CustomIterable<T> {

    private int ind = 0;

    @Override
    public boolean hasNext() {
      return ind < arr.length;
    }

    @Override
    public T next() {
      return (T) arr[ind++];
    }
  }

  public static void main(String[] args) {
    TestIterator<String> it = new TestIterator<>();
    CustomIterable<String> iterat = it.getIterator();
    while (iterat.hasNext()) {
      System.out.println(iterat.next());
    }
    
  }
}
