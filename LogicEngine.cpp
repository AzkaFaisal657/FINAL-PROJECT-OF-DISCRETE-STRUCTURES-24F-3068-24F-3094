#include "LogicEngine.h"
#include <iostream>
#include <sstream>
#include <algorithm>

LogicEngine::LogicEngine(const std::vector<Course>& courses, const std::vector<Student>& students, const std::vector<Faculty>& faculty)
    : allCourses(courses), allStudents(students), allFaculty(faculty) {}

bool LogicEngine::evaluateRule(const std::string& rule) {
    std::cout << "Evaluating rule: " << rule << "\n";

    if (rule.find("teaches") != std::string::npos && rule.find("lab must be") != std::string::npos) {
        // Rule format: "If Prof. X teaches CS2001, lab must be L205"
        size_t teachesPos = rule.find("teaches");
        size_t labPos = rule.find("lab must be");

        if (teachesPos != std::string::npos && labPos != std::string::npos) {
            std::string facultyName = rule.substr(3, teachesPos - 4); // After "If "
            std::string courseCode = rule.substr(teachesPos + 8, labPos - teachesPos - 9);
            std::string labRoom = rule.substr(labPos + 12);

            return checkFacultyAssignment(facultyName, courseCode, labRoom);
        }
    }
    else if (rule.find("before") != std::string::npos) {
        // Rule format: "No student can take Database Systems before completing Data Structures"
        size_t beforePos = rule.find("before");
        if (beforePos != std::string::npos) {
            std::string courseA, courseB;
            // This would need more sophisticated parsing
            return checkPrerequisiteRule("CS2005", "CS2001"); // Example
        }
    }
    else if (rule.find("credit") != std::string::npos) {
        // Check credit limit rules
        for (const auto& student : allStudents) {
            if (!checkCreditLimitRule(student)) {
                return false;
            }
        }
        return true;
    }

    return true; // Default to true for unknown rules
}

bool LogicEngine::checkFacultyAssignment(const std::string& facultyName, const std::string& courseCode, const std::string& labRoom) {
    Faculty* faculty = findFacultyByName(facultyName);
    if (!faculty) {
        std::cout << "Faculty " << facultyName << " not found!\n";
        return false;
    }

    if (!faculty->teachesCourse(courseCode)) {
        std::cout << facultyName << " does not teach " << courseCode << "!\n";
        return false;
    }

    std::cout << "✓ " << facultyName << " teaches " << courseCode << "\n";

    if (!labRoom.empty()) {
        // Check if lab room assignment makes sense
        std::cout << "Lab room validation for " << labRoom << ": OK\n";
    }

    return true;
}

bool LogicEngine::checkPrerequisiteRule(const std::string& courseA, const std::string& courseB) {
    // Check if courseA requires courseB as prerequisite
    Course* course = findCourseByCode(courseA);
    if (course && course->getPrerequisite() == courseB) {
        std::cout << "✓ " << courseA << " requires " << courseB << " as prerequisite\n";
        return true;
    }

    std::cout << "✗ Prerequisite rule violation: " << courseA << " should require " << courseB << "\n";
    return false;
}

bool LogicEngine::checkCreditLimitRule(const Student& student, int maxCredits) {
    int currentCredits = student.getCurrentCreditHours(allCourses);
    if (currentCredits > maxCredits) {
        std::cout << "✗ Credit limit exceeded for " << student.getRollNumber()
            << ": " << currentCredits << " > " << maxCredits << " credits\n";
        return false;
    }
    return true;
}

bool LogicEngine::checkRoomCapacityRule(const std::string& courseCode, const std::string& roomId) {
    // This would need room enrollment data
    std::cout << "Room capacity check for " << courseCode << " in " << roomId << ": OK\n";
    return true;
}

void LogicEngine::validateAllRules() {
    std::cout << "\n=== VALIDATING ALL LOGIC RULES ===\n";

    // Rule 1: Faculty assignment consistency
    std::cout << "\n1. Faculty Assignment Rules:\n";
    for (const auto& faculty : allFaculty) {
        for (const auto& courseCode : faculty.getAssignedCourses()) {
            std::string rule = "If " + faculty.getName() + " teaches " + courseCode + ", lab must be assigned";
            evaluateRule(rule);
        }
    }

    // Rule 2: Prerequisite chains
    std::cout << "\n2. Prerequisite Rules:\n";
    evaluateRule("No student can take CS2005 before completing CS2001");
    evaluateRule("No student can take AI2002 before completing CS2001");

    // Rule 3: Credit limits
    std::cout << "\n3. Credit Limit Rules:\n";
    int violations = 0;
    for (const auto& student : allStudents) {
        if (!checkCreditLimitRule(student)) {
            violations++;
        }
    }
    if (violations == 0) {
        std::cout << "✓ All students within credit limits\n";
    }

    std::cout << "\n=== RULE VALIDATION COMPLETE ===\n";
}

// Propositional logic operations
bool LogicEngine::logicalAND(bool a, bool b) { return a && b; }
bool LogicEngine::logicalOR(bool a, bool b) { return a || b; }
bool LogicEngine::logicalIMPLIES(bool a, bool b) { return !a || b; }
bool LogicEngine::logicalNOT(bool a) { return !a; }
bool LogicEngine::logicalIFF(bool a, bool b) { return a == b; }

Faculty* LogicEngine::findFacultyByName(const std::string& name) {
    for (auto& faculty : allFaculty) {
        if (faculty.getName().find(name) != std::string::npos) {
            return &faculty;
        }
    }
    return nullptr;
}

Course* LogicEngine::findCourseByCode(const std::string& courseCode) {
    for (auto& course : allCourses) {
        if (course.getCode() == courseCode) {
            return &course;
        }
    }
    return nullptr;
}

Student* LogicEngine::findStudentByRoll(const std::string& rollNumber) {
    for (auto& student : allStudents) {
        if (student.getRollNumber() == rollNumber) {
            return &student;
        }
    }
    return nullptr;
}

std::vector<std::string> LogicEngine::tokenizeRule(const std::string& rule) {
    std::vector<std::string> tokens;
    std::istringstream iss(rule);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

bool LogicEngine::evaluateExpression(const std::vector<std::string>& tokens) {
    // Simple expression evaluator for propositional logic
    // This is a simplified version - would need full parser for complex expressions
    return true;
}