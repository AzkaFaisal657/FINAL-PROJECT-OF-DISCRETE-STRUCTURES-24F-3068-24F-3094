#include "RelationsModule.h"

void RelationsModule::addPair(string first, string second) {
    Pair p;
    p.first = first;
    p.second = second;
    pairs.push_back(p);
}

bool RelationsModule::hasPair(string first, string second) const {
    for (const Pair& p : pairs) {
        if (p.first == first && p.second == second) return true;
    }
    return false;
}

bool RelationsModule::isReflexive(vector<string> domain) const {
    for (const string& elem : domain) {
        if (!hasPair(elem, elem)) return false;
    }
    return true;
}

bool RelationsModule::isSymmetric() const {
    for (const Pair& p : pairs) {
        if (!hasPair(p.second, p.first)) return false;
    }
    return true;
}

bool RelationsModule::isTransitive() const {
    for (const Pair& p1 : pairs) {
        for (const Pair& p2 : pairs) {
            if (p1.second == p2.first) {
                if (!hasPair(p1.first, p2.second)) return false;
            }
        }
    }
    return true;
}

bool RelationsModule::isEquivalence(vector<string> domain) const {
    return isReflexive(domain) && isSymmetric() && isTransitive();
}

bool RelationsModule::isPartialOrder(vector<string> domain) const {
    // Partial order: reflexive, antisymmetric, transitive
    if (!isReflexive(domain)) return false;
    if (!isTransitive()) return false;

    // Check antisymmetric: if (a,b) and (b,a) then a == b
    for (const Pair& p : pairs) {
        if (p.first != p.second && hasPair(p.second, p.first)) {
            return false;
        }
    }
    return true;
}

void RelationsModule::display(string relationName) const {
    cout << relationName << " = { ";
    for (int i = 0; i < pairs.size(); i++) {
        cout << "(" << pairs[i].first << ", " << pairs[i].second << ")";
        if (i < pairs.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void RelationsModule::demonstrateRelations() {
    cout << "\n=== MODULE 6: RELATIONS & PROPERTIES ===" << endl;

    cout << "\n1. PREREQUISITE RELATION:" << endl;
    RelationsModule prereqRelation;
    prereqRelation.addPair("CS1002", "CS1004");
    prereqRelation.addPair("CS1004", "CS2001");
    prereqRelation.addPair("CS2001", "CS2005");
    prereqRelation.addPair("MT1003", "MT1008");

    prereqRelation.display("Prerequisites");
    cout << "Transitive? " << (prereqRelation.isTransitive() ? "Yes" : "No") << endl;

    cout << "\n2. SAME-SECTION RELATION (Equivalence):" << endl;
    RelationsModule sameSection;
    vector<string> students = { "Ali", "Sara", "Ahmed" };

    // Make it reflexive
    for (const string& s : students) {
        sameSection.addPair(s, s);
    }
    // Make it symmetric and transitive
    sameSection.addPair("Ali", "Sara");
    sameSection.addPair("Sara", "Ali");
    sameSection.addPair("Sara", "Ahmed");
    sameSection.addPair("Ahmed", "Sara");
    sameSection.addPair("Ali", "Ahmed");
    sameSection.addPair("Ahmed", "Ali");

    sameSection.display("SameSection");
    cout << "Reflexive? " << (sameSection.isReflexive(students) ? "Yes" : "No") << endl;
    cout << "Symmetric? " << (sameSection.isSymmetric() ? "Yes" : "No") << endl;
    cout << "Transitive? " << (sameSection.isTransitive() ? "Yes" : "No") << endl;
    cout << "Equivalence Relation? " << (sameSection.isEquivalence(students) ? "Yes" : "No") << endl;

    cout << "\n3. COURSE LEVEL ORDERING (Partial Order):" << endl;
    RelationsModule courseOrder;
    vector<string> courses = { "CS1002", "CS1004", "CS2001" };

    // Reflexive
    for (const string& c : courses) {
        courseOrder.addPair(c, c);
    }
    // Antisymmetric ordering
    courseOrder.addPair("CS1002", "CS1004");
    courseOrder.addPair("CS1004", "CS2001");
    courseOrder.addPair("CS1002", "CS2001");

    courseOrder.display("CourseOrder");
    cout << "Partial Order? " << (courseOrder.isPartialOrder(courses) ? "Yes" : "No") << endl;
}