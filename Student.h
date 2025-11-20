#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Student {
private:
    string id;
    string name;
    int currentSemester;
    vector<string> completedCourses;
    vector<string> enrolledCourses;

public:
    Student();
    Student(string id, string name, int semester);

    void completeCourse(string courseCode);
    void enrollInCourse(string courseCode);
    bool hasCompleted(string courseCode) const;
    bool isEnrolled(string courseCode) const;

    string getId() const { return id; }
    string getName() const { return name; }
    int getCurrentSemester() const { return currentSemester; }
    int getCompletedCount() const { return completedCourses.size(); }
    int getEnrolledCount() const { return enrolledCourses.size(); }
    string getCompletedCourse(int index) const;
    string getEnrolledCourse(int index) const;

    void display() const;
};