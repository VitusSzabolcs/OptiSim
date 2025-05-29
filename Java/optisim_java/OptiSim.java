package optisim_java;

import javax.swing.*;
import java.awt.*;

public class OptiSim extends JFrame{

    private JPanel OptionPanel;
    private JButton Add;

    public OptiSim(OpticalSystem OpS){
        OpS.initialize();

        OptionPanel = new JPanel();
        Add = new JButton("Add");

        OptionPanel.add(Add);

        add(OptionPanel);
        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
}