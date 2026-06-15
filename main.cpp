#include <iostream>
#include <string>
#include <chrono>
#include "LogParser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_log_file>\n";
        return 1;
    }

    std::string filePath = argv[1];
    LogParser parser(filePath);

    std::cout << "Processing log file: " << filePath << "...\n";
    
    auto start = std::chrono::high_resolution_clock::now();
    
    if (!parser.processFile()) {
        std::cerr << " Error: Could not read or process the file.\n";
        return 1;
    }

    if (!parser.validateData()) {
        std::cerr << " Error: Data validation failed.\n";
        return 1;
    }
    
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    parser.printSummary(elapsed.count());

    return 0;
