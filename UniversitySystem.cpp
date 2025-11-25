#include "UniversitySystem.h"
#include <iostream>
#include <algorithm>

UniversitySystem::UniversitySystem() {
    std::cout << "Initializing FAST University System..." << std::endl;
    loadAllData();
}

UniversitySystem::~UniversitySystem() {
    std::cout << "Shutting down FAST University System..." << std::endl;
    saveAllData();
}

void UniversitySystem::loadAllData() {
    std::cout << "\n=== LOADING FAST UNIVERSITY DATA ===" << std::endl;

    courses = FileHandler::loadCourses(coursesFile);
    students = FileHandler::loadStudents(studentsFile, courses);
    faculty = FileHandler::loadFaculty(facultyFile);
    rooms = FileHandler::loadRooms(roomsFile);

    std::cout << "\n=== DATA LOADING COMPLETE ===" << std::endl;
    std::cout << "? Courses: " << courses.size() << " loaded" << std::endl;
    std::cout << "? Students: " << students.size() << " loaded" << std::endl;
    std::cout << "? Faculty: " << faculty.size() << " loaded" << std::endl;
    std::cout << "? Rooms: " << rooms.size() << " loaded" << std::endl;

    if (courses.empty() || students.empty()) {
        std::cout << "\n? WARNING: Some data files are empty or missing." << std::endl;
        std::cout << "Please ensure these files exist in your project directory:" << std::endl;
        std::cout << "- courses.txt" << std::endl;
        std::cout << "- students.txt" << std::endl;
        std::cout << "- faculty.txt" << std::endl;
        std::cout << "- rooms.txt" << std::endl;
    }
}

// ... rest of UniversitySystem.cpp remains the same ...

void UniversitySystem::saveAllData() {
    std::cout << "\n=== SAVING UNIVERSITY DATA ===" << std::endl;

    FileHandler::saveCourses(coursesFile, courses);
    FileHandler::saveStudents(studentsFile, students);
    FileHandler::saveFaculty(facultyFile, faculty);
    FileHandler::saveRooms(roomsFile, rooms);

    std::cout << "? All data saved successfully!" << std::endl;
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
    std::cout << "\n=== ALL STUDENTS (" << students.size() << ") ===" << std::endl;
    for (const auto& student : students) {
        std::cout << student.toString() << "\n" << std::endl;
    }
}

void UniversitySystem::displayAllCourses() const {
    std::cout << "\n=== ALL COURSES (" << courses.size() << ") ===" << std::endl;
    for (const auto& course : courses) {
        course.display();
        std::cout << std::endl;
    }
}

void UniversitySystem::displayAllFaculty() const {
    std::cout << "\n=== ALL FACULTY (" << faculty.size() << ") ===" << std::endl;
    for (const auto& fac : faculty) {
        std::cout << fac.toString() << "\n" << std::endl;
    }
}

void UniversitySystem::displayAllRooms() const {
    std::cout << "\n=== ALL ROOMS (" << rooms.size() << ") ===" << std::endl;
    for (const auto& room : rooms) {
        std::cout << room.toString() << std::endl;
    }
}

void UniversitySystem::addCourse(const Course& course) {
    // Check if course already exists
    if (findCourse(course.getCode()) == nullptr) {
        courses.push_back(course);
        std::cout << "Course " << course.getCode() << " added successfully." << std::endl;
    }
    else {
        std::cout << "Course " << course.getCode() << " already exists." << std::endl;
    }
}

void UniversitySystem::addStudent(const Student& student) {
    if (findStudent(student.getRollNumber()) == nullptr) {
        students.push_back(student);
        std::cout << "Student " << student.getRollNumber() << " added successfully." << std::endl;
    }
    else {
        std::cout << "Student " << student.getRollNumber() << " already exists." << std::endl;
    }
}

void UniversitySystem::addFaculty(const Faculty& faculty) {
    if (findFaculty(faculty.getFacultyId()) == nullptr) {
        this->faculty.push_back(faculty);
        std::cout << "Faculty " << faculty.getFacultyId() << " added successfully." << std::endl;
    }
    else {
        std::cout << "Faculty " << faculty.getFacultyId() << " already exists." << std::endl;
    }
}

void UniversitySystem::addRoom(const Room& room) {
    if (findRoom(room.getRoomId()) == nullptr) {
        rooms.push_back(room);
        std::cout << "Room " << room.getRoomId() << " added successfully." << std::endl;
    }
    else {
        std::cout << "Room " << room.getRoomId() << " already exists." << std::endl;
    }
}