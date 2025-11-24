#include "FunctionsModule.h"
#include <iostream>
#include <algorithm>

FunctionsModule::FunctionsModule(const std::vector<Course>& courses, const std::vector<Student>& students, const std::vector<Faculty>& faculty)
    : allCourses(courses), allStudents(students), allFaculty(faculty) {}

void FunctionsModule::analyzeCourseToFaculty() {
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "                FUNCTIONS & MAPPINGS MODULE\n";
    std::cout << "-------------------------------------------------------------\n";

    auto mapping = getCourseFacultyMapping();
    auto domain = getAllCourseCodes();
    auto codomain = getAllFacultyIds();

    std::cout << "Checking f: Course → Faculty\n";
    std::cout << "Total Courses: " << domain.size() << "\n";

    displayMappingProperties(mapping, domain, codomain, "Course → Faculty");

    std::cout << "Generating inverse mapping (Faculty → Courses)...\n";
    auto inverse = getInverseMapping(mapping);

    std::cout << " → Completed\n";
    for (const auto& faculty : allFaculty) {
        std::cout << " → " << faculty.getName() << ": ";
        bool first = true;
        for (const auto& pair : mapping) {
            if (pair.second == faculty.getFacultyId()) {
                if (!first) std::cout << ", ";
                std::cout << pair.first;
                first = false;
            }
        }
        std::cout << "\n";
    }

    std::cout << "Function module operations completed successfully.\n";
}

void FunctionsModule::analyzeFacultyToCourse() {
    auto mapping = getCourseFacultyMapping();
    auto inverse = getInverseMapping(mapping);
    auto domain = getAllFacultyIds();
    auto codomain = getAllCourseCodes();

    std::cout << "\nChecking f: Faculty → Course (Inverse)\n";
    displayMappingProperties(inverse, domain, codomain, "Faculty → Course");
}

void FunctionsModule::analyzeStudentToCourseLoad() {
    auto mapping = getStudentCourseLoadMapping();
    std::cout << "\nChecking f: Student → Course Load\n";

    std::cout << "Sample student course loads:\n";
    int count = 0;
    for (const auto& student : allStudents) {
        if (count++ < 5) {
            std::cout << " → " << student.getRollNumber() << ": "
                << mapping[student.getRollNumber()] << " credits\n";
        }
    }
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
    for (const auto& element : codomain) {
        bool found = false;
        for (const auto& pair : mapping) {
            if (pair.second == element) {
                found = true;
                break;
            }
        }
        if (!found) return false;
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
    std::cout << "Injective?  " << (isInjective(mapping) ? "YES" : "NO");
    if (isInjective(mapping)) {
        std::cout << "  (Each course has exactly one assigned faculty)";
    }
    std::cout << "\n";

    std::cout << "Surjective? " << (isSurjective(mapping, codomain) ? "YES" : "NO");
    if (!isSurjective(mapping, codomain)) {
        std::cout << "   (Some faculty not teaching any course)";
    }
    std::cout << "\n";

    std::cout << "Bijective?  " << (isBijective(mapping, codomain) ? "YES" : "NO") << "\n";
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