import jpype
import jpype.imports
import jpype.types
from jpype import JProxy
import optisim as op

# Defines the OpticalSystem class which acts as a Python wrapper for the OptiSim C++ library and implements a Java interface.
class OpticalSystem(object):
    # Initializes an OpticalSystem object.
    # A default LightSource is added upon instantiation.
    system = op.OpticalSystem()
    def __init__(self):
        try:
            # Create a LightSource with an x-coordinate of 0 and y-coordinate of 8.
            ls = op.LightSource(0, 8)
            # Add the light source to the optical system.
            self.system.add(ls)
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))

    # Initializes the optical system from a saved file.
    def initialize(self, filename):
        try:
            # Load the optical system from the specified file.
            self.system = op.OpticalSystem(str(filename))
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))

    # Adds a thin lens to the optical system.
    def add_thin_lens(self, name, x, f):
        try:
            # Create a ThinLens object with given x-coordinate and focal length.
            lens = op.ThinLens(x, f)
            # Add the thin lens to the system with a specified name.
            self.system.add(lens, str(name))
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))

    # Adds a thick lens to the optical system.
    def add_thick_lens(self, name, x, n, d, r_left, r_right):
        try:
            # Create a ThickLens object with given parameters.
            lens = op.ThickLens(x, n, d, r_left, r_right)
            # Add the thick lens to the system with a specified name.
            self.system.add(lens, str(name))
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))

    # Modifies a parameter of an existing optical object in the system.
    def modify_optical_object(self, name, param, val):
        try:
            # Modify the specified parameter of the optical object by its name.
            self.system.modifyOpticalObject(str(name), str(param), val)
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))

    # Modifies a parameter of the light source in the system.
    def modify_light_source(self, param, val):
        try:
            # Modify the specified parameter of the light source.
            self.system.modifyLightSource(str(param), val)
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))

    # Calculates the image formed by the optical system.
    def calculate(self):
        try:
            # Perform the calculation to get the image.
            img = self.system.Calculate()
            # Create a HashMap to store image properties.
            img_map = HashMap()
            # Put the x, y, and real components of the image into the map.
            img_map.put("x", img.getX())
            img_map.put("y", img.getY())
            img_map.put("real", img.getReal())
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))
        # Return the map containing image properties.
        return img_map

    # Saves the current optical system configuration to a file.
    def save(self, filename):
        try:
            # Save the system to the specified file.
            self.system.save(str(filename))
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))

    # Retrieves all optical elements in the system.
    def getSystemElements(self):
        try:
            # Get a map of optical elements by their names.
            name_lens_map = self.system.getSystemElements()
            # Create an outer HashMap to store details of each element.
            outer_map = HashMap()
            # Iterate through each element in the retrieved map.
            for name, oo in name_lens_map.items():
                # Create an inner HashMap for current element's properties.
                inner_map = HashMap()
                # Check if the element is a ThinLens.
                if isinstance(oo, op.ThinLens):
                    inner_map.put("type", "ThinLens")
                    inner_map.put("x", oo.getX())
                    inner_map.put("f", oo.getF())
                # Check if the element is a ThickLens.
                elif isinstance(oo, op.ThickLens):
                    inner_map.put("type", "ThickLens")
                    inner_map.put("x", oo.getX())
                    inner_map.put("n", oo.getN())
                    inner_map.put("d", oo.getD())
                    inner_map.put("r_left", oo.getR_left())
                    inner_map.put("r_right", oo.getR_right())
                    inner_map.put("f", oo.getF())
                # Add the inner map (element details) to the outer map with its name as key.
                outer_map.put(name, inner_map)
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))
        # Return the map containing all system elements.
        return outer_map

    # Retrieves the properties of the light source.
    def getLightSource(self):
        try:
            # Get the LightSource object.
            ls = self.system.getLightSource()
            # Create a HashMap to store light source properties.
            ls_map = HashMap()
            # Put the x and y coordinates of the light source into the map.
            ls_map.put("x", ls.getX())
            ls_map.put("y", ls.getY())
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))
        # Return the map containing light source properties.
        return ls_map

    # Retrieves the rays traced through the optical system.
    def getRays(self):
        try:
            # Get the rays from the system.
            rays = self.system.getRays()
            # Create an outer HashMap to store ray data.
            outer_map = HashMap()
            # Iterate through each ray.
            for key, ray in rays.items():
                # Create an inner HashMap for current ray's coordinates.
                inner_map = HashMap()
                # Create ArrayLists to store x and y coordinates of the ray.
                x_list = ArrayList()
                y_list = ArrayList()

                # Populate the lists with ray's x and y coordinates.
                for i in range(len(ray.x)):
                    x_list.add(ray.x[i])
                    y_list.add(ray.y[i])
                inner_map.put("x", x_list)
                inner_map.put("y", y_list)
                # Add the inner map (ray coordinates) to the outer map with its key.
                outer_map.put(key, inner_map)
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))
        # Return the map containing all ray data.
        return outer_map

    # Removes an optical object from the system by its name.
    def remove(self, name):
        try:
            # Remove the optical object with the specified name.
            self.system.remove(str(name))
        except op.OptiSimError as e:
            # If an OptiSimError occurs, re-raise it as an optisim_java.OptiSimError.
            raise optisim_java.OptiSimError(str(e))

# Starts the JVM with the necessary classpath for the OptiSim Java library.
jpype.startJVM(classpath = ['../Java/optisim_java.jar'])

# Import Java utility classes HashMap and ArrayList.
from java.util import HashMap, ArrayList

# Import the optisim_java package.
import optisim_java

# Create an instance of the Python OpticalSystem wrapper class.
OpS = OpticalSystem()

# Create a JProxy to expose the Python OpticalSystem object to Java,
# making it accessible from the Java GUI.
proxy = JProxy(optisim_java.OpticalSystem, inst = OpS)

# Instantiate and display the Java OpticalSimulatorGUI, passing the JProxy object
# so the GUI can interact with the Python-wrapped optical system.
optisim_java.OpticalSimulatorGUI(proxy)

# Shuts down the JVM when the application is closed.
jpype.shutdownJVM()