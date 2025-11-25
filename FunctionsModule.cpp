#include "FunctionsModule.h"
#include <iostream>
#include <algorithm>
#include <set>

FunctionsModule::FunctionsModule(const std::vector<Course>& courses, const std::vector<Student>& students, const std::vector<Faculty>& faculty)
    : allCourses(courses), allStudents(students), allFaculty(faculty) {}

void FunctionsModule::analyzeCourseToFaculty() {
    std::cout << "\n-------------------------------------------------------------" << std::endl;
    std::cout << "                FUNCTIONS & MAPPINGS MODULE" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    auto mapping = getCourseFacultyMapping();
    auto domain = getAllCourseCodes();
    auto codomain = getAllFacultyIds();

    std::cout << "Analyzing Function: f: Course → Faculty" << std::endl;
    std::cout << "Domain: " << domain.size() << " courses" << std::endl;
    std::cout << "Codomain: " << codomain.size() << " faculty" << std::endl;
    std::cout << "Mapping Size: " << mapping.size() << " assignments" << std::endl;

    displayMappingProperties(mapping, domain, codomain, "Course → Faculty");

    // Show actual mappings
    std::cout << "\nActual Course → Faculty Assignments:" << std::endl;
    for (const auto& pair : mapping) {
        std::string facultyName = "";
        for (const auto& faculty : allFaculty) {
            if (faculty.getFacultyId() == pair.second) {
                facultyName = faculty.getName();
                break;
            }
        }
        std::cout << "  " << pair.first << " → " << facultyName << " (" << pair.second << ")" << std::endl;
    }
}

void FunctionsModule::analyzeFacultyToCourse() {
    auto mapping = getFacultyCourseMapping();
    auto inverse = getInverseMapping(getCourseFacultyMapping());
    auto domain = getAllFacultyIds();
    auto codomain = getAllCourseCodes();

    std::cout << "\nAnalyzing Function: f: Faculty → Course (Inverse)" << std::endl;
    std::cout << "Domain: " << domain.size() << " faculty" << std::endl;
    std::cout << "Codomain: " << codomain.size() << " courses" << std::endl;

    displayMappingProperties(inverse, domain, codomain, "Faculty → Course");

    std::cout << "\nFaculty → Course Assignments:" << std::endl;
    for (const auto& faculty : allFaculty) {
        std::cout << "  " << faculty.getName() << " → ";
        bool first = true;
        for (const auto& courseCode : faculty.getAssignedCourses()) {
            if (!first) std::cout << ", ";
            std::cout << courseCode;
            first = false;
        }
        std::cout << std::endl;
    }
}

void FunctionsModule::analyzeStudentToCourseLoad() {
    auto mapping = getStudentCourseLoadMapping();
    std::cout << "\nAnalyzing Function: f: Student → Course Load (Credits)" << std::endl;

    std::cout << "Sample Student Course Loads:" << std::endl;
    int count = 0;
    for (const auto& student : allStudents) {
        if (count++ < 8) {
            int credits = student.getCurrentCreditHours(allCourses);
            std::cout << "  " << student.getRollNumber() << " → " << credits << " credits";
            if (credits > 18) std::cout << " [OVERLOAD!]";
            std::cout << std::endl;
        }
    }

    // Statistical analysis
    int totalCredits = 0;
    int maxCredits = 0;
    int overloadCount = 0;

    for (const auto& student : allStudents) {
        int credits = student.getCurrentCreditHours(allCourses);
        totalCredits += credits;
        if (credits > maxCredits) maxCredits = credits;
        if (credits > 18) overloadCount++;
    }

    double avgCredits = static_cast<double>(totalCredits) / allStudents.size();

    std::cout << "\nCourse Load Statistics:" << std::endl;
    std::cout << "  Average credits: " << avgCredits << std::endl;
    std::cout << "  Maximum credits: " << maxCredits << std::endl;
    std::cout << "  Students overloaded (>18): " << overloadCount << std::endl;
}

void FunctionsModule::analyzeAllMappings() {
    analyzeCourseToFaculty();
    analyzeFacultyToCourse();
    analyzeStudentToCourseLoad();
}

bool FunctionsModule::isInjective(const std::map<std::string, std::string>& mapping) {
    std::map<std::string, int> valueCount;
    for (const auto& pair : mapping) {
        valueCount[pair.second]++;
    }

    for (const auto& count : valueCount) {
        if (count.second > 1) return false;
    }
    return true;
}

