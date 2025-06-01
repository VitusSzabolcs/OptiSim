// DrawingPanel.java
package optisim_java;

import javax.swing.*;
import java.awt.*;
import java.util.Map;

// Custom panel where optical elements or rays can be drawn graphically
public class DrawingPanel extends JPanel {

    OpticalSystem OpS;
    boolean mode = false;
    double scale_x = 1;
    double scale_y = 1;

    public DrawingPanel(OpticalSystem OpS) {
        // Set the background color of the drawing canvas
        this.OpS = OpS;
        setBackground(Color.WHITE);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        // Cast Graphics to Graphics2D to access advanced features
        Graphics2D g2 = (Graphics2D) g;

        // Enable anti-aliasing for smoother lines
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        //draw x-axis
        g2.setColor(Color.GRAY);
        g2.drawLine(0, getHeight() / 2, getWidth(), getHeight() / 2);

        int width = getWidth();
        int height = getHeight();

        if(!mode){
            Map<String, Object> LightSource = OpS.getLightSource();

            double x_min = (double)LightSource.get("x");
            double x_max = x_min + 1e-3;
            double y_max = (double)LightSource.get("y");
            double y_min = -y_max;

            Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements();
            for (String key : SystemElements.keySet()) {
                Map<String, Object> fields = SystemElements.get(key);
                if((double)fields.get("x") > x_max){
                    x_max = (double)fields.get("x");
                }
            }

            scale_x = 0.8 * width / (x_max - x_min); 
            scale_y = 0.6 * height / (y_max - y_min);

            for (String key : SystemElements.keySet()) {
                Map<String, Object> lens = SystemElements.get(key);
                String type = (String) lens.get("type");
                if(type.contains("ThinLens")){
                    drawLens(g2, lens, x_min, 2);
                }
                else if(type.contains("ThickLens")){
                    drawLens(g2, lens, x_min, 6);
                }
            }
        }

        

        // Example drawing: Title
        // g2.setColor(Color.BLUE);

        // if(mode) g2.drawString("2D Optical Simulation", 20, 20);
        // if(!mode) g2.drawString("Masik opcio", 40, 40);

        // // Set thicker stroke for reference lines
        // g2.setStroke(new BasicStroke(2)); // 2-pixel thick line

        // // Draw horizontal reference line (e.g., optical axis)
        // g2.setColor(Color.GRAY);
        // g2.drawLine(0, getHeight() / 2, getWidth(), getHeight() / 2);

        // // Draw vertical reference line
        // g2.setColor(Color.LIGHT_GRAY);
        // g2.drawLine(getWidth() / 2, 0, getWidth() / 2, getHeight());

        // // Reset to default stroke for arrows
        // g2.setStroke(new BasicStroke(1));
        // g2.setColor(Color.RED);

        // // Arrow pointing right
        // g2.drawLine(100, getHeight() / 2, 150, getHeight() / 2);
        // g2.drawLine(150, getHeight() / 2, 145, getHeight() / 2 - 5);
        // g2.drawLine(150, getHeight() / 2, 145, getHeight() / 2 + 5);

        // // Arrow pointing up
        // g2.drawLine(getWidth() / 2, 300, getWidth() / 2, 250);
        // g2.drawLine(getWidth() / 2, 250, getWidth() / 2 - 5, 255);
        // g2.drawLine(getWidth() / 2, 250, getWidth() / 2 + 5, 255);
    }

    private void drawLens(Graphics2D g2, Map<String, Object> Lens, double x_min, int thickness){
        double x = (double) Lens.get("x");
        double f = (double) Lens.get("f");


        int x_draw = (int)Math.round((x - x_min) * scale_x + getWidth() * 0.1);
        int y_draw1 = (int)Math.round(getHeight() * 0.1);
        int y_draw2 = (int)Math.round(getHeight() * 0.9);

        g2.setColor(Color.BLACK);
        g2.setStroke(new BasicStroke(thickness));
        g2.drawLine(x_draw, y_draw1, x_draw, y_draw2);

        if(f > 0.0){
            g2.drawLine(x_draw, y_draw1, x_draw - (int)Math.round(getWidth())/90, y_draw1 + (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw1, x_draw + (int)Math.round(getWidth())/90, y_draw1 + (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw2, x_draw - (int)Math.round(getWidth())/90, y_draw2 - (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw2, x_draw + (int)Math.round(getWidth())/90, y_draw2 - (int)Math.round(getWidth())/70);
        }

        if(f < 0.0){
            g2.drawLine(x_draw, y_draw1, x_draw - (int)Math.round(getWidth())/90, y_draw1 - (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw1, x_draw + (int)Math.round(getWidth())/90, y_draw1 - (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw2, x_draw - (int)Math.round(getWidth())/90, y_draw2 + (int)Math.round(getWidth())/70);
            g2.drawLine(x_draw, y_draw2, x_draw + (int)Math.round(getWidth())/90, y_draw2 + (int)Math.round(getWidth())/70);
        }
    }

    public void setMode(boolean m){
        mode = m;
    }
}