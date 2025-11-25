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

// Note: GUI.h is commented out as it may not be available
// #include "GUI.h"

void displayHeader() {
    std::cout << "=============================================================\n";
    std::cout << "                   FAST-NUCES UNIDISC ENGINE\n";
    std::cout << "          Discrete Structures Computational Framework\n";
    std::cout << "                    Department: SOFTWARE ENGINEERING\n";
    std::cout << "=============================================================\n";
    std::cout << "        Modeling | Verification | Constraints | Consistency\n";
    std::cout << "=============================================================\n";
}

void displayMainMenu() {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "                    MAIN CONTROL INTERFACE\n";
    std::cout << "-------------------------------------------------------------\n";
    std::cout << "1. Course Scheduling Module\n";
    std::cout << "2. Manage Courses\n";
    std::cout << "3. Induction & Strong Induction Verification\n";
    std::cout << "4. Student Group Combination Generator\n";
    std::cout << "5. Logic & Inference Engine\n";
    std::cout << "6. Set Operations Center\n";
    std::cout << "7. Relations Analyzer\n";
    std::cout << "8. Functions & Mappings Module\n";
    std::cout << "9. Automated Proof Generator\n";
    std::cout << "10. Global Consistency Checker\n";
    std::cout << "11. Efficiency & Benchmarking Panel\n";
    std::cout << "12. Unit Testing & Benchmarking\n";
    std::cout << "13. Exit System\n";
    std::cout << "\n>> Enter choice: ";
}

void runCourseSchedulingModule(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "               COURSE SCHEDULING MODULE\n";
    std::cout << "-------------------------------------------------------------\n";

    CourseScheduler scheduler(system.getCourses(), system.getStudents());

    int choice;
    std::cout << "1. Generate Valid Course Sequences\n";
    std::cout << "2. Get Recommended Schedule for Student\n";
    std::cout << "3. Check Prerequisite Order\n";
    std::cout << "4. Back to Main Menu\n";
    std::cout << "\n>> Enter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        int maxCourses;
        std::cout << "Enter maximum courses per semester (default 5): ";
        std::cin >> maxCourses;
        if (maxCourses <= 0) maxCourses = 5;

        auto sequences = scheduler.generateValidSequences(maxCourses);
        scheduler.displayAllSequences(sequences);
    }
    else if (choice == 2) {
        std::string rollNumber;
        int targetSemester;

        std::cout << "Enter Student Roll Number: ";
        std::cin >> rollNumber;
        std::cout << "Enter Target Semester: ";
        std::cin >> targetSemester;

        Student* student = system.findStudent(rollNumber);
        if (student) {
            auto recommended = scheduler.getRecommendedSchedule(*student, targetSemester);
            std::cout << "\nRecommended courses for " << rollNumber << " in Semester " << targetSemester << ":\n";
            if (recommended.empty()) {
                std::cout << "No recommended courses found. Student may have completed all courses for this semester.\n";
            }
            else {
                for (const auto& course : recommended) {
                    std::cout << " - > " << course << "\n";
                }
            }
        }
        else {
            std::cout << "Student not found! Available students start with Roll-001 to Roll-"
                << (system.getStudents().size() < 10 ? "00" : (system.getStudents().size() < 100 ? "0" : ""))
                << system.getStudents().size() << "\n";
        }
    }
    else if (choice == 3) {
        std::vector<std::string> sequence;
        std::string courseCode;
        char more = 'Y';

        std::cout << "Enter course sequence to check (enter 'done' when finished):\n";
        while (more == 'Y' || more == 'y') {
            std::cout << "Course code: ";
            std::cin >> courseCode;
            if (courseCode == "done") break;
            sequence.push_back(courseCode);

            std::cout << "Add another course? (Y/N): ";
            std::cin >> more;
        }

        if (!sequence.empty()) {
            bool valid = scheduler.checkPrerequisiteOrder(sequence);
            std::cout << "Prerequisite order is " << (valid ? "VALID " : "INVALID ") << "\n";
        }
        else {
            std::cout << "No courses entered.\n";
        }
    }
}

