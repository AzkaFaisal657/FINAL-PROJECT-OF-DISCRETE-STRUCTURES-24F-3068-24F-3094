#include "SetOperations.h"

void SetOperations::add(string element) {
    for (string e : elements) {
        if (e == element) return;
    }
    elements.push_back(element);
}

bool SetOperations::contains(string element) const {
    for (string e : elements) {
        if (e == element) return true;
    }
    return false;
}

int SetOperations::size() const {
    return elements.size();
}

string SetOperations::getElement(int index) const {
    if (index >= 0 && index < elements.size()) {
        return elements[index];
    }
    return "";
}

SetOperations SetOperations::unionWith(const SetOperations& other) const {
    SetOperations result;
    for (string e : elements) result.add(e);
    for (string e : other.elements) result.add(e);
    return result;
}

SetOperations SetOperations::intersectionWith(const SetOperations& other) const {
    SetOperations result;
    for (string e : elements) {
        if (other.contains(e)) {
            result.add(e);
        }
    }
    return result;
}

SetOperations SetOperations::differenceWith(const SetOperations& other) const {
    SetOperations result;
    for (string e : elements) {
        if (!other.contains(e)) {
            result.add(e);
        }
    }
    return result;
}

bool SetOperations::isSubsetOf(const SetOperations& other) const {
    for (string e : elements) {
        if (!other.contains(e)) {
            return false;
        }
    }
    return true;
}

bool SetOperations::equals(const SetOperations& other) const {
    return isSubsetOf(other) && other.isSubsetOf(*this);
}

void SetOperations::display(string setName) const {
    cout << setName << " = { ";
    for (int i = 0; i < elements.size(); i++) {
        cout << elements[i];
        if (i < elements.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
    cout << "Cardinality: " << elements.size() << endl;
}

void SetOperations::demonstrateSetOperations() {
    cout << "\n=== MODULE 5: SET OPERATIONS ===" << endl;

    SetOperations csStudents, mathStudents;
    csStudents.add("22K-0001");
    csStudents.add("22K-0002");
    csStudents.add("22K-0003");

    mathStudents.add("22K-0002");
    mathStudents.add("22K-0003");
    mathStudents.add("22K-0004");

    cout << "\nOriginal Sets:" << endl;
    csStudents.display("CS Students");
    mathStudents.display("Math Students");

    cout << "\n--- SET OPERATIONS ---" << endl;
    SetOperations unionSet = csStudents.unionWith(mathStudents);
    unionSet.display("Union (CS U Math)");

    SetOperations intersectionSet = csStudents.intersectionWith(mathStudents);
    intersectionSet.display("Intersection (CS ∩ Math)");

    SetOperations differenceSet = csStudents.differenceWith(mathStudents);
    differenceSet.display("Difference (CS - Math)");
}