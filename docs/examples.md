# Examples

---

Dive into practical applications of the **OptiSim** with these illustrative examples. Whether you prefer C++, Python, or command line tools, we've got you covered. These examples demonstrate basic system creation, manipulation, and analysis.

## C++ Example

Our C++ library offers powerful capabilities for building and simulating optical systems directly within your applications. This example showcases how to create a simple system, add components, perform calculations, and even load/save systems from JSON files.

```cpp
#include <iostream>
#include "OptiSim.h"

using namespace std;

int main(){
    //create new empty system
    OpticalSystem my_system;

    //create new LightSource at x = 0 and height = 8
    LightSource LS(0, 8);

    //add light source to system
    my_system.add(LS);

    //create new thin lens at x = 20 with f = 10
    ThinLens L1(20, 10);

    //add Light thin lens to system
    my_system.add(L1, "Lens_1");

    //calculate image formation
    my_system.Calculate();

    //print informations about system and image formation
    my_system.toString();

    // ------------------------------------------------------------------------
    //create new system from jason
    OpticalSystem my_second_system("./json_files/presentation2.json");

    //calculate image formation
    my_second_system.Calculate();

    //print informations about system and image formation
    my_second_system.toString();

    //remove a lens
    my_second_system.remove("Lens_1");

    //recalculate image formation
    my_second_system.Calculate();

    //pritn information about system and image formation
    my_second_system.toString();

    //saved modified system
    my_second_system.save("./json_files/presentaion2_modified.json");

    return 0;
}
```
## Python Example

Leverage the OptiSim Python library for rapid prototyping, scripting, and integrating optical simulations into your data science workflows. This example mirrors the C++ functionality, demonstrating the ease of use in Python.

```python
import optisim as op

# create new empty system
my_system = op.OpticalSystem()

# create new light source at x = 0 and height = 8
LS = op.LightSource(0, 8)

# add light source to system
my_system.add(LS)

# create new thin lens at x = 20 with f = 10
L1 = op.ThinLens(20, 10)

# add light source to system
my_system.add(L1, "Lens_1")

# calculate image formation
my_system.Calculate()

# print informations about system and image formation
my_system.toString()

#-----------------------------------------------------
# create new system from json
my_second_system = op.OpticalSystem("./json_files/presentation2.json")

# calculate image formation
my_second_system.Calculate()

# print informations about system and image formation
my_second_system.toString()

# remove a lens
my_second_system.remove("Lens_1")

# recalculate the image formation
my_second_system.Calculate()

# print informations about system and image formation
my_second_system.toString()

my_second_system.save("./json_files/presentation2_modified.json")





```

## JSON Configuration Example

For quick setup or defining complex optical systems, you can use JSON files. This example shows a presentation2.json file used in the C++ and Python examples above, demonstrating how to define an object and multiple thin and thick lenses.

```json
{
  "lenses": [
    {
      "focal_length": 5.0,
      "name": "Lens_1",
      "position": 10.0,
      "type": "thin"
    },
    {
      "focal_length": -10.0,
      "name": "Lens_3",
      "position": 15.0,
      "type": "thin"
    },
    {
      "name": "Lens_4",
      "position": 40.0,
      "radius_left": 15.0,
      "radius_right": -20.0,
      "refractive_index": 1.52,
      "thickness": 4.0,
      "type": "thick"
    },
    {
      "name": "Lens_5",
      "position": 55.0,
      "radius_left": 17.0,
      "radius_right": -20.0,
      "refractive_index": 1.72,
      "thickness": 4.5,
      "type": "thick"
    },
    {
      "name": "Lens_2",
      "position": 60.0,
      "radius_left": 12.0,
      "radius_right": -21.0,
      "refractive_index": 1.52,
      "thickness": 3.5,
      "type": "thick"
    }
  ],
  "object": {
    "position": 0.0,
    "size": 1.5
  }
}
```
## Command Line Interface (CLI) Example

The OptiSim command-line tool provides a powerful way to run simulations and manage optical systems directly from your terminal. You can specify input/output files, print system details, and control the level of output detail.

To see the available options, simply run the tool with the --help flag:
```bash
$ ./OptiSim --help
-------------------------------------------------------------------------------
###    OptiSim - tool for simulating geometrical optics
-------------------------------------------------------------------------------

Description: By default, this tool reads an optical system from a file called "input.json" and writes the calculation results to a file called "output.txt".
Usage: OptiSim [OPTIONS]

Option             Long option           Meaning
-h                 --help                Show this help text and exit.
-i=<json-file>     --input=<json-file>   Specify the file from which to read the system.
-il                --imagelist           Expands the output with the image list.
-o=<file>          --output=<file>       Specify the file in which to save the output.
-p                 --print               Print the parameters of the optical system to the console.
-r                 --rays                Expands the output with the ray coordinates.
-v                 --version             Print version info.
```
Here's an example of how you might use the command-line tool to load a system from `presentation2.json`, print its parameters to the console, and save the detailed image list and ray coordinates to `my_simulation_results.txt`:
```bash
$ ./OptiSim --input=./json_files/presentation2.json --print --imagelist --rays --output=my_simulation_results.txt
```
This command will:

- Read the optical system definition from `./json_files/presentation2.json`.
- Print a summary of the system's parameters directly to your terminal.
- Calculate the image formation and include a detailed list of images and ray coordinates in the output.
- Save the complete results to `my_simulation_results.txt`.

### Example Output

When you run the command above, the `my_simulation_results.txt` file  will generate a detailed summary of the optical system, including image formation and ray coordinates. Here's what a typical output looks like:
```text
-------------------------------------------------------------------------------
#    SYSTEM SUMMARY
-------------------------------------------------------------------------------
Object Position: 0, Size: 1.5

Thin Lens: Lens_1,   Position: 10, Focal Length: 5

Thin Lens: Lens_3,   Position: 15, Focal Length: -10

Thick Lens: Lens_4, Position: 40, n: 1.52, Thickness: 4, Radius_left: 15, Radius_right: -20, Focal Length: 17.1542

Thick Lens: Lens_5, Position: 55, n: 1.72, Thickness: 4.5, Radius_left: 17, Radius_right: -20, Focal Length: 13.4474

Thick Lens: Lens_2, Position: 60, n: 1.52, Thickness: 3.5, Radius_left: 12, Radius_right: -21, Focal Length: 15.2382

Image Position: 67.0362, Size: 1.5723, Is real: 1
-------------------------------------------------------------------------------
#    Images
-------------------------------------------------------------------------------
X coordinate   Y coordinate   Is real?

   20.000000       -1.500000         1
   25.000000       -3.000000         1
  -41.141484      -17.266449         0
   71.420402        2.841596         1
   67.036177        1.572302         1

-------------------------------------------------------------------------------
#    Rays
-------------------------------------------------------------------------------
             Ray 1                       Ray 2

X coordinate   Y coordinate   X coordinate   Y coordinate 

    0.000000       1.500000       0.000000       1.500000
   10.000000       1.500000      10.000000       0.000000
   15.000000       0.000000      15.000000      -0.750000
   40.000000      -7.500000      40.000000      -6.375000
   55.000000      -5.694552      55.000000      -4.361582
   60.000000      -3.095302      60.000000      -2.168220
   67.036177       1.572302      67.036177       1.572302

-------------------------------------------------------------------------------
```
---
These examples provide a starting point. Feel free to modify them and experiment with different optical components and configurations.