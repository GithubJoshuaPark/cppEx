#include <iostream>
#include <fstream>   // For file I/O (ifstream, ofstream)
#include "helloEx.h" // for printLine
#include "file_ioEx.h"

void file_ioEx(void) {
    printLine("Demonstrating File I/O");

    const char* filename = "example.txt";

    // Writing to a file
    {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }
        outFile << "Hello, File I/O!" << std::endl;
        outFile << "This is a simple example of file writing in C++." << std::endl;
        outFile.close();
        std::cout << "Data written to " << filename << std::endl;
    }

    // Reading from a file
    {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
            return;
        }
        std::string line;
        std::cout << "Contents of " << filename << ":" << std::endl;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    }

    printLine("File I/O Example Completed");
}