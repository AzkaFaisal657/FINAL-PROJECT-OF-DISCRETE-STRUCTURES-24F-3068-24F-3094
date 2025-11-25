#include "CombinationsModule.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

CombinationsModule::CombinationsModule(const std::vector<Student>& students, const std::vector<Course>& courses)
    : allStudents(students), allCourses(courses) {}

std::vector<std::vector<std::string>> CombinationsModule::generateStudentGroups(const std::string& courseCode, int groupSize) {
    auto enrolledStudents = getStudentsEnrolledInCourse(courseCode);
    auto rollNumbers = getStudentRollNumbers(enrolledStudents);

    std::vector<std::vector<std::string>> allCombinations;

    if (rollNumbers.size() < groupSize) {
        std::cout << "ERROR: Not enough students for group size " << groupSize
            << " (only " << rollNumbers.size() << " students enrolled)" << std::endl;
        return allCombinations;
    }

    // For large combinations, generate only samples instead of all combinations
    long long totalCombs = calculateCombinations(rollNumbers.size(), groupSize);

    if (totalCombs > 1000000) { // If more than 1 million combinations
        std::cout << "Large combination detected: C(" << rollNumbers.size() << "," << groupSize
            << ") = " << totalCombs << std::endl;
        std::cout << "Generating sample groups instead of all combinations..." << std::endl;

        // Generate random sample groups
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

        for (int i = 0; i < 100 && i < totalCombs; i++) { // Generate max 100 samples
            std::vector<std::string> shuffled = rollNumbers;
            std::shuffle(shuffled.begin(), shuffled.end(), generator);

            std::vector<std::string> sampleGroup(shuffled.begin(), shuffled.begin() + groupSize);
            std::sort(sampleGroup.begin(), sampleGroup.end());

            // Check if this group is unique
            if (std::find(allCombinations.begin(), allCombinations.end(), sampleGroup) == allCombinations.end()) {
                allCombinations.push_back(sampleGroup);
            }
        }
    }
    else {
        // For small combinations, generate all
        std::vector<std::string> current;
        generateCombinations(rollNumbers, groupSize, allCombinations, 0, current);
    }

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

    if (rollNumbers.size() < groupSize) {
        std::cout << "ERROR: Not enough students in semester " << semester
            << " for group size " << groupSize << std::endl;
        return allCombinations;
    }

    std::vector<std::string> current;
    generateCombinations(rollNumbers, groupSize, allCombinations, 0, current);
    return allCombinations;
}

long long CombinationsModule::calculateCombinations(int n, int r) {
    if (r > n) return 0;
    if (r * 2 > n) r = n - r; // Use symmetry

    long long result = 1;
    for (int i = 1; i <= r; ++i) {
        result *= n - r + i;
        result /= i;

        // Safety check for overflow
        if (result < 0) {
            return -1; // Overflow occurred
        }
    }
    return result;
}

void CombinationsModule::displayGroups(const std::vector<std::vector<std::string>>& groups, const std::string& groupType) {
    std::cout << "\n=== " << groupType << " GROUPS ===" << std::endl;

    if (groups.empty()) {
        std::cout << "No groups generated." << std::endl;
        return;
    }

    std::cout << "Total groups: " << groups.size() << std::endl;

    if (groups.size() > 10) {
        std::cout << "Showing first 10 groups:" << std::endl;
        for (size_t i = 0; i < std::min(groups.size(), size_t(10)); ++i) {
            std::cout << "Group " << (i + 1) << ": {";
            for (size_t j = 0; j < groups[i].size(); ++j) {
                std::cout << groups[i][j];
                if (j < groups[i].size() - 1) std::cout << ", ";
            }
            std::cout << "}" << std::endl;
        }
        std::cout << "... and " << (groups.size() - 10) << " more groups." << std::endl;
    }
    else {
        for (size_t i = 0; i < groups.size(); ++i) {
            std::cout << "Group " << (i + 1) << ": {";
            for (size_t j = 0; j < groups[i].size(); ++j) {
                std::cout << groups[i][j];
                if (j < groups[i].size() - 1) std::cout << ", ";
            }
            std::cout << "}" << std::endl;
        }
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

    // Safety check: prevent stack overflow for large n
    if (result.size() > 100000) {
        std::cout << "WARNING: Stopping combination generation at 100,000 groups to prevent memory issues." << std::endl;
        return;
    }

    for (int i = index; i < elements.size(); ++i) {
        current.push_back(elements[i]);
        generateCombinations(elements, r, result, i + 1, current);
        current.pop_back();
    }
}