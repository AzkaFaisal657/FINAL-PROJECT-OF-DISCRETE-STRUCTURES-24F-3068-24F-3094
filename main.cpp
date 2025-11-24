#include <iostream>
#include <string>
#include <vector>
#include "UniversitySystem.h"
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
#include "TestModule.h"

using namespace std;

void displayHeader() {
    cout << "=============================================================\n";
    cout << "                   FAST-NUCES UNIDISC ENGINE\n";
    cout << "          Discrete Structures Computational Framework\n";
    cout << "                    Department: SOFTWARE ENGINEERING\n";
    cout << "=============================================================\n";
    cout << "        Modeling | Verification | Constraints | Consistency\n";
    cout << "=============================================================\n";
}

void displayMainMenu() {
    cout << "\n-------------------------------------------------------------\n";
    cout << "                    MAIN CONTROL INTERFACE\n";
    cout << "-------------------------------------------------------------\n";
    cout << "1. Course Scheduling Module\n";
    cout << "2. Manage Courses\n";
    cout << "3. Induction & Strong Induction Verification\n";
    cout << "4. Student Group Combination Generator\n";
    cout << "5. Logic & Inference Engine\n";
    cout << "6. Set Operations Center\n";
    cout << "7. Relations Analyzer\n";
    cout << "8. Functions & Mappings Module\n";
    cout << "9. Automated Proof Generator\n";
    cout << "10. Global Consistency Checker\n";
    cout << "11. Efficiency & Benchmarking Panel\n";
    cout << "12. Unit Testing & Benchmarking\n";
    cout << "13. Exit System\n";
    cout << "\n>> Enter choice: ";
}
void runCourseSchedulingModule(UniversitySystem& system) {
    cout << "\n-------------------------------------------------------------\n";
    cout << "               COURSE SCHEDULING MODULE\n";
    cout << "-------------------------------------------------------------\n";

    CourseScheduler scheduler(system.getCourses(), system.getStudents());

    int choice;
    cout << "1. Generate Valid Course Sequences\n";
    cout << "2. Get Recommended Schedule for Student\n";
    cout << "3. Check Prerequisite Order\n";
    cout << "4. Back to Main Menu\n";
    cout << "\n>> Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int maxCourses;
        cout << "Enter maximum courses per semester (default 5): ";
        cin >> maxCourses;
        if (maxCourses <= 0) maxCourses = 5;

        auto sequences = scheduler.generateValidSequences(maxCourses);
        scheduler.displayAllSequences(sequences);
    }
    else if (choice == 2) {
        string rollNumber;
        int targetSemester;

        cout << "Enter Student Roll Number: _ ";
        cin >> rollNumber;
        cout << "Enter Target Semester: ";
        cin >> targetSemester;

        Student* student = system.findStudent(rollNumber);
        if (student) {
            auto recommended = scheduler.getRecommendedSchedule(*student, targetSemester);
            cout << "\nRecommended courses for " << rollNumber << " in Semester " << targetSemester << ":\n";
            for (const auto& course : recommended) {
                cout << " -> " << course << "\n";
            }
        }
        else {
            cout << "Student not found!\n";
        }
    }
    else if (choice == 3) {
        vector<string> sequence;
        string courseCode;
        char more = 'Y';

        cout << "Enter course sequence to check (enter 'done' when finished):\n";
        while (more == 'Y' || more == 'y') {
            cout << "Course code: ";
            cin >> courseCode;
            if (courseCode == "done") break;
            sequence.push_back(courseCode);
        }

        bool valid = scheduler.checkPrerequisiteOrder(sequence);
        cout << "Prerequisite order is " << (valid ? "VALID [OK]" : "INVALID [X]") << "\n";
    }
}

void runInductionModule(UniversitySystem& system) {
    cout << "\n-------------------------------------------------------------\n";
    cout << "         INDUCTION & STRONG INDUCTION VERIFIER\n";
    cout << "-------------------------------------------------------------\n";

    string courseCode;
    cout << "Enter Course Code to Verify Prerequisites: _ ";
    cin >> courseCode;

    InductionModule induction(system.getStudents(), system.getCourses());
    auto results = induction.verifyAllStudentsForCourse(courseCode);
    induction.displayVerificationResults(results, courseCode);
}

