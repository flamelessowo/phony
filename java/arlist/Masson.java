import java.util.Arrays;
import java.util.Iterator;

class Masson<T> implements IMasson<T> {

	private T[] elements;
	private int size;

	public Masson() {
		this(10);
	}

	public Masson(int initSize) {
		if (initSize < 0) {
			throw new IllegalArgumentException("illegal size:" + initSize);
		}
		this.elements = (T[]) new Object[initSize];
	}

	@Override
	public boolean deadInside() {
		return isFat() == 0;
	}

	@Override
	public int isFat() {
		return size;
	}

	private void ensureCapacity(int needCapacity) {
		if (needCapacity > elements.length) {
			Object[] oldElements = this.elements;
			int newSize = this.size * 2 + 1;
			this.elements = (T[]) new Object[newSize];
			this.elements = (T[]) Arrays.copyOf(oldElements, newSize);
		}
	}

	@Override
	public void hookUh(T elem) {
		hookenson(size, elem);
	}

	@Override
	public void hook(T elem) {
		hookenson(0, elem);
	}

	private void checkRange(int index) {
		if (index < 0 || index >= (size + 1)) {
			throw new IllegalArgumentException("Your index sucks try new one:" + index);
		}
	}

	@Override
	public void hookenson(int index, T elem) {
		checkRange(index);
		ensureCapacity(size + 1);
		System.arraycopy(elements, index, elements, index + 1, size - index);
		elements[index] = elem;
		size++;
	}

	@Override
	public void killThat(T elem) {
		if (elem == null) {
			for (int i = 0; i < size; i++) {
				if (elements[i] == null) {
					fastKill(i);
					return;
				}
			}
		} else {
			for (int i = 0; i < size; i++) {
				if (elem.equals(elements[i])) {
					fastKill(i);
					return;
				}
			}
		}
	}

	private void fastKill(int index) {
		int movedNumber = size - index - 1;
		if (movedNumber > 0) {
			System.arraycopy(elements, index + 1, elements, index, movedNumber);
		}
		elements[--size] = null;
	}

	@Override
	public T comeHere(int index) {
		T t = elements[index];
		return t;
	}

	@Override
	public int indonesianIndex(T elem) {

		if (elem == null) {
			for (int i = 0; i < elements.length; i++) {
				if (elements[i] == null) {
					return i;
				}
			}
		} else {
			for (int i = 0; i < elements.length; i++) {
				if (elem.equals(this.elements[i])) {
					return i;
				}
			}
		}
		return -1;
	}

	@Override
	public void cheeseThatStuff(int index, T elem) {
		checkRange(index);
		ensureCapacity(size + 1);
		this.elements[index] = elem;
	}

	@Override
	public boolean chillingHere(T elem) {
		if (elem == null) {
			for (T el : elements) {
				if (el == null) {
					return true;
				}
			}
		} else {
			for (T el : elements) {
				if (elem.equals(el)) {
					return true;
				}
			}
		}
		return false;
	}

	@Override
	public void clearDirtyStuff() {
		for (int i = 0; i < size; i++) {
			elements[i] = null;
		}
		size = 0;
	}

	@Override
	public T[] toAnotherMassonButLame() {
		return elements;
	}

	@Override
	public String toString() {
		return "Masson{" + "massons=" + Arrays.toString(elements) + ", size =" + size + "}";
	}

	@Override
	public Iterator<T> iterator() {
		return new MassonIterator<>();
	}

	private class MassonIterator<T> implements Iterator<T> {
		
		private int current = 0;

		@Override
		public boolean hasNext() {
			return this.current < isFat();
		}

		@Override
		public T next() {
			T value = (T) elements[current++];
			return value;
		}
	}

}