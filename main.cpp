#include <iomanip>
#include <iostream>
#include <vector>

#include "grades.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <grades_file>\n";
        return 1;
    }
    std::vector<Student> students = readStudents(argv[1]);
    if (students.empty()) {
        std::cerr << "No students found in " << argv[1] << "\n";
        return 1;
    }

    std::cout << "Grades report\n\n";
    std::cout << std::left << std::setw(10) << "Name"
              << std::right << std::setw(9) << "Average"
              << std::setw(7) << "Max"
              << std::setw(7) << "Min"
              << "  Status\n";
    std::cout << std::fixed << std::setprecision(2);
    for (const Student& s : students) {
        std::cout << std::left << std::setw(10) << s.name
                  << std::right << std::setw(9) << average(s.grades)
                  << std::setw(7) << highest(s.grades)
                  << std::setw(7) << lowest(s.grades)
                  << "  " << (passed(s.grades) ? "PASS" : "FAIL") << "\n";
    }
    return 0;
}
