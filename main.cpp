#include "UniversitySystem.h"
#include "GUI.h"
#include <iostream>
using namespace std;

int main() {
    cout << "FAST University - GUI Test" << endl;
    cout << "==========================" << endl;

    UniversitySystem system;
    system.loadAllData();

    cout << "\nStarting SFML GUI..." << endl;
    cout << "Courses: " << system.getCourseCount() << endl;
    cout << "Students: " << system.getStudentCount() << endl;
    cout << "Faculty: " << system.getFacultyCount() << endl;

    GUI gui(&system);
    gui.run();

    return 0;
}