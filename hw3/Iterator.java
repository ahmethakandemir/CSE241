/**
    Iterator class to iterate over the set or vector
    I also added 3 more functions to make it easier to use
    @param <T> type of the set or vector
 */
public class Iterator<T>{
    /** currentIndex: index of the current element */
    private int currentIndex;
    /** size: size of the set or vector */
    private int size;
    /** array: set or vector's array */
    private Object[] array;
    /**
    constructor
    @param _array calling set or vector's array
    @param _size calling set or vector's size
     */
    public Iterator(Object[] _array, int _size){
        currentIndex = 0;
        size = _size;
        array = _array;
    }

    /**
    function to check if there is a next element
    @return true if there is a next element
    */
    boolean hasNext(){
        return currentIndex < size;
    }
    /**
    function to get the next element
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
     current: returns the current element
     @return current element
     */
    @SuppressWarnings("unchecked")
    T current(){
        return (T) array[currentIndex];
    }
    /**
    toString method 
    @return string representation of the iterator
     */
    public String toString(){
        return "current index is " + currentIndex;
    }

}
