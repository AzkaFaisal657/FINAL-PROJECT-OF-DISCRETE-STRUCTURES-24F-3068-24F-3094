#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Student.h"
#include "Course.h"

class CombinationsModule {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;

public:
    CombinationsModule(const std::vector<Student>& students, const std::vector<Course>& courses);

    std::vector<std::vector<std::string>> generateStudentGroups(const std::string& courseCode, int groupSize);
    std::vector<std::vector<std::string>> generateLabGroups(const std::string& labCourseCode, int groupSize);
    std::vector<std::vector<std::string>> generateProjectGroups(int semester, int groupSize);
    long long calculateCombinations(int n, int r);
    void displayGroups(const std::vector<std::vector<std::string>>& groups, const std::string& groupType);

    // MADE PUBLIC TO FIX ACCESS ERROR
    std::vector<Student> getStudentsEnrolledInCourse(const std::string& courseCode);

private:
    std::vector<std::string> getStudentRollNumbers(const std::vector<Student>& students);
    void generateCombinations(const std::vector<std::string>& elements, int r,
        std::vector<std::vector<std::string>>& result,
        int index, std::vector<std::string>& current);
};