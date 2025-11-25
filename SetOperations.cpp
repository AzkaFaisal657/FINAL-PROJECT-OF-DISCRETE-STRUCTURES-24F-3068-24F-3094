#include "SetOperations.h"
#include <iostream>
#include <cmath>
#include <algorithm>

SetOperations::SetOperations(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty)
    : allStudents(students), allCourses(courses), allFaculty(faculty) {}

std::vector<std::string> SetOperations::setUnion(const std::vector<std::string>& setA, const std::vector<std::string>& setB) {
    std::set<std::string> unionSet(setA.begin(), setA.end());
    unionSet.insert(setB.begin(), setB.end());
    return std::vector<std::string>(unionSet.begin(), unionSet.end());
}

std::vector<std::string> SetOperations::setIntersection(const std::vector<std::string>& setA, const std::vector<std::string>& setB) {
    std::vector<std::string> intersection;
    std::set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
        std::back_inserter(intersection));
    return removeDuplicates(intersection);
}

std::vector<std::string> SetOperations::setDifference(const std::vector<std::string>& setA, const std::vector<std::string>& setB) {
    std::vector<std::string> difference;
    std::set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(),
        std::back_inserter(difference));
    return removeDuplicates(difference);
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

std::vector<std::vector<std::string>> SetOperations::generatePowerSet(const std::vector<std::string>& elements) {
    std::vector<std::vector<std::string>> powerSet;
    int n = elements.size();

    // Safety check for large sets
    if (n > 15) {
        std::cout << "WARNING: Power set for " << n << " elements would have 2^" << n << " = "
            << (1 << n) << " subsets. Generating sample only." << std::endl;

        // Generate sample subsets instead of full power set
        powerSet.push_back({}); // Empty set

        // Add all single element subsets
        for (const auto& element : elements) {
            powerSet.push_back({ element });
        }

        // Add some 2-element subsets
        for (int i = 0; i < std::min(n, 10); i++) {
            for (int j = i + 1; j < std::min(n, 10); j++) {
                powerSet.push_back({ elements[i], elements[j] });
            }
        }

        return powerSet;
    }

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

std::vector<std::vector<std::string>> SetOperations::generateLabGroupCombinations(const std::string& courseCode, int maxGroupSize) {
    auto students = getStudentsEnrolledInCourse(courseCode);

    if (students.empty()) {
        std::cout << "No students enrolled in " << courseCode << std::endl;
        return {};
    }

    std::cout << "Generating lab groups for " << courseCode << " (" << students.size() << " students)" << std::endl;

    auto powerSet = generatePowerSet(students);
    std::vector<std::vector<std::string>> validGroups;

    for (const auto& subset : powerSet) {
        if (subset.size() >= 2 && subset.size() <= maxGroupSize) {
            validGroups.push_back(subset);
        }
    }

    return validGroups;
}

std::vector<std::string> SetOperations::getCommonCourses(const std::string& facultyA, const std::string& facultyB) {
    auto coursesA = getCoursesTaughtByFaculty(facultyA);
    auto coursesB = getCoursesTaughtByFaculty(facultyB);
    return setIntersection(coursesA, coursesB);
}

void SetOperations::displaySet(const std::vector<std::string>& set, const std::string& setName) {
    std::cout << "\n=== " << setName << " ===" << std::endl;
    std::cout << "Cardinality: |" << setName << "| = " << set.size() << std::endl;

    if (set.empty()) {
        std::cout << "Set is empty: {}" << std::endl;
        return;
    }

    std::cout << "Elements: {";
    for (size_t i = 0; i < set.size(); ++i) {
        std::cout << set[i];
        if (i < set.size() - 1) std::cout << ", ";
    }
    std::cout << "}" << std::endl;
}

void SetOperations::displayPowerSet(const std::vector<std::vector<std::string>>& powerSet, const std::string& setName) {
    std::cout << "\n=== POWER SET of " << setName << " ===" << std::endl;
    std::cout << "Total subsets: 2^" << setName << " = " << powerSet.size() << " subsets" << std::endl;

    if (powerSet.size() > 20) {
        std::cout << "Showing first 15 subsets:" << std::endl;
        for (size_t i = 0; i < std::min(powerSet.size(), size_t(15)); ++i) {
            std::cout << "  {";
            for (size_t j = 0; j < powerSet[i].size(); ++j) {
                std::cout << powerSet[i][j];
                if (j < powerSet[i].size() - 1) std::cout << ", ";
            }
            std::cout << "}" << std::endl;
        }
        std::cout << "... and " << (powerSet.size() - 15) << " more subsets" << std::endl;
    }
    else {
        for (size_t i = 0; i < powerSet.size(); ++i) {
            std::cout << "  {";
            for (size_t j = 0; j < powerSet[i].size(); ++j) {
                std::cout << powerSet[i][j];
                if (j < powerSet[i].size() - 1) std::cout << ", ";
            }
            std::cout << "}" << std::endl;
        }
    }
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

std::vector<std::string> SetOperations::getStudentsEnrolledInCourse(const std::string& courseCode) {
    std::vector<std::string> enrolled;
    for (const auto& student : allStudents) {
        if (student.isEnrolledIn(courseCode)) {
            enrolled.push_back(student.getRollNumber());
        }
    }
    return enrolled;
}

std::vector<std::string> SetOperations::getCoursesTaughtByFaculty(const std::string& facultyId) {
    for (const auto& faculty : allFaculty) {
        if (faculty.getFacultyId() == facultyId) {
            return faculty.getAssignedCourses();
        }
    }
    return {};
}