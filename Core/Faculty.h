#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <iostream>
using namespace std;

class Faculty {
private:
    string id;
    string name;
    string designation;
    string assignedCourses[20];
    int courseCount;

public:
    Faculty();
    Faculty(string id, string name, string designation);

    void assignCourse(string courseCode);
    bool isTeaching(string courseCode) const;
    int getCourseCount() const;
    string getAssignedCourse(int index) const;

    string getId() const;
    string getName() const;
    string getDesignation() const;

    void display() const;
};

#endif