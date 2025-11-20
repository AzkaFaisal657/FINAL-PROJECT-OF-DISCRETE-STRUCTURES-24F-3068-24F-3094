#pragma once
#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class InductionModule {
public:
    static void verifyPrerequisiteChain(string targetCourse, vector<string> completedCourses,
        vector<pair<string, vector<string>>> coursePrereqs);
    static void demonstrateStrongInduction();
    static void proveBaseCase(int n);
    static void proveInductiveStep(int k);
    static void demonstrateInduction();
};
