#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>

class SetOperations {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;
    std::vector<Faculty> allFaculty;

    std::vector<std::string> removeDuplicates(const std::vector<std::string>& input);
    std::vector<std::string> getStudentsEnrolledInCourse(const std::string& courseCode);
    std::vector<std::string> getCoursesTaughtByFaculty(const std::string& facultyId);

public:
    SetOperations(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty);

    // Basic set operations
    std::vector<std::string> setUnion(const std::vector<std::string>& setA, const std::vector<std::string>& setB);
    std::vector<std::string> setIntersection(const std::vector<std::string>& setA, const std::vector<std::string>& setB);
    std::vector<std::string> setDifference(const std::vector<std::string>& setA, const std::vector<std::string>& setB);
    bool isSubset(const std::vector<std::string>& setA, const std::vector<std::string>& setB);
    bool isSuperset(const std::vector<std::string>& setA, const std::vector<std::string>& setB);

    // Power set operations
    std::vector<std::vector<std::string>> generatePowerSet(const std::vector<std::string>& elements);

    // University-specific set operations
    std::vector<std::string> getStudentsInBothCourses(const std::string& courseA, const std::string& courseB);
    std::vector<std::string> getStudentsInEitherCourse(const std::string& courseA, const std::string& courseB);
    std::vector<std::string> getStudentsOnlyInFirstCourse(const std::string& courseA, const std::string& courseB);
    std::vector<std::string> getCommonCourses(const std::string& facultyA, const std::string& facultyB);

    // Group operations
    std::vector<std::vector<std::string>> generateLabGroupCombinations(const std::string& courseCode, int maxGroupSize);

    // Display methods
    void displaySet(const std::vector<std::string>& set, const std::string& setName);
    void displayPowerSet(const std::vector<std::vector<std::string>>& powerSet, const std::string& setName);
};

#endif