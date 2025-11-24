#pragma once
#include <vector>
#include <string>
#include <map>
#include "Student.h"
#include "Course.h"
#include "Faculty.h"

class RelationsModule {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;
    std::vector<Faculty> allFaculty;

public:
    RelationsModule(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty);

    // Relation analysis
    void analyzeStudentCourseRelation();
    void analyzeCourseFacultyRelation();
    void analyzeStudentFacultyRelation();
    void analyzeAllRelations();

    // Relation properties
    bool isReflexive(const std::vector<std::pair<std::string, std::string>>& relation);
    bool isSymmetric(const std::vector<std::pair<std::string, std::string>>& relation);
    bool isTransitive(const std::vector<std::pair<std::string, std::string>>& relation);
    bool isAntiSymmetric(const std::vector<std::pair<std::string, std::string>>& relation);

    // Relation composition
    std::vector<std::pair<std::string, std::string>> composeRelations(
        const std::vector<std::pair<std::string, std::string>>& R,
        const std::vector<std::pair<std::string, std::string>>& S);

    void displayRelationProperties(const std::vector<std::pair<std::string, std::string>>& relation, const std::string& relationName);

private:
    std::vector<std::pair<std::string, std::string>> getStudentCourseRelation();
    std::vector<std::pair<std::string, std::string>> getCourseFacultyRelation();
    std::vector<std::pair<std::string, std::string>> getStudentFacultyRelation();
};