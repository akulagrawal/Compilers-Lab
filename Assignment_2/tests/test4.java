/*
Lines with...
Objects: 1
Classes: 1
Constructors: 1
Inherited Classes: 0
*/

class ConsMain {
    private int x;

    // constructor
    private ConsMain(){
        System.out.println("Constructor Called");
        x = 5;
    }

    public static void main(String[] args){
        ConsMain obj = new ConsMain();
        System.out.println("Value of x = " + obj.x);
    }
}
