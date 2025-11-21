#include "CombinationsModule.h"

int CombinationsModule::factorial(int n) {
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int CombinationsModule::calculateCombinations(int n, int r) {
    if (r > n || r < 0) return 0;
    return factorial(n) / (factorial(r) * factorial(n - r));
}

int CombinationsModule::calculatePermutations(int n, int r) {
    if (r > n || r < 0) return 0;
    return factorial(n) / factorial(n - r);
}

void CombinationsModule::generateCombinationsHelper(string students[], int n, int r,
    int index, string data[], int i, StudentGroup groups[], int& groupCount) {
    if (index == r) {
        if (groupCount < 100) {
            groups[groupCount].memberCount = r;
            for (int j = 0; j < r; j++) {
                groups[groupCount].members[j] = data[j];
            }
            groupCount++;
        }
        return;
    }
    if (i >= n) return;

    data[index] = students[i];
    generateCombinationsHelper(students, n, r, index + 1, data, i + 1, groups, groupCount);
    generateCombinationsHelper(students, n, r, index, data, i + 1, groups, groupCount);
}

void CombinationsModule::generateAllGroups(string students[], int n, int r,
    StudentGroup groups[], int& groupCount) {
    groupCount = 0;
    string data[10];
    generateCombinationsHelper(students, n, r, 0, data, 0, groups, groupCount);
}

void CombinationsModule::displayGroup(StudentGroup& group, int groupNum) {
    cout << "Group " << groupNum << ": { ";
    for (int i = 0; i < group.memberCount; i++) {
        cout << group.members[i];
        if (i < group.memberCount - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void CombinationsModule::assignProjectGroups(string students[], int studentCount, int groupSize) {
    cout << "\n--- Project Group Assignment ---" << endl;
    cout << "Students: " << studentCount << ", Group Size: " << groupSize << endl;

    int numGroups = calculateCombinations(studentCount, groupSize);
    cout << "Possible groups: C(" << studentCount << "," << groupSize << ") = " << numGroups << endl;

    StudentGroup groups[100];
    int groupCount;
    generateAllGroups(students, studentCount, groupSize, groups, groupCount);

    cout << "First 5 possible groups:" << endl;
    for (int i = 0; i < min(5, groupCount); i++) {
        displayGroup(groups[i], i + 1);
    }
}

void CombinationsModule::assignLabSessions(string students[], int studentCount, int labCapacity) {
    cout << "\n--- Lab Session Assignment ---" << endl;
    cout << "Students: " << studentCount << ", Lab Capacity: " << labCapacity << endl;
    int sessions = (studentCount + labCapacity - 1) / labCapacity;
    cout << "Minimum sessions needed: " << sessions << endl;
}

void CombinationsModule::assignElectives(string students[], int studentCount, int electiveSlots) {
    cout << "\n--- Elective Assignment ---" << endl;
    cout << "Students: " << studentCount << ", Slots: " << electiveSlots << endl;
    int ways = calculatePermutations(studentCount, electiveSlots);
    cout << "Possible arrangements: P(" << studentCount << "," << electiveSlots << ") = " << ways << endl;
}

void CombinationsModule::demonstrateCombinations() {
    cout << "\n=== MODULE 2: COMBINATIONS & COUNTING ===" << endl;

    cout << "\n1. BASIC CALCULATIONS:" << endl;
    cout << "C(6,2) = " << calculateCombinations(6, 2) << " (ways to choose 2 from 6)" << endl;
    cout << "P(6,2) = " << calculatePermutations(6, 2) << " (arrangements of 2 from 6)" << endl;

    cout << "\n2. PROJECT GROUP FORMATION:" << endl;
    string students[] = { "Ali", "Sara", "Ahmed", "Fatima", "Hassan" };
    assignProjectGroups(students, 5, 2);

    cout << "\n3. LAB SESSION PLANNING:" << endl;
    assignLabSessions(students, 5, 2);

    cout << "\n4. ELECTIVE SLOT ALLOCATION:" << endl;
    assignElectives(students, 5, 3);
}