#include "Faculty.h"
#include <sstream>
#include <algorithm>

Faculty::Faculty() : facultyId(""), name(""), designation("") {}

Faculty::Faculty(const std::string& facultyId, const std::string& name,
    const std::string& designation, const std::vector<std::string>& assignedCourses)
    : facultyId(facultyId), name(name), designation(designation), assignedCourses(assignedCourses) {}

std::string Faculty::getFacultyId() const { return facultyId; }
std::string Faculty::getName() const { return name; }
std::string Faculty::getDesignation() const { return designation; }
std::vector<std::string> Faculty::getAssignedCourses() const { return assignedCourses; }

void Faculty::setFacultyId(const std::string& facultyId) { this->facultyId = facultyId; }
void Faculty::setName(const std::string& name) { this->name = name; }
void Faculty::setDesignation(const std::string& designation) { this->designation = designation; }
void Faculty::setAssignedCourses(const std::vector<std::string>& courses) { assignedCourses = courses; }

void Faculty::assignCourse(const std::string& courseCode) {
    if (std::find(assignedCourses.begin(), assignedCourses.end(), courseCode) == assignedCourses.end()) {
        assignedCourses.push_back(courseCode);
    }
}

void Faculty::removeCourse(const std::string& courseCode) {
    auto it = std::find(assignedCourses.begin(), assignedCourses.end(), courseCode);
    if (it != assignedCourses.end()) {
        assignedCourses.erase(it);
    }
}

bool Faculty::teachesCourse(const std::string& courseCode) const {
    return std::find(assignedCourses.begin(), assignedCourses.end(), courseCode) != assignedCourses.end();
}

std::string Faculty::toString() const {
    std::ostringstream oss;
    oss << facultyId << " - " << name << " (" << designation << ")";
    oss << "\nCourses: ";
    for (size_t i = 0; i < assignedCourses.size(); ++i) {
        oss << assignedCourses[i];
        if (i < assignedCourses.size() - 1) oss << ", ";
    }
    return oss.str();
}