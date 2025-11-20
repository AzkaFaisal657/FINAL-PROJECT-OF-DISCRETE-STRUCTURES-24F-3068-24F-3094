#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class CourseScheduler {
private:
    struct CourseNode {
        string code;
        vector<string> prerequisites;
        bool visited;
    };

    vector<CourseNode> courses;

public:
    CourseScheduler() {}

    void addCourse(string code, vector<string> prereqs);
    bool canTakeCourse(string targetCourse, vector<string> completedCourses);
    vector<vector<string>> generateValidSequences(int maxCourses);
    void displayAllSequences();

    static void demonstrateScheduling();

private:
    bool checkPrerequisites(string courseCode, vector<string> completedCourses);
    CourseNode* findCourse(string code);
    void generateSequencesHelper(vector<string> current, vector<vector<string>>& result, int maxDepth);
};