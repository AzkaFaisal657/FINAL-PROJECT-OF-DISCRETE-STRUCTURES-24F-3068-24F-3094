#ifndef INDUCTIONMODULE_H
#define INDUCTIONMODULE_H

#include "Student.h"
#include "Course.h"
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <iostream>

class InductionModule {
private:
    std::vector<Student> allStudents;
    std::vector<Course> allCourses;

    std::vector<std::string> getAllPrerequisites(const std::string& courseCode);
    Course* findCourseByCode(const std::string& courseCode);
    std::vector<Student> getStudentsEnrolledInCourse(const std::string& courseCode);
    bool hasCycle(const std::string& courseCode, std::map<std::string, bool>& visited, std::map<std::string, bool>& recursionStack);
    bool strongInductionVerification(const Student& student, const std::string& courseCode);
    bool baseCaseVerification(const Student& student, const std::vector<std::string>& prerequisites);
    bool inductiveStepVerification(const Student& student, const std::vector<std::string>& prerequisites, int k);

public:
    InductionModule(const std::vector<Student>& students, const std::vector<Course>& courses);

    bool verifyPrerequisiteChain(const std::string& courseCode);
    bool verifyStudentEligibility(const Student& student, const std::string& courseCode);
    std::vector<std::pair<std::string, bool>> verifyAllStudentsForCourse(const std::string& courseCode);
    void displayVerificationResults(const std::vector<std::pair<std::string, bool>>& results, const std::string& courseCode);
};

#endif