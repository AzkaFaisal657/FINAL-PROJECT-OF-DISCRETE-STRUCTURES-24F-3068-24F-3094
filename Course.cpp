#include "Course.h"
#include <sstream>

Course::Course(const std::string& code, const std::string& name, int creditHours,
    const std::string& type, int semester, const std::string& prerequisite)
    : code(code), name(name), creditHours(creditHours), type(type), semester(semester), prerequisite(prerequisite) {}

std::string Course::getCode() const { return code; }
std::string Course::getName() const { return name; }
int Course::getCreditHours() const { return creditHours; }
std::string Course::getType() const { return type; }
int Course::getSemester() const { return semester; }
std::string Course::getPrerequisite() const { return prerequisite; }

void Course::setCode(const std::string& code) { this->code = code; }
void Course::setName(const std::string& name) { this->name = name; }
void Course::setCreditHours(int creditHours) { this->creditHours = creditHours; }
void Course::setType(const std::string& type) { this->type = type; }
void Course::setSemester(int semester) { this->semester = semester; }
void Course::setPrerequisite(const std::string& prerequisite) { this->prerequisite = prerequisite; }

std::string Course::toString() const {
    std::ostringstream oss;
    oss << code << " - " << name << " (" << creditHours << " credits, Semester " << semester << ")";
    if (!prerequisite.empty()) {
        oss << " [Prereq: " << prerequisite << "]";
    }
    return oss.str();
}