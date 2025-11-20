#include "Core/UniversitySystem.h"
#include "GUI/GUI.h"
#include <iostream>
using namespace std;

int main() {
    cout << "====================================================" << endl;
    cout << "   FAST UNIVERSITY - DISCRETE MATH MANAGEMENT SYSTEM" << endl;
    cout << "   Complete Project with 12 Modules & SFML GUI" << endl;
    cout << "====================================================" << endl;

    UniversitySystem system;
    system.loadAllData();

    cout << "\nSystem Loaded Successfully!" << endl;
    cout << "Courses: " << system.getCourseCount() << endl;
    cout << "Students: " << system.getStudentCount() << endl;
    cout << "Faculty: " << system.getFacultyCount() << endl;

    cout << "\nChoose mode:" << endl;
    cout << "1. SFML GUI Mode (Recommended)" << endl;
    cout << "2. Console Mode - Run All Demonstrations" << endl;
    cout << "Enter choice (1 or 2): ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        GUI gui(&system);
        gui.run();
    }
    else {
        system.demonstrateAllModules();
    }

    cout << "\nThank you for using FAST University System!" << endl;
    return 0;
}