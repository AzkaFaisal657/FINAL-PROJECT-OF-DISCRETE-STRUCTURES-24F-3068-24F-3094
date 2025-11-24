#include "UniversitySystem.h"
#include <iostream>
#include <algorithm>

UniversitySystem::UniversitySystem() {
    loadAllData();
}

UniversitySystem::~UniversitySystem() {
    saveAllData();
}

void UniversitySystem::loadAllData() {
    courses = FileHandler::loadCourses(coursesFile);
    students = FileHandler::loadStudents(studentsFile, courses);
    faculty = FileHandler::loadFaculty(facultyFile);
    rooms = FileHandler::loadRooms(roomsFile);

    std::cout << "Data loaded successfully:\n";
    std::cout << " - Courses: " << courses.size() << "\n";
    std::cout << " - Students: " << students.size() << "\n";
    std::cout << " - Faculty: " << faculty.size() << "\n";
    std::cout << " - Rooms: " << rooms.size() << "\n";
}

void UniversitySystem::saveAllData() {
    FileHandler::saveCourses(coursesFile, courses);
    FileHandler::saveStudents(studentsFile, students);
    FileHandler::saveFaculty(facultyFile, faculty);
    FileHandler::saveRooms(roomsFile, rooms);
    std::cout << "All data saved successfully!\n";
}

std::vector<Course>& UniversitySystem::getCourses() { return courses; }
std::vector<Student>& UniversitySystem::getStudents() { return students; }
std::vector<Faculty>& UniversitySystem::getFaculty() { return faculty; }
std::vector<Room>& UniversitySystem::getRooms() { return rooms; }

Course* UniversitySystem::findCourse(const std::string& courseCode) {
    for (auto& course : courses) {
        if (course.getCode() == courseCode) {
            return &course;
        }
    }
    return nullptr;
}

Student* UniversitySystem::findStudent(const std::string& rollNumber) {
    for (auto& student : students) {
        if (student.getRollNumber() == rollNumber) {
            return &student;
        }
    }
    return nullptr;
}

Faculty* UniversitySystem::findFaculty(const std::string& facultyId) {
    for (auto& fac : faculty) {
        if (fac.getFacultyId() == facultyId) {
            return &fac;
        }
    }
    return nullptr;
}

Room* UniversitySystem::findRoom(const std::string& roomId) {
    for (auto& room : rooms) {
        if (room.getRoomId() == roomId) {
            return &room;
        }
    }
    return nullptr;
}

std::vector<Student> UniversitySystem::getStudentsEnrolledInCourse(const std::string& courseCode) {
    std::vector<Student> enrolled;
    for (const auto& student : students) {
        if (student.isEnrolledIn(courseCode)) {
            enrolled.push_back(student);
        }
    }
    return enrolled;
}

std::vector<std::string> UniversitySystem::getPrerequisiteChain(const std::string& courseCode) {
    std::vector<std::string> chain;
    std::string currentCourse = courseCode;

    while (true) {
        Course* course = findCourse(currentCourse);
        if (!course || course->getPrerequisite().empty()) {
            break;
        }
        chain.push_back(course->getPrerequisite());
        currentCourse = course->getPrerequisite();
    }

    std::reverse(chain.begin(), chain.end());
    return chain;
}

bool UniversitySystem::checkPrerequisiteSatisfaction(const Student& student, const std::string& courseCode) {
    auto chain = getPrerequisiteChain(courseCode);
    for (const auto& prereq : chain) {
        if (!student.hasCompleted(prereq)) {
            return false;
        }
    }
    return true;
}

void UniversitySystem::displayAllStudents() const {
    std::cout << "\n=== ALL STUDENTS ===\n";
    for (const auto& student : students) {
        std::cout << student.toString() << "\n\n";
    }
}

void UniversitySystem::displayAllCourses() const {
    std::cout << "\n=== ALL COURSES ===\n";
    for (const auto& course : courses) {
        std::cout << course.toString() << "\n";
    }
}

void UniversitySystem::displayAllFaculty() const {
    std::cout << "\n=== ALL FACULTY ===\n";
    for (const auto& fac : faculty) {
        std::cout << fac.toString() << "\n\n";
    }
}

void UniversitySystem::displayAllRooms() const {
    std::cout << "\n=== ALL ROOMS ===\n";
    for (const auto& room : rooms) {
        std::cout << room.toString() << "\n";
    }
}