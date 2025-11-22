#include "UniversitySystem.h"
#include "GUI.h"
#include "SetOperations.h"
#include "RelationsModule.h"
#include "FunctionsModule.h"
#include "CombinationsModule.h"
#include "LogicEngine.h"
#include "InductionModule.h"
#include "AutomatedProof.h"
#include "CourseScheduler.h"
#include "ConflictDetector.h"
#include "EfficiencyModule.h"
#include "TestModule.h"
#include <iostream>
#include <limits>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void displayHeader() {
    cout << "\n========================================================" << endl;
    cout << "     FAST UNIVERSITY - DISCRETE MATHEMATICS SYSTEM" << endl;
    cout << "========================================================\n" << endl;
}

// ==================== COURSE FUNCTIONS ====================
void viewAllCourses(UniversitySystem& sys) {
    clearScreen();
    cout << "\n=== ALL COURSES ===" << endl;
    for (int i = 0; i < sys.getCourseCount(); i++) {
        Course* c = sys.getCourseByIndex(i);
        if (c) {
            cout << i + 1 << ". ";
            c->display();
        }
    }
    cout << "\nTotal: " << sys.getCourseCount() << " courses" << endl;
    pause();
}

void viewCoursesBySemester(UniversitySystem& sys) {
    clearScreen();
    int sem;
    cout << "Enter semester (1-8): ";
    cin >> sem;
    cout << "\n=== SEMESTER " << sem << " COURSES ===" << endl;
    int count = 0;
    for (int i = 0; i < sys.getCourseCount(); i++) {
        Course* c = sys.getCourseByIndex(i);
        if (c && c->getSemester() == sem) {
            c->display();
            count++;
        }
    }
    cout << "\nTotal: " << count << " courses in semester " << sem << endl;
    pause();
}

void searchCourse(UniversitySystem& sys) {
    clearScreen();
    string code;
    cout << "Enter course code (e.g., CS2001): ";
    cin >> code;
    Course* c = sys.getCourse(code);
    if (c) {
        cout << "\n=== COURSE FOUND ===" << endl;
        c->display();
    }
    else {
        cout << "Course not found!" << endl;
    }
    pause();
}

// ==================== STUDENT FUNCTIONS ====================
void viewAllStudents(UniversitySystem& sys) {
    clearScreen();
    cout << "\n=== ALL STUDENTS ===" << endl;
    for (int i = 0; i < sys.getStudentCount(); i++) {
        Student* s = sys.getStudentByIndex(i);
        if (s) {
            cout << i + 1 << ". " << s->getId() << " - " << s->getName()
                << " (Sem " << s->getCurrentSemester() << ")" << endl;
        }
    }
    cout << "\nTotal: " << sys.getStudentCount() << " students" << endl;
    pause();
}

void viewStudentDetails(UniversitySystem& sys) {
    clearScreen();
    string id;
    cout << "Enter student ID (e.g., 24F-3001): ";
    cin >> id;
    Student* s = sys.getStudent(id);
    if (s) {
        cout << "\n=== STUDENT DETAILS ===" << endl;
        s->display();
        cout << "\nCompleted Courses:" << endl;
        for (int i = 0; i < s->getCompletedCount(); i++) {
            string code = s->getCompletedCourse(i);
            Course* c = sys.getCourse(code);
            cout << "  - " << code;
            if (c) cout << " (" << c->getName() << ")";
            cout << endl;
        }
    }
    else {
        cout << "Student not found!" << endl;
    }
    pause();
}

void checkEnrollmentEligibility(UniversitySystem& sys) {
    clearScreen();
    string studentId, courseCode;
    cout << "Enter student ID: ";
    cin >> studentId;
    cout << "Enter course code: ";
    cin >> courseCode;

    string reason;
    bool canEnroll = sys.canStudentEnroll(studentId, courseCode, reason);
    cout << "\n=== ENROLLMENT CHECK ===" << endl;
    cout << "Student: " << studentId << endl;
    cout << "Course: " << courseCode << endl;
    cout << "Result: " << (canEnroll ? "ELIGIBLE" : "NOT ELIGIBLE") << endl;
    cout << "Reason: " << reason << endl;
    pause();
}

