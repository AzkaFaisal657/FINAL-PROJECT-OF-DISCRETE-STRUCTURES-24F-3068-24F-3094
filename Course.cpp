#include "Course.h"
#include <algorithm>

Course::Course() : code(""), name(""), creditHours(0), type(""), semester(0), prerequisite("") {}

Course::Course(std::string code, std::string name, int credits, std::string type, int sem, std::string prereq)
    : code(code), name(name), creditHours(credits), type(type), semester(sem), prerequisite(prereq) {}

std::string Course::getCode() const { return code; }
std::string Course::getName() const { return name; }
int Course::getCreditHours() const { return creditHours; }
std::string Course::getType() const { return type; }
int Course::getSemester() const { return semester; }
std::string Course::getPrerequisite() const { return prerequisite; }
std::vector<std::string> Course::getPrerequisites() const { return prerequisites; }

void Course::setCode(const std::string& code) { this->code = code; }
void Course::setName(const std::string& name) { this->name = name; }
void Course::setCreditHours(int credits) { this->creditHours = credits; }
void Course::setType(const std::string& type) { this->type = type; }
void Course::setSemester(int sem) { this->semester = sem; }
void Course::setPrerequisite(const std::string& prereq) { this->prerequisite = prereq; }

void Course::addPrerequisite(const std::string& prereqCode) {
    if (std::find(prerequisites.begin(), prerequisites.end(), prereqCode) == prerequisites.end()) {
        prerequisites.push_back(prereqCode);
    }
}

bool Course::hasPrerequisite(const std::string& prereqCode) const {
    return std::find(prerequisites.begin(), prerequisites.end(), prereqCode) != prerequisites.end();
}

void Course::display() const {
    std::cout << code << " - " << name << " (" << creditHours << " credits, Sem " << semester << ")" << std::endl;
    if (!prerequisite.empty()) {
        std::cout << "  Prerequisite: " << prerequisite << std::endl;
    }
    if (!prerequisites.empty()) {
        std::cout << "  Prerequisites: ";
        for (size_t i = 0; i < prerequisites.size(); i++) {
            std::cout << prerequisites[i];
            if (i < prerequisites.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

std::string Course::toString() const {
    std::string result = code + " - " + name + " (" + std::to_string(creditHours) +
        " credits, Sem " + std::to_string(semester) + ")";
    if (!prerequisite.empty()) {
        result += " [Prereq: " + prerequisite + "]";
    }
    return result;
}