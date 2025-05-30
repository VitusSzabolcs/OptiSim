package optisim_java;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;

// This class defines the left panel with control buttons and a list of optical elements
public class ElementListPanel extends JPanel {
    private DefaultListModel<String> elementListModel; // Underlying data model for the list
    private JList<String> elementList;                 // GUI component displaying the optical elements
    private OpticalSimulatorGUI mainFrame;             // Reference to the main application window


    public ElementListPanel(OpticalSimulatorGUI frame, OpticalSystem OpS) {
        this.mainFrame = frame;
        setLayout(new BorderLayout()); // Use BorderLayout for layout management
        setPreferredSize(new Dimension(200, 600)); // Fixed width for the side panel
        
        // Create a grid layout panel for buttons (4 rows, 1 column, 5px spacing)
        JPanel buttonPanel = new JPanel(new GridLayout(4, 1, 5, 5));
        JButton loadButton = new JButton("Load");
        JButton saveButton = new JButton("Save");
        JButton addButton = new JButton("Add");
        JButton calculateButton = new JButton("Calculate");

        // Add all buttons to the button panel
        buttonPanel.add(loadButton);
        buttonPanel.add(saveButton);
        buttonPanel.add(addButton);
        buttonPanel.add(calculateButton);

        // Initialize list model and JList for displaying optical elements
        elementListModel = new DefaultListModel<>();
        elementList = new JList<>(elementListModel);
        JScrollPane listScrollPane = new JScrollPane(elementList); // Add scroll bar

        // Add both the button panel and scrollable list to the main panel
        add(buttonPanel, BorderLayout.NORTH);
        add(listScrollPane, BorderLayout.CENTER);

        // Assign event handlers to buttons using lambda expressions
        loadButton.addActionListener(e -> loadFile()); // Load file action
        saveButton.addActionListener(e -> saveFile()); // Save file action
        addButton.addActionListener(e -> showAddDialog()); // Add new lens
        calculateButton.addActionListener(e -> mainFrame.getDrawingPanel().repaint()); // Trigger redraw

        // Double-clicking a list item opens a dialog to modify its name
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

    // Open a file chooser to simulate loading a configuration file
    private void loadFile() {
        JFileChooser fileChooser = new JFileChooser();
        int result = fileChooser.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            //  .
            //  .
            //  .
            JOptionPane.showMessageDialog(this, "Loaded: " + selectedFile.getName());
        }
    }

    // Open a file chooser to simulate saving current configuration
    private void saveFile() {
        JFileChooser fileChooser = new JFileChooser();
        int result = fileChooser.showSaveDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            //  .
            //  .
            //  .
            JOptionPane.showMessageDialog(this, "Saved: " + selectedFile.getName());
        }
    }

    // Dialog for adding a new lens (thin or thick) with configurable parameters
    private void showAddDialog() {
        JDialog dialog = new JDialog((JFrame) SwingUtilities.getWindowAncestor(this), "Add Optical Element", true);
        dialog.setLayout(new BorderLayout());
        dialog.setSize(300, 450);
        dialog.setLocationRelativeTo(this);

        JPanel formPanel = new JPanel();
        formPanel.setLayout(new BoxLayout(formPanel, BoxLayout.Y_AXIS));

        // Dropdown to select type of lens
        String[] options = {"Thin Lens", "Thick Lens"};
        JComboBox<String> typeCombo = new JComboBox<>(options);
        formPanel.add(new JLabel("Type:"));
        formPanel.add(typeCombo);

        // Field to enter the name of the element
        JTextField nameField = new JTextField();
        formPanel.add(new JLabel("Name:"));
        formPanel.add(nameField);

        // Shared and specific input fields
        JTextField positionField = new JTextField();
        JTextField focalLengthField = new JTextField();
        JTextField refractiveIndexField = new JTextField();
        JTextField leftRadiusField = new JTextField();
        JTextField rightRadiusField = new JTextField();
        JTextField thicknessField = new JTextField();

        // Dynamic container for type-specific fields
        JPanel dynamicFieldsPanel = new JPanel();
        dynamicFieldsPanel.setLayout(new BoxLayout(dynamicFieldsPanel, BoxLayout.Y_AXIS));

        // Define a Runnable that updates the input fields shown in the dialog
        // based on the selected lens type (Thin or Thick).
        // This enables dynamic switching between relevant UI components.
        Runnable updateFields = () -> {
            // First, remove all previously added components from the dynamic section of the form.
            dynamicFieldsPanel.removeAll();

            // Always add the position field, since it's common for both thin and thick lenses
            dynamicFieldsPanel.add(new JLabel("Position:")); // Label for position
            dynamicFieldsPanel.add(positionField);           // Text field for position input

            // If the selected type is "Thin Lens", show fields relevant to a thin lens
            if (typeCombo.getSelectedItem().equals("Thin Lens")) {
                // Add label and input field for focal length (specific to thin lens)
                dynamicFieldsPanel.add(new JLabel("Focal Length:"));
                dynamicFieldsPanel.add(focalLengthField);
            } else {
                // Otherwise, the user selected "Thick Lens"
                // Show input fields relevant to thick lenses

                // Add refractive index
                dynamicFieldsPanel.add(new JLabel("Refractive Index:"));
                dynamicFieldsPanel.add(refractiveIndexField);

                // Add left surface radius of curvature
                dynamicFieldsPanel.add(new JLabel("Left Radius:"));
                dynamicFieldsPanel.add(leftRadiusField);

                // Add right surface radius of curvature
                dynamicFieldsPanel.add(new JLabel("Right Radius:"));
                dynamicFieldsPanel.add(rightRadiusField);

                // Add thickness of the lens
                dynamicFieldsPanel.add(new JLabel("Thickness:"));
                dynamicFieldsPanel.add(thicknessField);
            }
            // Refresh the panel to reflect the changes in the UI
            // `revalidate()` tells the layout manager to redo layout calculations
            dynamicFieldsPanel.revalidate();

            // `repaint()` triggers a redraw of the panel on screen to display new components
            dynamicFieldsPanel.repaint();
        };

        // Update form when user changes selection
        typeCombo.addActionListener(e -> updateFields.run());
        updateFields.run();

        // Add dynamic fields to the form
        formPanel.add(dynamicFieldsPanel);

        // Button to finalize and add the new element to the list
        JButton addButton = new JButton("Add");
        addButton.addActionListener(e -> {
            String type = (String) typeCombo.getSelectedItem();
            String name = nameField.getText();
            String position = positionField.getText();
            //  .
            //  .
            //  .
            if (!name.trim().isEmpty()) {
                // Add a summary line to the list (placeholder format)
                String entry = name + " (" + type + ", pos: " + position + ")";
                elementListModel.addElement(entry);
            }

            //close and clean up the dialog window
            dialog.dispose();
        });

        // Add form and button to the dialog
        dialog.add(formPanel, BorderLayout.CENTER);
        dialog.add(addButton, BorderLayout.SOUTH);
        dialog.setVisible(true);
    }
    // Show a simple input dialog to rename an existing element
    private void showModifyDialog(String element, int index) {
        String newName = JOptionPane.showInputDialog(this, "Modify element name:", element);
        if (newName != null && !newName.trim().isEmpty()) {
            elementListModel.set(index, newName);
        }
    }
}
