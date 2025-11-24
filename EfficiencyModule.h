#pragma once
#include <vector>
#include <string>
#include <chrono>
#include "Student.h"
#include "Course.h"

class EfficiencyModule {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;

public:
    EfficiencyModule(const std::vector<Student>& students, const std::vector<Course>& courses);

    void benchmarkAllAlgorithms();
    void displayComplexityAnalysis();
    void runPerformanceTests();

private:
    long long measureCombinationTime(int n, int r);
    long long measureSetOperationTime();
    long long measureRelationCheckTime();
    long long measureInductionVerificationTime();
};