void runInductionModule(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "         INDUCTION & STRONG INDUCTION VERIFIER\n";
    std::cout << "-------------------------------------------------------------\n";

    std::string courseCode;
    std::cout << "Enter Course Code to Verify Prerequisites: ";
    std::cin >> courseCode;

    InductionModule induction(system.getStudents(), system.getCourses());
    auto results = induction.verifyAllStudentsForCourse(courseCode);
    induction.displayVerificationResults(results, courseCode);
}

void runGroupCombinationModule(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "         STUDENT GROUP COMBINATION MODULE (COURSE-AWARE)\n";
    std::cout << "-------------------------------------------------------------\n";

    std::string courseCode;
    int groupSize;
    char generateSample;

    std::cout << "Enter Course Code to Generate Groups: ";
    std::cin >> courseCode;

    CombinationsModule combModule(system.getStudents(), system.getCourses());
    auto enrolledStudents = combModule.getStudentsEnrolledInCourse(courseCode);
    std::cout << "Fetching students currently enrolled in " << courseCode << "...\n";
    std::cout << " -> Total Students Enrolled: " << enrolledStudents.size() << "\n";

    if (enrolledStudents.empty()) {
        std::cout << "No students enrolled in " << courseCode << ". Try CS2001, CS1002, etc.\n";
        return;
    }

    std::cout << "Enter desired group size: ";
    std::cin >> groupSize;

    if (groupSize <= 0 || groupSize > enrolledStudents.size()) {
        std::cout << "Invalid group size! Must be between 1 and " << enrolledStudents.size() << "\n";
        return;
    }

    long long totalCombinations = combModule.calculateCombinations(enrolledStudents.size(), groupSize);
    std::cout << "Computing combinations: C(" << enrolledStudents.size() << "," << groupSize << ")\n";
    std::cout << " -> Total Possible Unique Groups = " << totalCombinations << "\n";

    if (totalCombinations > 1000000) {
        std::cout << " -> Large combination detected, will generate samples\n";
    }

    std::cout << "Generate sample groups? (Y/N): ";
    std::cin >> generateSample;

    if (generateSample == 'Y' || generateSample == 'y') {
        auto groups = combModule.generateStudentGroups(courseCode, groupSize);
        combModule.displayGroups(groups, "SAMPLE");
    }

    std::cout << "Group Generation Completed.\n";
    std::cout << "Each group respects current course enrollment.\n";
}

void runLogicEngine(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "                    LOGIC & INFERENCE ENGINE\n";
    std::cout << "-------------------------------------------------------------\n";

    LogicEngine logic(system.getCourses(), system.getStudents(), system.getFaculty());

    int choice;
    std::cout << "1. Evaluate Single Rule\n";
    std::cout << "2. Validate All System Rules\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << "\n>> Enter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::string rule;
        std::cout << "Enter Rule to Verify: ";
        std::cin.ignore();
        std::getline(std::cin, rule);

        if (rule.empty()) {
            rule = "If Dr. Ahmed teaches CS2001, lab must be L201";
            std::cout << "Using default rule: " << rule << "\n";
        }

        bool isValid = logic.evaluateRule(rule);
        std::cout << "\nRule Status: " << (isValid ? "VALID ?" : "INVALID ?") << "\n";
    }
    else if (choice == 2) {
        logic.validateAllRules();
    }
}

