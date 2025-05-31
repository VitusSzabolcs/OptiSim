package optisim_java;

import javax.swing.*;
import java.awt.*;
import java.util.Map;

// Main window class for the optical simulator GUI
public class OpticalSimulatorGUI extends JFrame {
    private ElementListPanel elementListPanel; // Panel for element controls and list
    private DrawingPanel drawingPanel;         // Panel for 2D graphics

    public OpticalSimulatorGUI(OpticalSystem OpS) {
        // Configure the main frame
        setTitle("Optical Simulator");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1000, 600); // Set initial window size
        setLocationRelativeTo(null); // Center the window on screen
        setLayout(new BorderLayout()); // Use BorderLayout for layout management
        
        // OpS.add_thin_lens("Lens1", 10, 10);
        // OpS.add_thick_lens("Lens2", 20, 10, 10, 10, 10);
        // OpS.modify_light_source("x", 1);
        // OpS.modify_optical_object("Lens1", "x", 10);
        // Map<String, Object> Image = OpS.calculate();

        // System.out.println(Image.get("x"));
        // System.out.println(Image.get("y"));

        // Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements();
        // for (String key : SystemElements.keySet()) {
        //     System.out.println("Element ID: " + key);
        //     Map<String, Object> fields = SystemElements.get(key);
        //     for (String field : fields.keySet()) {
        //         System.out.println("  " + field + ": " + fields.get(field));
        //     }
        // }
        // Map<String, Object> LightSource = OpS.getLightSource();
        // System.out.println(LightSource.get("x"));
        // System.out.println(LightSource.get("y"));
        // Map<String, Map<String, Object>> Rays = OpS.getRays();
        // for (String key : Rays.keySet()) {
        //     System.out.println("Element ID: " + key);
        //     Map<String, Object> fields = Rays.get(key);
        //     for (String field : fields.keySet()) {
        //         System.out.println("  " + field + ": " + fields.get(field));
        //     }
        // }
        
        // Initialize the left control panel and the center drawing panel
        elementListPanel = new ElementListPanel(this, OpS);
        drawingPanel = new DrawingPanel(OpS);

        // Add the panels to the respective positions in the layout
        add(elementListPanel, BorderLayout.WEST);
        add(drawingPanel, BorderLayout.CENTER);

        setVisible(true); // Display the window
    }
    
    // Provide access to the drawing panel for repainting purposes
    public DrawingPanel getDrawingPanel() {
        return drawingPanel;
    }
}