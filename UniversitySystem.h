#pragma once
#ifndef UNIVERSITY_SYSTEM_H
#define UNIVERSITY_SYSTEM_H

#include "Course.h"
#include "Student.h"
#include "Faculty.h"
#include "Room.h"
#include "FileHandler.h"
#include <vector>
#include <string>
using namespace std;

class UniversitySystem {
private:
    vector<Course*> courses;
    vector<Student*> students;
    vector<Faculty*> faculty;
    vector<Room*> rooms;

public:
    UniversitySystem();
    ~UniversitySystem();

    void loadAllData();
    void saveAllData();

    // FIXED: Added both const and non-const versions
    Course* getCourse(const string& code);
    Course* getCourse(const string& code) const;
    Student* getStudent(const string& id);
    const Student* getStudent(const string& id) const;
    Faculty* getFaculty(const string& id) const;
    Room* getRoom(const string& id) const;

    bool enrollStudent(string studentId, string courseCode, string& errorMsg);
    bool canStudentEnroll(string studentId, string courseCode, string& reason);

    void displaySystemInfo() const;
    void displayCoursesBySemester(int semester) const;
    void displayStudentInfo(string studentId) const;

    void demonstrateAllModules();

    int getCourseCount() const { return courses.size(); }
    int getStudentCount() const { return students.size(); }
    int getFacultyCount() const { return faculty.size(); }
    int getRoomCount() const { return rooms.size(); }

    Course* getCourseByIndex(int index) const {
        return (index >= 0 && index < courses.size()) ? courses[index] : nullptr;
    }
    Student* getStudentByIndex(int index) const {
        return (index >= 0 && index < students.size()) ? students[index] : nullptr;
    }
};

#endif