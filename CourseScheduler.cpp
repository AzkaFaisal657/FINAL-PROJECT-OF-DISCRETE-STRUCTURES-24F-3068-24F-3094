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

// Helper to check if course is already in sequence
bool isInSequence(const vector<string>& sequence, const string& course) {
    for (const string& s : sequence) {
        if (s == course) return true;
    }
    return false;
}

vector<vector<string>> CourseScheduler::generateValidSequences(int maxCourses) {
    vector<vector<string>> sequences;

    cout << "\n=== GENERATING VALID COURSE SEQUENCES (DP APPROACH) ===" << endl;
    cout << "Maximum courses per sequence: " << maxCourses << endl;

    // Find courses with no prerequisites (starting points)
    vector<vector<string>> currentSequences;
    for (const CourseNode& course : courses) {
        if (course.prerequisites.empty()) {
            vector<string> sequence;
            sequence.push_back(course.code);
            currentSequences.push_back(sequence);
        }
    }

    // Expand sequences using DP - NO DUPLICATES
    for (int depth = 1; depth < maxCourses; depth++) {
        vector<vector<string>> newSequences;

        for (const vector<string>& sequence : currentSequences) {
            // Find courses that can be taken next
            for (const CourseNode& nextCourse : courses) {
                // FIXED: Skip if course already in sequence
                if (isInSequence(sequence, nextCourse.code)) {
                    continue;
                }

                // Check if all prerequisites are satisfied by current sequence
                bool allPrereqsSatisfied = true;
                for (const string& prereq : nextCourse.prerequisites) {
                    if (!isInSequence(sequence, prereq)) {
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

        if (newSequences.empty()) break;

        // Keep both current and new sequences (some paths may end early)
        for (const auto& seq : currentSequences) {
            sequences.push_back(seq);
        }
        currentSequences = newSequences;
    }

    // Add final sequences
    for (const auto& seq : currentSequences) {
        sequences.push_back(seq);
    }

    cout << "Generated " << sequences.size() << " valid course sequences" << endl;
    return sequences;
}

void CourseScheduler::displayAllSequences() {
    vector<vector<string>> sequences = generateValidSequences(4);

    cout << "\nVALID COURSE SEQUENCES (unique courses only):" << endl;
    int displayCount = min(20, (int)sequences.size());
    for (int i = 0; i < displayCount; i++) {
        cout << "Sequence " << (i + 1) << ": ";
        for (int j = 0; j < sequences[i].size(); j++) {
            cout << sequences[i][j];
            if (j < sequences[i].size() - 1) cout << " -> ";
        }
        cout << " [END]" << endl;
    }
    if (sequences.size() > 20) {
        cout << "... and " << (sequences.size() - 20) << " more sequences" << endl;
    }
}

void CourseScheduler::demonstrateScheduling() {
    cout << "\n=== MODULE 1: COURSE SCHEDULING WITH DP ===" << endl;

    CourseScheduler scheduler;

    // Add courses with prerequisites (matching your courses.txt)
    scheduler.addCourse("CS1002", {});                    // Programming Fundamentals
    scheduler.addCourse("MT1003", {});                    // Calculus
    scheduler.addCourse("CS1004", { "CS1002" });            // OOP
    scheduler.addCourse("MT1008", { "MT1003" });            // Multivariable Calculus
    scheduler.addCourse("EE1005", {});                    // Digital Logic
    scheduler.addCourse("CS2001", { "CS1004" });            // Data Structures
    scheduler.addCourse("CS1005", { "CS1002" });            // Discrete Structures
    scheduler.addCourse("CS2005", { "CS2001" });            // Database Systems
    scheduler.addCourse("CS2006", { "CS2001" });            // Operating Systems
    scheduler.addCourse("AI2002", { "CS2001" });            // AI
    scheduler.addCourse("CS2009", { "CS2001", "CS1005" });  // Algorithms

    // Test prerequisite checking
    cout << "\nPrerequisite Check Examples:" << endl;
    vector<string> student1 = { "CS1002", "MT1003" };
    cout << "Student completed: CS1002, MT1003" << endl;
    cout << "  Can take CS1004 (needs CS1002)? " << (scheduler.canTakeCourse("CS1004", student1) ? "YES" : "NO") << endl;
    cout << "  Can take CS2001 (needs CS1004)? " << (scheduler.canTakeCourse("CS2001", student1) ? "YES" : "NO") << endl;

    vector<string> student2 = { "CS1002", "CS1004", "MT1003" };
    cout << "\nStudent completed: CS1002, CS1004, MT1003" << endl;
    cout << "  Can take CS2001? " << (scheduler.canTakeCourse("CS2001", student2) ? "YES" : "NO") << endl;
    cout << "  Can take CS2005 (needs CS2001)? " << (scheduler.canTakeCourse("CS2005", student2) ? "YES" : "NO") << endl;

    // Generate valid sequences
    scheduler.displayAllSequences();

    cout << "\nDynamic Programming Benefits:" << endl;
    cout << "* O(V*E) time complexity instead of O(2^n)" << endl;
    cout << "* Memoization of prerequisite checks" << endl;
    cout << "* No duplicate courses in sequences" << endl;
    cout << "* Efficient topological ordering" << endl;
}