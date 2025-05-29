package optisim_java;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;

public class ElementListPanel extends JPanel {
    private DefaultListModel<String> elementListModel;
    private JList<String> elementList;
    private OpticalSimulatorGUI mainFrame;

    public ElementListPanel(OpticalSimulatorGUI frame, OpticalSystem OpS) {
        this.mainFrame = frame;
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(200, 600));

        JPanel buttonPanel = new JPanel(new GridLayout(4, 1, 5, 5));
        JButton loadButton = new JButton("Load");
        JButton saveButton = new JButton("Save");
        JButton addButton = new JButton("Add");
        JButton calculateButton = new JButton("Calculate");

        buttonPanel.add(loadButton);
        buttonPanel.add(saveButton);
        buttonPanel.add(addButton);
        buttonPanel.add(calculateButton);

        elementListModel = new DefaultListModel<>();
        elementList = new JList<>(elementListModel);
        JScrollPane listScrollPane = new JScrollPane(elementList);

        add(buttonPanel, BorderLayout.NORTH);
        add(listScrollPane, BorderLayout.CENTER);

        // Button actions
        loadButton.addActionListener(e -> loadFile());
        saveButton.addActionListener(e -> saveFile());
        addButton.addActionListener(e -> showAddDialog());
        calculateButton.addActionListener(e -> mainFrame.getDrawingPanel().repaint());

        // List element click action
        elementList.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                if (evt.getClickCount() == 2) {
                    int index = elementList.locationToIndex(evt.getPoint());
                    if (index >= 0) {
                        String selectedElement = elementListModel.get(index);
                        showModifyDialog(selectedElement, index);
                    }
                }
            }
        });
    }

    private void loadFile() {
        JFileChooser fileChooser = new JFileChooser();
        int result = fileChooser.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            JOptionPane.showMessageDialog(this, "Loaded: " + selectedFile.getName());
        }
    }

    private void saveFile() {
        JFileChooser fileChooser = new JFileChooser();
        int result = fileChooser.showSaveDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            JOptionPane.showMessageDialog(this, "Saved: " + selectedFile.getName());
        }
    }

    private void showAddDialog() {
        String name = JOptionPane.showInputDialog(this, "Enter element name:");
        if (name != null && !name.trim().isEmpty()) {
            elementListModel.addElement(name);
        }
    }

    private void showModifyDialog(String element, int index) {
        String newName = JOptionPane.showInputDialog(this, "Modify element name:", element);
        if (newName != null && !newName.trim().isEmpty()) {
            elementListModel.set(index, newName);
        }
    }
}
