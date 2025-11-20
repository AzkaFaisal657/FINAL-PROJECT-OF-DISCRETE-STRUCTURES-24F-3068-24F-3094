#include "Course.h"

Course::Course() : code(""), name(""), creditHours(0), type(""), semester(0) {}

Course::Course(string code, string name, int credits, string type, int sem)
    : code(code), name(name), creditHours(credits), type(type), semester(sem) {
}

void Course::addPrerequisite(string prereqCode) {
    prerequisites.push_back(prereqCode);
}

bool Course::hasPrerequisite(string prereqCode) const {
    for (const string& prereq : prerequisites) {
        if (prereq == prereqCode) return true;
    }
    return false;
}

string Course::getPrerequisite(int index) const {
    if (index >= 0 && index < prerequisites.size()) {
        return prerequisites[index];
    }
    return "";
}

void Course::display() const {
    cout << code << " - " << name << " (" << creditHours << " credits)" << endl;
    if (!prerequisites.empty()) {
        cout << "  Prerequisites: ";
        for (int i = 0; i < prerequisites.size(); i++) {
            cout << prerequisites[i];
            if (i < prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}