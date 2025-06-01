package optisim_java;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.util.Map;
import java.util.ArrayList;

// This class defines the left panel with control buttons and a list of optical elements
public class ElementListPanel extends JPanel {
    private DefaultListModel<String> elementListModel; // Underlying data model for the list
    private JList<String> elementList;                 // GUI component displaying the optical elements
    private OpticalSimulatorGUI mainFrame;             // Reference to the main application window
    //private OpticalSystem OpSys;


    public ElementListPanel(OpticalSimulatorGUI frame, OpticalSystem OpS) {
        this.mainFrame = frame;
        //this.OpSys = OpS;
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

        // Add default light source element
        elementListModel.addElement("Light Source");

        elementList = new JList<>(elementListModel);
        JScrollPane listScrollPane = new JScrollPane(elementList); // Add scroll bar

        // Add both the button panel and scrollable list to the main panel
        add(buttonPanel, BorderLayout.NORTH);
        add(listScrollPane, BorderLayout.CENTER);

        // Assign event handlers to buttons using lambda expressions
        loadButton.addActionListener(e -> loadFile(OpS)); // Load file action
        saveButton.addActionListener(e -> saveFile(OpS)); // Save file action
        addButton.addActionListener(e -> showAddDialog(OpS)); // Add new lens
        calculateButton.addActionListener(e -> Calculate(OpS)); // Trigger redraw

        // Double-clicking a list item opens a dialog to modify its name
        elementList.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                if (evt.getClickCount() == 2) {
                    int index = elementList.locationToIndex(evt.getPoint());
                    if (index >= 0) {
                        String selectedElement = elementListModel.get(index);
                        showModifyDialog(selectedElement, index, OpS);
                    }
                }
            }
        });
    }

    private void Calculate(OpticalSystem OpS) {
        try{
            if(elementListModel.getElementAt(elementListModel.getSize()-1).contains("Image")){
                elementListModel.remove(elementListModel.getSize()-1);        
            }
            OpS.calculate();
            elementListModel.addElement("Image");
            mainFrame.getDrawingPanel().repaint();
        }catch(OptiSimError ex){
            JOptionPane.showMessageDialog(
            this,                         
            ex.getMessage(),
            "Optical Simulator Error",
            JOptionPane.ERROR_MESSAGE
            );
        }

    }
    // Open a file chooser to simulate loading a configuration file
    private void loadFile(OpticalSystem OpS) {
        JFileChooser fileChooser = new JFileChooser();
        int result = fileChooser.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            String path = selectedFile.getAbsolutePath();
            try {
                OpS.initialize(path);
                
                Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements();
                for (String key : SystemElements.keySet()) {
                    Map<String, Object> fields = SystemElements.get(key);
                    String type = (String) fields.get("type");
                    if (type.contains("ThinLens")) {
                        elementListModel.addElement(key + "-Thin Lens");
                    } else if (type.contains("ThickLens")){
                        elementListModel.addElement(key + "-Thick Lens");
                    }
                }
                JOptionPane.showMessageDialog(
                this,
                "Loaded: " + selectedFile.getName(),
                "Optical Simulator Message", 
                JOptionPane.INFORMATION_MESSAGE);

            } catch(OptiSimError ex){
                JOptionPane.showMessageDialog(
                this,                         
                ex.getMessage(),
                "Optical Simulator Error",
                JOptionPane.ERROR_MESSAGE
                );
            }
        }
    }

    // Open a file chooser to simulate saving current configuration
    private void saveFile(OpticalSystem OpS) {
        JFileChooser fileChooser = new JFileChooser();
        int result = fileChooser.showSaveDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            String path = selectedFile.getAbsolutePath();
            try {
                OpS.save(path);
                JOptionPane.showMessageDialog(
                this,
                "Saved: " + selectedFile.getName(),
                "Optical Simulator Message", 
                JOptionPane.INFORMATION_MESSAGE);
            } catch(OptiSimError ex){
                JOptionPane.showMessageDialog(
                this,                         
                ex.getMessage(),
                "Optical Simulator Error",
                JOptionPane.ERROR_MESSAGE
                );
            }
        }
    }

    // Dialog for adding a new lens (thin or thick) with configurable parameters
    private void showAddDialog(OpticalSystem OpS) {
        JDialog dialog = new JDialog((JFrame) SwingUtilities.getWindowAncestor(this), "Add Optical Element", true);
        dialog.setLayout(new BorderLayout());
        dialog.setLocationRelativeTo(this); // Optional: centers relative to parent

        JPanel formPanel = new JPanel();
        formPanel.setLayout(new BoxLayout(formPanel, BoxLayout.Y_AXIS));

        // Dropdown to select type of lens
        String[] options = {"Thin Lens", "Thick Lens"};
        JComboBox<String> typeCombo = new JComboBox<>(options);
        typeCombo.setAlignmentX(Component.LEFT_ALIGNMENT);

        formPanel.add(new JLabel("Type:"));
        formPanel.add(typeCombo);

        // Field to enter the name of the element
        JTextField nameField = new JTextField();
        nameField.setAlignmentX(Component.LEFT_ALIGNMENT);
        
        formPanel.add(new JLabel("Name:"));
        formPanel.add(nameField);

        // Shared and specific input fields
        JTextField positionField = new JTextField();
        JTextField focalLengthField = new JTextField();
        JTextField refractiveIndexField = new JTextField();
        JTextField leftRadiusField = new JTextField();
        JTextField rightRadiusField = new JTextField();
        JTextField thicknessField = new JTextField();
        positionField.setAlignmentX(Component.LEFT_ALIGNMENT);
        focalLengthField.setAlignmentX(Component.LEFT_ALIGNMENT);
        refractiveIndexField.setAlignmentX(Component.LEFT_ALIGNMENT);
        leftRadiusField.setAlignmentX(Component.LEFT_ALIGNMENT);
        rightRadiusField.setAlignmentX(Component.LEFT_ALIGNMENT);
        thicknessField.setAlignmentX(Component.LEFT_ALIGNMENT);

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
                dialog.pack(); // Let Java calculate optimal height
                Dimension window_size = dialog.getSize();
                dialog.setSize(new Dimension(300, window_size.height)); // Set width manually, keep calculated height
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

                dialog.pack(); // Let Java calculate optimal height
                Dimension window_size = dialog.getSize();
                dialog.setSize(new Dimension(300, window_size.height)); // Set width manually, keep calculated height
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

            try{
                if(elementListModel.getElementAt(elementListModel.getSize()-1).contains("Image")){
                    elementListModel.remove(elementListModel.getSize()-1);        
                }
                String type = (String) typeCombo.getSelectedItem();
                String name = nameField.getText();
                double position = Double.parseDouble(positionField.getText()); // returns double primitive

                if (type == "Thin Lens") {
                    double focal_length = Double.parseDouble(focalLengthField.getText());
                    OpS.add_thin_lens(name, position, focal_length);
                }
                else {
                    double refractive_index = Double.parseDouble(refractiveIndexField.getText());
                    double left_radius = Double.parseDouble(leftRadiusField.getText());
                    double right_radius = Double.parseDouble(rightRadiusField.getText());
                    double thickness = Double.parseDouble(thicknessField.getText());
                    OpS.add_thick_lens(name, position, refractive_index, thickness, left_radius, right_radius);
                }

                if (!name.trim().isEmpty()) {
                    // Add a summary line to the list (placeholder format)
                    String entry = name;
                    elementListModel.addElement(entry + "-" + type);
                }
                //close and clean up the dialog window
                dialog.dispose();

            }catch(OptiSimError ex){
                JOptionPane.showMessageDialog(
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }catch(NumberFormatException ex){
                JOptionPane.showMessageDialog(
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }
        });

        // Add form and button to the dialog
        dialog.add(formPanel, BorderLayout.CENTER);
        dialog.add(addButton, BorderLayout.SOUTH);
        dialog.pack(); // Let Java calculate optimal height
        Dimension window_size = dialog.getSize();
        dialog.setSize(new Dimension(300, window_size.height)); // Set width manually, keep calculated height
        dialog.setVisible(true);
    }

    // Opens a dialog window that allows the user to modify the selected optical element.
    // The fields shown depend on the type of element (Thin Lens, Thick Lens, Light Source).
    // On confirmation, updates the element's name in the GUI list if it was changed.
    private void showModifyDialog(String element, int index, OpticalSystem OpS) {
        JDialog dialog = new JDialog((JFrame) SwingUtilities.getWindowAncestor(this), "Modify :" + element, true);
        dialog.setLayout(new BorderLayout());
        dialog.setLocationRelativeTo(this); // Center on parent

        JPanel formPanel = new JPanel();
        formPanel.setLayout(new BoxLayout(formPanel, BoxLayout.Y_AXIS));

        double position = 0;
        double focal_length = 0;
        double refractive_index = 0;
        double left_radius = 0;
        double right_radius = 0;
        double thickness = 0;
        double size = 0;

        // Get element current values to display
        if (element.contains("Light Source")) {
            Map<String, Object> LightSource = OpS.getLightSource();
            position = (Double) LightSource.get("x");
            size = (Double) LightSource.get("y");

        } else if (element.contains("Image")) {
            Map<String, Map<String, Object>> Rays = OpS.getRays(); // We use this to get the image position and size
            Map<String, Object> fields = Rays.get("ray_1");
            ArrayList list = (ArrayList) fields.get("x");
            position = (Double) list.get(list.size() - 1);
            list = (ArrayList) fields.get("y");
            size = (Double) list.get(list.size() - 1);

        } else if (element.split("-")[1].contains("Thin Lens")) {
            Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements();
            Map<String, Object> fields = SystemElements.get(element.split("-")[0]);
            position = (Double) fields.get("x");
            focal_length = (Double) fields.get("f");

        } else if (element.split("-")[1].contains("Thick Lens")) {
            Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements();
            Map<String, Object> fields = SystemElements.get(element.split("-")[0]);
            position = (Double) fields.get("x");
            refractive_index = (Double) fields.get("n");
            left_radius = (Double) fields.get("r_left");
            right_radius = (Double) fields.get("r_right");
            thickness = (Double) fields.get("d");
        }
        

        // Common field: Position
        JTextField positionField = new JTextField(Double.toString(position));
        formPanel.add(new JLabel("Position:"));
        formPanel.add(positionField);

        // Type-specific fields
        JTextField focalLengthField = new JTextField(Double.toString(focal_length));
        JTextField refractiveIndexField = new JTextField(Double.toString(refractive_index));
        JTextField leftRadiusField = new JTextField(Double.toString(left_radius));
        JTextField rightRadiusField = new JTextField(Double.toString(right_radius));
        JTextField thicknessField = new JTextField(Double.toString(thickness));
        JTextField sizeField = new JTextField(Double.toString(size));

        if (element.contains("Light Source")) {
            formPanel.add(new JLabel("Size:"));
            formPanel.add(sizeField);
        } else if (element.contains("Image")) {
            formPanel.add(new JLabel("Size:"));
            positionField.setEditable(false);
            sizeField.setEditable(false);
            formPanel.add(sizeField);
        } else if (element.split("-")[1].contains("Thin Lens")) {
            formPanel.add(new JLabel("Focal Length:"));
            formPanel.add(focalLengthField);
        } else if (element.split("-")[1].contains("Thick Lens")) {
            formPanel.add(new JLabel("Refractive Index:"));
            formPanel.add(refractiveIndexField);
            formPanel.add(new JLabel("Left Radius:"));
            formPanel.add(leftRadiusField);
            formPanel.add(new JLabel("Right Radius:"));
            formPanel.add(rightRadiusField);
            formPanel.add(new JLabel("Thickness:"));
            formPanel.add(thicknessField);
        }

        // Buttons panel
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JButton deleteButton = new JButton("Delete");
        deleteButton.setForeground(Color.RED);
        JButton modifyButton = new JButton("Modify");
        if (element.contains("Image")) {
            modifyButton.setEnabled(false);
            deleteButton.setEnabled(false);
        }

        // Delete logic
        deleteButton.addActionListener(e -> {
            // We can not delete elements from C++ so at this point this button does nothing
            try{
                if(elementListModel.getElementAt(elementListModel.getSize()-1).contains("Image")){
                    elementListModel.remove(elementListModel.getSize()-1);        
                }
                OpS.remove(element.split("-")[0]);
                elementListModel.remove(index);
                dialog.dispose();
            }catch(OptiSimError ex){
                JOptionPane.showMessageDialog(
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }
        });

        // Modify logic
        modifyButton.addActionListener(e -> {
            
            try{
                if(elementListModel.getElementAt(elementListModel.getSize()-1).contains("Image")){
                    elementListModel.remove(elementListModel.getSize()-1);        
                }
                double position_m = Double.parseDouble(positionField.getText());
                if (element.contains("Light Source")) {
                    double size_m = Double.parseDouble(sizeField.getText());
                    OpS.modify_light_source("x", position_m);
                    OpS.modify_light_source("y", size_m);
                    

                } else if (element.split("-")[1].contains("Thin Lens")) {
                    double focal_length_m = Double.parseDouble(focalLengthField.getText());
                    OpS.modify_optical_object(element.split("-")[0], "x", position_m);
                    OpS.modify_optical_object(element.split("-")[0], "f", focal_length_m);

                } else if (element.split("-")[1].contains("Thick Lens")) {
                    double refractive_index_m = Double.parseDouble(refractiveIndexField.getText());
                    double left_radius_m = Double.parseDouble(leftRadiusField.getText());
                    double right_radius_m = Double.parseDouble(rightRadiusField.getText());
                    double thickness_m = Double.parseDouble(thicknessField.getText());
                    OpS.modify_optical_object(element.split("-")[0], "x", position_m);
                    OpS.modify_optical_object(element.split("-")[0], "n", refractive_index_m);
                    OpS.modify_optical_object(element.split("-")[0], "r_left", left_radius_m); 
                    OpS.modify_optical_object(element.split("-")[0], "r_right", right_radius_m); 
                    OpS.modify_optical_object(element.split("-")[0], "d", thickness_m);
                }
                dialog.dispose();
            }catch(OptiSimError ex){
                JOptionPane.showMessageDialog(
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }catch(NumberFormatException ex){
                JOptionPane.showMessageDialog(
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }
        });

        buttonPanel.add(deleteButton);
        buttonPanel.add(modifyButton);

        dialog.add(formPanel, BorderLayout.CENTER);
        dialog.add(buttonPanel, BorderLayout.SOUTH);

        dialog.pack();
        Dimension window_size = dialog.getSize();
        dialog.setSize(new Dimension(300, window_size.height)); // Fixed width
        dialog.setVisible(true);
    }
}
