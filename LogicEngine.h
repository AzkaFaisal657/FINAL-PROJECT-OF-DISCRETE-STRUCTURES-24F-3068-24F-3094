#pragma once
#include <string>
#include <iostream>
using namespace std;

struct LogicalRule {
    string condition;
    string action;
    string ruleType;
};

class LogicEngine {
private:
    LogicalRule rules[50];
    int ruleCount;

public:
    LogicEngine();
    void addRule(string condition, string action, string ruleType);
    bool checkRule(string fact) const;
    void performModusPonens(string p, string implication, string& conclusion);
    void performModusTollens(string notQ, string implication, string& conclusion);
    void demonstrateLogicEngine();
    void verifyFacultyAssignment(string faculty, string course, string lab);
    void checkEnrollmentRules(string student, string course);
};
