package optisim_java;

import javax.swing.*;
import java.awt.*;

// Main window class for the optical simulator GUI
public class OpticalSimulatorGUI extends JFrame {
    private ElementListPanel elementListPanel; // Panel for element controls and list
    private DrawingPanel drawingPanel;         // Panel for 2D graphics

    public OpticalSimulatorGUI(OpticalSystem OpS) {
        // Configure the main frame
        setTitle("Optical Simulator");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1400, 800); // Set initial window size
        setLocationRelativeTo(null); // Center the window on screen
        setLayout(new BorderLayout()); // Use BorderLayout for layout management
        
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