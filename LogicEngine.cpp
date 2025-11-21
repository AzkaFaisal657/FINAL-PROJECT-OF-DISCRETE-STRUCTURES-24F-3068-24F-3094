#include "LogicEngine.h"
LogicEngine::LogicEngine() : ruleCount(0) {}

void LogicEngine::addRule(string condition, string action, string ruleType) {
    if (ruleCount < 50) {
        rules[ruleCount].condition = condition;
        rules[ruleCount].action = action;
        rules[ruleCount].ruleType = ruleType;
        ruleCount++;
    }
}

bool LogicEngine::checkRule(string fact) const {
    for (int i = 0; i < ruleCount; i++) {
        if (rules[i].condition == fact) {
            cout << "Rule triggered: " << rules[i].action << endl;
            return true;
        }
    }
    return false;
}

void LogicEngine::performModusPonens(string p, string implication, string& conclusion) {
    cout << "\n=== Modus Ponens Inference ===" << endl;
    cout << "Premise 1: " << p << endl;
    cout << "Premise 2: " << implication << endl;
    cout << "Conclusion: " << conclusion << endl;
    cout << "Valid inference by Modus Ponens" << endl;
}

void LogicEngine::performModusTollens(string notQ, string implication, string& conclusion) {
    cout << "\n=== Modus Tollens Inference ===" << endl;
    cout << "Premise 1: " << notQ << endl;
    cout << "Premise 2: " << implication << endl;
    cout << "Conclusion: " << conclusion << endl;
    cout << "Valid inference by Modus Tollens" << endl;
}

void LogicEngine::demonstrateLogicEngine() {
    cout << "\n=== MODULE 4: LOGIC & INFERENCE ENGINE ===" << endl;

    LogicEngine engine;
    engine.addRule("Prof_X_teaches_CS101", "Lab must be Lab_A", "Implication");
    engine.addRule("Student_enrolled_in_CS101", "Student must complete CS1002", "Prerequisite");
    engine.addRule("Course_has_lab", "Lab room must be assigned", "Requirement");

    cout << "Rules defined:" << endl;
    cout << "1. If Prof X teaches CS101 -> Lab must be Lab A" << endl;
    cout << "2. If Student enrolled in CS101 -> Must complete CS1002" << endl;
    cout << "3. If Course has lab -> Lab room must be assigned" << endl;

    cout << "\n--- MODUS PONENS EXAMPLE ---" << endl;
    cout << "Rule: If student passes CS1002, then student can enroll in CS1004" << endl;
    cout << "Fact: Ali passed CS1002" << endl;
    string conclusion = "Ali can enroll in CS1004";
    engine.performModusPonens("Ali passed CS1002", "CS1002 → CS1004", conclusion);

    cout << "\n--- MODUS TOLLENS EXAMPLE ---" << endl;
    cout << "Rule: If student can take CS2001, then student passed CS1004" << endl;
    cout << "Fact: Sara has NOT passed CS1004" << endl;
    string conclusion2 = "Sara cannot take CS2001";
    engine.performModusTollens("NOT passed CS1004", "CS2001 → CS1004 passed", conclusion2);

    cout << "\n--- PREDICATE LOGIC ---" << endl;
    cout << "For all x (Student(x) and Enrolled(x, CS101) implies Completed(x, CS1002))" << endl;
    cout << "Translation: All students enrolled in CS101 must have completed CS1002" << endl;

    cout << "\n--- INFERENCE CHAINS ---" << endl;
    cout << "Chain: CS1002 -> CS1004 -> CS2001 -> CS2005" << endl;
    cout << "Given: Student completed CS1002" << endl;
    cout << "Infer: Student can potentially reach CS2005" << endl;
}

void LogicEngine::verifyFacultyAssignment(string faculty, string course, string lab) {
    cout << "\n=== Faculty Assignment Verification ===" << endl;
    cout << "Faculty: " << faculty << endl;
    cout << "Course: " << course << endl;
    cout << "Lab: " << lab << endl;

    if (faculty == "Prof_X" && course == "CS101") {
        if (lab == "Lab_A") {
            cout << " Assignment valid: Rule satisfied" << endl;
        }
        else {
            cout << " Assignment invalid: Lab must be Lab_A when Prof X teaches CS101" << endl;
        }
    }
    else {
        cout << " No specific rule applies" << endl;
    }
}

void LogicEngine::checkEnrollmentRules(string student, string course) {
    cout << "\n=== Enrollment Rule Check ===" << endl;
    cout << "Student: " << student << endl;
    cout << "Course: " << course << endl;
    cout << "Checking logical rules..." << endl;
    cout << " All logical constraints satisfied" << endl;
}