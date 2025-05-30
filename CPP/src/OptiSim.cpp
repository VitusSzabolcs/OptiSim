#include <iostream>
#include <vector>
#include <iomanip>
#include "OptiSim.h"

using namespace std;


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

struct command_path {
    string command; 
    string file;
};

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

int main(int argc, char* argv[]){
    try{
        string input_file = "./input.json";
        string output_file = "./output.txt";
        bool should_I_print = false;
        bool should_I_calc = true;
        bool should_I_print_il = false;
        bool should_I_print_rays = false;
    	if (argc < 2) {
    		throw runtime_error("\033[1mDescription\033[0m: By default, this tool reads an "
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
                if (splitted.file == "") throw runtime_error("Check help for correct usage:  OptiSim --help");
                input_file = splitted.file;

            } else if (splitted.command == "-o" || splitted.command == "--output"){
                if (splitted.file == "") throw runtime_error("Check help for correct usage:  OptiSim --help");
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
    	
    }catch(exception& e)
    {
        cout << e.what() << "\n";
    }
    return 0;
}