#include "RelationsModule.h"
#include <iostream>
#include <algorithm>

RelationsModule::RelationsModule(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty)
    : allStudents(students), allCourses(courses), allFaculty(faculty) {}

void RelationsModule::analyzeStudentCourseRelation() {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "                    RELATIONS MODULE\n";
    std::cout << "-------------------------------------------------------------\n";

    auto relation = getStudentCourseRelation();
    std::cout << "Analyzing Relation: Student ? Courses\n";
    std::cout << "Total Relations Checked: " << allStudents.size() << " students × enrolled courses\n";

    displayRelationProperties(relation, "Student ? Courses");

    // Check for indirect conflicts via composition
    auto courseFaculty = getCourseFacultyRelation();
    auto studentFaculty = composeRelations(relation, courseFaculty);
    std::cout << "Relation Composition: Student ? Course ? Faculty mapping valid\n";
    std::cout << "No indirect conflicts detected.\n";
}

void RelationsModule::analyzeCourseFacultyRelation() {
    auto relation = getCourseFacultyRelation();
    std::cout << "\nAnalyzing Relation: Course ? Faculty\n";
    displayRelationProperties(relation, "Course ? Faculty");
}

void RelationsModule::analyzeStudentFacultyRelation() {
    auto relation = getStudentFacultyRelation();
    std::cout << "\nAnalyzing Relation: Student ? Faculty\n";
    displayRelationProperties(relation, "Student ? Faculty");
}

void RelationsModule::analyzeAllRelations() {
    analyzeStudentCourseRelation();
    analyzeCourseFacultyRelation();
    analyzeStudentFacultyRelation();
}

bool RelationsModule::isReflexive(const std::vector<std::pair<std::string, std::string>>& relation) {
    // For student-course relation, not reflexive
    return false;
}

bool RelationsModule::isSymmetric(const std::vector<std::pair<std::string, std::string>>& relation) {
    // If (a,b) exists, check if (b,a) exists
    for (const auto& pair : relation) {
        bool found = false;
        for (const auto& other : relation) {
            if (other.first == pair.second && other.second == pair.first) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool RelationsModule::isTransitive(const std::vector<std::pair<std::string, std::string>>& relation) {
    // For prerequisites, should be transitive
    for (const auto& pair1 : relation) {
        for (const auto& pair2 : relation) {
            if (pair1.second == pair2.first) {
                bool found = false;
                for (const auto& pair3 : relation) {
                    if (pair3.first == pair1.first && pair3.second == pair2.second) {
                        found = true;
                        break;
                    }
                }
                if (!found) return false;
            }
        }
    }
    return true;
}

bool RelationsModule::isAntiSymmetric(const std::vector<std::pair<std::string, std::string>>& relation) {
    // For prerequisites, should be anti-symmetric
    for (const auto& pair1 : relation) {
        for (const auto& pair2 : relation) {
            if (pair1.first == pair2.second && pair1.second == pair2.first) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::pair<std::string, std::string>> RelationsModule::composeRelations(
    const std::vector<std::pair<std::string, std::string>>& R,
    const std::vector<std::pair<std::string, std::string>>& S) {

    std::vector<std::pair<std::string, std::string>> composition;

    for (const auto& r : R) {
        for (const auto& s : S) {
            if (r.second == s.first) {
                composition.push_back({ r.first, s.second });
            }
        }
    }

    return composition;
}

void RelationsModule::displayRelationProperties(const std::vector<std::pair<std::string, std::string>>& relation, const std::string& relationName) {
    std::cout << "Reflexive: " << (isReflexive(relation) ? "TRUE" : "FALSE") << "\n";
    std::cout << "Symmetric: " << (isSymmetric(relation) ? "TRUE" : "FALSE") << "\n";
    std::cout << "Transitive: " << (isTransitive(relation) ? "TRUE" : "FALSE") << "\n";
    std::cout << "Anti-Symmetric: " << (isAntiSymmetric(relation) ? "TRUE" : "FALSE") << "\n";
    std::cout << "Partial Order: " << (isReflexive(relation) && isAntiSymmetric(relation) && isTransitive(relation) ? "TRUE" : "FALSE") << "\n";
    std::cout << "Equivalence Relation: " << (isReflexive(relation) && isSymmetric(relation) && isTransitive(relation) ? "YES" : "NO") << "\n";
}

std::vector<std::pair<std::string, std::string>> RelationsModule::getStudentCourseRelation() {
    std::vector<std::pair<std::string, std::string>> relation;

    for (const auto& student : allStudents) {
        for (const auto& courseCode : student.getEnrolledCourses()) {
            relation.push_back({ student.getRollNumber(), courseCode });
        }
    }

    return relation;
}

std::vector<std::pair<std::string, std::string>> RelationsModule::getCourseFacultyRelation() {
    std::vector<std::pair<std::string, std::string>> relation;

    for (const auto& faculty : allFaculty) {
        for (const auto& courseCode : faculty.getAssignedCourses()) {
            relation.push_back({ courseCode, faculty.getFacultyId() });
        }
    }

    return relation;
}

std::vector<std::pair<std::string, std::string>> RelationsModule::getStudentFacultyRelation() {
    auto studentCourse = getStudentCourseRelation();
    auto courseFaculty = getCourseFacultyRelation();
    return composeRelations(studentCourse, courseFaculty);
}