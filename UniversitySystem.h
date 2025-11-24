#pragma once
#include <vector>
#include <string>
#include "Course.h"
#include "Student.h"
#include "Faculty.h"
#include "Room.h"
#include "FileHandler.h"

class UniversitySystem {
private:
    std::vector<Course> courses;
    std::vector<Student> students;
    std::vector<Faculty> faculty;
    std::vector<Room> rooms;

    std::string coursesFile = "courses.txt";
    std::string studentsFile = "students.txt";
    std::string facultyFile = "faculty.txt";
    std::string roomsFile = "rooms.txt";

public:
    UniversitySystem();
    ~UniversitySystem();

    void loadAllData();
    void saveAllData();

    // Getters
    std::vector<Course>& getCourses();
    std::vector<Student>& getStudents();
    std::vector<Faculty>& getFaculty();
    std::vector<Room>& getRooms();

    // Utility methods
    Course* findCourse(const std::string& courseCode);
    Student* findStudent(const std::string& rollNumber);
    Faculty* findFaculty(const std::string& facultyId);
    Room* findRoom(const std::string& roomId);

    std::vector<Student> getStudentsEnrolledInCourse(const std::string& courseCode);
    std::vector<std::string> getPrerequisiteChain(const std::string& courseCode);
    bool checkPrerequisiteSatisfaction(const Student& student, const std::string& courseCode);

    void displayAllStudents() const;
    void displayAllCourses() const;
    void displayAllFaculty() const;
    void displayAllRooms() const;
};