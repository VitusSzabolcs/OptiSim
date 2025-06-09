package optisim_java; // Declares the package for this class

import javax.swing.*; // Imports Swing components for GUI
import java.awt.*; // Imports AWT classes for graphics and UI
import java.awt.event.*; // Imports AWT event classes for event handling
import java.io.File; // Imports File class for file operations
import java.util.Map; // Imports Map for key-value pairs
import java.util.ArrayList; // Imports ArrayList for dynamic lists

// This class defines the left panel with control buttons and a list of optical elements
public class ElementListPanel extends JPanel { // ElementListPanel extends JPanel to create a side panel
    private DefaultListModel<String> elementListModel; // Underlying data model for the list
    private JList<String> elementList;                 // GUI component displaying the optical elements
    private OpticalSimulatorGUI mainFrame;             // Reference to the main application window
    //private OpticalSystem OpSys; // Unused, commented out

    // Constructor for ElementListPanel
    public ElementListPanel(OpticalSimulatorGUI frame, OpticalSystem OpS) {
        this.mainFrame = frame; // Stores reference to the main GUI frame
        //this.OpSys = OpS; // Not used
        setLayout(new BorderLayout()); // Use BorderLayout for layout management of this panel
        setPreferredSize(new Dimension(200, 600)); // Fixed width for the side panel

        // Create a grid layout panel for buttons (4 rows, 1 column, 5px spacing)
        JPanel buttonPanel = new JPanel(new GridLayout(4, 1, 5, 5)); // Panel for buttons
        JButton loadButton = new JButton("Load"); // Button to load configuration
        JButton saveButton = new JButton("Save"); // Button to save configuration
        JButton addButton = new JButton("Add"); // Button to add a new element
        JButton calculateButton = new JButton("Calculate"); // Button to trigger calculation and drawing

        // Add all buttons to the button panel
        buttonPanel.add(loadButton); // Adds load button
        buttonPanel.add(saveButton); // Adds save button
        buttonPanel.add(addButton); // Adds add button
        buttonPanel.add(calculateButton); // Adds calculate button

        // Initialize list model and JList for displaying optical elements
        elementListModel = new DefaultListModel<>(); // Creates a new list model

        // Add default light source element
        elementListModel.addElement("Light Source"); // Adds "Light Source" as the initial element

        elementList = new JList<>(elementListModel); // Creates a JList with the model
        JScrollPane listScrollPane = new JScrollPane(elementList); // Add scroll bar to the list

        // Add both the button panel and scrollable list to the main panel
        add(buttonPanel, BorderLayout.NORTH); // Adds button panel to the top
        add(listScrollPane, BorderLayout.CENTER); // Adds list with scroll pane to the center

        // Assign event handlers to buttons using lambda expressions
        loadButton.addActionListener(e -> loadFile(OpS)); // Action listener for load button
        saveButton.addActionListener(e -> saveFile(OpS)); // Action listener for save button
        addButton.addActionListener(e -> showAddDialog(OpS)); // Action listener for add button
        calculateButton.addActionListener(e -> Calculate(OpS)); // Action listener for calculate button

        // Double-clicking a list item opens a dialog to modify its name
        elementList.addMouseListener(new MouseAdapter() { // Adds a mouse listener for double-click events
            public void mouseClicked(MouseEvent evt) { // Overrides mouseClicked method
                if (evt.getClickCount() == 2) { // Checks for double-click
                    int index = elementList.locationToIndex(evt.getPoint()); // Gets index of clicked item
                    if (index >= 0) { // If a valid item was clicked
                        String selectedElement = elementListModel.get(index); // Gets the selected element string
                        showModifyDialog(selectedElement, index, OpS); // Opens modify dialog
                    }
                }
            }
        });
    }

