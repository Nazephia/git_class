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

    std::cout << "Grades report\n";
    for (const Student& s : students) {
        std::cout << s.name << "  avg: " << average(s.grades)
                  << "  max: " << highest(s.grades)
                  << "  min: " << lowest(s.grades)
                  << "  " << (passed(s.grades) ? "PASS" : "FAIL") << "\n";
    }
    return 0;
}
