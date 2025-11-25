#ifndef EFFICIENCYMODULE_H
#define EFFICIENCYMODULE_H

#include "Student.h"
#include "Course.h"
#include <vector>
#include <string>
#include <chrono>
#include <iostream>

class EfficiencyModule {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;

    long long measureCombinationTime(int n, int r);
    long long measureSetOperationTime();
    long long measureRelationCheckTime();
    long long measureInductionVerificationTime();

public:
    EfficiencyModule(const std::vector<Student>& students, const std::vector<Course>& courses);

    void benchmarkAllAlgorithms();
    void displayComplexityAnalysis();
    void runPerformanceTests();
};

#endif