void enrollStudent(UniversitySystem& sys) {
    clearScreen();
    string studentId, courseCode;
    cout << "Enter student ID: ";
    cin >> studentId;
    cout << "Enter course code: ";
    cin >> courseCode;

    string errorMsg;
    if (sys.enrollStudent(studentId, courseCode, errorMsg)) {
        cout << "\nSUCCESS: Student enrolled in " << courseCode << endl;
    }
    else {
        cout << "\nFAILED: " << errorMsg << endl;
    }
    pause();
}

// ==================== SET OPERATIONS ====================
void interactiveSetOperations(UniversitySystem& sys) {
    clearScreen();
    cout << "\n=== INTERACTIVE SET OPERATIONS ===" << endl;

    SetOperations set1, set2;

    // Build sets from actual students
    cout << "Building sets from student data...\n" << endl;

    // Set1: Students in semester 3+
    // Set2: Students with 5+ completed courses
    for (int i = 0; i < sys.getStudentCount(); i++) {
        Student* s = sys.getStudentByIndex(i);
        if (s) {
            if (s->getCurrentSemester() >= 3) {
                set1.add(s->getId());
            }
            if (s->getCompletedCount() >= 5) {
                set2.add(s->getId());
            }
        }
    }

    set1.display("Set A (Semester >= 3)");
    set2.display("Set B (Completed >= 5 courses)");

    cout << "\n--- OPERATIONS ---" << endl;
    SetOperations unionSet = set1.unionWith(set2);
    unionSet.display("A UNION B");

    SetOperations intersect = set1.intersectionWith(set2);
    intersect.display("A INTERSECT B");

    SetOperations diff = set1.differenceWith(set2);
    diff.display("A - B");

    cout << "\nIs A subset of B? " << (set1.isSubsetOf(set2) ? "Yes" : "No") << endl;
    cout << "Are A and B equal? " << (set1.equals(set2) ? "Yes" : "No") << endl;
    pause();
}

// ==================== RELATIONS ====================
void interactiveRelations(UniversitySystem& sys) {
    clearScreen();
    cout << "\n=== INTERACTIVE RELATIONS ===" << endl;

    RelationsModule prereqRel;
    vector<string> courses;

    // Build prerequisite relation from course data
    cout << "Building prerequisite relation from course data...\n" << endl;

    for (int i = 0; i < sys.getCourseCount(); i++) {
        Course* c = sys.getCourseByIndex(i);
        if (c) {
            courses.push_back(c->getCode());
            for (int j = 0; j < c->getPrereqCount(); j++) {
                prereqRel.addPair(c->getPrerequisite(j), c->getCode());
            }
        }
    }

    prereqRel.display("Prerequisite Relation");

    cout << "\nRelation Properties:" << endl;
    cout << "Reflexive? " << (prereqRel.isReflexive(courses) ? "Yes" : "No") << endl;
    cout << "Symmetric? " << (prereqRel.isSymmetric() ? "Yes" : "No") << endl;
    cout << "Transitive? " << (prereqRel.isTransitive() ? "Yes" : "No") << endl;
    pause();
}

// ==================== COMBINATIONS ====================
void interactiveCombinations(UniversitySystem& sys) {
    clearScreen();
    cout << "\n=== INTERACTIVE COMBINATIONS ===" << endl;

    int n, r;
    cout << "Enter n (total items): ";
    cin >> n;
    cout << "Enter r (items to choose): ";
    cin >> r;

    cout << "\nC(" << n << "," << r << ") = " << CombinationsModule::calculateCombinations(n, r) << endl;
    cout << "P(" << n << "," << r << ") = " << CombinationsModule::calculatePermutations(n, r) << endl;

    cout << "\n--- PRACTICAL EXAMPLE ---" << endl;
    cout << "With " << sys.getStudentCount() << " students:" << endl;
    cout << "Ways to form groups of 3: C(" << sys.getStudentCount() << ",3) = "
        << CombinationsModule::calculateCombinations(sys.getStudentCount(), 3) << endl;
    cout << "Ways to select president, VP, secretary: P(" << sys.getStudentCount() << ",3) = "
        << CombinationsModule::calculatePermutations(sys.getStudentCount(), 3) << endl;
    pause();
}

