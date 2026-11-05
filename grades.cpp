#include "grades.h"

#include <fstream>
#include <sstream>

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

// All helpers use the same index-based loop style for consistency.

double average(const std::vector<double>& grades) {
    if (grades.empty()) return 0.0;
    double sum = 0.0;
    for (size_t i = 1; i < grades.size(); ++i)
        sum += grades[i];
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
