#pragma once
#include <string>
#include <iostream>
using namespace std;

struct StudentGroup {
    string members[10];
    int memberCount;
};

class CombinationsModule {
private:
    static int factorial(int n);
    static void generateCombinationsHelper(string students[], int n, int r,
        int index, string data[], int i,
        StudentGroup groups[], int& groupCount);

public:
    static int calculateCombinations(int n, int r);
    static int calculatePermutations(int n, int r);
    static void generateAllGroups(string students[], int n, int r, StudentGroup groups[], int& groupCount);
    static void assignProjectGroups(string students[], int studentCount, int groupSize);
    static void assignLabSessions(string students[], int studentCount, int labCapacity);
    static void assignElectives(string students[], int studentCount, int electiveSlots);
    static void demonstrateCombinations();
    static void displayGroup(StudentGroup& group, int groupNum);
};