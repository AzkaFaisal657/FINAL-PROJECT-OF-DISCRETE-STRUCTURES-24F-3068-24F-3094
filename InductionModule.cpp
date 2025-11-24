#include "InductionModule.h"
#include <iostream>
#include <algorithm>

InductionModule::InductionModule(const std::vector<Student>& students, const std::vector<Course>& courses)
    : allStudents(students), allCourses(courses) {}

bool InductionModule::verifyPrerequisiteChain(const std::string& courseCode) {
    auto prerequisites = getAllPrerequisites(courseCode);
    std::cout << "Prerequisite chain for " << courseCode << ": ";
    for (const auto& prereq : prerequisites) {
        std::cout << prereq << " -> ";
    }
    std::cout << courseCode << "\n";

    // Check for cycles (should be a DAG)
    std::map<std::string, bool> visited;
    std::map<std::string, bool> recursionStack;

    for (const auto& course : allCourses) {
        if (hasCycle(course.getCode(), visited, recursionStack)) {
            std::cout << "CYCLE DETECTED in prerequisite chain!\n";
            return false;
        }
    }

    std::cout << "Prerequisite chain is valid (DAG)\n";
    return true;
}

bool InductionModule::verifyStudentEligibility(const Student& student, const std::string& courseCode) {
    return strongInductionVerification(student, courseCode);
}

std::vector<std::pair<std::string, bool>> InductionModule::verifyAllStudentsForCourse(const std::string& courseCode) {
    std::vector<std::pair<std::string, bool>> results;
    auto enrolledStudents = getStudentsEnrolledInCourse(courseCode);

    for (const auto& student : enrolledStudents) {
        bool eligible = strongInductionVerification(student, courseCode);
        results.push_back(std::make_pair(student.getRollNumber(), eligible));
    }

    return results;
}

void InductionModule::displayVerificationResults(const std::vector<std::pair<std::string, bool>>& results, const std::string& courseCode) {
    std::cout << "\n=== INDUCTION VERIFICATION RESULTS for " << courseCode << " ===\n";

    int eligibleCount = 0;
    int totalCount = results.size();

    for (const auto& result : results) {
        std::cout << "Student " << result.first << ": ";
        if (result.second) {
            std::cout << "ELIGIBLE [OK]";
            eligibleCount++;
        }
        else {
            std::cout << "NOT ELIGIBLE [X]";
        }
        std::cout << "\n";
    }

    std::cout << "\nSUMMARY:\n";
    std::cout << " - Total Students: " << totalCount << "\n";
    std::cout << " - Eligible: " << eligibleCount << "\n";
    std::cout << " - Not Eligible: " << (totalCount - eligibleCount) << "\n";
    std::cout << " - Success Rate: " << (totalCount > 0 ? (eligibleCount * 100 / totalCount) : 0) << "%\n";
}

bool InductionModule::strongInductionVerification(const Student& student, const std::string& courseCode) {
    auto prerequisites = getAllPrerequisites(courseCode);

    // Base case: Check immediate prerequisite
    if (!prerequisites.empty()) {
        std::string immediatePrereq = prerequisites.back();
        if (!student.hasCompleted(immediatePrereq)) {
            return false;
        }
    }

    // Strong induction: Check all prerequisites in chain
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
    // Assume P(1), P(2), ..., P(k) are true, verify P(k+1)
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