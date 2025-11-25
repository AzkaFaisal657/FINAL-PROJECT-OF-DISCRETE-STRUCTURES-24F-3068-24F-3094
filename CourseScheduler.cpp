#include "CourseScheduler.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

CourseScheduler::CourseScheduler(const std::vector<Course>& courses, const std::vector<Student>& students)
    : allCourses(courses), allStudents(students) {}

std::vector<std::vector<std::string>> CourseScheduler::generateValidSequences(int maxCoursesPerSemester) {
    std::vector<std::vector<std::string>> sequences;

    if (maxCoursesPerSemester <= 0) {
        std::cout << "ERROR: Max courses per semester must be positive." << std::endl;
        return sequences;
    }

    if (allCourses.empty()) {
        std::cout << "ERROR: No courses available for scheduling." << std::endl;
        return sequences;
    }

    std::cout << "Generating valid course sequences (max " << maxCoursesPerSemester << " courses/semester)..." << std::endl;

    // Build prerequisite map
    std::map<std::string, std::string> prerequisites;
    std::map<std::string, int> semesters;

    for (const auto& course : allCourses) {
        prerequisites[course.getCode()] = course.getPrerequisite();
        semesters[course.getCode()] = course.getSemester();
    }

    // Generate valid sequence using topological sort approach
    std::vector<std::string> sequence;
    std::set<std::string> completed;

    // Group courses by semester
    std::map<int, std::vector<std::string>> coursesBySemester;
    for (const auto& course : allCourses) {
        coursesBySemester[course.getSemester()].push_back(course.getCode());
    }

    // Take courses semester by semester, respecting prerequisites
    for (int semester = 1; semester <= 8; semester++) {
        if (coursesBySemester.find(semester) != coursesBySemester.end()) {
            std::vector<std::string> canTakeThisSemester;

            // Check which courses we can take this semester
            for (const auto& courseCode : coursesBySemester[semester]) {
                std::string prereq = prerequisites[courseCode];

                // Can take if no prerequisite OR prerequisite already completed
                if (prereq.empty() || completed.find(prereq) != completed.end()) {
                    canTakeThisSemester.push_back(courseCode);
                }
            }

            // Take up to max courses
            int coursesToTake = std::min(static_cast<int>(canTakeThisSemester.size()), maxCoursesPerSemester);
            for (int i = 0; i < coursesToTake; i++) {
                sequence.push_back(canTakeThisSemester[i]);
                completed.insert(canTakeThisSemester[i]);
            }
        }
    }

    if (!sequence.empty()) {
        sequences.push_back(sequence);
        std::cout << "✓ Generated valid sequence respecting all prerequisites" << std::endl;
    }

    return sequences;
}

bool CourseScheduler::canTakeCourse(const std::string& courseCode, const std::set<std::string>& takenCourses) {
    for (const auto& course : allCourses) {
        if (course.getCode() == courseCode) {
            std::string prereq = course.getPrerequisite();
            if (!prereq.empty() && takenCourses.find(prereq) == takenCourses.end()) {
                return false;
            }
            return true;
        }
    }
    return false;
}

bool CourseScheduler::canTakeCourse(const std::string& courseCode, const std::map<std::string, bool>& takenCourses) {
    std::set<std::string> takenSet;
    for (const auto& pair : takenCourses) {
        if (pair.second) {
            takenSet.insert(pair.first);
        }
    }
    return canTakeCourse(courseCode, takenSet);
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

    if (targetSemester < 1 || targetSemester > 8) {
        std::cout << "ERROR: Target semester must be between 1 and 8." << std::endl;
        return recommended;
    }

    auto completed = student.getCompletedCourses();
    auto enrolled = student.getEnrolledCourses();

    std::map<std::string, bool> taken;
    for (const auto& course : completed) taken[course] = true;
    for (const auto& course : enrolled) taken[course] = true;

    auto targetCourses = getCoursesForSemester(targetSemester);

    for (const auto& courseCode : targetCourses) {
        if (taken.find(courseCode) == taken.end()) {
            if (canTakeCourse(courseCode, taken)) {
                recommended.push_back(courseCode);
            }
        }
    }

    return recommended;
}

bool CourseScheduler::checkPrerequisiteOrder(const std::vector<std::string>& sequence) {
    std::set<std::string> taken;

    for (const auto& courseCode : sequence) {
        bool courseFound = false;
        for (const auto& course : allCourses) {
            if (course.getCode() == courseCode) {
                courseFound = true;
                std::string prereq = course.getPrerequisite();
                if (!prereq.empty() && taken.find(prereq) == taken.end()) {
                    std::cout << "✗ Prerequisite violation: " << courseCode << " requires " << prereq << std::endl;
                    return false;
                }
                taken.insert(courseCode);
                break;
            }
        }
        if (!courseFound) {
            std::cout << "✗ Course not found: " << courseCode << std::endl;
            return false;
        }
    }
    return true;
}

void CourseScheduler::displayAllSequences(const std::vector<std::vector<std::string>>& sequences) {
    std::cout << "\n=== VALID COURSE SEQUENCES ===" << std::endl;

    if (sequences.empty()) {
        std::cout << "No valid sequences found." << std::endl;
        return;
    }

    for (size_t i = 0; i < sequences.size(); ++i) {
        std::cout << "\nSequence " << (i + 1) << ":" << std::endl;

        // Verify prerequisite order
        bool isValid = checkPrerequisiteOrder(sequences[i]);
        std::cout << "Prerequisite validation: " << (isValid ? "VALID ✓" : "INVALID ✗") << std::endl;

        if (isValid) {
            // Display by actual semesters
            std::map<int, std::vector<std::string>> semCourses;
            for (const auto& courseCode : sequences[i]) {
                for (const auto& course : allCourses) {
                    if (course.getCode() == courseCode) {
                        semCourses[course.getSemester()].push_back(courseCode);
                        break;
                    }
                }
            }

            for (const auto& pair : semCourses) {
                std::cout << "Semester " << pair.first << ": ";
                for (size_t j = 0; j < pair.second.size(); ++j) {
                    std::cout << pair.second[j];
                    if (j < pair.second.size() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
            }
        }
    }

    // Show important prerequisite chains
    std::cout << "\n=== KEY PREREQUISITE CHAINS ===" << std::endl;
    std::vector<std::string> keyCourses = { "CS2001", "CS2005", "CS2006", "AI2002", "SE3002", "CS3001" };

    for (const auto& courseCode : keyCourses) {
        std::cout << courseCode << " < - ";
        std::vector<std::string> chain;
        std::string current = courseCode;

        while (true) {
            std::string prereq = "";
            for (const auto& course : allCourses) {
                if (course.getCode() == current) {
                    prereq = course.getPrerequisite();
                    break;
                }
            }
            if (prereq.empty()) break;
            chain.push_back(prereq);
            current = prereq;
        }

        if (chain.empty()) {
            std::cout << "None";
        }
        else {
            for (int i = chain.size() - 1; i >= 0; i--) {
                std::cout << chain[i];
                if (i > 0) std::cout << " < - ";
            }
        }
        std::cout << std::endl;
    }
}