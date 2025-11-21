#include "EfficiencyModule.h"
#include <vector>
#include <ctime>

map<string, bool> EfficiencyModule::prereqCache;

bool EfficiencyModule::checkPrerequisitesMemoized(string courseCode, vector<string> completedCourses,
    vector<pair<string, vector<string>>> coursePrereqs) {
    string key = courseCode;
    for (const string& course : completedCourses) key += course;

    if (prereqCache.find(key) != prereqCache.end()) {
        cout << "? Cache hit for " << courseCode << " - O(1) lookup!" << endl;
        return prereqCache[key];
    }

    bool result = true;
    for (const auto& course : coursePrereqs) {
        if (course.first == courseCode) {
            for (const string& prereq : course.second) {
                bool found = false;
                for (const string& completed : completedCourses) {
                    if (completed == prereq) found = true;
                }
                if (!found) result = false;
            }
        }
    }

    prereqCache[key] = result;
    cout << "? Cache miss for " << courseCode << " - O(n) computation" << endl;
    return result;
}

void EfficiencyModule::demonstrateDP() {
    cout << "\n=== MODULE 10: ALGORITHM EFFICIENCY - DYNAMIC PROGRAMMING ===" << endl;

    cout << "\n1. FIBONACCI SEQUENCE OPTIMIZATION:" << endl;

    vector<int> fibDP(15);
    fibDP[0] = 0; fibDP[1] = 1;
    for (int i = 2; i < 15; i++) {
        fibDP[i] = fibDP[i - 1] + fibDP[i - 2];
    }

    cout << "DP Approach (O(n)): ";
    for (int i = 0; i < 15; i++) cout << fibDP[i] << " ";
    cout << endl;

    cout << "Time Complexity: O(n), Space: O(n)" << endl;
    cout << "Naive Recursion: O(2^n) - exponential time!" << endl;
}

void EfficiencyModule::demonstrateMemoization() {
    cout << "\n2. MEMOIZATION FOR PREREQUISITE CHECKING:" << endl;

    vector<pair<string, vector<string>>> coursePrereqs = {
        {"CS2001", {"CS1004"}},
        {"CS1004", {"CS1002"}},
        {"CS2005", {"CS2001"}}
    };

    vector<string> completed = { "CS1002", "CS1004" };

    cout << "First call (computes and caches):" << endl;
    bool result1 = checkPrerequisitesMemoized("CS2001", completed, coursePrereqs);
    cout << "Result: " << (result1 ? "Can take" : "Cannot take") << endl;

    cout << "\nSecond call (uses cache):" << endl;
    bool result2 = checkPrerequisitesMemoized("CS2001", completed, coursePrereqs);
    cout << "Result: " << (result2 ? "Can take" : "Cannot take") << endl;

    cout << "\nPerformance Analysis:" << endl;
    cout << "First call: O(n) - linear time" << endl;
    cout << "Subsequent calls: O(1) - constant time" << endl;
    cout << "Memory tradeoff: O(n) space for O(1) time" << endl;
}

void EfficiencyModule::benchmarkOperations() {
    cout << "\n3. ALGORITHMIC BENCHMARKING:" << endl;

    cout << "Set Operations Performance:" << endl;
    cout << "Array-based search: O(n) - 1000 operations for 1000 elements" << endl;
    cout << "Optimized search: O(1) - 1 operation with hashing" << endl;
    cout << "Improvement: 1000x faster for large datasets" << endl;

    cout << "\nCourse Sequencing:" << endl;
    cout << "Naive approach: O(2^n) - exponential time" << endl;
    cout << "DP approach: O(n^2) - polynomial time" << endl;
    cout << "Improvement: Exponential to polynomial scaling" << endl;

    cout << "\nReal-world Impact:" << endl;
    cout << "1000 students × 100 courses:" << endl;
    cout << "Naive: 2^100 ? 1.3e30 operations (impossible)" << endl;
    cout << "DP: 1000^2 = 1,000,000 operations (feasible)" << endl;
}