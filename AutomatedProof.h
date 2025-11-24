#pragma once
#include <vector>
#include <string>
#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include "InductionModule.h"
#include "LogicEngine.h"

class AutomatedProof {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;
    std::vector<Faculty> allFaculty;
    InductionModule inductionModule;
    LogicEngine logicEngine;

public:
    AutomatedProof(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty);

    void generatePrerequisiteProof(const std::string& statement);
    void generateCreditLimitProof();
    void generateFacultyAssignmentProof();
    void displayProofStepByStep(const std::string& courseCode);

private:
    std::string extractCoursesFromStatement(const std::string& statement);
    std::pair<std::string, std::string> parsePrerequisiteStatement(const std::string& statement);
    void proveForStudent(const Student& student, const std::string& courseA, const std::string& courseB);
};