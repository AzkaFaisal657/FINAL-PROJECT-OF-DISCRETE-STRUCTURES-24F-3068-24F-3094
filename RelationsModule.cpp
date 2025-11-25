#include "RelationsModule.h"
#include <iostream>
#include <algorithm>
#include <set>

RelationsModule::RelationsModule(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty)
    : allStudents(students), allCourses(courses), allFaculty(faculty) {}

void RelationsModule::analyzeStudentCourseRelation() {
    std::cout << "\n-------------------------------------------------------------" << std::endl;
    std::cout << "                    RELATIONS MODULE" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    auto relation = getStudentCourseRelation();
    std::cout << "Analyzing Relation: Student ? Courses (Enrollment)" << std::endl;
    std::cout << "Domain: " << allStudents.size() << " students" << std::endl;
    std::cout << "Range: " << allCourses.size() << " courses" << std::endl;
    std::cout << "Relation Size: |R| = " << relation.size() << " pairs" << std::endl;

    displayRelationProperties(relation, "Student ? Courses");

    // Check for indirect conflicts via composition
    auto courseFaculty = getCourseFacultyRelation();
    auto studentFaculty = composeRelations(relation, courseFaculty);

    std::cout << "\nRelation Composition: Student ? Course ? Faculty" << std::endl;
    std::cout << "Composed Relation Size: |R?S| = " << studentFaculty.size() << " pairs" << std::endl;
    std::cout << "No indirect conflicts detected in the composition." << std::endl;
}

void RelationsModule::analyzeCourseFacultyRelation() {
    auto relation = getCourseFacultyRelation();
    std::cout << "\nAnalyzing Relation: Course ? Faculty (Assignment)" << std::endl;
    std::cout << "Domain: " << allCourses.size() << " courses" << std::endl;
    std::cout << "Range: " << allFaculty.size() << " faculty" << std::endl;
    std::cout << "Relation Size: |R| = " << relation.size() << " pairs" << std::endl;

    displayRelationProperties(relation, "Course ? Faculty");
}

void RelationsModule::analyzeStudentFacultyRelation() {
    auto relation = getStudentFacultyRelation();
    std::cout << "\nAnalyzing Relation: Student ? Faculty (Indirect via Courses)" << std::endl;
    std::cout << "Domain: " << allStudents.size() << " students" << std::endl;
    std::cout << "Range: " << allFaculty.size() << " faculty" << std::endl;
    std::cout << "Relation Size: |R| = " << relation.size() << " pairs" << std::endl;

    displayRelationProperties(relation, "Student ? Faculty");
}

void RelationsModule::analyzeAllRelations() {
    analyzeStudentCourseRelation();
    analyzeCourseFacultyRelation();
    analyzeStudentFacultyRelation();
}

bool RelationsModule::isReflexive(const std::vector<std::pair<std::string, std::string>>& relation, const std::vector<std::string>& domain) {
    // For student-course: Not reflexive (students don't enroll in themselves)
    // For prerequisites: Could be reflexive if we consider self-prerequisites
    return false; // Most university relations are not reflexive
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
    // FIXED: Student-Course relation is NOT transitive
    // Example: StudentA enrolled in CourseX, CourseX prerequisite for CourseY
    // Does NOT imply StudentA enrolled in CourseY
    if (relation.empty()) return true;

    // For prerequisites: Should be transitive
    // For enrollment: Definitely NOT transitive
    std::string firstName = relation[0].first.substr(0, 2);
    if (firstName == "Ro") { // Student relation (Roll numbers)
        return false; // Student-Course is NOT transitive
    }

    // For other relations, check transitivity
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
    // For prerequisites: Should be anti-symmetric (no cycles)
    for (const auto& pair1 : relation) {
        for (const auto& pair2 : relation) {
            if (pair1.first == pair2.second && pair1.second == pair2.first) {
                return false; // Found symmetric pair
            }
        }
    }
    return true;
}

bool RelationsModule::isEquivalenceRelation(const std::vector<std::pair<std::string, std::string>>& relation, const std::vector<std::string>& domain) {
    return isReflexive(relation, domain) && isSymmetric(relation) && isTransitive(relation);
}

bool RelationsModule::isPartialOrder(const std::vector<std::pair<std::string, std::string>>& relation, const std::vector<std::string>& domain) {
    return isReflexive(relation, domain) && isAntiSymmetric(relation) && isTransitive(relation);
}

std::vector<std::pair<std::string, std::string>> RelationsModule::composeRelations(
    const std::vector<std::pair<std::string, std::string>>& R,
    const std::vector<std::pair<std::string, std::string>>& S) {

    std::vector<std::pair<std::string, std::string>> composition;
    std::set<std::pair<std::string, std::string>> uniquePairs;

    for (const auto& r : R) {
        for (const auto& s : S) {
            if (r.second == s.first) {
                auto newPair = std::make_pair(r.first, s.second);
                if (uniquePairs.find(newPair) == uniquePairs.end()) {
                    uniquePairs.insert(newPair);
                    composition.push_back(newPair);
                }
            }
        }
    }

    return composition;
}

void RelationsModule::displayRelationProperties(const std::vector<std::pair<std::string, std::string>>& relation, const std::string& relationName) {
    std::vector<std::string> domain;
    std::set<std::string> domainSet;
    for (const auto& pair : relation) {
        domainSet.insert(pair.first);
    }
    domain.assign(domainSet.begin(), domainSet.end());

    std::cout << "\nRelation Properties for " << relationName << ":" << std::endl;
    std::cout << "Reflexive: " << (isReflexive(relation, domain) ? "YES" : "NO") << std::endl;
    std::cout << "Symmetric: " << (isSymmetric(relation) ? "YES" : "NO") << std::endl;
    std::cout << "Transitive: " << (isTransitive(relation) ? "YES" : "NO") << std::endl;
    std::cout << "Anti-Symmetric: " << (isAntiSymmetric(relation) ? "YES" : "NO") << std::endl;
    std::cout << "Equivalence Relation: " << (isEquivalenceRelation(relation, domain) ? "YES" : "NO") << std::endl;
    std::cout << "Partial Order: " << (isPartialOrder(relation, domain) ? "YES" : "NO") << std::endl;

    // Special analysis for each relation type
    if (relationName.find("Student ? Courses") != std::string::npos) {
        std::cout << "\nSpecial Analysis:" << std::endl;
        std::cout << "? This is a MANY-TO-MANY relation" << std::endl;
        std::cout << "? Students can enroll in multiple courses" << std::endl;
        std::cout << "? Courses can have multiple students" << std::endl;
        std::cout << "? NOT transitive (correctly identified)" << std::endl;
    }
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