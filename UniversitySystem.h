#pragma once
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

    Course* getCourse(string code);
    Student* getStudent(string id);
    Faculty* getFaculty(string id);
    Room* getRoom(string id);

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