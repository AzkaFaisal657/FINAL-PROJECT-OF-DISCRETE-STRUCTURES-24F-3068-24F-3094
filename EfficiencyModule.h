#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class EfficiencyModule {
private:
    static map<string, bool> prereqCache;

public:
    static void demonstrateDP();
    static void demonstrateMemoization();
    static void benchmarkOperations();
    static bool checkPrerequisitesMemoized(string courseCode, vector<string> completedCourses,
        vector<pair<string, vector<string>>> coursePrereqs);
};