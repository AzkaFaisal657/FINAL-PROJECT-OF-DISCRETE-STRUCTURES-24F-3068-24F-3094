#pragma once
#include <vector>
#include <string>
#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include "Room.h"

class TestModule {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;
    std::vector<Faculty> allFaculty;
    std::vector<Room> allRooms;

public:
    TestModule(const std::vector<Student>& students, const std::vector<Course>& courses,
        const std::vector<Faculty>& faculty, const std::vector<Room>& rooms);

    void runAllTests();
    bool testStudentEnrollment();
    bool testCourseScheduling();
    bool testStudentGroups();
    bool testFacultyAssignments();
    bool testRoomAllocations();
    bool testSetOperations();
    bool testRelationsFunctions();
    bool testAutomatedProofs();

    void displayTestResults(bool result, const std::string& testName);
    void displayFinalSummary(int passed, int total);
};