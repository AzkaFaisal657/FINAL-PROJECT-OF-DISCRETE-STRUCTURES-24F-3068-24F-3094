#pragma once
#include <vector>
#include <string>
#include <map>
#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include "Room.h"

class ConflictDetector {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;
    std::vector<Faculty> allFaculty;
    std::vector<Room> allRooms;

public:
    ConflictDetector(const std::vector<Student>& students, const std::vector<Course>& courses,
        const std::vector<Faculty>& faculty, const std::vector<Room>& rooms);

    void checkAllConflicts();
    void checkPrerequisiteConflicts();
    void checkFacultyConflicts();
    void checkCreditLimitConflicts();
    void checkRoomConflicts();
    void generateDetailedReport();

    std::vector<std::string> getStudentsWithCreditOverload(int maxCredits = 18);
    std::vector<std::string> getStudentsWithMissingPrerequisites();
    std::vector<std::string> getFacultyWithOverload();

private:
    bool checkPrerequisiteForStudent(const Student& student, const std::string& courseCode);
    int getFacultyCourseCount(const std::string& facultyId);
};