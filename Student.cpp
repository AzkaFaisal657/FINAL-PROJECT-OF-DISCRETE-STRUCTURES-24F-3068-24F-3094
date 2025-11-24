#include "Student.h"
#include "Course.h"
#include <sstream>
#include <algorithm>

Student::Student(const std::string& rollNumber, const std::string& name, int currentSemester,
    const std::vector<std::string>& enrolledCourses)
    : rollNumber(rollNumber), name(name), currentSemester(currentSemester), enrolledCourses(enrolledCourses) {}

std::string Student::getRollNumber() const { return rollNumber; }
std::string Student::getName() const { return name; }
int Student::getCurrentSemester() const { return currentSemester; }
std::vector<std::string> Student::getEnrolledCourses() const { return enrolledCourses; }
std::vector<std::string> Student::getCompletedCourses() const { return completedCourses; }

void Student::setRollNumber(const std::string& rollNumber) { this->rollNumber = rollNumber; }
void Student::setName(const std::string& name) { this->name = name; }
void Student::setCurrentSemester(int semester) { this->currentSemester = semester; }
void Student::setEnrolledCourses(const std::vector<std::string>& courses) { enrolledCourses = courses; }
void Student::setCompletedCourses(const std::vector<std::string>& courses) { completedCourses = courses; }

void Student::enrollInCourse(const std::string& courseCode) {
    if (std::find(enrolledCourses.begin(), enrolledCourses.end(), courseCode) == enrolledCourses.end()) {
        enrolledCourses.push_back(courseCode);
    }
}

void Student::completeCourse(const std::string& courseCode) {
    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), courseCode);
    if (it != enrolledCourses.end()) {
        enrolledCourses.erase(it);
        if (std::find(completedCourses.begin(), completedCourses.end(), courseCode) == completedCourses.end()) {
            completedCourses.push_back(courseCode);
        }
    }
}

bool Student::hasCompleted(const std::string& courseCode) const {
    return std::find(completedCourses.begin(), completedCourses.end(), courseCode) != completedCourses.end();
}

bool Student::isEnrolledIn(const std::string& courseCode) const {
    return std::find(enrolledCourses.begin(), enrolledCourses.end(), courseCode) != enrolledCourses.end();
}

int Student::getCurrentCreditHours(const std::vector<Course>& allCourses) const {
    int totalCredits = 0;
    for (const auto& courseCode : enrolledCourses) {
        for (const auto& course : allCourses) {
            if (course.getCode() == courseCode) {
                totalCredits += course.getCreditHours();
                break;
            }
        }
    }
    return totalCredits;
}

std::string Student::toString() const {
    std::ostringstream oss;
    oss << rollNumber << " - " << name << " (Semester " << currentSemester << ")";
    oss << "\nEnrolled Courses: ";
    for (const auto& course : enrolledCourses) {
        oss << course << " ";
    }
    return oss.str();
}