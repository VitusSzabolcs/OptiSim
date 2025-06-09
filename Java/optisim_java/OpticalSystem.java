package optisim_java; // Declares the package for this interface

import java.util.Map; // Imports Map for key-value pairs

public interface OpticalSystem{ // Defines the OpticalSystem interface
    // Initializes the optical system from a specified file
    void initialize(String filename);
    // Adds a new thin lens to the optical system
    void add_thin_lens(String name, double x, double f);
    // Adds a new thick lens to the optical system
    void add_thick_lens(String name, double x, double n, double d, double r_left, double r_right);
    // Modifies a parameter of an existing optical object
    void modify_optical_object(String name, String param, double val);
    // Modifies a parameter of the light source
    void modify_light_source(String param, double val);
    // Calculates the light propagation through the system and returns image properties
    Map<String, Object> calculate();
    // Saves the current optical system configuration to a file
    void save(String filename);
    // Retrieves a map of all system elements
    Map<String, Map<String, Object>> getSystemElements();
    // Retrieves the light source properties
    Map<String, Object> getLightSource();
    // Retrieves a map of all calculated rays
    Map<String, Map<String, Object>> getRays();
    // Removes an optical object from the system by its name
    void remove(String name);
}