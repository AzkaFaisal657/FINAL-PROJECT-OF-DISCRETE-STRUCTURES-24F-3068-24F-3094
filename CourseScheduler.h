#ifndef COURSESCHEDULER_H
#define COURSESCHEDULER_H

#include "Course.h"
#include "Student.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>

class CourseScheduler {
private:
    std::vector<Course> allCourses;
    std::vector<Student> allStudents;

    bool canTakeCourse(const std::string& courseCode, const std::set<std::string>& takenCourses);
    bool canTakeCourse(const std::string& courseCode, const std::map<std::string, bool>& takenCourses);
    std::vector<std::string> getCoursesForSemester(int semester);

public:
    CourseScheduler(const std::vector<Course>& courses, const std::vector<Student>& students);

    std::vector<std::vector<std::string>> generateValidSequences(int maxCoursesPerSemester);
    std::vector<std::string> getRecommendedSchedule(const Student& student, int targetSemester);
    bool checkPrerequisiteOrder(const std::vector<std::string>& sequence);
    void displayAllSequences(const std::vector<std::vector<std::string>>& sequences);
};

#endif