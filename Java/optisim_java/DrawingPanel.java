package optisim_java;

import javax.swing.*;
import java.awt.*;

// Custom panel where optical elements or rays can be drawn graphically
public class DrawingPanel extends JPanel {
    public DrawingPanel(OpticalSystem OpS) {
        // Set the background color of the drawing canvas
        setBackground(Color.WHITE);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        // Example drawing (placeholder for future simulation visuals)
        //  .
        //  .
        //  .
        g.setColor(Color.BLUE);
        g.drawString("2D Optical Simulation", 20, 20);
    }
}
