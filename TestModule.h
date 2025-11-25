#ifndef TESTMODULE_H
#define TESTMODULE_H

#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include "Room.h"
#include "CourseScheduler.h"
#include "CombinationsModule.h"
#include "InductionModule.h"
#include "LogicEngine.h"
#include "SetOperations.h"
#include "RelationsModule.h"
#include "FunctionsModule.h"
#include "AutomatedProof.h"
#include "ConflictDetector.h"
#include "EfficiencyModule.h"
#include <vector>
#include <string>
#include <iostream>

class TestModule {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;
    std::vector<Faculty> allFaculty;
    std::vector<Room> allRooms;

    void displayTestResults(bool result, const std::string& testName);
    void displayFinalSummary(int passed, int total);

public:
    TestModule(const std::vector<Student>& students, const std::vector<Course>& courses,
        const std::vector<Faculty>& faculty, const std::vector<Room>& rooms);

    void runAllTests();

    // Individual test methods
    bool testStudentEnrollment();
    bool testCourseScheduling();
    bool testStudentGroups();
    bool testFacultyAssignments();
    bool testRoomAllocations();
    bool testSetOperations();
    bool testRelationsFunctions();
    bool testAutomatedProofs();
    bool testInductionModule();
    bool testLogicEngine();
    bool testConflictDetection();
    bool testEfficiencyBenchmarks();
};

#endif