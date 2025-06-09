package optisim_java; // Declares the package for this class

import javax.swing.*; // Imports Swing components for GUI
import java.awt.*; // Imports AWT classes for graphics and UI

// Main window class for the optical simulator GUI
public class OpticalSimulatorGUI extends JFrame { // OpticalSimulatorGUI extends JFrame to create the main application window
    private ElementListPanel elementListPanel; // Panel for element controls and list
    private DrawingPanel drawingPanel;         // Panel for 2D graphics

    // Constructor for OpticalSimulatorGUI
    public OpticalSimulatorGUI(OpticalSystem OpS) {
        // Configure the main frame
        setTitle("Optical Simulator"); // Sets the title of the window
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Sets default close operation to exit the application
        setSize(1400, 800); // Set initial window size
        setLocationRelativeTo(null); // Center the window on screen
        setLayout(new BorderLayout()); // Use BorderLayout for layout management of the main frame
        
        // Initialize the left control panel and the center drawing panel
        elementListPanel = new ElementListPanel(this, OpS); // Creates an instance of ElementListPanel
        drawingPanel = new DrawingPanel(OpS);         // Creates an instance of DrawingPanel

        // Add the panels to the respective positions in the layout
        add(elementListPanel, BorderLayout.WEST); // Adds the element list panel to the west (left)
        add(drawingPanel, BorderLayout.CENTER); // Adds the drawing panel to the center

        setVisible(true); // Display the window
    }
    
    // Provide access to the drawing panel for repainting purposes
    public DrawingPanel getDrawingPanel() {
        return drawingPanel; // Returns the DrawingPanel instance
    }
}