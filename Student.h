#pragma once
#include <string>
#include "Course.h"
#include <vector>

class Student {
private:
    std::string rollNumber;
    std::string name;
    int currentSemester;
    std::vector<std::string> enrolledCourses;
    std::vector<std::string> completedCourses;

public:
    Student(const std::string& rollNumber, const std::string& name, int currentSemester,
        const std::vector<std::string>& enrolledCourses);

    // Getters
    std::string getRollNumber() const;
    std::string getName() const;
    int getCurrentSemester() const;
    std::vector<std::string> getEnrolledCourses() const;
    std::vector<std::string> getCompletedCourses() const;

    // Setters
    void setRollNumber(const std::string& rollNumber);
    void setName(const std::string& name);
    void setCurrentSemester(int semester);
    void setEnrolledCourses(const std::vector<std::string>& courses);
    void setCompletedCourses(const std::vector<std::string>& courses);

    // Course management
    void enrollInCourse(const std::string& courseCode);
    void completeCourse(const std::string& courseCode);
    bool hasCompleted(const std::string& courseCode) const;
    bool isEnrolledIn(const std::string& courseCode) const;

    int getCurrentCreditHours(const std::vector<Course>& allCourses) const;

    std::string toString() const;
};