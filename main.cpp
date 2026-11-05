#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    std::vector<double> grades;
};

std::vector<Student> readStudents(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        Student s;
        iss >> s.name;
        double g;
        while (iss >> g) s.grades.push_back(g);
        students.push_back(s);
    }
    return students;
}

double average(const std::vector<double>& grades) {
    if (grades.empty()) return 0.0;
    double sum = 0.0;
    for (double g : grades) sum += g;
    return sum / grades.size();
}

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
        std::cout << s.name << "  avg: " << average(s.grades) << "\n";
    }
    return 0;
}
