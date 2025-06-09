package optisim_java; // Declares the package for this exception class

public class OptiSimError extends RuntimeException{ // OptiSimError extends RuntimeException for unchecked exceptions
    // Constructor for OptiSimError that takes a message
    public OptiSimError(String message){
        super(message); // Calls the superclass (RuntimeException) constructor with the provided message
    }
}