void runSetOperations(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "                    SET OPERATIONS CENTER\n";
    std::cout << "-------------------------------------------------------------\n";

    SetOperations setOps(system.getStudents(), system.getCourses(), system.getFaculty());

    int choice;
    std::cout << "1. Students enrolled in multiple courses\n";
    std::cout << "2. Students only in one course but not another\n";
    std::cout << "3. Power set of lab groups for a course\n";
    std::cout << "4. Intersection of faculty teaching sets\n";
    std::cout << "5. Back to Main Menu\n";
    std::cout << "\n>> Enter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::string courseA, courseB;
        std::cout << "Enter First Course Code: ";
        std::cin >> courseA;
        std::cout << "Enter Second Course Code: ";
        std::cin >> courseB;

        auto intersection = setOps.getStudentsInBothCourses(courseA, courseB);
        std::cout << "Computing Intersection of enrolled students...\n";
        std::cout << " -> Students in both " << courseA << " & " << courseB << ": " << intersection.size() << "\n";

        if (!intersection.empty()) {
            std::cout << "Sample students:\n {";
            for (size_t i = 0; i < std::min(intersection.size(), size_t(7)); ++i) {
                std::cout << intersection[i];
                if (i < std::min(intersection.size(), size_t(7)) - 1) std::cout << ", ";
            }
            std::cout << "}\n";
        }

        std::cout << "Intersection operation completed successfully.\n";
    }
    else if (choice == 2) {
        std::string courseA, courseB;
        std::cout << "Enter First Course Code: ";
        std::cin >> courseA;
        std::cout << "Enter Second Course Code: ";
        std::cin >> courseB;

        auto difference = setOps.getStudentsOnlyInFirstCourse(courseA, courseB);
        std::cout << "Students only in " << courseA << " but not " << courseB << ": " << difference.size() << "\n";
    }
    else if (choice == 3) {
        std::string courseCode;
        int maxGroupSize;
        std::cout << "Enter Course Code for lab groups: ";
        std::cin >> courseCode;
        std::cout << "Enter maximum group size: ";
        std::cin >> maxGroupSize;

        auto groups = setOps.generateLabGroupCombinations(courseCode, maxGroupSize);
        std::cout << "Generated " << groups.size() << " valid lab groups\n";
    }
    else if (choice == 4) {
        std::string facultyA, facultyB;
        std::cout << "Enter First Faculty ID: ";
        std::cin >> facultyA;
        std::cout << "Enter Second Faculty ID: ";
        std::cin >> facultyB;

        auto commonCourses = setOps.getCommonCourses(facultyA, facultyB);
        std::cout << "Common courses taught by both faculty: " << commonCourses.size() << "\n";
    }
}

void runRelationsModule(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "                    RELATIONS ANALYZER\n";
    std::cout << "-------------------------------------------------------------\n";

    RelationsModule relations(system.getStudents(), system.getCourses(), system.getFaculty());

    int choice;
    std::cout << "\nSelect Relation to Analyze:\n";
    std::cout << "1. Student -> Courses\n";
    std::cout << "2. Course -> Faculty\n";
    std::cout << "3. Student -> Faculty\n";
    std::cout << "4. Analyze All Relations\n";
    std::cout << "5. Back\n";
    std::cout << "\n>> Choice: ";
    std::cin >> choice;

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
        relations.analyzeAllRelations();
        break;
    case 5:
        return;
    default:
        std::cout << "Invalid choice!\n";
    }
}

void runFunctionsModule(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "                FUNCTIONS & MAPPINGS MODULE\n";
    std::cout << "-------------------------------------------------------------\n";

    FunctionsModule functions(system.getCourses(), system.getStudents(), system.getFaculty());

    int choice;
    std::cout << "\nSelect Mapping:\n";
    std::cout << "1. Course -> Faculty\n";
    std::cout << "2. Faculty -> Course (Inverse)\n";
    std::cout << "3. Student -> Course Load\n";
    std::cout << "4. Analyze All Mappings\n";
    std::cout << "5. Back\n";
    std::cout << "\n>> Choice: ";
    std::cin >> choice;

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
        functions.analyzeAllMappings();
        break;
    case 5:
        return;
    default:
        std::cout << "Invalid choice!\n";
    }
}

void runAutomatedProof(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "              AUTOMATED PROOF GENERATOR\n";
    std::cout << "-------------------------------------------------------------\n";

    AutomatedProof proof(system.getStudents(), system.getCourses(), system.getFaculty());

    int choice;
    std::cout << "1. Generate Prerequisite Proof\n";
    std::cout << "2. Generate Credit Limit Proof\n";
    std::cout << "3. Generate Faculty Assignment Proof\n";
    std::cout << "4. Generate All Proofs\n";
    std::cout << "5. Back\n";
    std::cout << "\n>> Choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::string statement;
        std::cout << "Enter Statement to Prove: ";
        std::cin.ignore();
        std::getline(std::cin, statement);

        if (statement.empty()) {
            statement = "Database Systems requires Data Structures";
        }
        proof.generatePrerequisiteProof(statement);
    }
    else if (choice == 2) {
        proof.generateCreditLimitProof();
    }
    else if (choice == 3) {
        proof.generateFacultyAssignmentProof();
    }
    else if (choice == 4) {
        proof.generateAllProofs();
    }
}

