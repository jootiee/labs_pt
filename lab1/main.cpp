#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "sorts.h"
#include "applicant.h"
#include "utils.h"

/**
 * @mainpage
 * 
 * Link to repository: https://github.com/jootiee/labs_pt
 * 
 * Results
 * @image html graph.png
 */

/**
 * @brief Wrapper function for merge sort
 * @param a Array of applicants to sort
 * @param s Size of the array
 */
void mergeSortWrapper(Applicant* a, size_t s) {
    mergeSort(a, 0, s - 1);
}

/**
 * @brief Print help message for program usage
 */
void printHelp() {
    std::cout << "Usage:\n"
              << "  ./main.out --generate <size> <output_filename> - Generate test data\n"
              << "  ./main.out --test <input_filename> <output_filename> - Test sorting algorithms\n"
              << "  ./main.out --help                             - Show this help message\n";
}

/**
 * @brief Test sorting algorithms on data from a file and save results to another file
 * @param inputFilename Name of the input CSV file containing applicant data
 * @param outputFilename Name of the output CSV file to save sorting results
 */
void testSortingAlgorithms(const std::string& inputFilename, const std::string& outputFilename) {
    size_t totalApplicants = 0;
    Applicant* applicants = readApplicantsFromFile(inputFilename, totalApplicants);

    const int sizes[] = {500, 1000, 2500, 5000, 7500, 10000, 20000, 25000, 50000, 75000, 100000};
    using SortFunc = void(*)(Applicant*, size_t);
    SortFunc sortFuncs[] = {
        standartSort<Applicant>,
        heapSort<Applicant>,
        mergeSortWrapper,
        selectSort<Applicant>
    };
    const int numSortFuncs = 4;

    std::ofstream output(outputFilename);
    if (!output.is_open()) {
        std::cerr << "Error: Unable to open output file '" << outputFilename << "'.\n";
        delete[] applicants;
        return;
    }

    output << "Size;Standart;Heap;Merge;Selection" << std::endl;
    std::cout << "Size\tC\tHeap\tMerge\tSelection" << std::endl;

    for (size_t size : sizes) {
        if (size > totalApplicants) break;

        output << size;
        std::cout << size << "\t";

        for (int i = 0; i < numSortFuncs; i++) {
            Applicant* applicantsCopy = new Applicant[size];
            std::copy(applicants, applicants + size, applicantsCopy);

            long sortTime = measureSortTime(sortFuncs[i], applicantsCopy, size);

            output << ";" << sortTime;
            std::cout << sortTime << "\t";

            delete[] applicantsCopy;
        }

        output << std::endl;
        std::cout << std::endl;
    }

    output.close();
    delete[] applicants;
}

/**
 * @brief Main function to handle program arguments and execute commands
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit status
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Missing arguments. Use '--help' for usage instructions.\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "--generate") {
        if (argc != 4) {
            std::cerr << "Error: Invalid arguments for 'generate'.\n";
            printHelp();
            return 1;
        }

        size_t totalApplicants = std::stoul(argv[2]);
        std::string outputFilename = argv[3];
        generateDataCSV(outputFilename, totalApplicants);
        std::cout << "Data generated to " << outputFilename << " with " << totalApplicants << " records.\n";

    } else if (command == "--test") {
        if (argc != 4) {
            std::cerr << "Error: Invalid arguments for 'test'.\n";
            printHelp();
            return 1;
        }

        std::string inputFilename = argv[2];
        std::string outputFilename = argv[3];
        testSortingAlgorithms(inputFilename, outputFilename);

    } else if (command == "--help" || command == "-h") {
        printHelp();

    } else {
        std::cerr << "Error: Unknown command '" << command << "'. Use 'help' for usage instructions.\n";
        return 1;
    }

    return 0;
}