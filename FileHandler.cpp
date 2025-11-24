#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<Course> FileHandler::loadCourses(const std::string& filename) {
    std::vector<Course> courses;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 5) {
            std::string prerequisite = tokens.size() > 5 ? tokens[5] : "";
            Course course(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3], std::stoi(tokens[4]), prerequisite);
            courses.push_back(course);
        }
    }

    return courses;
}

std::vector<Student> FileHandler::loadStudents(const std::string& filename, const std::vector<Course>& allCourses) {
    std::vector<Student> students;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            auto courseTokens = split(tokens[3], ';');
            std::vector<std::string> enrolledCourses(courseTokens.begin(), courseTokens.end());

            Student student(tokens[0], tokens[1], std::stoi(tokens[2]), enrolledCourses);

            // Mark all enrolled courses as completed for previous semesters
            int currentSem = std::stoi(tokens[2]);
            for (const auto& courseCode : enrolledCourses) {
                for (const auto& course : allCourses) {
                    if (course.getCode() == courseCode && course.getSemester() < currentSem) {
                        student.completeCourse(courseCode);
                    }
                }
            }

            students.push_back(student);
        }
    }

    return students;
}

std::vector<Faculty> FileHandler::loadFaculty(const std::string& filename) {
    std::vector<Faculty> faculty;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            auto courseTokens = split(tokens[3], ';');
            std::vector<std::string> assignedCourses(courseTokens.begin(), courseTokens.end());

            Faculty fac(tokens[0], tokens[1], tokens[2], assignedCourses);
            faculty.push_back(fac);
        }
    }

    return faculty;
}

std::vector<Room> FileHandler::loadRooms(const std::string& filename) {
    std::vector<Room> rooms;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            Room room(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3]);
            rooms.push_back(room);
        }
    }

    return rooms;
}

void FileHandler::saveCourses(const std::string& filename, const std::vector<Course>& courses) {
    std::ofstream file(filename);
    for (const auto& course : courses) {
        file << course.getCode() << "," << course.getName() << "," << course.getCreditHours() << ","
            << course.getType() << "," << course.getSemester() << "," << course.getPrerequisite() << "\n";
    }
}

void FileHandler::saveStudents(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream file(filename);
    for (const auto& student : students) {
        file << student.getRollNumber() << "," << student.getName() << "," << student.getCurrentSemester() << ",";
        auto courses = student.getEnrolledCourses();
        for (size_t i = 0; i < courses.size(); ++i) {
            file << courses[i];
            if (i < courses.size() - 1) file << ";";
        }
        file << "\n";
    }
}

void FileHandler::saveFaculty(const std::string& filename, const std::vector<Faculty>& faculty) {
    std::ofstream file(filename);
    for (const auto& fac : faculty) {
        file << fac.getFacultyId() << "," << fac.getName() << "," << fac.getDesignation() << ",";
        auto courses = fac.getAssignedCourses();
        for (size_t i = 0; i < courses.size(); ++i) {
            file << courses[i];
            if (i < courses.size() - 1) file << ";";
        }
        file << "\n";
    }
}

void FileHandler::saveRooms(const std::string& filename, const std::vector<Room>& rooms) {
    std::ofstream file(filename);
    for (const auto& room : rooms) {
        file << room.getRoomId() << "," << room.getType() << "," << room.getCapacity() << "," << room.getStatus() << "\n";
    }
}

std::vector<std::string> FileHandler::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}