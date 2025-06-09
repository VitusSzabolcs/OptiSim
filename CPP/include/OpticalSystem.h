/**
* @file OpticalSystem.h
* @brief Defines the OpticalSystem class, which manages a collection of optical elements.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include "ThinLens.h"       // Include for ThinLens objects
#include "ThickLens.h"      // Include for ThickLens objects
#include "Image.h"          // Include for Image objects
#include "LightSource.h"    // Include for LightSource objects

#include <map>              // For storing named optical objects
#include <vector>           // For sequences of images and element order
#include <string>           // For names and file operations
#include <fstream>          // For file I/O operations (e.g., save)
#include <iostream>         // For console output (e.g., toString)

using namespace std;

/**
 * @struct ray
 * @brief Represents the path of a ray through the optical system.
 *
 * This struct stores a sequence of x and y coordinates, tracing a ray's path
 * as it interacts with various optical objects.
 */
struct ray {
    /** @brief A vector storing the x-coordinates of the ray's path. */
    vector<double> x;
    /** @brief A vector storing the y-coordinates of the ray's path. */
    vector<double> y;
};

/**
 * @class OpticalSystem
 * @brief Manages a collection of optical elements and simulates ray propagation.
 *
 * This class allows for the creation, modification, and simulation of an optical system.
 * It holds a light source, a sequence of images formed, and a mapping of named optical objects
 * (like lenses) in a specific order. It can calculate the final image and trace rays.
 */
class OpticalSystem{ 
    private:
        /**
         * @brief Pointer to the LightSource illuminating the system.
         * @warning The OpticalSystem takes ownership of this pointer; it is allocated
         * internally or upon adding a LightSource and deallocated by the destructor.
         */
        LightSource *LS;

        /**
         * @brief A sequence of Image objects, representing the image formed by each optical object in order.
         */
        vector<Image> imageSequence;

        /**
         * @brief A map associating string names with pointers to OpticalObject instances.
         * @details This map stores the optical objects (e.g., lenses) by a user-defined name.
         * The `OpticalSystem` manages the memory of these objects.
         */
    	map<string, OpticalObject*> name_lens_map;

        /**
         * @brief A vector storing the names of optical objects in the order they appear in the system.
         * @details This vector dictates the sequence in which light interacts with the optical objects.
         */
    	vector<string> order;

        /**
         * @brief A map storing ray coordinate data, keyed by the name of the optical object.
         * @details This map holds the x and y coordinates of rays as they pass through
         * different optical elements, useful for visualization.
         */
        map<string, ray> ray_coord;

        /**
         * @brief Calculates and stores the next ray coordinates after interaction with an optical object.
         */
        void NextRayCoords(OpticalObject*, Image, string);
    public:
        /**
         * @brief Constructs a new, empty OpticalSystem.
         */
		OpticalSystem();

        /**
         * @brief Constructs an OpticalSystem by loading its configuration from a json file.
         */
    	OpticalSystem(string);
        
        /**
         * @brief Adds an OpticalObject to the system.
         */
    	void add(OpticalObject&, string);

        /**
         * @brief Adds a LightSource to the system.
         * @note If a LightSource already exists, it will be replaced.
         */
    	void add(LightSource);
		
        /**
         * @brief Removes an optical object from the system by its name.
         */
		void remove(string);
        
        /**
         * @brief Modifies a property of the existing LightSource.
         */
    	void modifyLightSource(string, double);

        /**
         * @brief Modifies a property of an existing OpticalObject by its name.
         */
    	void modifyOpticalObject(string, string, double);
        
        /**
         * @brief Prints a string representation of the optical system to an output stream.
         * @param os The output stream to which the system's details will be printed (defaults to `cout`).
         */
        void toString(ostream& os = cout);

        /**
         * @brief Saves the current configuration of the optical system to a file.
         */
    	void save(string);

        /**
         * @brief Retrieves the sequence of images formed by the optical objects.
         * @return A vector of `Image` objects, ordered by their formation in the system.
         */
		vector<Image> getImageSequence();

        /**
         * @brief Calculates the final image formed by the entire optical system.
         * @return The final `Image` object produced by the last optical element.
         */
    	Image Calculate();

        /**
         * @brief Retrieves the stored ray coordinates for visualization.
         * @return A map where keys are object names and values are `ray` structs.
         */
        map<string, ray> getRays();

        /**
         * @brief Retrieves a map of all optical elements in the system.
         * @return A map associating string names with pointers to OpticalObject instances.
         */
        map<string, OpticalObject*> getSystemElements();

        /**
         * @brief Retrieves the LightSource currently set in the system.
         * @return The LightSource object.
         */
        LightSource getLightSource();
        
        /**
         * @brief Destroys the OpticalSystem object.
         */
		~OpticalSystem();
};


#endif // OPTICALSYSTEM_H