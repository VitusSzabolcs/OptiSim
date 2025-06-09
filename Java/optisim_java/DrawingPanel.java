// DrawingPanel.java
package optisim_java; // Declares the package for this class

import javax.swing.*; // Imports Swing components for GUI
import java.awt.*; // Imports AWT classes for graphics and UI
import java.util.ArrayList; // Imports ArrayList for dynamic lists
import java.util.Map; // Imports Map for key-value pairs

// Custom panel where optical elements or rays can be drawn graphically
public class DrawingPanel extends JPanel { // DrawingPanel extends JPanel to create a custom drawing area

    OpticalSystem OpS; // Reference to the optical system data
    boolean mode = false; // Drawing mode: false for elements only, true for rays and image
    double scale_x = 1; // Scaling factor for x-coordinates
    double scale_y = 1; // Scaling factor for y-coordinates

    // Constructor for DrawingPanel
    public DrawingPanel(OpticalSystem OpS) {
        // Set the background color of the drawing canvas
        this.OpS = OpS; // Initializes the OpticalSystem object
        setBackground(Color.WHITE); // Sets the background color of the panel
    }

    @Override // Indicates that this method overrides a superclass method
    protected void paintComponent(Graphics g) { // Method to perform custom drawing
        super.paintComponent(g); // Calls the superclass's paintComponent to ensure proper rendering

        // Cast Graphics to Graphics2D to access advanced features
        Graphics2D g2 = (Graphics2D) g; // Casts Graphics object to Graphics2D for enhanced drawing capabilities

        // Enable anti-aliasing for smoother lines
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON); // Sets rendering hint for smoother lines

        //draw x-axis
        g2.setColor(Color.GRAY); // Sets the color for the x-axis
        g2.drawLine(0, getHeight() / 2, getWidth(), getHeight() / 2); // Draws the horizontal x-axis in the middle of the panel

        int width = getWidth(); // Gets the current width of the panel
        int height = getHeight(); // Gets the current height of the panel

        Map<String, Object> LightSource = OpS.getLightSource(); // Retrieves light source data from the optical system
        Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements(); // Retrieves system elements data

        double x_min = 0; // Minimum x-coordinate for scaling
        double x_max = 0; // Maximum x-coordinate for scaling
        double y_max = 0; // Maximum y-coordinate for scaling
        double y_min = 0; // Minimum y-coordinate for scaling

        // If not in ray-tracing mode, calculate scales based on elements
        if(!mode){
            x_min = (double)LightSource.get("x"); // Sets initial x_min to light source's x-position
            x_max = x_min + 1e-3; // Sets initial x_max slightly beyond x_min
            y_max = Math.abs((double)LightSource.get("y")); // Sets y_max based on light source's y-position
            y_min = -y_max; // Sets y_min as the negative of y_max

            // Iterate through system elements to find the maximum x-coordinate
            for (String key : SystemElements.keySet()) {
                Map<String, Object> lens = SystemElements.get(key);
                if((double)lens.get("x") > x_max){ // If a lens is further right, update x_max
                    x_max = (double)lens.get("x");
                }
            }

            // Calculate scaling factors for x and y based on determined ranges
            scale_x = 0.8 * width / (x_max - x_min); 
            scale_y = 0.6 * height / (y_max - y_min);
        }