void runGroupCombinationModule(UniversitySystem& system) {
    cout << "\n-------------------------------------------------------------\n";
    cout << "         STUDENT GROUP COMBINATION MODULE (COURSE-AWARE)\n";
    cout << "-------------------------------------------------------------\n";

    string courseCode;
    int groupSize;
    char generateSample;

    cout << "Enter Course Code to Generate Groups: _ ";
    cin >> courseCode;

    CombinationsModule combModule(system.getStudents(), system.getCourses());
    auto enrolledStudents = combModule.getStudentsEnrolledInCourse(courseCode);
    cout << "Fetching students currently enrolled in " << courseCode << "...\n";
    cout << " -> Total Students Enrolled: " << enrolledStudents.size() << "\n";

    cout << "Enter desired group size: ";
    cin >> groupSize;

    long long totalCombinations = combModule.calculateCombinations(enrolledStudents.size(), groupSize);
    cout << "Computing combinations: C(" << enrolledStudents.size() << "," << groupSize << ")\n";
    cout << " -> Total Possible Unique Groups = " << totalCombinations << "\n";

    cout << "Generate sample groups? (Y/N): ";
    cin >> generateSample;

    if (generateSample == 'Y' || generateSample == 'y') {
        auto groups = combModule.generateStudentGroups(courseCode, groupSize);
        combModule.displayGroups(groups, "SAMPLE");
    }

    cout << "Group Generation Completed.\n";
    cout << "Each group respects current course enrollment.\n";
}

void runLogicEngine(UniversitySystem& system) {
    cout << "\n-------------------------------------------------------------\n";
    cout << "                    LOGIC & INFERENCE ENGINE\n";
    cout << "-------------------------------------------------------------\n";

    LogicEngine logic(system.getCourses(), system.getStudents(), system.getFaculty());

    string rule;
    cout << "Enter Rule to Verify: _ ";
    cin.ignore();
    getline(cin, rule);

    bool isValid = logic.evaluateRule(rule);
    cout << "\nRule Status: " << (isValid ? "VALID [OK]" : "INVALID [X]") << "\n";
    cout << "Logical Inference: " << (isValid ? "Satisfied for all enrolled students" : "Rule violation detected") << "\n";

    char another;
    cout << "\nDo you want to check another rule? (Y/N): ";
    cin >> another;

    if (another == 'Y' || another == 'y') {
        runLogicEngine(system);
    }
}

void runSetOperations(UniversitySystem& system) {
    cout << "\n-------------------------------------------------------------\n";
    cout << "                    SET OPERATIONS CENTER\n";
    cout << "-------------------------------------------------------------\n";

    SetOperations setOps(system.getStudents(), system.getCourses(), system.getFaculty());

    int choice;
    cout << "1. Students enrolled in multiple courses\n";
    cout << "2. Students only in one course but not another\n";
    cout << "3. Power set of lab groups for a course\n";
    cout << "4. Intersection of faculty teaching sets\n";
    cout << "5. Back to Main Menu\n";
    cout << "\n>> Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        string courseA, courseB;
        cout << "Enter First Course Code: _ ";
        cin >> courseA;
        cout << "Enter Second Course Code: _ ";
        cin >> courseB;

        auto intersection = setOps.getStudentsInBothCourses(courseA, courseB);
        cout << "Computing Intersection of enrolled students...\n";
        cout << " -> Students in both " << courseA << " & " << courseB << ": " << intersection.size() << "\n";

        cout << "Sample:\n {";
        for (size_t i = 0; i < min(intersection.size(), size_t(7)); ++i) {
            cout << intersection[i];
            if (i < min(intersection.size(), size_t(7)) - 1) cout << ", ";
        }
        cout << "}\n";

        cout << "Intersection operation completed successfully.\n";
    }
}

void runRelationsModule(UniversitySystem& system) {
    RelationsModule relations(system.getStudents(), system.getCourses(), system.getFaculty());

    int choice;
    cout << "\nSelect Relation to Analyze:\n";
    cout << "1. Student -> Courses\n";
    cout << "2. Course -> Faculty\n";
    cout << "3. Student -> Faculty\n";
    cout << "4. Back\n";
    cout << "\n>> Choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        relations.analyzeStudentCourseRelation();
        break;
    case 2:
        relations.analyzeCourseFacultyRelation();
        break;
    case 3:
        relations.analyzeStudentFacultyRelation();
        break;
    case 4:
        return;
    default:
        cout << "Invalid choice!\n";
    }
}

