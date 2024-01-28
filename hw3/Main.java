/**
 * Main class for testing JavaSet and JavaVector classes.
*/

public class Main {
    /**
     * Constructor for Main class.
     */
    public Main(){
        //initially empty constructor
    }
    

    /**
     * Main method for testing JavaSet and JavaVector classes.
     * @param args command line arguments
     */
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
        set2.add(3.0);
        set2.remove(3.0);


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
