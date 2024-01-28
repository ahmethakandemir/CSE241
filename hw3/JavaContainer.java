/**
JavaContainer: an interface for a container that holds elements of type T
@param <T> type of the container 
 */
public interface JavaContainer<T>{


    /**
    adds an element to the container 
    @param item element to be added
    */
    void add(T item);
    /**
    removes an element from the container
    @param item element to be removed
    */
    void remove(T item);
    /**
    returns the number of elements in the container
    @return size of the container
    */
    int size();
    /**
    returns an iterator for the container
    @return iterator of the container
    */
    Iterator<T> getIterator();

}

