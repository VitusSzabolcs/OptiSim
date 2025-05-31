// DrawingPanel.java
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

        // Cast Graphics to Graphics2D to access advanced features
        Graphics2D g2 = (Graphics2D) g;

        // Enable anti-aliasing for smoother lines
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // Example drawing: Title
        g2.setColor(Color.BLUE);
        g2.drawString("2D Optical Simulation", 20, 20);

        // Set thicker stroke for reference lines
        g2.setStroke(new BasicStroke(2)); // 2-pixel thick line

        // Draw horizontal reference line (e.g., optical axis)
        g2.setColor(Color.GRAY);
        g2.drawLine(0, getHeight() / 2, getWidth(), getHeight() / 2);

        // Draw vertical reference line
        g2.setColor(Color.LIGHT_GRAY);
        g2.drawLine(getWidth() / 2, 0, getWidth() / 2, getHeight());

        // Reset to default stroke for arrows
        g2.setStroke(new BasicStroke(1));
        g2.setColor(Color.RED);

        // Arrow pointing right
        g2.drawLine(100, getHeight() / 2, 150, getHeight() / 2);
        g2.drawLine(150, getHeight() / 2, 145, getHeight() / 2 - 5);
        g2.drawLine(150, getHeight() / 2, 145, getHeight() / 2 + 5);

        // Arrow pointing up
        g2.drawLine(getWidth() / 2, 300, getWidth() / 2, 250);
        g2.drawLine(getWidth() / 2, 250, getWidth() / 2 - 5, 255);
        g2.drawLine(getWidth() / 2, 250, getWidth() / 2 + 5, 255);
    }
}