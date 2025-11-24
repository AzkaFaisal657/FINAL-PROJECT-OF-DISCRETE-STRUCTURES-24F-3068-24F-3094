#pragma once
#include <vector>
#include <string>
#include <map>
#include "Course.h"
#include "Student.h"
#include "Faculty.h"

class FunctionsModule {
private:
    std::vector<Course> allCourses;
    std::vector<Student> allStudents;
    std::vector<Faculty> allFaculty;

public:
    FunctionsModule(const std::vector<Course>& courses, const std::vector<Student>& students, const std::vector<Faculty>& faculty);

    // Function analysis
    void analyzeCourseToFaculty();
    void analyzeFacultyToCourse();
    void analyzeStudentToCourseLoad();
    void analyzeAllMappings();

    // Function properties
    bool isInjective(const std::map<std::string, std::string>& mapping);
    bool isSurjective(const std::map<std::string, std::string>& mapping, const std::vector<std::string>& codomain);
    bool isBijective(const std::map<std::string, std::string>& mapping, const std::vector<std::string>& codomain);

    // Function operations
    std::map<std::string, std::string> getInverseMapping(const std::map<std::string, std::string>& mapping);
    std::map<std::string, std::string> composeMappings(const std::map<std::string, std::string>& f, const std::map<std::string, std::string>& g);

    void displayMappingProperties(const std::map<std::string, std::string>& mapping,
        const std::vector<std::string>& domain,
        const std::vector<std::string>& codomain,
        const std::string& mappingName);

private:
    std::map<std::string, std::string> getCourseFacultyMapping();
    std::map<std::string, int> getStudentCourseLoadMapping();
    std::vector<std::string> getAllCourseCodes();
    std::vector<std::string> getAllFacultyIds();
    std::vector<std::string> getAllStudentRolls();
};