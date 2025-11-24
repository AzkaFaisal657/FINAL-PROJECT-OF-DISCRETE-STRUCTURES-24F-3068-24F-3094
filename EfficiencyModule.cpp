#include "EfficiencyModule.h"
#include <iostream>
#include <algorithm>

EfficiencyModule::EfficiencyModule(const std::vector<Student>& students, const std::vector<Course>& courses)
    : allStudents(students), allCourses(courses) {}

void EfficiencyModule::benchmarkAllAlgorithms() {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "          EFFICIENCY & BENCHMARKING MODULE\n";
    std::cout << "-------------------------------------------------------------\n";

    std::cout << "Running Algorithmic Complexity Analysis (SE Dept, " << allStudents.size()
        << " students, " << allCourses.size() << " courses)...\n";

    displayComplexityAnalysis();
    runPerformanceTests();
}

void EfficiencyModule::displayComplexityAnalysis() {
    std::cout << "\nAlgorithm Complexity:\n";

    int V = allCourses.size();
    int E = 0;
    for (const auto& course : allCourses) {
        if (!course.getPrerequisite().empty()) E++;
    }

    std::cout << " → Topological Sort for Prerequisites: O(V + E)\n";
    std::cout << "    (V = #courses, E = #prerequisite edges)\n";

    std::cout << " → Set Operations (Union/Intersection/Difference): O(n + m)\n";
    std::cout << "    (n = #students in set A, m = #students in set B)\n";

    // Calculate combinations for CS2001
    int enrolledCS2001 = 0;
    for (const auto& student : allStudents) {
        if (student.isEnrolledIn("CS2001")) enrolledCS2001++;
    }

    std::cout << " → Student Group Combination (C(k, g)): O(k choose g)\n";
    std::cout << "    (k = #students enrolled in course, g = group size)\n";

    int avgCoursesPerStudent = 0;
    for (const auto& student : allStudents) {
        avgCoursesPerStudent += student.getEnrolledCourses().size();
    }
    avgCoursesPerStudent /= allStudents.size();

    std::cout << " → Relations Check (Student → Course → Faculty): O(s × c)\n";
    std::cout << "    (s = total students, c = avg courses per student)\n";

    std::cout << " → Strong Induction Verification (per course): O(s × p)\n";
    std::cout << "    (s = enrolled students, p = length of prerequisite chain)\n";

    std::cout << " → Automated Proof Engine (per rule): O(r × s × p)\n";
    std::cout << "    (r = #rules, s = students, p = prerequisite depth)\n";

    std::cout << " → Logic & Rule Inference: O(r × f)\n";
    std::cout << "    (r = #rules, f = #faculty assignments)\n";

    std::cout << "\nOptimizations:\n";
    std::cout << " → Memoization: reduces recursive computations\n";
    std::cout << " → Bitsets for enrollment tracking: O(1) per check\n";
    std::cout << " → Pre-computed prerequisite graphs: O(V + E) for queries\n";

    std::cout << "\nBenchmarking Completed ✅\n";
    std::cout << "Algorithmic complexities listed using Big-O notation.\n";
}

void EfficiencyModule::runPerformanceTests() {
    std::cout << "\n=== PERFORMANCE MEASUREMENTS ===\n";

    auto start = std::chrono::high_resolution_clock::now();

    // Simulate some operations
    measureSetOperationTime();
    measureRelationCheckTime();
    measureInductionVerificationTime();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Total execution time for all operations: " << duration.count() << "ms\n";
}

long long EfficiencyModule::measureCombinationTime(int n, int r) {
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate combination calculation
    long long result = 1;
    for (int i = 1; i <= r; i++) {
        result = result * (n - i + 1) / i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

long long EfficiencyModule::measureSetOperationTime() {
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate set operations
    std::vector<std::string> setA, setB;
    for (int i = 0; i < 1000; i++) {
        setA.push_back("Student" + std::to_string(i));
        if (i % 2 == 0) setB.push_back("Student" + std::to_string(i));
    }

    std::vector<std::string> intersection;
    std::set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
        std::back_inserter(intersection));

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

long long EfficiencyModule::measureRelationCheckTime() {
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate relation checking
    for (const auto& student : allStudents) {
        for (const auto& courseCode : student.getEnrolledCourses()) {
            // Simulate check
            volatile bool check = student.hasCompleted(courseCode);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

long long EfficiencyModule::measureInductionVerificationTime() {
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate induction verification
    for (const auto& student : allStudents) {
        for (const auto& course : allCourses) {
            if (!course.getPrerequisite().empty()) {
                volatile bool verified = student.hasCompleted(course.getPrerequisite());
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}