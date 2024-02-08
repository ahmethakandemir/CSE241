/** JavaVector Class
 * implements JavaContainer interface
 * @param <T> type of the vector
 */
public class JavaVector<T> implements JavaContainer<T>{
    /** capacity of JavaVector */
    private int capacity;
    /** size of JavaVector */
    private int size;
    /** array of JavaVector */
    private Object[] array;
    
    /**
    constructor
    creates an empty vector sized 0
    @param _capacity capacity of the vector
     */
    public JavaVector(int _capacity) {
        capacity = _capacity;
        array = new Object[_capacity];
        size = 0;
    }
    /**
    overloaded equals method
    checks if two vectors are equal
    @param other other vector
    @return true if they are equal
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
    adds @param item to the vector
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
    removes @param item from the vector
     */
    @Override
    public void remove(T item) {
        if(size == 0){
            System.out.println("JavaVector has no element in it!");
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
            System.out.println("The element you are trying to remove is not in JavaVector");
        }
    }
    /**
    @return size of the vector
     */
    @Override
    public int size() {
        return size;
    }
    /**
    @return iterator of the vector
     */
    @Override
    public Iterator<T> getIterator(){
        return new Iterator<T>(array, size);
    }

    /**
    @return string representation of the vector
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
     * checks if the element is in the vector
    @return true if the element is in the vector
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
    increases capacity by multiplying it with 2
    copies the old array to the new one
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
