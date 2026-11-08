#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "grades.h"
#include "./colors/colors.hpp"

// Flags CLI
static void printHelp(const char* prog) {
    std::cout << "Usage: " << prog << " [OPTIONS] <grades_file>\n\n";
    std::cout << "Reads a file of students and their grades and prints a report.\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help    Show this help message and exit\n";
    std::cout << "  -v, --version Show version information and exit\n";
    std::cout << "\nInput format:\n";
    std::cout << "  One student per line: the name followed by their grades.\n";
}


std::ostream& operator<<(std::ostream& os, Color c) {
    return os << "\033[" << static_cast<int>(c) << "m";
}


static void printVersion() {
    std::cout << "grades report 1.0\n";
}

int main(int argc, char* argv[]) {
    std::string gradesFile;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            return 0;
        } else if (arg == "-v" || arg == "--version") {
            printVersion();
            return 0;
        } else if (arg.size() > 1 && arg[0] == '-') {
            std::cerr << "Unknown option: " << arg << "\n";
            std::cerr << "Try '" << argv[0] << " --help' for more information.\n";
            return 1;
        } else if (gradesFile.empty()) {
            gradesFile = arg;
        } else {
            std::cerr << "Unexpected argument: " << arg << "\n";
            std::cerr << "Try '" << argv[0] << " --help' for more information.\n";
            return 1;
        }
    }

    if (gradesFile.empty()) {
        std::cerr << "Usage: " << argv[0] << " <grades_file>\n";
        std::cerr << "Try '" << argv[0] << " --help' for more information.\n";
        return 1;
    }

    std::vector<Student> students = readStudents(gradesFile);
    if (students.empty()) {
        std::cerr << "No students found in " << argv[1] << "\n";
        return 1;
    }

    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  return average(a.grades) > average(b.grades);
              });

    const int colName = 10;
    const int colAvg = 9;
    const int colMax = 7;
    const int colMin = 7;
    const int colStatus = 6;

    std::cout << "Grades report\n\n";
    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::left << std::setw(colName) << "Name"
              << std::right << std::setw(colAvg) << "Average"
              << std::setw(colMax) << "Max"
              << std::setw(colMin) << "Min"
              << "  " << std::setw(colStatus) << "Status" << "\n";
    std::vector<double> averages;
    for (const Student& s : students) {
        averages.push_back(average(s.grades));
        std::cout << std::left << std::setw(colName) << s.name
                  << std::right << std::setw(colAvg) << average(s.grades)
                  << std::setw(colMax) << highest(s.grades)
                  << std::setw(colMin) << lowest(s.grades)
                  << "  " << (passed(s.grades) ? Color::Green : Color::Red)
                  << std::left << std::setw(colStatus)
                  << (passed(s.grades) ? "PASS" : "FAIL")
                  << Color::Reset << "\n";
    }

    std::cout << "\nClass average: " << average(averages) << "\n";
    return 0;
}
