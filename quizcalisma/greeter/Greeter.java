package greeter;
public class Greeter {
    /**
     constructer for class greeter
     @param aName is assigned to name string in class
     */
    public Greeter(String aName) {
        name = aName;
    }

    /**
    greeter function.
     @return "hello" and name that Greeter class contains.
     */
    public String sayHello() {
        return "Hello, " + name + "!";
    }

    /**
    setting the name
    @param other other Greeter object's name assigned to the calling object.
    */
    public void setName(Greeter other) {
        other.name = name;
    }

    private String name;

    /**
    This is main function
    */
    public static void main() {
        Greeter worldGreeter = new Greeter("World");
        String greeting = worldGreeter.sayHello();
        System.out.println(greeting);
        // double x = 10.0 / 3.0; // sets x to 3.3333333333333335
        // int n = (int)x; // sets n to 3
        // float f = (float)x; // sets f to 3.3333333
        // System.out.println(x+ " " + n+" " +f);
        Greeter newgreeter = new Greeter("Zort");
        newgreeter.setName(worldGreeter);
        String greeting2 = worldGreeter.sayHello();
        System.out.println(greeting2);

    }
}
