#ifndef RELATIONSMODULE_H
#define RELATIONSMODULE_H

#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <iostream>

class RelationsModule {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;
    std::vector<Faculty> allFaculty;

    std::vector<std::pair<std::string, std::string>> getStudentCourseRelation();
    std::vector<std::pair<std::string, std::string>> getCourseFacultyRelation();
    std::vector<std::pair<std::string, std::string>> getStudentFacultyRelation();

    bool isReflexive(const std::vector<std::pair<std::string, std::string>>& relation, const std::vector<std::string>& domain);
    bool isSymmetric(const std::vector<std::pair<std::string, std::string>>& relation);
    bool isTransitive(const std::vector<std::pair<std::string, std::string>>& relation);
    bool isAntiSymmetric(const std::vector<std::pair<std::string, std::string>>& relation);
    bool isEquivalenceRelation(const std::vector<std::pair<std::string, std::string>>& relation, const std::vector<std::string>& domain);
    bool isPartialOrder(const std::vector<std::pair<std::string, std::string>>& relation, const std::vector<std::string>& domain);

public:
    RelationsModule(const std::vector<Student>& students, const std::vector<Course>& courses, const std::vector<Faculty>& faculty);

    void analyzeStudentCourseRelation();
    void analyzeCourseFacultyRelation();
    void analyzeStudentFacultyRelation();
    void analyzeAllRelations();

    std::vector<std::pair<std::string, std::string>> composeRelations(
        const std::vector<std::pair<std::string, std::string>>& R,
        const std::vector<std::pair<std::string, std::string>>& S);

    void displayRelationProperties(const std::vector<std::pair<std::string, std::string>>& relation, const std::string& relationName);
};

#endif