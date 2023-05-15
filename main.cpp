/*
main.cpp
*/

#include <iostream>
#include <fstream>
#include <string>

#include "osSimulator.h"

// This function reads the input file and populates the `jobs` and `devices` vectors.
void read_input_file(const char *filename) {
    // Open the input file.
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cout << "Error opening input file: " << filename << std::endl;
        return;
    }

    // for each line in the file send the line to processFileData
    std::string line;
    while (getline(input_file, line)) {
        processInstruction(line);
    }

    // Close the input file.
    input_file.close();
}

// The main function of the program.
int main(int argc, char *argv[]) {
    // Check the number of command-line arguments.
    if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
    }

    // Read the input file.
    read_input_file(argv[1]);
        
    processQueues();
        
    return 0;
}
