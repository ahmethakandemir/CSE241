// Example of a simple class
public class javadeneme {
    public String brand;
    String model;

    public javadeneme(String brand, String model) {
        this.brand = brand;
        this.model = model;
    }

    public void startEngine() {
        System.out.println("Engine started for " + brand + " " + model);
    }
    public static void main(String[] args){
        System.out.println();
    }
}
