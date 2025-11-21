#include "SetOperations.h"

void SetOperations::add(string element) {
    for (string e : elements) {
        if (e == element) return;
    }
    elements.push_back(element);
}

SetOperations SetOperations::unionWith(const SetOperations& other) const {
    SetOperations result;
    for (string e : elements) result.add(e);
    for (string e : other.elements) result.add(e);
    return result;
}

void SetOperations::demonstrateSetOperations() {
    cout << "\n=== MODULE 5: SET OPERATIONS ===" << endl;

    SetOperations csStudents, mathStudents;
    csStudents.add("22K-0001"); csStudents.add("22K-0002");
    mathStudents.add("22K-0002"); mathStudents.add("22K-0003");

    csStudents.display("CS Students");
    mathStudents.display("Math Students");

    SetOperations unionSet = csStudents.unionWith(mathStudents);
    unionSet.display("Union");
}