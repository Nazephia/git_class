#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const double PASSING_GRADE = 10.0;

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

double highest(const std::vector<double>& grades) {
    if (grades.empty()) return 0.0;
    double best = grades[0];
    for (size_t i = 1; i < grades.size(); ++i)
        if (grades[i] > best) best = grades[i];
    return best;
}

double lowest(const std::vector<double>& grades) {
    if (grades.empty()) return 0.0;
    double worst = grades[0];
    for (size_t i = 1; i < grades.size(); ++i)
        if (grades[i] < worst) worst = grades[i];
    return worst;
}

bool passed(const std::vector<double>& grades) {
    return average(grades) >= PASSING_GRADE;
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
        std::cout << s.name << "  avg: " << average(s.grades)
                  << "  max: " << highest(s.grades)
                  << "  min: " << lowest(s.grades)
                  << "  " << (passed(s.grades) ? "PASS" : "FAIL") << "\n";
    }
    return 0;
}
