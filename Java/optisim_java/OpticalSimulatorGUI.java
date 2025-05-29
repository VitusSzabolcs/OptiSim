package optisim_java;

import javax.swing.*;
import java.awt.*;

public class OpticalSimulatorGUI extends JFrame {
    private ElementListPanel elementListPanel;
    private DrawingPanel drawingPanel;

    public OpticalSimulatorGUI(OpticalSystem OpS) {
        setTitle("Optical Simulator");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1000, 600);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        OpS.add_thin_lens("Lens1", 10, 10);
        OpS.add_thick_lens("Lens2", 10, 10, 10, 10, 10);
        OpS.modify_light_source("x", 10);
        OpS.modify_optical_object("Lens1", "x", 10);
        OpS.calculate();
        //OpS.initialize("/home/vszabolcs/OOP/GeomSim/Python/json_files/input.json");
        //OpS.save("system.json");

        // Left panel with controls and list
        elementListPanel = new ElementListPanel(this, OpS);
        drawingPanel = new DrawingPanel(OpS);

        add(elementListPanel, BorderLayout.WEST);
        add(drawingPanel, BorderLayout.CENTER);

        setVisible(true);
    }

    public DrawingPanel getDrawingPanel() {
        return drawingPanel;
    }
}