void runConsistencyChecker(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "               GLOBAL CONSISTENCY CHECKER\n";
    std::cout << "-------------------------------------------------------------\n";

    ConflictDetector detector(system.getStudents(), system.getCourses(), system.getFaculty(), system.getRooms());

    int choice;
    std::cout << "1. Run All Conflict Checks\n";
    std::cout << "2. Generate Detailed Report\n";
    std::cout << "3. Back\n";
    std::cout << "\n>> Choice: ";
    std::cin >> choice;

    if (choice == 1) {
        detector.checkAllConflicts();
    }
    else if (choice == 2) {
        detector.generateDetailedReport();
    }
}

void runEfficiencyModule(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "          EFFICIENCY & BENCHMARKING PANEL\n";
    std::cout << "-------------------------------------------------------------\n";

    EfficiencyModule efficiency(system.getStudents(), system.getCourses());

    int choice;
    std::cout << "\nSelect Operation:\n";
    std::cout << "1. Benchmark Algorithm Performance\n";
    std::cout << "2. Display Complexity Analysis\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << "\n>> Choice: ";
    std::cin >> choice;

    if (choice == 1) {
        efficiency.benchmarkAllAlgorithms();
    }
    else if (choice == 2) {
        efficiency.displayComplexityAnalysis();
    }
}

void runUnitTesting(UniversitySystem& system) {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "          UNIT TESTING & BENCHMARKING\n";
    std::cout << "-------------------------------------------------------------\n";

    TestModule tester(system.getStudents(), system.getCourses(), system.getFaculty(), system.getRooms());

    int choice;
    std::cout << "\nSelect Test Type:\n";
    std::cout << "1. Run All Tests\n";
    std::cout << "2. Test Student Enrollment\n";
    std::cout << "3. Test Course Scheduling\n";
    std::cout << "4. Test Student Groups\n";
    std::cout << "5. Test Faculty Assignments\n";
    std::cout << "6. Back to Main Menu\n";
    std::cout << "\n>> Choice: ";
    std::cin >> choice;

    if (choice == 1) {
        tester.runAllTests();
    }
    else if (choice == 2) {
        tester.testStudentEnrollment();
    }
    else if (choice == 3) {
        tester.testCourseScheduling();
    }
    else if (choice == 4) {
        tester.testStudentGroups();
    }
    else if (choice == 5) {
        tester.testFacultyAssignments();
    }
}

int main() {
    UniversitySystem system;

    displayHeader();
    std::cout << "\n[System Initialized Successfully]\n";
    std::cout << " -> Courses Loaded: " << system.getCourses().size() << " (SE Department Core + Electives)\n";
    std::cout << " -> Students Loaded: " << system.getStudents().size() << " (SE Department)\n";
    std::cout << " -> Faculty Loaded: " << system.getFaculty().size() << "\n";
    std::cout << " -> Rooms Loaded: " << system.getRooms().size() << "\n";
    std::cout << " -> Prerequisites Initialized\n";
    std::cout << " -> Induction & Logic Engine Online\n";
    std::cout << " -> Consistency Checker: ACTIVE\n";
    std::cout << " -> Student-Course Relations Verified\n";

    std::cout << "\n=============================================================\n";
    std::cout << "                    SYSTEM READY\n";
    std::cout << "=============================================================\n";

    // For now, we'll use only console interface since GUI might not be available
    std::cout << "Starting Console Interface...\n";

    // Console Interface
    while (true) {
        displayMainMenu();

        int choice;
        std::cin >> choice;

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
            std::cout << "\nThank you for using FAST UNIDISC ENGINE!\n";
            std::cout << "System shutdown completed.\n";
            return 0;
        default:
            std::cout << "Invalid choice! Please try again.\n";
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}