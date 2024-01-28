import java.io.FileWriter;
import java.io.IOException;

interface JavaContainer<T>{


    /**
    add: adds an element to the container 
    */
    void add(T item);
    /**
     * remove: removes an element from the container
     */
    void remove(T item);
    /**
     * size: returns the number of elements in the container
     */
    int size();
    /**
     * getIterator: returns an iterator for the container
     */
    Iterator<T> getIterator();

}
class Iterator<T>{
    private int currentIndex;
    private int size;
    private Object[] array;
    /**
     * constructor
     * @param _array calling set or vector's array
     * @param _size calling set or vector's size
     */
    public Iterator(Object[] _array, int _size){
        currentIndex = 0;
        size = _size;
        array = _array;
    }

    /**
    @return true if there is a next element
    */
    boolean hasNext(){
        return currentIndex < size;
    }
    /**
    @return next element
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
    /**
    I added 3 more functions to make it easier to use
    */
    /**
    begin: sets the iterator to the first element
    @return first element
    */
    @SuppressWarnings("unchecked")
    T begin(){
        currentIndex = 0;
        return (T) array[0];
    }
    /**
    end: sets the iterator to the last element
    @return last element
    */
    @SuppressWarnings("unchecked")
    T end(){
        currentIndex = size - 1;
        return (T) array[currentIndex];
    }
    /**
    current: @return current element
     */
    @SuppressWarnings("unchecked")
    T current(){
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
    

    /**
     * constructor
     * creates an empty set sized 0
     * @param _array
     * @param _capacity
     */
    public JavaSet(int _capacity) {
        capacity = _capacity;
        array = new Object[capacity];
        size = 0;
    }
    /**
     * overloaded equals method
     * checks if two sets are equal
     * @param other
     * @return
     */
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
     * prints the set to a file
     * @param filename name of the file, .txt will be added automatically
     */
    public void printToFile(String filename){
        System.out.println("\nPrinting set to file...");
        String fpath = filename + ".txt";
        try {
            FileWriter fp = new FileWriter(fpath);

            Iterator<T> setiterator = this.getIterator();
            while (setiterator.hasNext()) {
                fp.write(setiterator.current() + "\n");
                setiterator.next();
            }
            fp.close();
            System.out.println("JavaSet printed to file.");

        } catch (IOException e) {
            System.out.println("An error occurred at writing set to file.");
        }
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


    /**
     * increases capacity by multiplying it with 2
     * copies the old array to the new one
     */
    private void addCap(){
        capacity *= 2;
        Object[] newarray = new Object[capacity]; 
        for(int i = 0; i < size; i++){
            newarray[i] = array[i];
        }
        array = newarray;
    }
    
    /**
     * adds an element to the set
     * @param item element to be added
     */
    @Override
    public void add(T item) {
        try{
            if(isIn(item)){
                System.out.println("The element you are trying to add is already in JavaSet");
                throw new Exception();
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


    /**
     * removes an element from the set
     * @param item element to be removed
     */
    @Override
    public void remove(T item) {
        if(size == 0){
            System.out.println("JavaSet has no element in it!");
            return;
        }
        if(isIn(item)){
            for(int i = 0; i < size; i++){
                if(array[i] == item){
                    int k;
                    for(k = i; k < size - 1; k++){
                        array[k] = array[k + 1];
                    }
                    array[k] = null;
                    size--;
                    break;
                }
            }
        }
        else{
            System.out.println("The element you are trying to remove is not in JavaSet");
        }
    }

    /**
     * @return size of the set
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * @return iterator of the set
     */
    @Override
    public Iterator<T> getIterator(){
        return new Iterator<T>(array, size);
    }

    /**
     * @return true if the element is in the set
     */
    private boolean isIn(T item) {
        for (var i : array) {
            if (i == item) {
                return true;
            }
        }
        return false;
    }
    /**
     * @return string representation of the set
     */
    @Override
    public String toString(){
        if(size == 0){
            return "JavaVector is empty";
        }
        String all = "";
        for(int i = 0; i < size; i++){
            if (array[i] != null){
                all += "\"" + array[i] + "\"";
            }
            if(i != size - 1){
                all += ", ";
            }
        }
        return all;
    }


}

class JavaVector<T> implements JavaContainer<T>{
    private int capacity;
    private int size;
    private Object[] array;
    
    /**
     * constructor
     * creates an empty vector sized 0
     * @param _array
     * @param _capacity
     */
    public JavaVector(int _capacity) {
        capacity = _capacity;
        array = new Object[_capacity];
        size = 0;
    }
    /**
     * overloaded equals method
     * checks if two vectors are equal
     * @param other
     * @return
     */
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

    /**
     * adds @param item to the vector
     */
    @Override
    public void add(T item) {
        if(capacity < size + 1){
            addCap();
        }
        array[size] = item;
        size++;
    }

    /**
     * removes @param item from the vector
     */
    @Override
    public void remove(T item) {
        if(size == 0){
            System.out.println("JavaVector has no element in it!");
            return;
        }
        if(isIn(item)){
            for(int i = 0; i < size; i++){
                if(array[i] == item){
                    int k;
                    for(k = i; k < size - 1; k++){
                        array[k] = array[k + 1];
                    }
                    array[k] = null;
                    size--;
                    break;
                }
            }
        }
        else{
            System.out.println("The element you are trying to remove is not in JavaVector");
        }
    }
    /**
     * @return size of the vector
     */
    @Override
    public int size() {
        return size;
    }
    /**
     * @return iterator of the vector
     */
    @Override
    public Iterator<T> getIterator(){
        return new Iterator<T>(array, size);
    }

    /**
     * @return string representation of the vector
     */
    @Override
    public String toString(){
        if(size == 0){
            return "JavaVector is empty";
        }
        String all = "";
        for(int i = 0; i < size; i++){
            if (array[i] != null){
                all += "\"" + array[i] + "\"";
            }
            if(i != size - 1){
                all += ", ";
            }
        }
        return all;
    }

    /**
     * @return true if the element is in the vector
     */
    private boolean isIn(T item) {
        for (var i : array) {
            if (i == item) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * increases capacity by multiplying it with 2
     * copies the old array to the new one
     */
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
        System.out.println("JavaSet Created...");
        //testing constructers
        System.out.println(set.toString()); 
        System.out.println("JavaSet size is : " + set.size()); 

        try {    
            set.add("cc");
            set.add("aa");
            set.add("bb");
            set.add("dd");
            set.add("ee");
            set.remove("dd");
        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }
        System.out.println("Made changes on JavaSet by adding elements or removing...");
        System.out.println("\nJavaSet toString() method calling..."); // testing toString
        System.out.println(set.toString()); // check to string

        // printing one by one by using iterator
        System.out.println("\nJavaSet Iterator method calling and printing all elements one by one...");
        Iterator<String> iterator = set.getIterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.current());
            iterator.next();
        }

        // Testing JavaVector
        JavaVector<Integer> vector = new JavaVector<>(3);
        System.out.println("\nJavaVector Created...");
        //testing constructers
        System.out.println(vector.toString());
        System.out.println("JavaVector size is : " + vector.size());

        try {
            vector.add(1);
            vector.add(2);
            vector.add(3);
            vector.add(4);
            vector.add(5);
            vector.remove(3);            
        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }

        System.out.println("Made changes on JavaVector by adding elements or removing...");
        System.out.println("\nJavaVector toString() method calling..."); // testing toString
        System.out.println(vector.toString()); // testing toString

        // printing one by one by using iterator
        System.out.println("\nJavaVector Iterator method calling and printing all elements one by one...");
        Iterator<Integer> vectiterator = vector.getIterator();
        while (vectiterator.hasNext()) {
            System.out.println(vectiterator.current()); 
            vectiterator.next();
        }
        System.out.println("JavaVector size is : " + vector.size());

        // Testing equals method
        System.out.println("\nTesting equals method...");
        JavaVector<Integer> vector2 = new JavaVector<>(3);
        vector2.add(1);
        vector2.add(2);
        vector2.add(4);
        System.out.println("vector2: " + vector2.toString());
        System.out.println("vector: " + vector.toString());
        System.out.println("vector2.equals(vector): " + vector2.equals(vector));
        System.out.println("vector.equals(vector2): " + vector.equals(vector2));
        System.out.println("vector.equals(vector): " + vector.equals(vector));
        vector2.add(5);
        System.out.println("added 5 to vector2");
        System.out.println("vector2: " + vector2.toString());
        System.out.println("vector: " + vector.toString());
        System.out.println("vector2.equals(vector): " + vector2.equals(vector));
        
        // Testing equals method
        System.out.println("\nTesting equals method for JavaSet...");
        JavaSet<Double> set2 = new JavaSet<>(2);
        set2.add(1.0);
        set2.add(4.0);
        set2.add(2.0);
        System.out.println("set2: " + set2.toString());
        System.out.println("set: " + set.toString());
        System.out.println("set2.equals(set): " + set2.equals(set));
        System.out.println("set.equals(set2): " + set.equals(set2));
        System.out.println("set.equals(set): " + set.equals(set));

        // printing sets to files

        set.printToFile("set1");
        set2.printToFile("set2");
    }

}
