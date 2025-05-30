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
        JDialog dialog = new JDialog((JFrame) SwingUtilities.getWindowAncestor(this), "Add Optical Element", true);
        dialog.setLayout(new BorderLayout());
        dialog.setSize(300, 450);
        dialog.setLocationRelativeTo(this);

        JPanel formPanel = new JPanel();
        formPanel.setLayout(new BoxLayout(formPanel, BoxLayout.Y_AXIS));

        String[] options = {"Thin Lens", "Thick Lens"};
        JComboBox<String> typeCombo = new JComboBox<>(options);
        formPanel.add(new JLabel("Type:"));
        formPanel.add(typeCombo);

        JTextField nameField = new JTextField();
        formPanel.add(new JLabel("Name:"));
        formPanel.add(nameField);

        JTextField positionField = new JTextField();
        JTextField focalLengthField = new JTextField();
        JTextField refractiveIndexField = new JTextField();
        JTextField leftRadiusField = new JTextField();
        JTextField rightRadiusField = new JTextField();
        JTextField thicknessField = new JTextField();

        JPanel dynamicFieldsPanel = new JPanel();
        dynamicFieldsPanel.setLayout(new BoxLayout(dynamicFieldsPanel, BoxLayout.Y_AXIS));

        Runnable updateFields = () -> {
            dynamicFieldsPanel.removeAll();
            dynamicFieldsPanel.add(new JLabel("Position:"));
            dynamicFieldsPanel.add(positionField);
            if (typeCombo.getSelectedItem().equals("Thin Lens")) {
                dynamicFieldsPanel.add(new JLabel("Focal Length:"));
                dynamicFieldsPanel.add(focalLengthField);
            } else {
                dynamicFieldsPanel.add(new JLabel("Refractive Index:"));
                dynamicFieldsPanel.add(refractiveIndexField);
                dynamicFieldsPanel.add(new JLabel("Left Radius:"));
                dynamicFieldsPanel.add(leftRadiusField);
                dynamicFieldsPanel.add(new JLabel("Right Radius:"));
                dynamicFieldsPanel.add(rightRadiusField);
                dynamicFieldsPanel.add(new JLabel("Thickness:"));
                dynamicFieldsPanel.add(thicknessField);
            }
            dynamicFieldsPanel.revalidate();
            dynamicFieldsPanel.repaint();
        };

        typeCombo.addActionListener(e -> updateFields.run());
        updateFields.run();

        formPanel.add(dynamicFieldsPanel);

        JButton addButton = new JButton("Add");
        addButton.addActionListener(e -> {
            String type = (String) typeCombo.getSelectedItem();
            String name = nameField.getText();
            String position = positionField.getText();
            if (!name.trim().isEmpty()) {
                String entry = name + " (" + type + ", pos: " + position + ")";
                elementListModel.addElement(entry);
            }
            dialog.dispose();
        });

        dialog.add(formPanel, BorderLayout.CENTER);
        dialog.add(addButton, BorderLayout.SOUTH);
        dialog.setVisible(true);
    }

    private void showModifyDialog(String element, int index) {
        String newName = JOptionPane.showInputDialog(this, "Modify element name:", element);
        if (newName != null && !newName.trim().isEmpty()) {
            elementListModel.set(index, newName);
        }
    }
}