        // If in ray-tracing mode, calculate scales based on rays and elements
        if(mode){
            Map<String, Map<String, Object>> Rays = OpS.getRays(); // Retrieves ray data
            Map<String, Object> ray = Rays.get("ray_1"); // Gets the first ray for initial calculations
            ArrayList list = (ArrayList) ray.get("x"); // Gets the x-coordinates of the ray
            double x_last = (Double) list.get(list.size() - 1); // Gets the last x-coordinate of the ray

            x_min = (double)LightSource.get("x"); // Resets x_min to light source position
            x_max = x_min + 1e-3; // Resets x_max slightly beyond x_min

            // Update x_max based on system elements
            for (String key : SystemElements.keySet()) {
                Map<String, Object> lens = SystemElements.get(key);
                if((double)lens.get("x") > x_max){
                    x_max = (double)lens.get("x");
                }
            }

            // If the last x-coordinate of the ray is infinite (ray goes to infinity)
            if(Double.isInfinite(x_last)){
                double x_ls = (double)LightSource.get("x"); // Stores original light source x
                OpS.modify_light_source("x", x_ls - 1e-2); // Temporarily modify light source x to recalculate rays
                OpS.calculate(); // Recalculates the optical system
                Rays = OpS.getRays(); // Retrieves updated ray data

                y_max = Math.abs((double)LightSource.get("y")); // Updates y_max based on light source

                // Iterate through rays to find maximum y-coordinate for scaling
                for (String key : Rays.keySet()) {
                    ray = Rays.get(key);
                    list = (ArrayList) ray.get("y");
                    for(int i = 0; i < list.size()-1; i++){
                        double y = (double)list.get(i);
                        if(Math.abs(y) > y_max){
                            y_max = Math.abs(y);
                        }
                    }
                }

                y_min = -y_max; // Sets y_min

                // Recalculate scaling factors
                scale_x = 0.8 * width / (x_max - x_min);
                scale_y = 0.6 * height / (y_max - y_min);

                // Draw rays when x_last is infinite
                for (String key : Rays.keySet()) {
                    ray = Rays.get(key);
                    ArrayList list_x = (ArrayList) ray.get("x"); // X-coordinates of the ray
                    ArrayList list_y = (ArrayList) ray.get("y"); // Y-coordinates of the ray
                    Color color = Color.BLUE; // Default ray color
                    if(key.contains("ray_2")){ // Second ray gets a different color
                        color = Color.GREEN;
                    }
                    // Loop to draw each segment of the ray
                    for(int i = list_x.size()-1; i > 0; i--){
                        double y1 = (double)list_y.get(i-1); // Start y of segment
                        double x1 = (double)list_x.get(i-1); // Start x of segment
                        double y2 = (double)list_y.get(i); // End y of segment
                        double x2 = (double)list_x.get(i); // End x of segment
                    
                        // Convert real-world coordinates to screen coordinates
                        int x1_draw = (int)Math.round(getWidth() * 0.1 + (x1 - x_min) * scale_x);
                        int x2_draw = (int)Math.round(getWidth() * 0.1 + (x2 - x_min) * scale_x);
                        int y1_draw = (int)Math.round(getHeight() / 2 - y1 * scale_y);
                        int y2_draw = (int)Math.round(getHeight() / 2 - y2 * scale_y);
                        
                        g2.setColor(color); // Sets ray color
                        g2.setStroke(new BasicStroke(2)); // Sets stroke thickness for solid lines
                        // If ray goes backward (virtual ray)
                        if(x2 < x1){
                            // Draws a very long line to represent the virtual extension
                            g2.drawLine(x1_draw, y1_draw, x1_draw + 1000 * (x1_draw - x2_draw), y1_draw + 1000 * (y1_draw - y2_draw));
                            float[] dash = {10.0f, 5.0f}; // Defines dash pattern for virtual rays
                            g2.setStroke(new BasicStroke( // Sets dashed stroke for virtual rays
                                2.0f,                      // Line width
                                BasicStroke.CAP_BUTT,     // End cap
                                BasicStroke.JOIN_MITER,   // Line join
                                10.0f,                     // Miter limit
                                dash,                     // Dash pattern
                                0.0f                      // Dash phase
                            ));
                        }
                        g2.drawLine(x1_draw, y1_draw, x2_draw, y2_draw); // Draws the ray segment
                    }
                }

                OpS.modify_light_source("x", x_ls); // Restores original light source x
                OpS.calculate(); // Recalculates the optical system to its original state
            }
            // If the last x-coordinate of the ray is finite (ray converges)
            else if(Double.isFinite(x_last)){
                if(x_last > x_max) x_max = x_last; // Updates x_max if ray extends further
                if(x_last < x_min) x_min = x_last; // Updates x_min if ray extends backward

                y_max = Math.abs((double)LightSource.get("y")); // Updates y_max based on light source

                // Iterate through rays to find maximum y-coordinate for scaling
                for (String key : Rays.keySet()) {
                    ray = Rays.get(key);
                    list = (ArrayList) ray.get("y");
                    for(int i = 0; i < list.size(); i++){
                        double y = (double)list.get(i);
                        if(Math.abs(y) > y_max){
                            y_max = Math.abs(y);
                        }
                    }
                }
                y_min = -y_max; // Sets y_min

                // Recalculate scaling factors
                scale_x = 0.8 * width / (x_max - x_min);
                scale_y = 0.6 * height / (y_max - y_min);

                Map<String, Object> img = OpS.calculate(); // Calculates the image properties
        
                drawImagingSubject(g2, img, x_min, y_min, y_max, Color.ORANGE, "Image"); // Draws the image

                // Draw rays when x_last is finite
                for (String key : Rays.keySet()) {
                    ray = Rays.get(key);
                    ArrayList list_x = (ArrayList) ray.get("x"); // X-coordinates of the ray
                    ArrayList list_y = (ArrayList) ray.get("y"); // Y-coordinates of the ray
                    Color color = Color.BLUE; // Default ray color
                    if(key.contains("ray_2")){ // Second ray gets a different color
                        color = Color.GREEN;
                    }
                    // Loop to draw each segment of the ray
                    for(int i = list_x.size()-1; i > 0; i--){
                        double y1 = (double)list_y.get(i-1); // Start y of segment
                        double x1 = (double)list_x.get(i-1); // Start x of segment
                        double y2 = (double)list_y.get(i); // End y of segment
                        double x2 = (double)list_x.get(i); // End x of segment
                    
                        // Convert real-world coordinates to screen coordinates
                        int x1_draw = (int)Math.round(getWidth() * 0.1 + (x1 - x_min) * scale_x);
                        int x2_draw = (int)Math.round(getWidth() * 0.1 + (x2 - x_min) * scale_x);
                        int y1_draw = (int)Math.round(getHeight() / 2 - y1 * scale_y);
                        int y2_draw = (int)Math.round(getHeight() / 2 - y2 * scale_y);
                        
                        g2.setColor(color); // Sets ray color
                        // If ray goes backward (virtual ray)
                        if(x2 < x1){
                            // Draws a very long line to represent the virtual extension
                            g2.drawLine(x1_draw, y1_draw, x1_draw + 1000 * (x1_draw - x2_draw), y1_draw + 1000 * (y1_draw - y2_draw));
                            float[] dash = {10.0f, 5.0f}; // Defines dash pattern for virtual rays
                            g2.setStroke(new BasicStroke( // Sets dashed stroke for virtual rays
                                2.0f,                      // Line width
                                BasicStroke.CAP_BUTT,     // End cap
                                BasicStroke.JOIN_MITER,   // Line join
                                10.0f,                     // Miter limit
                                dash,                     // Dash pattern
                                0.0f                      // Dash phase
                            ));
                        }
                        g2.drawLine(x1_draw, y1_draw, x2_draw, y2_draw); // Draws the ray segment
                        g2.setStroke(new BasicStroke(2)); // Resets stroke to solid for subsequent drawings
                    }
                }
            }
        }

