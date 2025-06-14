/**
* @file OptiSim.cpp
* @brief This is the main executable for the OptiSim optical simulation tool.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*
* It handles command-line arguments, sets up the optical system, performs calculations,
* and manages output to console and files.
*/

#include <iostream>  // For standard input/output operations (cout, cerr)
#include <vector>    // For using std::vector
#include <iomanip>   // For formatting output (setw, setprecision)
#include "OptiSim.h" // Main header for the OptiSim library components

using namespace std;

/**
 * @brief Displays the help text for the OptiSim command-line tool.
 *
 * This function prints detailed information about the tool's description,
 * usage, and available command-line options with their meanings.
 */
void help(){
	cout << "-------------------------------------------------------------------------------"
         << "\n###\t\e[1mOptiSim\e[0m - tool for simulating geometrical optics\n"
         << "-------------------------------------------------------------------------------"
         << "\n\n\e[1mDescription\e[0m: By default, this tool reads an optical system from a file called \"input.json\" and writes the calculation results to a file called \"output.txt\"."
         << "\n\e[1mUsage\e[0m: OptiSim [OPTIONS]\n"<< endl;
    cout << left; // Align left for all fields

    cout << setw(18) << "Option"
         << setw(22) << "Long option"
         << "Meaning" << endl;

    cout << setw(18) << "-h"
         << setw(22) << "--help"
         << "Show this help text and exit." << endl;

    cout << setw(18) << "-i=<json-file>"
         << setw(22) << "--input=<json-file>"
         << "Specify the file from which to read the system." << endl;

    cout << setw(18) << "-il"
         << setw(22) << "--imagelist"
         << "Expands the output with the image list." << endl;

    cout << setw(18) << "-o=<file>"
         << setw(22) << "--output=<file>"
         << "Specify the file in which to save the output." << endl;

    cout << setw(18) << "-p"
         << setw(22) << "--print"
         << "Print the parameters of the optical system to the console." << endl;

    cout << setw(18) << "-r"
         << setw(22) << "--rays"
         << "Expands the output with the ray coordinates." << endl;

    cout << setw(18) << "-v"
         << setw(22) << "--version"
         << "Print version info." << endl;
}

/**
 * @brief A structure to hold a command-line option and its associated file path (if any).
 */
struct command_path {
    /** @brief The command-line option string (e.g., "-i", "--input"). */
    string command; 
    /** @brief The associated file path, if the command uses the `=<file>` syntax. */
    string file;
};

/**
 * @brief Splits a command-line argument string into a command and a file path if an '=' is present.
 *
 * @param S The input command-line argument string (e.g., "-i=input.json" or "--help").
 * @return A `command_path` struct containing the extracted command and file.
 */
command_path split(string S) {
    size_t pos = S.find('=');
    command_path return_box;
    if (pos != string::npos) {
        return_box.command = S.substr(0, pos);
        return_box.file = S.substr(pos + 1);
    } else {
        return_box.command = S;
        return_box.file = "";
    }
    return return_box;
}

/**
 * @brief The main entry point of the OptiSim application.
 *
 * This function parses command-line arguments to determine input/output files,
 * display options, and then constructs and simulates an optical system.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of C-style strings representing the command-line arguments.
 * @return 0 if the program executes successfully, non-zero otherwise (e.g., on error).
 */
int main(int argc, char* argv[]){
    try{
        string input_file = "./input.json";
        string output_file = "./output.txt";
        bool should_I_print = false;
        bool should_I_calc = true;
        bool should_I_print_il = false;
        bool should_I_print_rays = false;
    	if (argc < 2) {
    		throw OptiSimError("\033[1mDescription\033[0m: By default, this tool reads an "
                        "optical system from a file called \"input.json\" and "
                        "writes the calculation results to a file called \"output.txt\".\n"
                        "\033[1mUsage\033[0m: OptiSim [OPTIONS]\n"
                        "For more details run: OptiSim --help"
                        );
	    }

	    for (int i = 1; i < argc; ++i){
            command_path splitted = split(argv[i]);
            if (string(argv[i]) == "-h" || string(argv[i]) == "--help"){
                help();
                if (argc == 2) should_I_calc = false;

            } else if (string(argv[i]) == "-v" || string(argv[i]) == "--version"){
                const char* version_string = getOptiSimVersionString();
                cout << version_string << endl;
                if (argc == 2) should_I_calc = false;

            } else if (string(argv[i]) == "-p" || string(argv[i]) == "--print"){
                should_I_print = true;

            } else if (string(argv[i]) == "-r" || string(argv[i]) == "--rays"){
                should_I_print_rays = true;

            } else if (string(argv[i]) == "-il" || string(argv[i]) == "--imagelist"){
                should_I_print_il = true;

            } else if (splitted.command == "-i" || splitted.command == "--input"){
                if (splitted.file == "") throw OptiSimError("Check help for correct usage:  OptiSim --help");
                input_file = splitted.file;

            } else if (splitted.command == "-o" || splitted.command == "--output"){
                if (splitted.file == "") throw OptiSimError("Check help for correct usage:  OptiSim --help");
                output_file = splitted.file;
            }
	    }
        if (should_I_calc) {
            // instantiate an Optical System object using a .json file
            OpticalSystem my_system(input_file);
            
            // calculate the system's imaging and print the system into the console
            Image final_image = my_system.Calculate();

            // save the output information into a file
            ofstream outputFile(output_file);
            my_system.toString(outputFile);

            // print the optical system parameters and result on the console
            if (should_I_print) my_system.toString();

            // expands the output file with the image list
            if (should_I_print_il) {
                vector<Image> imageSequence = my_system.getImageSequence();
                vector<Image>::iterator it;
                outputFile << "#\tImages"
                << "\n-------------------------------------------------------------------------------\n";
                outputFile << left
                           << setw(15) << "X coordinate"
                           << setw(15) << "Y coordinate"
                           << "Is real?" << "\n\n";

                for (it = imageSequence.begin(); it < imageSequence.end(); ++it) {
                    outputFile << right << fixed << setprecision(6)
                               << setw(12) << (*it).getX()
                               << setw(15) << (*it).getY()
                               << setw(10) << setprecision(1) << (*it).getReal()
                               << "\n";
                }
                outputFile << "\n-------------------------------------------------------------------------------\n";
            }
            if (should_I_print_rays){
                map<string, ray> rays = my_system.getRays();
                outputFile << "#\tRays"
                << "\n-------------------------------------------------------------------------------\n";
                outputFile << right
                           << setw(16) << "Ray 1"
                           << setw(30) << "Ray 2"<< "\n\n";
                outputFile << left
                           << setw(15) << "X coordinate"
                           << setw(15) << "Y coordinate"
                           << setw(15) << "X coordinate"
                           << setw(15) << "Y coordinate"<< "\n\n";
                for (int i =0; i<rays["ray_1"].x.size(); i++){
                    outputFile << right << fixed << setprecision(6)
                               << setw(12) << rays["ray_1"].x[i]
                               << setw(15) << rays["ray_1"].y[i]
                               << setw(15) << rays["ray_2"].x[i]
                               << setw(15) << rays["ray_2"].y[i]
                               << "\n";
                }
                outputFile << "\n-------------------------------------------------------------------------------\n";
            }
        }
    	
    }catch(exception& e) // Catch any standard exception or custom OptiSimError
    {
        cout << e.what() << "\n";
    }
    return 0;  // Indicate successful execution
}