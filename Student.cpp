#include "Student.h"

Student::Student() : id(""), name(""), currentSemester(0) {}

Student::Student(string id, string name, int semester)
    : id(id), name(name), currentSemester(semester) {
}

void Student::completeCourse(string courseCode) {
    for (int i = 0; i < enrolledCourses.size(); i++) {
        if (enrolledCourses[i] == courseCode) {
            enrolledCourses.erase(enrolledCourses.begin() + i);
            break;
        }
    }

    if (!hasCompleted(courseCode)) {
        completedCourses.push_back(courseCode);
    }
}

void Student::enrollInCourse(string courseCode) {
    if (!isEnrolled(courseCode)) {
        enrolledCourses.push_back(courseCode);
    }
}

bool Student::hasCompleted(string courseCode) const {
    for (const string& course : completedCourses) {
        if (course == courseCode) return true;
    }
    return false;
}

bool Student::isEnrolled(string courseCode) const {
    for (const string& course : enrolledCourses) {
        if (course == courseCode) return true;
    }
    return false;
}

string Student::getCompletedCourse(int index) const {
    if (index >= 0 && index < completedCourses.size()) {
        return completedCourses[index];
    }
    return "";
}

string Student::getEnrolledCourse(int index) const {
    if (index >= 0 && index < enrolledCourses.size()) {
        return enrolledCourses[index];
    }
    return "";
}

void Student::display() const {
    cout << "Student: " << name << " (ID: " << id << ")" << endl;
    cout << "Current Semester: " << currentSemester << endl;
    cout << "Completed Courses: " << completedCourses.size() << endl;
    cout << "Enrolled Courses: " << enrolledCourses.size() << endl;
}