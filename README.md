This is a README file!

cd CPP

mkdir build

cd build 

cmake .. -G "MinGW Makefiles"

cmake --build .

in java folder:

    javac ./optisim_java/*.java
    jar cf optisim_java.jar ./optisim_java/*.class


# Optical System Simulator GUI

This application provides a user-friendly graphical interface for designing, visualizing, and simulating optical systems.

---

## Key Features:

* **Intuitive Layout:** The GUI is divided into two main sections:
    * **Left Panel:** Contains control buttons and a list of all optical elements in the current system.
    * **Right Panel:** Displays a visual representation of the optical system and the resulting image formation.
* **Default Light Source:** Every new system starts with a default **light source/object**, forming the basis of your optical setup.
* **System Management:**
    * **Load System:** Import existing optical systems from `.json` files. Upon loading, elements automatically populate the list and visualization.
    * **Save System:** Export your constructed optical systems as `.json` files for future use.
* **Element Addition:** Easily add new optical elements to your system:
    * **Thin Lenses:** Define by name, position, and focal length.
    * **Thick Lenses:** Define by name, position, refractive index, thickness, left radius, and right radius.
    * Newly added elements are immediately reflected in both the element list and the visualization.
* **System Calculation:** After constructing your system, click **Calculate** to visualize ray traces and the final image formation. The calculated image also appears in the element list.
* **Element Modification:**
    * Clicking on any optical element in the list opens a dedicated modification window.
    * Adjust parameters or delete elements (except for the light source/object).
    * The calculated image cannot be modified or deleted; its modification window only displays its parameters.
* **Dynamic Visualization:**
    * The optical system visualization is automatically scaled to fit the window, with independent scaling for horizontal and vertical axes for optimal viewing.
    * Image formation and ray traces are only displayed after calculation and disappear if any modifications are made to the system (e.g., adding or altering elements).

---

This simulator provides a comprehensive environment for experimenting with and understanding optical principles.
