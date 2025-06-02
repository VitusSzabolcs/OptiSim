// DrawingPanel.java
package optisim_java;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
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

        Map<String, Object> LightSource = OpS.getLightSource();
        Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements();

        double x_min = 0;
        double x_max = 0;
        double y_max = 0;
        double y_min = 0;

        if(!mode){

            x_min = (double)LightSource.get("x");
            x_max = x_min + 1e-3;
            y_max = Math.abs((double)LightSource.get("y"));
            y_min = -y_max;

            
            for (String key : SystemElements.keySet()) {
                Map<String, Object> lens = SystemElements.get(key);
                if((double)lens.get("x") > x_max){
                    x_max = (double)lens.get("x");
                }
            }

            scale_x = 0.8 * width / (x_max - x_min); 
            scale_y = 0.6 * height / (y_max - y_min);
        }

        if(mode){
            Map<String, Map<String, Object>> Rays = OpS.getRays();
            Map<String, Object> ray = Rays.get("ray_1");
            ArrayList list = (ArrayList) ray.get("x");
            double x_last = (Double) list.get(list.size() - 1);

            x_min = (double)LightSource.get("x");
            x_max = x_min + 1e-3;

            for (String key : SystemElements.keySet()) {
                Map<String, Object> lens = SystemElements.get(key);
                if((double)lens.get("x") > x_max){
                    x_max = (double)lens.get("x");
                }
            }

            if(Double.isInfinite(x_last)){

                double x_ls = (double)LightSource.get("x");
                OpS.modify_light_source("x", x_ls - 1e-2);
                OpS.calculate();
                Rays = OpS.getRays();


                y_max = Math.abs((double)LightSource.get("y"));

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

                y_min = -y_max;

                scale_x = 0.8 * width / (x_max - x_min);
                scale_y = 0.6 * height / (y_max - y_min);

                for (String key : Rays.keySet()) {
                    ray = Rays.get(key);
                    ArrayList list_x = (ArrayList) ray.get("x");
                    ArrayList list_y = (ArrayList) ray.get("y");
                    Color color = Color.BLUE;
                    if(key.contains("ray_2")){
                        color = Color.GREEN;
                    }
                    for(int i = list_x.size()-1; i > 0; i--){
                        double y1 = (double)list_y.get(i-1);
                        double x1 = (double)list_x.get(i-1);
                        double y2 = (double)list_y.get(i);
                        double x2 = (double)list_x.get(i);
                    
                        int x1_draw = (int)Math.round(getWidth() * 0.1 + (x1 - x_min) * scale_x);
                        int x2_draw = (int)Math.round(getWidth() * 0.1 + (x2 - x_min) * scale_x);
                        int y1_draw = (int)Math.round(getHeight() / 2 - y1 * scale_y);
                        int y2_draw = (int)Math.round(getHeight() / 2 - y2 * scale_y);
                        
                        
                        g2.setColor(color);
                        g2.setStroke(new BasicStroke(2));
                        if(x2 < x1){
                            g2.drawLine(x1_draw, y1_draw, x1_draw + 1000 * (x1_draw - x2_draw), y1_draw + 1000 * (y1_draw - y2_draw));
                            float[] dash = {10.0f, 5.0f};
                            g2.setStroke(new BasicStroke(
                                2.0f,                      // Line width
                                BasicStroke.CAP_BUTT,     // End cap
                                BasicStroke.JOIN_MITER,   // Line join
                                10.0f,                     // Miter limit
                                dash,                     // Dash pattern
                                0.0f                      // Dash phase
                            ));
                        }
                        g2.drawLine(x1_draw, y1_draw, x2_draw, y2_draw);
                    }
                }

                OpS.modify_light_source("x", x_ls);
                OpS.calculate();
            }
            else if(Double.isFinite(x_last)){
                if(x_last > x_max) x_max = x_last;
                if(x_last < x_min) x_min = x_last;

                y_max = Math.abs((double)LightSource.get("y"));

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
                y_min = -y_max;

                scale_x = 0.8 * width / (x_max - x_min);
                scale_y = 0.6 * height / (y_max - y_min);

                Map<String, Object> img = OpS.calculate();
        
                drawImagingSubject(g2, img, x_min, y_min, y_max, Color.ORANGE, "Image");

                for (String key : Rays.keySet()) {
                    ray = Rays.get(key);
                    ArrayList list_x = (ArrayList) ray.get("x");
                    ArrayList list_y = (ArrayList) ray.get("y");
                    Color color = Color.BLUE;
                    if(key.contains("ray_2")){
                        color = Color.GREEN;
                    }
                    for(int i = list_x.size()-1; i > 0; i--){
                        double y1 = (double)list_y.get(i-1);
                        double x1 = (double)list_x.get(i-1);
                        double y2 = (double)list_y.get(i);
                        double x2 = (double)list_x.get(i);
                    
                        int x1_draw = (int)Math.round(getWidth() * 0.1 + (x1 - x_min) * scale_x);
                        int x2_draw = (int)Math.round(getWidth() * 0.1 + (x2 - x_min) * scale_x);
                        int y1_draw = (int)Math.round(getHeight() / 2 - y1 * scale_y);
                        int y2_draw = (int)Math.round(getHeight() / 2 - y2 * scale_y);
                        
                        
                        g2.setColor(color);
                        if(x2 < x1){
                            g2.drawLine(x1_draw, y1_draw, x1_draw + 1000 * (x1_draw - x2_draw), y1_draw + 1000 * (y1_draw - y2_draw));
                            float[] dash = {10.0f, 5.0f};
                            g2.setStroke(new BasicStroke(
                                2.0f,                      // Line width
                                BasicStroke.CAP_BUTT,     // End cap
                                BasicStroke.JOIN_MITER,   // Line join
                                10.0f,                     // Miter limit
                                dash,                     // Dash pattern
                                0.0f                      // Dash phase
                            ));
                        }
                        g2.drawLine(x1_draw, y1_draw, x2_draw, y2_draw);
                        g2.setStroke(new BasicStroke(2));
                    }
                }
            }

        }

        for (String key : SystemElements.keySet()) {
                Map<String, Object> lens = SystemElements.get(key);
                String type = (String) lens.get("type");
                if(type.contains("ThinLens")){
                    drawLens(g2, lens, x_min, 2, key);
                }
                else if(type.contains("ThickLens")){
                    drawLens(g2, lens, x_min, 6, key);
                }
            }
            drawImagingSubject(g2, LightSource, x_min, y_min, y_max, Color.RED, "Light Source");

    }

    private void drawLens(Graphics2D g2, Map<String, Object> Lens, double x_min, int thickness, String name){
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

        g2.setFont(new Font("Arial", Font.BOLD, 16));
        FontMetrics fm = g2.getFontMetrics();
        int textWidth = fm.stringWidth(name);
        g2.drawString(name, x_draw - textWidth/2, (int)Math.round(getHeight() * 0.95));
    }

    private void drawImagingSubject(Graphics2D g2, Map<String, Object> LS, double x_min, double y_min, double y_max, Color color, String name){
        double x = (double) LS.get("x");
        double y = (double) LS.get("y");

        int x_draw = (int)Math.round((x - x_min) * scale_x + getWidth() * 0.1);

        int y_draw1 = (int)Math.round(getHeight() / 2 - y * scale_y);
        int y_draw2 = getHeight()/2;

        g2.setColor(color);
        g2.setStroke(new BasicStroke(2));
        g2.drawLine(x_draw, y_draw1, x_draw, y_draw2);
        if(y > 0){
            g2.drawLine(x_draw, y_draw1, x_draw - (int)Math.round(Math.abs(y_draw1 - y_draw2)/10), y_draw1 + (int)Math.round(Math.abs(y_draw1 - y_draw2)/8));
            g2.drawLine(x_draw, y_draw1, x_draw + (int)Math.round(Math.abs(y_draw1 - y_draw2)/10), y_draw1 + (int)Math.round(Math.abs(y_draw1 - y_draw2)/8));
        }
        else if(y < 0){
            g2.drawLine(x_draw, y_draw1, x_draw - (int)Math.round(Math.abs(y_draw1 - y_draw2)/10), y_draw1 - (int)Math.round(Math.abs(y_draw1 - y_draw2)/8));
            g2.drawLine(x_draw, y_draw1, x_draw + (int)Math.round(Math.abs(y_draw1 - y_draw2)/10), y_draw1 - (int)Math.round(Math.abs(y_draw1 - y_draw2)/8));
        }
        g2.setFont(new Font("Arial", Font.BOLD, 16));
        FontMetrics fm = g2.getFontMetrics();
        int textWidth = fm.stringWidth(name);
        g2.drawString(name, x_draw - textWidth/2, (int)Math.round(Math.signum(y) * getHeight() * 0.03) + getHeight()/2);
    }

    public void setMode(boolean m){
        mode = m;
    }
}