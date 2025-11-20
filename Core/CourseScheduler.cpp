#include "CourseScheduler.h"

void CourseScheduler::addCourse(string code, vector<string> prereqs) {
    CourseNode node;
    node.code = code;
    node.prerequisites = prereqs;
    node.visited = false;
    courses.push_back(node);
}

bool CourseScheduler::canTakeCourse(string targetCourse, vector<string> completedCourses) {
    for (CourseNode& course : courses) {
        course.visited = false;
    }
    return checkPrerequisites(targetCourse, completedCourses);
}

bool CourseScheduler::checkPrerequisites(string courseCode, vector<string> completedCourses) {
    CourseNode* course = findCourse(courseCode);
    if (!course) return false;
    if (course->visited) return true;

    course->visited = true;

    for (string prereq : course->prerequisites) {
        bool found = false;
        for (string completed : completedCourses) {
            if (completed == prereq) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (!checkPrerequisites(prereq, completedCourses)) {
                return false;
            }
        }
    }
    return true;
}

CourseScheduler::CourseNode* CourseScheduler::findCourse(string code) {
    for (CourseNode& course : courses) {
        if (course.code == code) {
            return &course;
        }
    }
    return nullptr;
}

vector<vector<string>> CourseScheduler::generateValidSequences(int maxCourses) {
    vector<vector<string>> sequences;

    cout << "\n=== GENERATING VALID COURSE SEQUENCES (DP APPROACH) ===" << endl;
    cout << "Maximum courses per sequence: " << maxCourses << endl;

    // Find courses with no prerequisites (starting points)
    for (const CourseNode& course : courses) {
        if (course.prerequisites.empty()) {
            vector<string> sequence;
            sequence.push_back(course.code);
            sequences.push_back(sequence);
        }
    }

    // Expand sequences using DP
    for (int depth = 1; depth < maxCourses; depth++) {
        vector<vector<string>> newSequences;

        for (const vector<string>& sequence : sequences) {
            string lastCourse = sequence.back();
            CourseNode* last = findCourse(lastCourse);

            if (last) {
                // Find courses that have all prerequisites satisfied by current sequence
                for (const CourseNode& nextCourse : courses) {
                    bool allPrereqsSatisfied = true;

                    for (const string& prereq : nextCourse.prerequisites) {
                        bool found = false;
                        for (const string& taken : sequence) {
                            if (taken == prereq) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            allPrereqsSatisfied = false;
                            break;
                        }
                    }

                    if (allPrereqsSatisfied) {
                        vector<string> newSequence = sequence;
                        newSequence.push_back(nextCourse.code);
                        newSequences.push_back(newSequence);
                    }
                }
            }
        }

        if (newSequences.empty()) break;
        sequences = newSequences;
    }

    cout << "Generated " << sequences.size() << " valid course sequences" << endl;
    return sequences;
}

void CourseScheduler::displayAllSequences() {
    vector<vector<string>> sequences = generateValidSequences(4);

    cout << "\nVALID COURSE SEQUENCES:" << endl;
    for (int i = 0; i < sequences.size(); i++) {
        cout << "Sequence " << (i + 1) << ": ";
        for (const string& course : sequences[i]) {
            cout << course << " ? ";
        }
        cout << "END" << endl;
    }
}

void CourseScheduler::demonstrateScheduling() {
    cout << "\n=== MODULE 1: COURSE SCHEDULING WITH DP ===" << endl;

    CourseScheduler scheduler;

    // Add courses with prerequisites
    scheduler.addCourse("CS1002", {});
    scheduler.addCourse("CS1004", { "CS1002" });
    scheduler.addCourse("MT1003", {});
    scheduler.addCourse("MT1008", { "MT1003" });
    scheduler.addCourse("CS2001", { "CS1004" });
    scheduler.addCourse("CS2005", { "CS2001" });
    scheduler.addCourse("CS2006", { "CS2001" });

    // Test prerequisite checking
    vector<string> completed = { "CS1002", "MT1003" };
    cout << "\nPrerequisite Check Results:" << endl;
    cout << "Can take CS1004: " << (scheduler.canTakeCourse("CS1004", completed) ? "YES" : "NO") << endl;
    cout << "Can take CS2001: " << (scheduler.canTakeCourse("CS2001", completed) ? "YES" : "NO") << endl;
    cout << "Can take CS2005: " << (scheduler.canTakeCourse("CS2005", completed) ? "YES" : "NO") << endl;

    // Generate sequences
    scheduler.displayAllSequences();

    cout << "\nDynamic Programming Benefits:" << endl;
    cout << "• O(n^2) time complexity instead of O(2^n)" << endl;
    cout << "• Memoization of prerequisite checks" << endl;
    cout << "• Efficient sequence generation" << endl;
}