bool FunctionsModule::isSurjective(const std::map<std::string, std::string>& mapping, const std::vector<std::string>& codomain) {
    std::set<std::string> mappedValues;
    for (const auto& pair : mapping) {
        mappedValues.insert(pair.second);
    }

    for (const auto& element : codomain) {
        if (mappedValues.find(element) == mappedValues.end()) {
            return false;
        }
    }
    return true;
}

bool FunctionsModule::isBijective(const std::map<std::string, std::string>& mapping, const std::vector<std::string>& codomain) {
    return isInjective(mapping) && isSurjective(mapping, codomain);
}

std::map<std::string, std::string> FunctionsModule::getInverseMapping(const std::map<std::string, std::string>& mapping) {
    std::map<std::string, std::string> inverse;
    for (const auto& pair : mapping) {
        // For one-to-many, store as comma-separated
        if (inverse.find(pair.second) == inverse.end()) {
            inverse[pair.second] = pair.first;
        }
        else {
            inverse[pair.second] += ", " + pair.first;
        }
    }
    return inverse;
}

std::map<std::string, std::string> FunctionsModule::composeMappings(const std::map<std::string, std::string>& f, const std::map<std::string, std::string>& g) {
    std::map<std::string, std::string> composition;

    for (const auto& f_pair : f) {
        if (g.find(f_pair.second) != g.end()) {
            composition[f_pair.first] = g.at(f_pair.second);
        }
    }

    return composition;
}

void FunctionsModule::displayMappingProperties(const std::map<std::string, std::string>& mapping,
    const std::vector<std::string>& domain,
    const std::vector<std::string>& codomain,
    const std::string& mappingName) {
    std::cout << "\nFunction Properties for " << mappingName << ":" << std::endl;
    std::cout << "Injective (One-to-One): " << (isInjective(mapping) ? "YES" : "NO") << std::endl;

    if (isInjective(mapping)) {
        std::cout << "  ✓ Each course has exactly one assigned faculty" << std::endl;
    }
    else {
        std::cout << "  ✗ Multiple courses may share the same faculty" << std::endl;
    }

    std::cout << "Surjective (Onto): " << (isSurjective(mapping, codomain) ? "YES" : "NO") << std::endl;

    if (isSurjective(mapping, codomain)) {
        std::cout << "  ✓ Every faculty teaches at least one course" << std::endl;
    }
    else {
        std::cout << "  ✗ Some faculty may not be teaching any course" << std::endl;
    }

    std::cout << "Bijective (One-to-One Correspondence): " << (isBijective(mapping, codomain) ? "YES" : "NO") << std::endl;

    if (isBijective(mapping, codomain)) {
        std::cout << "  ✓ Perfect one-to-one mapping between courses and faculty" << std::endl;
    }
    else {
        std::cout << "  ✗ Not a perfect one-to-one correspondence" << std::endl;
    }
}

std::map<std::string, std::string> FunctionsModule::getCourseFacultyMapping() {
    std::map<std::string, std::string> mapping;

    for (const auto& faculty : allFaculty) {
        for (const auto& courseCode : faculty.getAssignedCourses()) {
            mapping[courseCode] = faculty.getFacultyId();
        }
    }

    return mapping;
}

std::map<std::string, int> FunctionsModule::getStudentCourseLoadMapping() {
    std::map<std::string, int> mapping;

    for (const auto& student : allStudents) {
        mapping[student.getRollNumber()] = student.getCurrentCreditHours(allCourses);
    }

    return mapping;
}

std::map<std::string, std::string> FunctionsModule::getFacultyCourseMapping() {
    std::map<std::string, std::string> mapping;

    for (const auto& faculty : allFaculty) {
        std::string courses = "";
        bool first = true;
        for (const auto& courseCode : faculty.getAssignedCourses()) {
            if (!first) courses += ", ";
            courses += courseCode;
            first = false;
        }
        mapping[faculty.getFacultyId()] = courses;
    }

    return mapping;
}

std::vector<std::string> FunctionsModule::getAllCourseCodes() {
    std::vector<std::string> codes;
    for (const auto& course : allCourses) {
        codes.push_back(course.getCode());
    }
    return codes;
}

std::vector<std::string> FunctionsModule::getAllFacultyIds() {
    std::vector<std::string> ids;
    for (const auto& faculty : allFaculty) {
        ids.push_back(faculty.getFacultyId());
    }
    return ids;
}

std::vector<std::string> FunctionsModule::getAllStudentRolls() {
    std::vector<std::string> rolls;
    for (const auto& student : allStudents) {
        rolls.push_back(student.getRollNumber());
    }
    return rolls;
}