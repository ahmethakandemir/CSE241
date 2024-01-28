import java.io.FileWriter;
import java.io.IOException;
/**
    * JavaSet
    * @param <T> type of the set
 */
public class JavaSet<T> implements JavaContainer<T>{
    /** capacity: capacity of the set */
    private int capacity;
    /** array: set's array */
    private Object[] array;
    /** size: size of the set */
    private int size;
    

    /**
    constructor
    creates an empty set sized 0
    @param _capacity capacity of the set
     */
    public JavaSet(int _capacity) {
        capacity = _capacity;
        array = new Object[capacity];
        size = 0;
    }
    /**
    overloaded equals method
    checks if two sets are equal
    @param other other set
    @return true if they are equal
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
    prints the set to a file
    @param filename name of the file, .txt will be added automatically
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
    adds an element to the set
    @param item element to be added
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
    removes an element from the set
    @param item element to be removed
     */

    @Override
    public void remove(T item) {
        if(size == 0){
            System.out.println("JavaSet has no element in it!");
            return;
        }
        if(isIn(item)){
            /**
                * if the item is a double, we need to use Math.abs() to compare
                * because of the precision of double
             */
            if(item instanceof Double){
                for(int i = 0; i < size; i++){
                    if(Math.abs((Double) array[i] - (Double) item) < 1e-6){
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
        }
        else{
            System.out.println("The element you are trying to remove is not in JavaSet");
        }
    }

    /**
    @return size of the set
     */
    @Override
    public int size() {
        return size;
    }

    /**
    @return iterator of the set
     */
    @Override
    public Iterator<T> getIterator(){
        return new Iterator<T>(array, size);
    }

    /**
     * checks if the element is in the set
    @return true if the element is in the set
    @param item element to be checked
     */
    private boolean isIn(T item) {
        if(item instanceof Double){
            for(int i = 0; i < size; i++){
                if(Math.abs((Double) array[i] - (Double) item) < 1e-6){
                    return true;
                }
            }
        }
        else{
            for (var _item : array) {
                if (_item == item) {
                    return true;
                }
            }
        }
        return false;
    }
    /**
    @return string representation of the set
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