        // Draw system elements (lenses)
        for (String key : SystemElements.keySet()) {
                Map<String, Object> lens = SystemElements.get(key);
                String type = (String) lens.get("type"); // Gets the type of the lens
                if(type.contains("ThinLens")){ // If it's a thin lens
                    drawLens(g2, lens, x_min, 2, key); // Draw thin lens with thickness 2
                }
                else if(type.contains("ThickLens")){ // If it's a thick lens
                    drawLens(g2, lens, x_min, 6, key); // Draw thick lens with thickness 6
                }
            }
            drawImagingSubject(g2, LightSource, x_min, y_min, y_max, Color.RED, "Light Source"); // Draws the light source

    }

    // Helper method to draw a lens on the panel
    private void drawLens(Graphics2D g2, Map<String, Object> Lens, double x_min, int thickness, String name){
        double x = (double) Lens.get("x"); // Gets the x-position of the lens
        double f = (double) Lens.get("f"); // Gets the focal length of the lens

        // Convert lens x-position to screen coordinates
        int x_draw = (int)Math.round((x - x_min) * scale_x + getWidth() * 0.1);
        int y_draw1 = (int)Math.round(getHeight() * 0.1); // Top y-coordinate for the lens line
        int y_draw2 = (int)Math.round(getHeight() * 0.9); // Bottom y-coordinate for the lens line

        g2.setColor(Color.BLACK); // Sets lens color to black
        g2.setStroke(new BasicStroke(thickness)); // Sets lens line thickness
        g2.drawLine(x_draw, y_draw1, x_draw, y_draw2); // Draws the main vertical line for the lens

        // Draw arrows for converging (positive focal length) lens
        if(f > 0.0){
            g2.drawLine(x_draw, y_draw1, x_draw - (int)Math.round(getWidth())/90, y_draw1 + (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw1, x_draw + (int)Math.round(getWidth())/90, y_draw1 + (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw2, x_draw - (int)Math.round(getWidth())/90, y_draw2 - (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw2, x_draw + (int)Math.round(getWidth())/90, y_draw2 - (int)Math.round(getWidth())/70);
        }

        // Draw arrows for diverging (negative focal length) lens
        if(f < 0.0){
            g2.drawLine(x_draw, y_draw1, x_draw - (int)Math.round(getWidth())/90, y_draw1 - (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw1, x_draw + (int)Math.round(getWidth())/90, y_draw1 - (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw2, x_draw - (int)Math.round(getWidth())/90, y_draw2 + (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw2, x_draw + (int)Math.round(getWidth())/90, y_draw2 + (int)Math.round(getWidth())/70);
        }

        g2.setFont(new Font("Arial", Font.BOLD, 16)); // Sets font for lens name
        FontMetrics fm = g2.getFontMetrics(); // Gets font metrics to measure text width
        int textWidth = fm.stringWidth(name); // Calculates the width of the lens name
        g2.drawString(name, x_draw - textWidth/2, (int)Math.round(getHeight() * 0.95)); // Draws the lens name below it
    }

    // Helper method to draw an imaging subject (light source or image)
    private void drawImagingSubject(Graphics2D g2, Map<String, Object> LS, double x_min, double y_min, double y_max, Color color, String name){
        double x = (double) LS.get("x"); // Gets the x-position of the subject
        double y = (double) LS.get("y"); // Gets the y-size of the subject

        // Convert x-position to screen coordinates
        int x_draw = (int)Math.round((x - x_min) * scale_x + getWidth() * 0.1);

        // Convert y-size to screen coordinates, relative to the center axis
        int y_draw1 = (int)Math.round(getHeight() / 2 - y * scale_y);
        int y_draw2 = getHeight()/2; // Y-coordinate of the optical axis

        g2.setColor(color); // Sets the color for the imaging subject
        g2.setStroke(new BasicStroke(2)); // Sets stroke thickness
        g2.drawLine(x_draw, y_draw1, x_draw, y_draw2); // Draws the vertical line representing the subject
        // Draw an arrow head pointing upwards if y is positive
        if(y > 0){
            g2.drawLine(x_draw, y_draw1, x_draw - (int)Math.round(Math.abs(y_draw1 - y_draw2)/10), y_draw1 + (int)Math.round(Math.abs(y_draw1 - y_draw2)/8));
            g2.drawLine(x_draw, y_draw1, x_draw + (int)Math.round(Math.abs(y_draw1 - y_draw2)/10), y_draw1 + (int)Math.round(Math.abs(y_draw1 - y_draw2)/8));
        }
        // Draw an arrow head pointing downwards if y is negative
        else if(y < 0){
            g2.drawLine(x_draw, y_draw1, x_draw - (int)Math.round(Math.abs(y_draw1 - y_draw2)/10), y_draw1 - (int)Math.round(Math.abs(y_draw1 - y_draw2)/8));
            g2.drawLine(x_draw, y_draw1, x_draw + (int)Math.round(Math.abs(y_draw1 - y_draw2)/10), y_draw1 - (int)Math.round(Math.abs(y_draw1 - y_draw2)/8));
        }
        g2.setFont(new Font("Arial", Font.BOLD, 16)); // Sets font for subject name
        FontMetrics fm = g2.getFontMetrics(); // Gets font metrics
        int textWidth = fm.stringWidth(name); // Calculates width of the subject name
        g2.drawString(name, x_draw - textWidth/2, (int)Math.round(Math.signum(y) * getHeight() * 0.03) + getHeight()/2); // Draws the subject name
    }

    // Setter for the drawing mode
    public void setMode(boolean m){
        mode = m; // Sets the drawing mode (true for ray tracing, false for just elements)
    }
}