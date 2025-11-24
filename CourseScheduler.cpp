#include "CourseScheduler.h"
#include <iostream>
#include <algorithm>

CourseScheduler::CourseScheduler(const std::vector<Course>& courses, const std::vector<Student>& students)
    : allCourses(courses), allStudents(students) {}

std::vector<std::vector<std::string>> CourseScheduler::generateValidSequences(int maxCoursesPerSemester) {
    std::vector<std::vector<std::string>> sequences;
    std::vector<std::string> currentSequence;
    std::map<std::string, bool> takenCourses;

    generateSequencesDFS(1, currentSequence, sequences, takenCourses, maxCoursesPerSemester);
    return sequences;
}

void CourseScheduler::generateSequencesDFS(int semester, std::vector<std::string>& current,
    std::vector<std::vector<std::string>>& result,
    std::map<std::string, bool>& taken, int maxPerSem) {
    if (semester > 8) { // Assuming 8 semesters max
        result.push_back(current);
        return;
    }

    auto availableCourses = getCoursesForSemester(semester);
    std::vector<std::string> canTakeThisSem;

    for (const auto& course : availableCourses) {
        if (!taken[course] && canTakeCourse(course, taken)) {
            canTakeThisSem.push_back(course);
        }
    }

    // Generate combinations of courses for this semester
    int n = std::min(static_cast<int>(canTakeThisSem.size()), maxPerSem);
    for (int i = 0; i <= n; ++i) {
        // Generate combinations of size i
        std::vector<bool> v(canTakeThisSem.size(), false);
        std::fill(v.begin(), v.begin() + i, true);

        do {
            std::vector<std::string> semCourses;
            for (int j = 0; j < canTakeThisSem.size(); ++j) {
                if (v[j]) {
                    semCourses.push_back(canTakeThisSem[j]);
                    taken[canTakeThisSem[j]] = true;
                    current.push_back(canTakeThisSem[j]);
                }
            }

            if (!semCourses.empty()) {
                generateSequencesDFS(semester + 1, current, result, taken, maxPerSem);
            }

            // Backtrack
            for (const auto& course : semCourses) {
                taken[course] = false;
                current.pop_back();
            }

        } while (std::prev_permutation(v.begin(), v.end()));
    }
}

bool CourseScheduler::canTakeCourse(const std::string& courseCode, const std::map<std::string, bool>& takenCourses) {
    for (const auto& course : allCourses) {
        if (course.getCode() == courseCode) {
            std::string prereq = course.getPrerequisite();
            if (!prereq.empty() && !takenCourses.at(prereq)) {
                return false;
            }
            return true;
        }
    }
    return false;
}

std::vector<std::string> CourseScheduler::getCoursesForSemester(int semester) {
    std::vector<std::string> semCourses;
    for (const auto& course : allCourses) {
        if (course.getSemester() == semester) {
            semCourses.push_back(course.getCode());
        }
    }
    return semCourses;
}

std::vector<std::string> CourseScheduler::getRecommendedSchedule(const Student& student, int targetSemester) {
    std::vector<std::string> recommended;
    auto completed = student.getCompletedCourses();
    auto enrolled = student.getEnrolledCourses();

    std::map<std::string, bool> taken;
    for (const auto& course : completed) taken[course] = true;
    for (const auto& course : enrolled) taken[course] = true;

    for (const auto& course : allCourses) {
        if (course.getSemester() == targetSemester && !taken[course.getCode()]) {
            if (canTakeCourse(course.getCode(), taken)) {
                recommended.push_back(course.getCode());
            }
        }
    }

    return recommended;
}

bool CourseScheduler::checkPrerequisiteOrder(const std::vector<std::string>& sequence) {
    std::map<std::string, bool> taken;
    for (const auto& courseCode : sequence) {
        for (const auto& course : allCourses) {
            if (course.getCode() == courseCode) {
                std::string prereq = course.getPrerequisite();
                if (!prereq.empty() && !taken[prereq]) {
                    return false;
                }
                taken[courseCode] = true;
                break;
            }
        }
    }
    return true;
}

void CourseScheduler::displayAllSequences(const std::vector<std::vector<std::string>>& sequences) {
    std::cout << "\n=== VALID COURSE SEQUENCES ===\n";
    for (size_t i = 0; i < sequences.size() && i < 5; ++i) { // Show first 5 sequences
        std::cout << "Sequence " << (i + 1) << ": ";
        for (const auto& course : sequences[i]) {
            std::cout << course << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Total valid sequences: " << sequences.size() << "\n";
}