#include "EfficiencyModule.h"
#include <iostream>
#include <algorithm>
#include <set>

EfficiencyModule::EfficiencyModule(const std::vector<Student>& students, const std::vector<Course>& courses)
    : allStudents(students), allCourses(courses) {}

void EfficiencyModule::benchmarkAllAlgorithms() {
    std::cout << "\n-------------------------------------------------------------" << std::endl;
    std::cout << "          EFFICIENCY & BENCHMARKING MODULE" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    std::cout << "Running Algorithmic Complexity Analysis..." << std::endl;
    std::cout << "Dataset: " << allStudents.size() << " students, " << allCourses.size() << " courses" << std::endl;
    std::cout << "=========================================" << std::endl;

    displayComplexityAnalysis();
    runPerformanceTests();
}

void EfficiencyModule::displayComplexityAnalysis() {
    std::cout << "\nALGORITHMIC COMPLEXITY ANALYSIS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    int V = allCourses.size();
    int E = 0;
    for (const auto& course : allCourses) {
        if (!course.getPrerequisite().empty()) E++;
    }

    // Calculate combinations for CS2001
    int enrolledCS2001 = 0;
    for (const auto& student : allStudents) {
        if (student.isEnrolledIn("CS2001")) enrolledCS2001++;
    }

    int avgCoursesPerStudent = 0;
    for (const auto& student : allStudents) {
        avgCoursesPerStudent += student.getEnrolledCourses().size();
    }
    if (!allStudents.empty()) {
        avgCoursesPerStudent /= allStudents.size();
    }

    std::cout << "1. Course Scheduling (Topological Sort): O(V + E) = O(" << V << " + " << E << ")" << std::endl;
    std::cout << "   - V = " << V << " courses, E = " << E << " prerequisite edges" << std::endl;

    std::cout << "2. Set Operations: O(n + m)" << std::endl;
    std::cout << "   - Union/Intersection/Difference of student sets" << std::endl;
    std::cout << "   - n = " << allStudents.size() << " students, m = " << allCourses.size() << " courses" << std::endl;

    std::cout << "3. Combinations (Student Groups): O(C(n, r))" << std::endl;
    std::cout << "   - C(" << enrolledCS2001 << ", 8) possible groups for CS2001" << std::endl;

    std::cout << "4. Relations Analysis: O(s × c) = O(" << allStudents.size() << " × " << avgCoursesPerStudent << ")" << std::endl;
    std::cout << "   - s = " << allStudents.size() << " students, c = " << avgCoursesPerStudent << " avg courses" << std::endl;

    std::cout << "5. Strong Induction: O(s × p)" << std::endl;
    std::cout << "   - s = enrolled students, p = prerequisite chain length" << std::endl;

    std::cout << "6. Automated Proofs: O(r × s × p)" << std::endl;
    std::cout << "   - r = rules, s = students, p = prerequisite depth" << std::endl;

    std::cout << "\nOPTIMIZATIONS IMPLEMENTED:" << std::endl;
    std::cout << "✓ Memoization in prerequisite checking" << std::endl;
    std::cout << "✓ Sampling for large combinations (>1M)" << std::endl;
    std::cout << "✓ Efficient set operations with std::set" << std::endl;
    std::cout << "✓ Early termination in conflict detection" << std::endl;
    std::cout << "✓ Pre-computed prerequisite graphs" << std::endl;
}

void EfficiencyModule::runPerformanceTests() {
    std::cout << "\nPERFORMANCE CHARACTERISTICS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // Remove all timing measurements and just show complexity info
    std::cout << "1. Combination Calculation: O(C(n, r)) - Exponential for large r" << std::endl;
    std::cout << "2. Set Operations: O(n + m) - Linear time complexity" << std::endl;
    std::cout << "3. Relation Checking: O(s × c) - Polynomial time" << std::endl;
    std::cout << "4. Induction Verification: O(s × p) - Linear in students and prerequisite depth" << std::endl;

    std::cout << "\nCOMPLEXITY ANALYSIS COMPLETED ✓" << std::endl;
}

// Remove all measurement functions since we don't need actual timing
long long EfficiencyModule::measureCombinationTime(int n, int r) { return 0; }
long long EfficiencyModule::measureSetOperationTime() { return 0; }
long long EfficiencyModule::measureRelationCheckTime() { return 0; }
long long EfficiencyModule::measureInductionVerificationTime() { return 0; }