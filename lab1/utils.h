#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <sstream>

#include "applicant.h"

/**
 * @brief Measure the time of sorting function
 * @tparam Func 
 * @param sortFunc sorting function 
 * @param applicants applicants array to sort
 * @param size size of applicants' array
 * @return long duration of sorting in microseconds
 */
template <typename Func>
long measureSortTime(Func sortFunc, Applicant* applicants, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(applicants, size);
    auto end = std::chrono::high_resolution_clock::now();
    long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration;
}

/**
 * @brief Generate random string of given length
 * @param length length of the string
 * @return random string
 */
std::string randomString(int length) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    for (int i = 0; i < length; ++i)
        result += chars[rand() % (chars.size() - 1)];

    return result;
}

/**
 * @brief Generate data and write to CSV file
 * @param filename name of the file
 * @param total number of records to generate
 */
void generateDataCSV(const std::string& filename, int total = 101000) {
    const std::string faculties[] = {"Engineering", "Science", "Arts", "Business"};
    const std::string specialties[] = {"Computer Science", "Mathematics", "Physics", "Chemistry", "Economics"};
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    for (int i = 0; i < total; ++i) {
        std::string name = randomString(10);
        std::string faculty = faculties[rand() % (sizeof(faculties) / sizeof(faculties[0]))];
        std::string specialty = specialties[rand() % (sizeof(specialties) / sizeof(specialties[0]))];
        int score = rand() % 100 + 1;
        file << name << ";" << faculty << ";" << specialty << ";" << score << "\n";
    }
    file.close();
}

/**
 * @brief Read applicants from CSV file
 * @param filename name of the file
 * @param size size of the array
 * @return pointer to the array of applicants
 */
Applicant* readApplicantsFromFile(const std::string& filename, size_t& size) {
    std::ifstream file(filename);
    std::vector<Applicant> tempApplicants;

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name, faculty, specialty;
        int score;

        getline(ss, name, ';');
        getline(ss, faculty, ';');
        getline(ss, specialty, ';');
        ss >> score;

        tempApplicants.push_back(Applicant{name, faculty, specialty, score});
    }

    size = tempApplicants.size();
    Applicant* applicants = new Applicant[size];
    std::copy(tempApplicants.begin(), tempApplicants.end(), applicants);

    return applicants;
}

#endif