void runFunctionsModule(UniversitySystem& system) {
    FunctionsModule functions(system.getCourses(), system.getStudents(), system.getFaculty());

    int choice;
    cout << "\nSelect Mapping:\n";
    cout << "1. Course -> Faculty\n";
    cout << "2. Faculty -> Course (Inverse)\n";
    cout << "3. Student -> Course Load\n";
    cout << "4. Back\n";
    cout << "\n>> Choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        functions.analyzeCourseToFaculty();
        break;
    case 2:
        functions.analyzeFacultyToCourse();
        break;
    case 3:
        functions.analyzeStudentToCourseLoad();
        break;
    case 4:
        return;
    default:
        cout << "Invalid choice!\n";
    }
}

void runAutomatedProof(UniversitySystem& system) {
    AutomatedProof proof(system.getStudents(), system.getCourses(), system.getFaculty());

    string statement;
    cout << "Enter Statement to Prove: _ ";
    cin.ignore();
    getline(cin, statement);

    if (statement.empty()) {
        statement = "No student can take Database Systems before completing Data Structures";
    }

    proof.generatePrerequisiteProof(statement);
}

void runConsistencyChecker(UniversitySystem& system) {
    ConflictDetector detector(system.getStudents(), system.getCourses(), system.getFaculty(), system.getRooms());
    detector.checkAllConflicts();
}

void runEfficiencyModule(UniversitySystem& system) {
    EfficiencyModule efficiency(system.getStudents(), system.getCourses());

    int choice;
    cout << "\nSelect Operation:\n";
    cout << "1. Benchmark Algorithm Performance\n";
    cout << "2. Run Unit Tests for Modules\n";
    cout << "3. Back to Main Menu\n";
    cout << "\n>> Choice: ";
    cin >> choice;

    if (choice == 1) {
        efficiency.benchmarkAllAlgorithms();
    }
}

void runUnitTesting(UniversitySystem& system) {
    TestModule tester(system.getStudents(), system.getCourses(), system.getFaculty(), system.getRooms());

    int choice;
    cout << "\nSelect Test Type:\n";
    cout << "1. Test Student Enrollment & Eligibility\n";
    cout << "2. Test Course Scheduling & Prerequisites\n";
    cout << "3. Test Student Group Combinations\n";
    cout << "4. Test Faculty Assignments\n";
    cout << "5. Test Room Allocations & Capacity\n";
    cout << "6. Test Set Operations\n";
    cout << "7. Test Relations & Functions\n";
    cout << "8. Run All Tests\n";
    cout << "9. Back to Main Menu\n";
    cout << "\n>> Choice: ";
    cin >> choice;

    if (choice == 8) {
        tester.runAllTests();
    }
}

int main() {
    UniversitySystem system;

    displayHeader();
    cout << "\n[Loaded Dataset]\n";
    cout << " -> Courses Loaded: " << system.getCourses().size() << " (SE Department Core + Electives)\n";
    cout << " -> Students Loaded: " << system.getStudents().size() << " (SE Department)\n";
    cout << " -> Faculty Loaded: " << system.getFaculty().size() << "\n";
    cout << " -> Prerequisites Initialized\n";
    cout << " -> Induction & Logic Engine Online\n";
    cout << " -> Consistency Checker: ACTIVE\n";
    cout << " -> Student-Course Relations Verified\n";

    while (true) {
        displayMainMenu();

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            runCourseSchedulingModule(system);
            break;
        case 2:
            system.displayAllCourses();
            break;
        case 3:
            runInductionModule(system);
            break;
        case 4:
            runGroupCombinationModule(system);
            break;
        case 5:
            runLogicEngine(system);
            break;
        case 6:
            runSetOperations(system);
            break;
        case 7:
            runRelationsModule(system);
            break;
        case 8:
            runFunctionsModule(system);
            break;
        case 9:
            runAutomatedProof(system);
            break;
        case 10:
            runConsistencyChecker(system);
            break;
        case 11:
            runEfficiencyModule(system);
            break;
        case 12:
            runUnitTesting(system);
            break;
        case 13:
            cout << "\nThank you for using UNIDISC ENGINE!\n";
            cout << "System shutdown completed.\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}