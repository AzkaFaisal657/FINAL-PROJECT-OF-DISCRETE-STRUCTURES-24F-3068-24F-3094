#include "ConflictDetector.h"
#include <iostream>

bool ConflictDetector::checkRoomCapacity(Room& room, int enrolledStudents) {
    if (enrolledStudents > room.getCapacity()) {
        cout << "? Conflict: Room " << room.getRoomId()
            << " capacity exceeded! Capacity: " << room.getCapacity()
            << ", Enrolled: " << enrolledStudents << endl;
        return false;
    }
    return true;
}

bool ConflictDetector::checkCreditLimit(Student& student, vector<Course*> courses, int maxCredits) {
    int totalCredits = 0;
    for (int i = 0; i < student.getEnrolledCount(); i++) {
        string courseCode = student.getEnrolledCourse(i);
        for (Course* course : courses) {
            if (course->getCode() == courseCode) {
                totalCredits += course->getCreditHours();
                break;
            }
        }
    }

    if (totalCredits > maxCredits) {
        cout << "? Conflict: Student " << student.getId()
            << " exceeded credit limit! Credits: " << totalCredits
            << ", Max: " << maxCredits << endl;
        return false;
    }
    return true;
}

bool ConflictDetector::detectPrerequisiteViolation(Student& student, Course& course, vector<Course*> allCourses) {
    for (int i = 0; i < course.getPrereqCount(); i++) {
        string prereq = course.getPrerequisite(i);
        if (!student.hasCompleted(prereq)) {
            cout << "? Prerequisite Violation: Student " << student.getId()
                << " missing " << prereq << " for " << course.getCode() << endl;
            return true;
        }
    }
    return false;
}

bool ConflictDetector::detectTeachingOverload(Faculty& faculty, int maxCourses) {
    if (faculty.getCourseCount() > maxCourses) {
        cout << "? Teaching Overload: " << faculty.getName()
            << " teaching " << faculty.getCourseCount()
            << " courses (Max: " << maxCourses << ")" << endl;
        return true;
    }
    return false;
}

bool ConflictDetector::hasTimeConflict(string time1, string time2) {
    if (time1 == time2 && !time1.empty()) {
        cout << "? Time Conflict: Overlapping time slots detected" << endl;
        return true;
    }
    return false;
}

void ConflictDetector::generateConflictReport(vector<Student*> students, vector<Course*> courses,
    vector<Faculty*> faculty, vector<Room*> rooms) {
    cout << "\n=== MODULE 9: CONFLICT DETECTION REPORT ===" << endl;

    bool conflictsFound = false;

    cout << "\n1. STUDENT CONFLICTS:" << endl;
    for (Student* student : students) {
        if (!checkCreditLimit(*student, courses, MAX_CREDITS_PER_SEMESTER)) {
            conflictsFound = true;
        }

        for (int i = 0; i < student->getEnrolledCount(); i++) {
            string courseCode = student->getEnrolledCourse(i);
            Course* course = nullptr;
            for (Course* c : courses) {
                if (c->getCode() == courseCode) {
                    course = c;
                    break;
                }
            }
            if (course && detectPrerequisiteViolation(*student, *course, courses)) {
                conflictsFound = true;
            }
        }
    }

    cout << "\n2. FACULTY CONFLICTS:" << endl;
    for (Faculty* fac : faculty) {
        if (detectTeachingOverload(*fac, MAX_COURSES_PER_FACULTY)) {
            conflictsFound = true;
        }
    }

    cout << "\n3. ROOM CONFLICTS:" << endl;
    cout << "Total rooms: " << rooms.size() << endl;
    int available = 0;
    for (Room* room : rooms) {
        if (room->isAvailable()) available++;
    }
    cout << "Available rooms: " << available << endl;

    if (!conflictsFound) {
        cout << "\n? SYSTEM STATUS: NO CONFLICTS DETECTED" << endl;
        cout << "All constraints satisfied - system is consistent" << endl;
    }
    else {
        cout << "\n? SYSTEM STATUS: CONFLICTS DETECTED" << endl;
        cout << "Please resolve the above conflicts" << endl;
    }
}