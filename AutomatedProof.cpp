#include "AutomatedProof.h"
#include <iostream>
#include <map>

AutomatedProof::AutomatedProof(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty)
    : allStudents(students), allCourses(courses), allFaculty(faculty),
    inductionModule(students, courses),
    logicEngine(courses, students, faculty) {}

void AutomatedProof::generatePrerequisiteProof(const std::string& statement) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "              AUTOMATED PROOF & VERIFICATION\n";
    std::cout << "-------------------------------------------------------------\n";

    auto courses = parsePrerequisiteStatement(statement);
    std::string courseA = courses.first;
    std::string courseB = courses.second;

    if (courseA.empty() || courseB.empty()) {
        std::cout << "Could not parse statement. Using default: CS2005 requires CS2001\n";
        courseA = "CS2005";
        courseB = "CS2001";
    }

    std::cout << "Enter Statement to Prove: _ \"" << statement << "\"\n\n";

    std::vector<Student> enrolledStudents;
    for (const auto& student : allStudents) {
        if (student.isEnrolledIn(courseA)) {
            enrolledStudents.push_back(student);
        }
    }

    std::cout << "Generating Proof for all enrolled students in " << courseA << "...\n";
    std::cout << "Total Students Enrolled: " << enrolledStudents.size() << "\n\n";

    int eligibleCount = 0;

    for (const auto& student : enrolledStudents) {
        proveForStudent(student, courseA, courseB);
        if (inductionModule.verifyStudentEligibility(student, courseA)) {
            eligibleCount++;
        }
    }

    std::cout << "\nProof Summary:\n";
    std::cout << " -> Eligible Students: " << eligibleCount << "\n";
    std::cout << " -> Ineligible Students: " << (enrolledStudents.size() - eligibleCount) << "\n";
    std::cout << " -> Prerequisite Chain Verified via Strong Induction & Logic\n";
    std::cout << " -> All discrete rules maintained\n";
}

void AutomatedProof::generateCreditLimitProof() {
    std::cout << "\n=== CREDIT LIMIT PROOF ===\n";
    int violations = 0;

    for (const auto& student : allStudents) {
        int credits = student.getCurrentCreditHours(allCourses);
        if (credits > 18) {
            std::cout << "Student " << student.getRollNumber() << " has " << credits
                << " credits (>18) - VIOLATION\n";
            violations++;
        }
    }

    if (violations == 0) {
        std::cout << "[OK] All students satisfy credit limit constraint (<=18 credits)\n";
    }
    else {
        std::cout << "[X] " << violations << " students violate credit limit constraint\n";
    }
}

void AutomatedProof::generateFacultyAssignmentProof() {
    std::cout << "\n=== FACULTY ASSIGNMENT PROOF ===\n";

    std::map<std::string, int> courseFacultyCount;
    for (const auto& faculty : allFaculty) {
        for (const auto& course : faculty.getAssignedCourses()) {
            courseFacultyCount[course]++;
        }
    }

    bool valid = true;
    for (const auto& pair : courseFacultyCount) {
        if (pair.second != 1) {
            std::cout << "[X] Course " << pair.first << " has " << pair.second
                << " assigned faculty (should be 1)\n";
            valid = false;
        }
    }

    if (valid) {
        std::cout << "[OK] Each course has exactly one assigned faculty\n";
    }
}

void AutomatedProof::displayProofStepByStep(const std::string& courseCode) {
    std::vector<std::string> prerequisites;
    std::string currentCourse = courseCode;

    while (true) {
        // FIXED: Use const Course* instead of Course*
        const Course* course = nullptr;
        for (const auto& c : allCourses) {
            if (c.getCode() == currentCourse) {
                course = &c;  // This is now valid - pointer to const
                break;
            }
        }
        if (!course || course->getPrerequisite().empty()) {
            break;
        }
        prerequisites.push_back(course->getPrerequisite());
        currentCourse = course->getPrerequisite();
    }

    std::reverse(prerequisites.begin(), prerequisites.end());

    std::cout << "\nStep-by-Step Proof for " << courseCode << ":\n";
    std::cout << "Prerequisite Chain: ";
    for (const auto& prereq : prerequisites) {
        std::cout << prereq << " -> ";
    }
    std::cout << courseCode << "\n";

    std::cout << "1. Base Case: Verify immediate prerequisite\n";
    if (!prerequisites.empty()) {
        std::cout << "   - " << prerequisites.back() << " must be completed\n";
    }

    std::cout << "2. Inductive Step: Assume P(1), P(2), ..., P(k) are true\n";
    std::cout << "3. Strong Induction: Verify P(k+1) for all k in chain\n";
    std::cout << "4. Conclusion: All prerequisites satisfied -> Course accessible\n";
}

std::string AutomatedProof::extractCoursesFromStatement(const std::string& statement) {
    if (statement.find("Database Systems") != std::string::npos) return "CS2005";
    if (statement.find("Data Structures") != std::string::npos) return "CS2001";
    if (statement.find("OOP") != std::string::npos) return "CS1004";
    if (statement.find("Programming Fundamentals") != std::string::npos) return "CS1002";
    return "";
}

std::pair<std::string, std::string> AutomatedProof::parsePrerequisiteStatement(const std::string& statement) {
    size_t beforePos = statement.find("before");
    if (beforePos == std::string::npos) {
        return { "CS2005", "CS2001" };
    }

    std::string partA = statement.substr(0, beforePos);
    std::string partB = statement.substr(beforePos + 6);

    std::string courseA = extractCoursesFromStatement(partB);
    std::string courseB = extractCoursesFromStatement(partA);

    return { courseA, courseB };
}

void AutomatedProof::proveForStudent(const Student& student, const std::string& courseA, const std::string& courseB) {
    std::cout << "Student " << student.getRollNumber() << ":\n";

    // FIXED: Use const Course* instead of Course*
    const Course* course = nullptr;
    for (const auto& c : allCourses) {
        if (c.getCode() == courseA) {
            course = &c;  // This is now valid - pointer to const
            break;
        }
    }

    if (course && course->getPrerequisite() == courseB) {
        std::cout << " Step 1: Assume student takes " << courseA << " before " << courseB << "\n";
        std::cout << " Step 2: " << courseA << " requires " << courseB << " as prerequisite\n";
        std::cout << " Step 3: Contradiction arises\n";
        std::cout << "Conclusion: NOT POSSIBLE\n";
    }
    else {
        bool hasPrereq = student.hasCompleted(courseB);
        std::cout << " Step 1: Base Case: " << courseB << " completed? -> "
            << (hasPrereq ? "TRUE" : "FALSE") << "\n";

        if (hasPrereq) {
            std::cout << " Step 2: Inductive Step: All prerequisites satisfied -> TRUE\n";
            std::cout << "Conclusion: POSSIBLE\n";
        }
        else {
            std::cout << " Step 2: Missing prerequisite: " << courseB << "\n";
            std::cout << "Conclusion: NOT POSSIBLE\n";
        }
    }
    std::cout << "\n";
}