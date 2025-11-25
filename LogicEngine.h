#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include "Course.h"
#include "Student.h"
#include "Faculty.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

class LogicEngine {
private:
    std::vector<Course> allCourses;
    std::vector<Student> allStudents;
    std::vector<Faculty> allFaculty;

    Faculty* findFacultyByName(const std::string& name);
    Course* findCourseByCode(const std::string& courseCode);
    Student* findStudentByRoll(const std::string& rollNumber);
    std::vector<std::string> tokenizeRule(const std::string& rule);
    bool evaluateExpression(const std::vector<std::string>& tokens);

    bool checkFacultyAssignment(const std::string& facultyName, const std::string& courseCode, const std::string& labRoom);
    bool checkPrerequisiteRule(const std::string& courseA, const std::string& courseB);
    bool checkCreditLimitRule(const Student& student, int maxCredits = 18);
    bool checkRoomCapacityRule(const std::string& courseCode, const std::string& roomId);

public:
    LogicEngine(const std::vector<Course>& courses, const std::vector<Student>& students, const std::vector<Faculty>& faculty);

    bool evaluateRule(const std::string& rule);
    void validateAllRules();

    // Propositional logic operations
    bool logicalAND(bool a, bool b);
    bool logicalOR(bool a, bool b);
    bool logicalIMPLIES(bool a, bool b);
    bool logicalNOT(bool a);
    bool logicalIFF(bool a, bool b);
};

#endif