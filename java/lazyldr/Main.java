import java.util.*;

class LazyLoadExample {
  public static void main(String[] args) {
    System.out.println("Wow i really want to know where de fuk is cats");
    CatListI catListProxy = new CatListProxy();
    System.out.println("My proxy with cats now loaded. And i should ask it for cats");
    List<Cat> myCatList = catListProxy.getCatList();
    System.out.println("Here my lovely cats:");
    myCatList.forEach(cat->System.out.println(cat));
  }
}

interface CatListI {
  public List<Cat> getCatList();
}

class Cat {
  String name;
  String breed;
  String color;
  Boolean isCute;

  public Cat(String name, String breed, String color, Boolean isCute) {
    this.name = name;
    this.breed = breed;
    this.color = color;
    this.isCute = isCute;
  }

  @Override
  public String toString() {
    return String.format("Cat: %s\nBreed: %s\nColor: %s\nIs cute cat: %b\n", name, breed, color, isCute);
  }
}

class CatList implements CatListI {

  public CatList() {
    // Here imagine really heavy constructor logic
    // so proxy makes sense
  }
  @Override
  public List<Cat> getCatList() {
    return Arrays.asList(
        new Cat("Richard", "The Ragdoll", "white", true),
        new Cat("Miku", "Abyssinian", "brown", true),
        new Cat("Bogdan", "Sphynx", "gray", false),
        new Cat("Arie", "Scottish Fold", "brown-white", !!true)
    );
  }
}

class CatListProxy implements CatListI {
  @Override
  public List<Cat> getCatList() {
    System.out.println("Loading really big list of cats....");
    CatListI catList = new CatList();
    System.out.println("Loaded successfully returning list of cats....");
    return catList.getCatList();
  }
}
