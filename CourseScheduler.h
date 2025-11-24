#pragma once
#include <vector>
#include <string>
#include <map>
#include "Course.h"
#include "Student.h"

class CourseScheduler {
private:
    std::vector<Course> allCourses;
    std::vector<Student> allStudents;

public:
    CourseScheduler(const std::vector<Course>& courses, const std::vector<Student>& students);

    std::vector<std::vector<std::string>> generateValidSequences(int maxCoursesPerSemester = 5);
    std::vector<std::string> getRecommendedSchedule(const Student& student, int targetSemester);
    bool checkPrerequisiteOrder(const std::vector<std::string>& sequence);
    void displayAllSequences(const std::vector<std::vector<std::string>>& sequences);

private:
    void generateSequencesDFS(int semester, std::vector<std::string>& current,
        std::vector<std::vector<std::string>>& result,
        std::map<std::string, bool>& taken, int maxPerSem);
    bool canTakeCourse(const std::string& courseCode, const std::map<std::string, bool>& takenCourses);
    std::vector<std::string> getCoursesForSemester(int semester);
};