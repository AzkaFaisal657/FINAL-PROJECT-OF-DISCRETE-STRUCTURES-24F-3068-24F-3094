#ifndef FUNCTIONSMODULE_H
#define FUNCTIONSMODULE_H

#include "Course.h"
#include "Student.h"
#include "Faculty.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

class FunctionsModule {
private:
    std::vector<Course> allCourses;
    std::vector<Student> allStudents;
    std::vector<Faculty> allFaculty;

    std::map<std::string, std::string> getCourseFacultyMapping();
    std::map<std::string, int> getStudentCourseLoadMapping();
    std::map<std::string, std::string> getFacultyCourseMapping();

    std::vector<std::string> getAllCourseCodes();
    std::vector<std::string> getAllFacultyIds();
    std::vector<std::string> getAllStudentRolls();

    bool isInjective(const std::map<std::string, std::string>& mapping);
    bool isSurjective(const std::map<std::string, std::string>& mapping, const std::vector<std::string>& codomain);
    bool isBijective(const std::map<std::string, std::string>& mapping, const std::vector<std::string>& codomain);

    std::map<std::string, std::string> getInverseMapping(const std::map<std::string, std::string>& mapping);
    std::map<std::string, std::string> composeMappings(const std::map<std::string, std::string>& f, const std::map<std::string, std::string>& g);

public:
    FunctionsModule(const std::vector<Course>& courses, const std::vector<Student>& students, const std::vector<Faculty>& faculty);

    void analyzeCourseToFaculty();
    void analyzeFacultyToCourse();
    void analyzeStudentToCourseLoad();
    void analyzeAllMappings();

    void displayMappingProperties(const std::map<std::string, std::string>& mapping,
        const std::vector<std::string>& domain,
        const std::vector<std::string>& codomain,
        const std::string& mappingName);
};

#endif