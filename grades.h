#ifndef GRADES_H
#define GRADES_H

#include <string>
#include <vector>

const double PASSING_GRADE = 10.0;

struct Student {
    std::string name;
    std::vector<double> grades;
};

std::vector<Student> readStudents(const std::string& filename);

double average(const std::vector<double>& grades);
double highest(const std::vector<double>& grades);
double lowest(const std::vector<double>& grades);
bool passed(const std::vector<double>& grades);

#endif
