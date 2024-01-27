

interface JavaContainer<T>{
    /*    
    Add: adds and element to the container
    Remove: removes a given element
    Size: returns the number of elements
    getIterator: returns an iterator object of class Iterator that has the following mehods
    hasNext: returns true if there is a next element
    next: returns the next element and advances the iterator  All the classes have the following
    Overridden ToString method.
    Overridden equals method
    Uses keyword var in its implementation.
    */
    void add(T item);
    void remove(T item);
    int size();
    Iterator<T> getIterator();

}
class Iterator<T>{
    private int currentIndex;
    private int size;
    private Object[] array;

    public Iterator(Object[] _array, int _size){
        currentIndex = 0;
        size = _size;
        array = _array;
    }

    /**
    hasNext: returns true if there is a next element
    */
    boolean hasNext(){
        return currentIndex < size;
    }
    /**
    next: returns the next element and advances the iterator
    */
    @SuppressWarnings("unchecked")
    T next(){
        try {        
            if(hasNext()){
                return (T) array[++currentIndex];
            }
            else{
                throw new Exception("has no next element");   
            }
        } catch (Exception e) {
            System.out.println("has no next element");
            return null;
        }
    }
    @SuppressWarnings("unchecked")
    T begin(){
        currentIndex = 0;
        return (T) array[0];
    }
    @SuppressWarnings("unchecked")
    T end(){
        currentIndex = size - 1;
        return (T) array[currentIndex];
    }

    public String toString(){
        return "current index is " + currentIndex;
    }

}



class JavaSet<T> implements JavaContainer<T>{
    
    private int capacity;
    private Object[] array;
    private int size;
    
    public JavaSet(int _capacity) {
        capacity = _capacity;
        array = new Object[capacity];
        size = 0;
    }

    public boolean equals(JavaSet<T> other){
        if(other == this){
            return true;
        }
        if(other == null || other.size != this.size){
            return false;
        }
        for(int i = 0; i < size; i++){
            if(!other.array[i].equals(this.array[i])){
                return false;
            }
        }
        return true;
    }



    /**
    a bubble sort algorithm to sort the array
     */
    @SuppressWarnings("unchecked")
    private void sort() {
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (((Comparable<T>) array[i]).compareTo((T) array[j]) > 0) {
                    T temp = (T) array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }


    
    private void addCap(){
        capacity *= 2;
        Object[] newarray = new Object[capacity]; 
        for(int i = 0; i < size; i++){
            newarray[i] = array[i];
        }
        array = newarray;
    }
    
    @Override
    public void add(T item) {
        try{
            if(isIn(item)){
                throw new Exception("item is already in set");
            }
            else{
                if(capacity < size + 1){
                    addCap();
                }
                array[size] = item;
                size++;
            }
        }
        catch(Exception e){
            return;
        }
        sort();
    }

    @Override
    public void remove(T item) {
        if(size == 0){
            return;
        }
        if(isIn(item)){
            for(int i = 0; i < size; i++){
                if(array[i] == item){
                    int k;
                    for(k = i; k < size - 1; k++){
                        array[k] = array[k + 1];
                    }
                    array[k + 1] = null;
                }
            }
        }
        size--;
        
    }


    @Override
    public int size() {
        return size;
    }


    @Override
    public Iterator<T> getIterator(){
        return new Iterator<T>(array, size);
    }

    private boolean isIn(T item) {
        for (var i : array) {
            if (i == item) {
                return true;
            }
        }
        return false;
    }
    

    public String toString(){
        if(size == 0){
            return "JavaSet is empty";
        }
        
        String all = "";
        for(var i : array){
            System.out.println(i);
        }
        return all;
    }


}

class JavaVector<T> implements JavaContainer<T>{
    private int capacity;
    private int size;
    private Object[] array;
    
    public JavaVector(int _capacity) {
        capacity = _capacity;
        array = new Object[_capacity];
        size = 0;
    }

    public boolean equals(JavaVector<T> other){
        if(other == this){
            return true;
        }
        if(other == null || other.size != this.size){
            return false;
        }
        for(int i = 0; i < size; i++){
            if(!other.array[i].equals(this.array[i])){
                return false;
            }
        }
        return true;
    }


    @Override
    public void add(T item) {
        if(capacity < size + 1){
            addCap();
        }
        array[size] = item;
        size++;
    }

    @Override
    public void remove(T item) {
        if(isIn(item)){
            for(int i = 0; i < size; i++){
                if(array[i] == item){
                    int k;
                    for(k = i; k < size - 1; k++){
                        array[k] = array[k + 1];
                    }
                    array[k + 1] = null;
                }
            }
        }
        size--;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Iterator<T> getIterator(){
        return new Iterator<T>(array, size);
    }


    public String toString(){
        if(size == 0){
            return "JavaVector is empty";
        }
        String all = "";
        for(var i : array){
            System.out.println(i);
        }
        return all;
    }

    private boolean isIn(T item) {
        for (var i : array) {
            if (i == item) {
                return true;
            }
        }
        return false;
    }
    
    private void addCap(){
        capacity *= 2;
        Object[] newarray = new Object[capacity]; 
        for(int i = 0; i < size; i++){
            newarray[i] = array[i];
        }
        array = newarray;
    }

}


public class container {
    public static void main(String[] args) {
        // Testing JavaSet
        JavaSet<String> set = new JavaSet<>(2);

        set.add("aasd");
        set.add("basd");
        set.add("casdas");
        set.add("dqweqw");
        set.add("e");

        
        // System.out.println(set.toString()); // check to string

        // printing one by one by using iterator
        Iterator<String> iterator = set.getIterator();
        System.out.println(iterator.begin());
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }

        // Testing JavaVector
        JavaVector<Integer> vector = new JavaVector<>(3);

        vector.add(1);
        vector.add(2);
        vector.add(3);
        vector.add(4);
        vector.add(5);
        // vector.remove(3);

        // System.out.println(vector.toString()); // testing toString

        // printing one by one by using iterator
        Iterator<Integer> vectiterator = vector.getIterator();
        
        System.out.println(vectiterator.begin());
        while (vectiterator.hasNext()) {
            System.out.println(vectiterator.next());
        }
    }
}
