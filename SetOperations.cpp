#include "SetOperations.h"
#include <iostream>
#include <cmath>

SetOperations::SetOperations(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty)
    : allStudents(students), allCourses(courses), allFaculty(faculty) {}

std::vector<std::string> SetOperations::setUnion(const std::vector<std::string>& setA, const std::vector<std::string>& setB) {
    std::set<std::string> unionSet(setA.begin(), setA.end());
    unionSet.insert(setB.begin(), setB.end());
    return std::vector<std::string>(unionSet.begin(), unionSet.end());
}

std::vector<std::string> SetOperations::setIntersection(const std::vector<std::string>& setA, const std::vector<std::string>& setB) {
    std::vector<std::string> intersection;
    for (const auto& element : setA) {
        if (std::find(setB.begin(), setB.end(), element) != setB.end()) {
            intersection.push_back(element);
        }
    }
    return removeDuplicates(intersection);
}

std::vector<std::string> SetOperations::setDifference(const std::vector<std::string>& setA, const std::vector<std::string>& setB) {
    std::vector<std::string> difference;
    for (const auto& element : setA) {
        if (std::find(setB.begin(), setB.end(), element) == setB.end()) {
            difference.push_back(element);
        }
    }
    return difference;
}

bool SetOperations::isSubset(const std::vector<std::string>& setA, const std::vector<std::string>& setB) {
    for (const auto& element : setA) {
        if (std::find(setB.begin(), setB.end(), element) == setB.end()) {
            return false;
        }
    }
    return true;
}

bool SetOperations::isSuperset(const std::vector<std::string>& setA, const std::vector<std::string>& setB) {
    return isSubset(setB, setA);
}

std::vector<std::string> SetOperations::getStudentsInBothCourses(const std::string& courseA, const std::string& courseB) {
    auto studentsA = getStudentsEnrolledInCourse(courseA);
    auto studentsB = getStudentsEnrolledInCourse(courseB);
    return setIntersection(studentsA, studentsB);
}

std::vector<std::string> SetOperations::getStudentsInEitherCourse(const std::string& courseA, const std::string& courseB) {
    auto studentsA = getStudentsEnrolledInCourse(courseA);
    auto studentsB = getStudentsEnrolledInCourse(courseB);
    return setUnion(studentsA, studentsB);
}

std::vector<std::string> SetOperations::getStudentsOnlyInFirstCourse(const std::string& courseA, const std::string& courseB) {
    auto studentsA = getStudentsEnrolledInCourse(courseA);
    auto studentsB = getStudentsEnrolledInCourse(courseB);
    return setDifference(studentsA, studentsB);
}

std::vector<std::vector<std::string>> SetOperations::generatePowerSet(const std::vector<std::string>& elements) {
    std::vector<std::vector<std::string>> powerSet;
    int n = elements.size();
    int total = 1 << n; // 2^n

    for (int i = 0; i < total; ++i) {
        std::vector<std::string> subset;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                subset.push_back(elements[j]);
            }
        }
        powerSet.push_back(subset);
    }

    return powerSet;
}

std::vector<std::vector<std::string>> SetOperations::generateLabGroupCombinations(const std::string& courseCode, int maxGroupSize) {
    auto students = getStudentsEnrolledInCourse(courseCode);
    auto powerSet = generatePowerSet(students);

    std::vector<std::vector<std::string>> validGroups;
    for (const auto& subset : powerSet) {
        if (subset.size() >= 2 && subset.size() <= maxGroupSize) {
            validGroups.push_back(subset);
        }
    }

    return validGroups;
}

std::vector<std::string> SetOperations::getCoursesTaughtByFaculty(const std::string& facultyId) {
    for (const auto& faculty : allFaculty) {
        if (faculty.getFacultyId() == facultyId) {
            return faculty.getAssignedCourses();
        }
    }
    return {};
}

std::vector<std::string> SetOperations::getCommonCourses(const std::string& facultyA, const std::string& facultyB) {
    auto coursesA = getCoursesTaughtByFaculty(facultyA);
    auto coursesB = getCoursesTaughtByFaculty(facultyB);
    return setIntersection(coursesA, coursesB);
}

void SetOperations::displaySet(const std::vector<std::string>& set, const std::string& setName) {
    std::cout << "\n=== " << setName << " ===\n";
    std::cout << "Size: " << set.size() << " elements\n";
    std::cout << "Elements: {";
    for (size_t i = 0; i < set.size(); ++i) {
        std::cout << set[i];
        if (i < set.size() - 1) std::cout << ", ";
    }
    std::cout << "}\n";
}

void SetOperations::displayPowerSet(const std::vector<std::vector<std::string>>& powerSet, const std::string& setName) {
    std::cout << "\n=== " << setName << " (Power Set) ===\n";
    std::cout << "Total subsets: " << powerSet.size() << "\n";
    std::cout << "Sample subsets (first 10):\n";

    for (size_t i = 0; i < std::min(powerSet.size(), size_t(10)); ++i) {
        std::cout << "  {";
        for (size_t j = 0; j < powerSet[i].size(); ++j) {
            std::cout << powerSet[i][j];
            if (j < powerSet[i].size() - 1) std::cout << ", ";
        }
        std::cout << "}\n";
    }
}

std::vector<std::string> SetOperations::getStudentsEnrolledInCourse(const std::string& courseCode) {
    std::vector<std::string> enrolled;
    for (const auto& student : allStudents) {
        if (student.isEnrolledIn(courseCode)) {
            enrolled.push_back(student.getRollNumber());
        }
    }
    return enrolled;
}

std::vector<std::string> SetOperations::removeDuplicates(const std::vector<std::string>& input) {
    std::vector<std::string> result;
    std::set<std::string> seen;

    for (const auto& element : input) {
        if (seen.find(element) == seen.end()) {
            seen.insert(element);
            result.push_back(element);
        }
    }

    return result;
}