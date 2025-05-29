package optisim_java;

public interface OpticalSystem{
    void initialize(String filename);
    void add_thin_lens(String name, double x, double f);
    void add_thick_lens(String name, double x, double n, double d, double r_left, double r_right);
    void modify_optical_object(String name, String param, double val);
    void modify_light_source(String param, double val);
    void calculate();
    void save(String filename);
}