// ==================== MENUS ====================
void courseMenu(UniversitySystem& sys) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "=== COURSE MANAGEMENT ===" << endl;
        cout << "1. View All Courses" << endl;
        cout << "2. View Courses by Semester" << endl;
        cout << "3. Search Course by Code" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: viewAllCourses(sys); break;
        case 2: viewCoursesBySemester(sys); break;
        case 3: searchCourse(sys); break;
        }
    } while (choice != 0);
}

void studentMenu(UniversitySystem& sys) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "=== STUDENT MANAGEMENT ===" << endl;
        cout << "1. View All Students" << endl;
        cout << "2. View Student Details" << endl;
        cout << "3. Check Enrollment Eligibility" << endl;
        cout << "4. Enroll Student in Course" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: viewAllStudents(sys); break;
        case 2: viewStudentDetails(sys); break;
        case 3: checkEnrollmentEligibility(sys); break;
        case 4: enrollStudent(sys); break;
        }
    } while (choice != 0);
}

void discreteMathMenu(UniversitySystem& sys) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "=== DISCRETE MATHEMATICS ===" << endl;
        cout << "1. Set Operations (Interactive)" << endl;
        cout << "2. Relations (Interactive)" << endl;
        cout << "3. Combinations & Counting" << endl;
        cout << "4. Logic Engine Demo" << endl;
        cout << "5. Induction Demo" << endl;
        cout << "6. Functions Demo" << endl;
        cout << "7. Automated Proofs Demo" << endl;
        cout << "8. Course Scheduling (DP)" << endl;
        cout << "9. Efficiency & Memoization" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "\nChoice: ";
        cin >> choice;

        clearScreen();
        switch (choice) {
        case 1: interactiveSetOperations(sys); break;
        case 2: interactiveRelations(sys); break;
        case 3: interactiveCombinations(sys); break;
        case 4: { LogicEngine e; e.demonstrateLogicEngine(); pause(); break; }
        case 5: InductionModule::demonstrateStrongInduction(); pause(); break;
        case 6: FunctionsModule::demonstrateFunctions(); pause(); break;
        case 7: AutomatedProof::demonstrateAutomatedProof(); pause(); break;
        case 8: CourseScheduler::demonstrateScheduling(); pause(); break;
        case 9: EfficiencyModule::demonstrateDP(); EfficiencyModule::demonstrateMemoization(); pause(); break;
        }
    } while (choice != 0);
}

void runTests() {
    clearScreen();
    TestModule::runAllTests();
    pause();
}

int selectInterface() {
    clearScreen();
    cout << "\n========================================================" << endl;
    cout << "     FAST UNIVERSITY - DISCRETE MATHEMATICS SYSTEM" << endl;
    cout << "========================================================" << endl;
    cout << "\nSelect Interface:" << endl;
    cout << "1. Console Interface" << endl;
    cout << "2. Graphical Interface (SFML)" << endl;
    cout << "0. Exit" << endl;
    cout << "\nChoice: ";
    int choice;
    cin >> choice;
    return choice;
}

void consoleInterface(UniversitySystem& sys) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "=== MAIN MENU ===" << endl;
        cout << "1. Course Management" << endl;
        cout << "2. Student Management" << endl;
        cout << "3. Discrete Mathematics Modules" << endl;
        cout << "4. Run All Tests" << endl;
        cout << "5. System Information" << endl;
        cout << "0. Back to Interface Selection" << endl;
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: courseMenu(sys); break;
        case 2: studentMenu(sys); break;
        case 3: discreteMathMenu(sys); break;
        case 4: runTests(); break;
        case 5:
            clearScreen();
            sys.displaySystemInfo();
            pause();
            break;
        }
    } while (choice != 0);
}

int main() {
    UniversitySystem system;
    cout << "Loading university data..." << endl;
    system.loadAllData();

    int interfaceChoice;
    do {
        interfaceChoice = selectInterface();

        switch (interfaceChoice) {
        case 1:
            consoleInterface(system);
            break;
        case 2:
        {
            GUI gui(&system);
            gui.run();
        }
        break;
        case 0:
            cout << "\nGoodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (interfaceChoice != 0);

    return 0;
}