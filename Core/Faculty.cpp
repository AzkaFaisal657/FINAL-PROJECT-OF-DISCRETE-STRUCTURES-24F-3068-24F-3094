#include "Faculty.h"

Faculty::Faculty() : id(""), name(""), designation(""), courseCount(0) {}

Faculty::Faculty(string id, string name, string designation)
    : id(id), name(name), designation(designation), courseCount(0) {
}

void Faculty::assignCourse(string courseCode) {
    if (courseCount < 20 && !isTeaching(courseCode)) {
        assignedCourses[courseCount] = courseCode;
        courseCount++;
    }
}

bool Faculty::isTeaching(string courseCode) const {
    for (int i = 0; i < courseCount; i++) {
        if (assignedCourses[i] == courseCode) {
            return true;
        }
    }
    return false;
}

int Faculty::getCourseCount() const {
    return courseCount;
}

string Faculty::getAssignedCourse(int index) const {
    if (index >= 0 && index < courseCount) {
        return assignedCourses[index];
    }
    return "";
}

string Faculty::getId() const { return id; }
string Faculty::getName() const { return name; }
string Faculty::getDesignation() const { return designation; }

void Faculty::display() const {
    cout << name << " (" << designation << ")" << endl;
    cout << "Teaching " << courseCount << " courses" << endl;
}