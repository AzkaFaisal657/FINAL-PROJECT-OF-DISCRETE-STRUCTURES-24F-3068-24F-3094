#include "CombinationsModule.h"
#include <iostream>
#include <cmath>

CombinationsModule::CombinationsModule(const std::vector<Student>& students, const std::vector<Course>& courses)
    : allStudents(students), allCourses(courses) {}

std::vector<std::vector<std::string>> CombinationsModule::generateStudentGroups(const std::string& courseCode, int groupSize) {
    auto enrolledStudents = getStudentsEnrolledInCourse(courseCode);
    auto rollNumbers = getStudentRollNumbers(enrolledStudents);

    std::vector<std::vector<std::string>> allCombinations;
    std::vector<std::string> current;

    if (rollNumbers.size() < groupSize) {
        std::cout << "Not enough students for group size " << groupSize << "\n";
        return allCombinations;
    }

    generateCombinations(rollNumbers, groupSize, allCombinations, 0, current);
    return allCombinations;
}

std::vector<std::vector<std::string>> CombinationsModule::generateLabGroups(const std::string& labCourseCode, int groupSize) {
    return generateStudentGroups(labCourseCode, groupSize);
}

std::vector<std::vector<std::string>> CombinationsModule::generateProjectGroups(int semester, int groupSize) {
    std::vector<Student> semesterStudents;
    for (const auto& student : allStudents) {
        if (student.getCurrentSemester() == semester) {
            semesterStudents.push_back(student);
        }
    }

    auto rollNumbers = getStudentRollNumbers(semesterStudents);
    std::vector<std::vector<std::string>> allCombinations;
    std::vector<std::string> current;

    if (rollNumbers.size() < groupSize) {
        std::cout << "Not enough students in semester " << semester << " for group size " << groupSize << "\n";
        return allCombinations;
    }

    generateCombinations(rollNumbers, groupSize, allCombinations, 0, current);
    return allCombinations;
}

long long CombinationsModule::calculateCombinations(int n, int r) {
    if (r > n) return 0;
    if (r * 2 > n) r = n - r;

    long long result = 1;
    for (int i = 1; i <= r; ++i) {
        result *= n - r + i;
        result /= i;
    }
    return result;
}

void CombinationsModule::displayGroups(const std::vector<std::vector<std::string>>& groups, const std::string& groupType) {
    std::cout << "\n=== " << groupType << " GROUPS ===\n";
    std::cout << "Total possible groups: " << groups.size() << "\n";
    std::cout << "Sample groups (showing first 5):\n";

    for (size_t i = 0; i < std::min(groups.size(), size_t(5)); ++i) {
        std::cout << "Group " << (i + 1) << ": {";
        for (size_t j = 0; j < groups[i].size(); ++j) {
            std::cout << groups[i][j];
            if (j < groups[i].size() - 1) std::cout << ", ";
        }
        std::cout << "}\n";
    }
}

std::vector<Student> CombinationsModule::getStudentsEnrolledInCourse(const std::string& courseCode) {
    std::vector<Student> enrolled;
    for (const auto& student : allStudents) {
        if (student.isEnrolledIn(courseCode)) {
            enrolled.push_back(student);
        }
    }
    return enrolled;
}

std::vector<std::string> CombinationsModule::getStudentRollNumbers(const std::vector<Student>& students) {
    std::vector<std::string> rollNumbers;
    for (const auto& student : students) {
        rollNumbers.push_back(student.getRollNumber());
    }
    return rollNumbers;
}

void CombinationsModule::generateCombinations(const std::vector<std::string>& elements, int r,
    std::vector<std::vector<std::string>>& result,
    int index, std::vector<std::string>& current) {
    if (current.size() == r) {
        result.push_back(current);
        return;
    }

    for (int i = index; i < elements.size(); ++i) {
        current.push_back(elements[i]);
        generateCombinations(elements, r, result, i + 1, current);
        current.pop_back();
    }
}