    // Method to trigger the optical system calculation and update the display
    private void Calculate(OpticalSystem OpS) {
        try{
            // If "Image" is already in the list, remove it to avoid duplicates before recalculating
            if(elementListModel.getElementAt(elementListModel.getSize()-1).contains("Image")){
                elementListModel.remove(elementListModel.getSize()-1);        
            }
            OpS.calculate(); // Calls the calculate method on the OpticalSystem
            elementListModel.addElement("Image"); // Adds "Image" to the list model
            mainFrame.getDrawingPanel().setMode(true); // Sets the drawing panel to ray-tracing mode
            mainFrame.getDrawingPanel().repaint(); // Repaints the drawing panel to show rays and image
        }catch(OptiSimError ex){ // Catches custom OptiSimError exceptions
            JOptionPane.showMessageDialog( // Displays an error message dialog
            this,                         
            ex.getMessage(), // Shows the error message
            "Optical Simulator Error",
            JOptionPane.ERROR_MESSAGE
            );
        }
    }

    // Open a file chooser to simulate loading a configuration file
    private void loadFile(OpticalSystem OpS) {
        JFileChooser fileChooser = new JFileChooser(); // Creates a new file chooser
        int result = fileChooser.showOpenDialog(this); // Shows the open file dialog
        if (result == JFileChooser.APPROVE_OPTION) { // If user selects a file and clicks "Open"
            File selectedFile = fileChooser.getSelectedFile(); // Gets the selected file
            String path = selectedFile.getAbsolutePath(); // Gets the absolute path of the file
            try {
                OpS.initialize(path); // Initializes the optical system with the loaded file

                elementListModel.clear(); // Clears all existing elements from the list model
                elementListModel.addElement("Light Source"); // Adds "Light Source" back

                Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements(); // Gets all system elements
                // Iterates through system elements and adds them to the list model
                for (String key : SystemElements.keySet()) {
                    Map<String, Object> fields = SystemElements.get(key);
                    String type = (String) fields.get("type"); // Gets the type of the element
                    if (type.contains("ThinLens")) { // If it's a thin lens
                        elementListModel.addElement(key + "-Thin Lens"); // Add to list with "Thin Lens" label
                    } else if (type.contains("ThickLens")){ // If it's a thick lens
                        elementListModel.addElement(key + "-Thick Lens"); // Add to list with "Thick Lens" label
                    }
                }

                JOptionPane.showMessageDialog( // Displays a success message
                this,
                "Loaded: " + selectedFile.getName(),
                "Optical Simulator Message", 
                JOptionPane.INFORMATION_MESSAGE);
                mainFrame.getDrawingPanel().setMode(false); // Sets drawing mode to element-only
                mainFrame.getDrawingPanel().repaint(); // Repaints the drawing panel
            } catch(OptiSimError ex){ // Catches custom OptiSimError exceptions
                JOptionPane.showMessageDialog( // Displays an error message
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
        JFileChooser fileChooser = new JFileChooser(); // Creates a new file chooser
        int result = fileChooser.showSaveDialog(this); // Shows the save file dialog
        if (result == JFileChooser.APPROVE_OPTION) { // If user selects a file and clicks "Save"
            File selectedFile = fileChooser.getSelectedFile(); // Gets the selected file
            String path = selectedFile.getAbsolutePath(); // Gets the absolute path
            try {
                OpS.save(path); // Saves the optical system configuration to the file
                JOptionPane.showMessageDialog( // Displays a success message
                this,
                "Saved: " + selectedFile.getName(),
                "Optical Simulator Message", 
                JOptionPane.INFORMATION_MESSAGE);
            } catch(OptiSimError ex){ // Catches custom OptiSimError exceptions
                JOptionPane.showMessageDialog( // Displays an error message
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
        JDialog dialog = new JDialog((JFrame) SwingUtilities.getWindowAncestor(this), "Add Optical Element", true); // Creates a modal dialog
        dialog.setLayout(new BorderLayout()); // Sets layout for the dialog
        dialog.setLocationRelativeTo(this); // Centers the dialog relative to its parent

        JPanel formPanel = new JPanel(); // Panel to hold form fields
        formPanel.setLayout(new BoxLayout(formPanel, BoxLayout.Y_AXIS)); // Arranges components vertically

        // Dropdown to select type of lens
        String[] options = {"Thin Lens", "Thick Lens"}; // Options for lens type
        JComboBox<String> typeCombo = new JComboBox<>(options); // Combo box for type selection
        typeCombo.setAlignmentX(Component.LEFT_ALIGNMENT); // Aligns the combo box to the left

        formPanel.add(new JLabel("Type:")); // Label for type
        formPanel.add(typeCombo); // Adds type combo box

        // Field to enter the name of the element
        JTextField nameField = new JTextField(); // Text field for element name
        nameField.setAlignmentX(Component.LEFT_ALIGNMENT); // Aligns name field to the left
        
        formPanel.add(new JLabel("Name:")); // Label for name
        formPanel.add(nameField); // Adds name field

        // Shared and specific input fields
        JTextField positionField = new JTextField(); // Text field for position
        JTextField focalLengthField = new JTextField(); // Text field for focal length
        JTextField refractiveIndexField = new JTextField(); // Text field for refractive index
        JTextField leftRadiusField = new JTextField(); // Text field for left radius
        JTextField rightRadiusField = new JTextField(); // Text field for right radius
        JTextField thicknessField = new JTextField(); // Text field for thickness
        // Align all text fields to the left
        positionField.setAlignmentX(Component.LEFT_ALIGNMENT);
        focalLengthField.setAlignmentX(Component.LEFT_ALIGNMENT);
        refractiveIndexField.setAlignmentX(Component.LEFT_ALIGNMENT);
        leftRadiusField.setAlignmentX(Component.LEFT_ALIGNMENT);
        rightRadiusField.setAlignmentX(Component.LEFT_ALIGNMENT);
        thicknessField.setAlignmentX(Component.LEFT_ALIGNMENT);

        // Dynamic container for type-specific fields
        JPanel dynamicFieldsPanel = new JPanel(); // Panel to dynamically add fields
        dynamicFieldsPanel.setLayout(new BoxLayout(dynamicFieldsPanel, BoxLayout.Y_AXIS)); // Arranges dynamically added components vertically

        // Define a Runnable that updates the input fields shown in the dialog
        // based on the selected lens type (Thin or Thick).
        // This enables dynamic switching between relevant UI components.
        Runnable updateFields = () -> { // Runnable to update fields based on type selection
            // First, remove all previously added components from the dynamic section of the form.
            dynamicFieldsPanel.removeAll(); // Clears existing dynamic fields

            // Always add the position field, since it's common for both thin and thick lenses
            dynamicFieldsPanel.add(new JLabel("Position:")); // Label for position
            dynamicFieldsPanel.add(positionField);           // Text field for position input

            // If the selected type is "Thin Lens", show fields relevant to a thin lens
            if (typeCombo.getSelectedItem().equals("Thin Lens")) {
                // Add label and input field for focal length (specific to thin lens)
                dynamicFieldsPanel.add(new JLabel("Focal Length:"));
                dynamicFieldsPanel.add(focalLengthField);
                dialog.pack(); // Let Java calculate optimal height
                Dimension window_size = dialog.getSize(); // Gets current dialog size
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
                Dimension window_size = dialog.getSize(); // Gets current dialog size
                dialog.setSize(new Dimension(300, window_size.height)); // Set width manually, keep calculated height
            }
            // Refresh the panel to reflect the changes in the UI
            // `revalidate()` tells the layout manager to redo layout calculations
            dynamicFieldsPanel.revalidate(); // Re-lays out the components

            // `repaint()` triggers a redraw of the panel on screen to display new components
            dynamicFieldsPanel.repaint(); // Repaints the panel
        };

        // Update form when user changes selection
        typeCombo.addActionListener(e -> updateFields.run()); // Adds action listener to type combo box
        updateFields.run(); // Calls updateFields initially to set up the dialog

        // Add dynamic fields to the form
        formPanel.add(dynamicFieldsPanel); // Adds the panel containing dynamic fields to the main form panel

        // Button to finalize and add the new element to the list
        JButton addButton = new JButton("Add"); // Button to add the element
        addButton.addActionListener(e -> { // Action listener for the add button

            try{
                // If "Image" is present, remove it as adding a new element invalidates previous calculation
                if(elementListModel.getElementAt(elementListModel.getSize()-1).contains("Image")){
                    elementListModel.remove(elementListModel.getSize()-1);        
                }
                String type = (String) typeCombo.getSelectedItem(); // Gets selected lens type
                String name = nameField.getText(); // Gets the name entered by the user
                double position = Double.parseDouble(positionField.getText()); // Parses position as a double

                // Based on type, add either a thin or thick lens to the optical system
                if (type == "Thin Lens") {
                    double focal_length = Double.parseDouble(focalLengthField.getText()); // Parses focal length
                    OpS.add_thin_lens(name, position, focal_length); // Adds thin lens
                }
                else {
                    double refractive_index = Double.parseDouble(refractiveIndexField.getText()); // Parses refractive index
                    double left_radius = Double.parseDouble(leftRadiusField.getText()); // Parses left radius
                    double right_radius = Double.parseDouble(rightRadiusField.getText()); // Parses right radius
                    double thickness = Double.parseDouble(thicknessField.getText()); // Parses thickness
                    OpS.add_thick_lens(name, position, refractive_index, thickness, left_radius, right_radius); // Adds thick lens
                }

                if (!name.trim().isEmpty()) { // If the name is not empty
                    // Add a summary line to the list (placeholder format)
                    String entry = name;
                    elementListModel.addElement(entry + "-" + type); // Adds the new element to the list model
                }
                //close and clean up the dialog window
                dialog.dispose(); // Closes the dialog

                mainFrame.getDrawingPanel().setMode(false); // Sets drawing mode back to elements only
                mainFrame.getDrawingPanel().repaint(); // Repaints the drawing panel
            }catch(OptiSimError ex){ // Catches custom OptiSimError
                JOptionPane.showMessageDialog( // Shows error message
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }catch(NumberFormatException ex){ // Catches NumberFormatException if parsing fails
                JOptionPane.showMessageDialog( // Shows error message for invalid number input
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }
        });

        // Add form and button to the dialog
        dialog.add(formPanel, BorderLayout.CENTER); // Adds form panel to the center
        dialog.add(addButton, BorderLayout.SOUTH); // Adds add button to the south
        dialog.pack(); // Lets Java determine preferred size
        Dimension window_size = dialog.getSize(); // Gets current dialog size
        dialog.setSize(new Dimension(300, window_size.height)); // Sets fixed width, keeps calculated height
        dialog.setVisible(true); // Makes the dialog visible
    }

    // Opens a dialog window that allows the user to modify the selected optical element.
    // The fields shown depend on the type of element (Thin Lens, Thick Lens, Light Source).
    // On confirmation, updates the element's name in the GUI list if it was changed.
    private void showModifyDialog(String element, int index, OpticalSystem OpS) {
        JDialog dialog = new JDialog((JFrame) SwingUtilities.getWindowAncestor(this), "Modify :" + element, true); // Creates modal dialog for modification
        dialog.setLayout(new BorderLayout()); // Sets layout for the dialog
        dialog.setLocationRelativeTo(this); // Centers dialog on parent

        JPanel formPanel = new JPanel(); // Panel to hold form fields
        formPanel.setLayout(new BoxLayout(formPanel, BoxLayout.Y_AXIS)); // Arranges components vertically

        double position = 0; // Variable for element position
        double focal_length = 0; // Variable for focal length
        double refractive_index = 0; // Variable for refractive index
        double left_radius = 0; // Variable for left radius
        double right_radius = 0; // Variable for right radius
        double thickness = 0; // Variable for thickness
        double size = 0; // Variable for size (light source or image)
        String image_type = "Real"; // Variable for image type (real/virtual)

        // Get element current values to display based on its type
        if (element.contains("Light Source")) {
            Map<String, Object> LightSource = OpS.getLightSource(); // Gets light source data
            position = (Double) LightSource.get("x"); // Gets light source x-position
            size = (Double) LightSource.get("y"); // Gets light source y-size
        } else if (element.contains("Image")) {
            Map<String, Map<String, Object>> Rays = OpS.getRays(); // Gets ray data to determine image properties
            Map<String, Object> fields = Rays.get("ray_1"); // Gets properties of the first ray
            ArrayList list = (ArrayList) fields.get("x"); // Gets x-coordinates of the ray
            position = (Double) list.get(list.size() - 1); // Gets image x-position (last x of ray)
            // Determines if image is virtual based on ray direction
            if((double)list.get(list.size()-1) < (double)list.get(list.size()-2)){
                image_type = "Virtual";
            }
            
            list = (ArrayList) fields.get("y"); // Gets y-coordinates of the ray
            size = (Double) list.get(list.size() - 1); // Gets image size (last y of ray)
            if(Double.isInfinite(size)) image_type = "-"; // If size is infinite, image type is undefined
            
        } else if (element.split("-")[1].contains("Thin Lens")) {
            Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements(); // Gets system elements
            Map<String, Object> fields = SystemElements.get(element.split("-")[0]); // Gets data for the specific thin lens
            position = (Double) fields.get("x"); // Gets thin lens x-position
            focal_length = (Double) fields.get("f"); // Gets thin lens focal length
        } else if (element.split("-")[1].contains("Thick Lens")) {
            Map<String, Map<String, Object>> SystemElements = OpS.getSystemElements(); // Gets system elements
            Map<String, Object> fields = SystemElements.get(element.split("-")[0]); // Gets data for the specific thick lens
            position = (Double) fields.get("x"); // Gets thick lens x-position
            refractive_index = (Double) fields.get("n"); // Gets refractive index
            left_radius = (Double) fields.get("r_left"); // Gets left radius
            right_radius = (Double) fields.get("r_right"); // Gets right radius
            thickness = (Double) fields.get("d"); // Gets thickness
        }
        
        // Common field: Position
        JTextField positionField = new JTextField(Double.toString(position)); // Text field for position, initialized with current value
        formPanel.add(new JLabel("Position:")); // Label for position
        formPanel.add(positionField); // Adds position field

        // Type-specific fields, initialized with current values
        JTextField focalLengthField = new JTextField(Double.toString(focal_length));
        JTextField refractiveIndexField = new JTextField(Double.toString(refractive_index));
        JTextField leftRadiusField = new JTextField(Double.toString(left_radius));
        JTextField rightRadiusField = new JTextField(Double.toString(right_radius));
        JTextField thicknessField = new JTextField(Double.toString(thickness));
        JTextField sizeField = new JTextField(Double.toString(size));
        JTextField imageType = new JTextField(image_type);

        // Add fields based on element type
        if (element.contains("Light Source")) {
            formPanel.add(new JLabel("Size:")); // Label for size
            formPanel.add(sizeField); // Adds size field
        } else if (element.contains("Image")) {
            formPanel.add(new JLabel("Size:")); // Label for size
            positionField.setEditable(false); // Position and size fields are not editable for image
            sizeField.setEditable(false);
            formPanel.add(sizeField); // Adds size field
            formPanel.add(new JLabel("Image Type:")); // Label for image type
            imageType.setEditable(false); // Image type field is not editable
            formPanel.add(imageType); // Adds image type field
        } else if (element.split("-")[1].contains("Thin Lens")) {
            formPanel.add(new JLabel("Focal Length:")); // Label for focal length
            formPanel.add(focalLengthField); // Adds focal length field
        } else if (element.split("-")[1].contains("Thick Lens")) {
            formPanel.add(new JLabel("Refractive Index:")); // Label for refractive index
            formPanel.add(refractiveIndexField); // Adds refractive index field
            formPanel.add(new JLabel("Left Radius:")); // Label for left radius
            formPanel.add(leftRadiusField); // Adds left radius field
            formPanel.add(new JLabel("Right Radius:")); // Label for right radius
            formPanel.add(rightRadiusField); // Adds right radius field
            formPanel.add(new JLabel("Thickness:")); // Label for thickness
            formPanel.add(thicknessField); // Adds thickness field
        }

        // Buttons panel
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.LEFT)); // Panel for buttons, left-aligned
        JButton deleteButton = new JButton("Delete"); // Delete button
        deleteButton.setForeground(Color.RED); // Sets delete button color to red
        JButton modifyButton = new JButton("Modify"); // Modify button
        // Disable modify and delete buttons for "Image"
        if (element.contains("Image")) {
            modifyButton.setEnabled(false);
            deleteButton.setEnabled(false);
        }

        // Disable delete button for "Light Source"
        if (element.contains("Light Source")) {
            deleteButton.setEnabled(false);
        }

        // Delete logic
        deleteButton.addActionListener(e -> { // Action listener for delete button
            // We can not delete elements from C++ so at this point this button does nothing
            try{
                // If "Image" is present, remove it as deleting an element invalidates previous calculation
                if(elementListModel.getElementAt(elementListModel.getSize()-1).contains("Image")){
                    elementListModel.remove(elementListModel.getSize()-1);        
                }
                OpS.remove(element.split("-")[0]); // Calls remove on the optical system
                elementListModel.remove(index); // Removes the element from the list model
                dialog.dispose(); // Closes the dialog
                mainFrame.getDrawingPanel().setMode(false); // Sets drawing mode to elements only
                mainFrame.getDrawingPanel().repaint(); // Repaints the drawing panel
            }catch(OptiSimError ex){ // Catches custom OptiSimError
                JOptionPane.showMessageDialog( // Shows error message
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }
        });

        // Modify logic
        modifyButton.addActionListener(e -> { // Action listener for modify button
            
            try{
                // If "Image" is present, remove it as modifying an element invalidates previous calculation
                if(elementListModel.getElementAt(elementListModel.getSize()-1).contains("Image")){
                    elementListModel.remove(elementListModel.getSize()-1);        
                }
                double position_m = Double.parseDouble(positionField.getText()); // Parses modified position
                if (element.contains("Light Source")) {
                    double size_m = Double.parseDouble(sizeField.getText()); // Parses modified size
                    OpS.modify_light_source("x", position_m); // Modifies light source x-position
                    OpS.modify_light_source("y", size_m); // Modifies light source y-size
                } else if (element.split("-")[1].contains("Thin Lens")) {
                    double focal_length_m = Double.parseDouble(focalLengthField.getText()); // Parses modified focal length
                    OpS.modify_optical_object(element.split("-")[0], "x", position_m); // Modifies thin lens x-position
                    OpS.modify_optical_object(element.split("-")[0], "f", focal_length_m); // Modifies thin lens focal length
                } else if (element.split("-")[1].contains("Thick Lens")) {
                    double refractive_index_m = Double.parseDouble(refractiveIndexField.getText()); // Parses modified refractive index
                    double left_radius_m = Double.parseDouble(leftRadiusField.getText()); // Parses modified left radius
                    double right_radius_m = Double.parseDouble(rightRadiusField.getText()); // Parses modified right radius
                    double thickness_m = Double.parseDouble(thicknessField.getText()); // Parses modified thickness
                    OpS.modify_optical_object(element.split("-")[0], "x", position_m); // Modifies thick lens x-position
                    OpS.modify_optical_object(element.split("-")[0], "n", refractive_index_m); // Modifies refractive index
                    OpS.modify_optical_object(element.split("-")[0], "r_left", left_radius_m); 
                    OpS.modify_optical_object(element.split("-")[0], "r_right", right_radius_m); 
                    OpS.modify_optical_object(element.split("-")[0], "d", thickness_m);
                }
                dialog.dispose(); // Closes the dialog
                mainFrame.getDrawingPanel().setMode(false); // Sets drawing mode to elements only
                mainFrame.getDrawingPanel().repaint(); // Repaints the drawing panel
            }catch(OptiSimError ex){ // Catches custom OptiSimError
                JOptionPane.showMessageDialog( // Shows error message
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }catch(NumberFormatException ex){ // Catches NumberFormatException
                JOptionPane.showMessageDialog( // Shows error message for invalid number input
                    this,                         
                    ex.getMessage(),
                    "Optical Simulator Error",
                    JOptionPane.ERROR_MESSAGE
                );
            }
        });

        buttonPanel.add(deleteButton); // Adds delete button to the button panel
        buttonPanel.add(modifyButton); // Adds modify button to the button panel

        dialog.add(formPanel, BorderLayout.CENTER); // Adds form panel to the center of the dialog
        dialog.add(buttonPanel, BorderLayout.SOUTH); // Adds button panel to the south of the dialog

        dialog.pack(); // Packs the dialog to its preferred size
        Dimension window_size = dialog.getSize(); // Gets current dialog size
        dialog.setSize(new Dimension(300, window_size.height)); // Fixed width, keeps calculated height
        dialog.setVisible(true); // Makes the dialog visible
    }
}