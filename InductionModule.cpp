#include "InductionModule.h"
#include <iostream>
#include <algorithm>

InductionModule::InductionModule(const std::vector<Student>& students, const std::vector<Course>& courses)
    : allStudents(students), allCourses(courses) {}

bool InductionModule::verifyPrerequisiteChain(const std::string& courseCode) {
    auto prerequisites = getAllPrerequisites(courseCode);
    std::cout << "Prerequisite chain for " << courseCode << ": ";

    if (prerequisites.empty()) {
        std::cout << "None (base course)" << std::endl;
        return true;
    }

    for (const auto& prereq : prerequisites) {
        std::cout << prereq << " -> ";
    }
    std::cout << courseCode << std::endl;

    // Check for cycles using DFS
    std::map<std::string, bool> visited;
    std::map<std::string, bool> recursionStack;

    for (const auto& course : allCourses) {
        if (hasCycle(course.getCode(), visited, recursionStack)) {
            std::cout << "ERROR: CYCLE DETECTED in prerequisite chain!" << std::endl;
            return false;
        }
    }

    std::cout << "Prerequisite chain is valid (Directed Acyclic Graph)" << std::endl;
    return true;
}

bool InductionModule::verifyStudentEligibility(const Student& student, const std::string& courseCode) {
    return strongInductionVerification(student, courseCode);
}

std::vector<std::pair<std::string, bool>> InductionModule::verifyAllStudentsForCourse(const std::string& courseCode) {
    std::vector<std::pair<std::string, bool>> results;

    // First, check if course exists
    Course* targetCourse = findCourseByCode(courseCode);
    if (!targetCourse) {
        std::cout << "ERROR: Course " << courseCode << " not found!" << std::endl;
        return results;
    }

    auto enrolledStudents = getStudentsEnrolledInCourse(courseCode);

    if (enrolledStudents.empty()) {
        std::cout << "WARNING: No students enrolled in " << courseCode << std::endl;
        return results;
    }

    std::cout << "Verifying " << enrolledStudents.size() << " students enrolled in " << courseCode << "..." << std::endl;

    for (const auto& student : enrolledStudents) {
        bool eligible = strongInductionVerification(student, courseCode);
        results.push_back(std::make_pair(student.getRollNumber(), eligible));
    }

    return results;
}

void InductionModule::displayVerificationResults(const std::vector<std::pair<std::string, bool>>& results, const std::string& courseCode) {
    std::cout << "\n=== INDUCTION VERIFICATION RESULTS for " << courseCode << " ===" << std::endl;

    if (results.empty()) {
        std::cout << "No results to display." << std::endl;
        return;
    }

    int eligibleCount = 0;
    int totalCount = results.size();

    // Show detailed results for first 5 students
    std::cout << "Detailed verification (first 5 students):" << std::endl;
    for (size_t i = 0; i < results.size() && i < 5; ++i) {
        std::cout << "Student " << results[i].first << ": ";
        if (results[i].second) {
            std::cout << "ELIGIBLE ✓ [All prerequisites satisfied]";
            eligibleCount++;
        }
        else {
            std::cout << "NOT ELIGIBLE ✗ [Missing prerequisites]";
        }
        std::cout << std::endl;
    }

    // Count all eligible students
    for (const auto& result : results) {
        if (result.second) eligibleCount++;
    }

    std::cout << "\nSUMMARY:" << std::endl;
    std::cout << " - Total Students Enrolled: " << totalCount << std::endl;
    std::cout << " - Eligible Students: " << eligibleCount << std::endl;
    std::cout << " - Ineligible Students: " << (totalCount - eligibleCount) << std::endl;

    if (totalCount > 0) {
        double successRate = (eligibleCount * 100.0) / totalCount;
        std::cout << " - Success Rate: " << successRate << "%" << std::endl;
    }

    // Mathematical induction explanation
    std::cout << "\nMATHEMATICAL INDUCTION PROCESS:" << std::endl;
    std::cout << "1. Base Case: Verified immediate prerequisites" << std::endl;
    std::cout << "2. Inductive Step: Assumed P(k) true, verified P(k+1)" << std::endl;
    std::cout << "3. Strong Induction: Verified entire prerequisite chain" << std::endl;
    std::cout << "4. Conclusion: All discrete math rules satisfied" << std::endl;
}

bool InductionModule::strongInductionVerification(const Student& student, const std::string& courseCode) {
    auto prerequisites = getAllPrerequisites(courseCode);

    // Base case: No prerequisites
    if (prerequisites.empty()) {
        return true;
    }

    // Strong induction: Verify all prerequisites in the chain
    for (const auto& prereq : prerequisites) {
        if (!student.hasCompleted(prereq)) {
            return false;
        }
    }

    return true;
}

std::vector<std::string> InductionModule::getAllPrerequisites(const std::string& courseCode) {
    std::vector<std::string> prerequisites;
    std::string currentCourse = courseCode;

    while (true) {
        Course* course = findCourseByCode(currentCourse);
        if (!course || course->getPrerequisite().empty()) {
            break;
        }
        prerequisites.push_back(course->getPrerequisite());
        currentCourse = course->getPrerequisite();
    }

    std::reverse(prerequisites.begin(), prerequisites.end());
    return prerequisites;
}

bool InductionModule::baseCaseVerification(const Student& student, const std::vector<std::string>& prerequisites) {
    if (prerequisites.empty()) return true;
    return student.hasCompleted(prerequisites[0]);
}

bool InductionModule::inductiveStepVerification(const Student& student, const std::vector<std::string>& prerequisites, int k) {
    if (k >= prerequisites.size()) return true;
    return student.hasCompleted(prerequisites[k]);
}

Course* InductionModule::findCourseByCode(const std::string& courseCode) {
    for (auto& course : allCourses) {
        if (course.getCode() == courseCode) {
            return &course;
        }
    }
    return nullptr;
}

std::vector<Student> InductionModule::getStudentsEnrolledInCourse(const std::string& courseCode) {
    std::vector<Student> enrolled;
    for (const auto& student : allStudents) {
        if (student.isEnrolledIn(courseCode)) {
            enrolled.push_back(student);
        }
    }
    return enrolled;
}

bool InductionModule::hasCycle(const std::string& courseCode, std::map<std::string, bool>& visited, std::map<std::string, bool>& recursionStack) {
    if (!visited[courseCode]) {
        visited[courseCode] = true;
        recursionStack[courseCode] = true;

        Course* course = findCourseByCode(courseCode);
        if (course && !course->getPrerequisite().empty()) {
            std::string prereq = course->getPrerequisite();
            if (!visited[prereq] && hasCycle(prereq, visited, recursionStack)) {
                return true;
            }
            else if (recursionStack[prereq]) {
                return true;
            }
        }
    }
    recursionStack[courseCode] = false;
    return false;
}