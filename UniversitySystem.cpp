#include "UniversitySystem.h"
#include <iostream>
using namespace std;

UniversitySystem::UniversitySystem() {}

UniversitySystem::~UniversitySystem() {
    for (Course* course : courses) delete course;
    for (Student* student : students) delete student;
    for (Faculty* fac : faculty) delete fac;
    for (Room* room : rooms) delete room;
}

void UniversitySystem::loadAllData() {
    // Load from files using FileHandler
    Course tempCourses[100];
    int courseCount = 0;
    FileHandler::loadCourses(tempCourses, courseCount);
    for (int i = 0; i < courseCount; i++) {
        courses.push_back(new Course(tempCourses[i]));
    }

    Student tempStudents[100];
    int studentCount = 0;
    FileHandler::loadStudents(tempStudents, studentCount);
    for (int i = 0; i < studentCount; i++) {
        students.push_back(new Student(tempStudents[i]));
    }

    Faculty tempFaculty[50];
    int facultyCount = 0;
    FileHandler::loadFaculty(tempFaculty, facultyCount);
    for (int i = 0; i < facultyCount; i++) {
        faculty.push_back(new Faculty(tempFaculty[i]));
    }

    Room tempRooms[50];
    int roomCount = 0;
    FileHandler::loadRooms(tempRooms, roomCount);
    for (int i = 0; i < roomCount; i++) {
        rooms.push_back(new Room(tempRooms[i]));
    }
}

// Implement other methods...