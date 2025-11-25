#include "FileHandler.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <sstream>

std::vector<Course> FileHandler::loadCourses(const std::string& filename) {
    std::vector<Course> courses;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "ERROR: Cannot open courses file: " << filename << std::endl;
        std::cout << "Please make sure 'courses.txt' exists in your project directory." << std::endl;
        return courses; // Return empty vector instead of creating demo data
    }

    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        auto tokens = split(line, ',');
        if (tokens.size() >= 5) {
            try {
                std::string code = tokens[0];
                std::string name = tokens[1];
                int credits = std::stoi(tokens[2]);
                std::string type = tokens[3];
                int semester = std::stoi(tokens[4]);
                std::string prerequisite = tokens.size() > 5 ? tokens[5] : "";

                Course course(code, name, credits, type, semester, prerequisite);
                courses.push_back(course);
            }
            catch (const std::exception& e) {
                std::cout << "WARNING: Invalid course data at line " << lineNum << ": " << line << std::endl;
            }
        }
        else {
            std::cout << "WARNING: Invalid course format at line " << lineNum << ": " << line << std::endl;
        }
    }

    file.close();
    std::cout << "Loaded " << courses.size() << " courses from " << filename << std::endl;
    return courses;
}

std::vector<Student> FileHandler::loadStudents(const std::string& filename, const std::vector<Course>& allCourses) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "ERROR: Cannot open students file: " << filename << std::endl;
        std::cout << "Please make sure 'students.txt' exists in your project directory." << std::endl;
        return students; // Return empty vector instead of creating demo data
    }

    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            try {
                std::string roll = tokens[0];
                std::string name = tokens[1];
                int semester = std::stoi(tokens[2]);
                std::string coursesStr = tokens[3];

                auto courseTokens = split(coursesStr, ';');
                std::vector<std::string> enrolledCourses(courseTokens.begin(), courseTokens.end());

                Student student(roll, name, semester, enrolledCourses);

                // Mark courses from previous semesters as completed
                for (const auto& course : allCourses) {
                    if (course.getSemester() < semester) {
                        student.completeCourse(course.getCode());
                    }
                }

                students.push_back(student);
            }
            catch (const std::exception& e) {
                std::cout << "WARNING: Invalid student data at line " << lineNum << ": " << line << std::endl;
            }
        }
        else {
            std::cout << "WARNING: Invalid student format at line " << lineNum << ": " << line << std::endl;
        }
    }

    file.close();
    std::cout << "Loaded " << students.size() << " students from " << filename << std::endl;
    return students;
}

std::vector<Faculty> FileHandler::loadFaculty(const std::string& filename) {
    std::vector<Faculty> faculty;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "ERROR: Cannot open faculty file: " << filename << std::endl;
        std::cout << "Please make sure 'faculty.txt' exists in your project directory." << std::endl;
        return faculty; // Return empty vector instead of creating demo data
    }

    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            try {
                std::string facultyId = tokens[0];
                std::string name = tokens[1];
                std::string designation = tokens[2];
                std::string coursesStr = tokens[3];

                auto courseTokens = split(coursesStr, ';');
                std::vector<std::string> assignedCourses(courseTokens.begin(), courseTokens.end());

                Faculty fac(facultyId, name, designation, assignedCourses);
                faculty.push_back(fac);
            }
            catch (const std::exception& e) {
                std::cout << "WARNING: Invalid faculty data at line " << lineNum << ": " << line << std::endl;
            }
        }
        else {
            std::cout << "WARNING: Invalid faculty format at line " << lineNum << ": " << line << std::endl;
        }
    }

    file.close();
    std::cout << "Loaded " << faculty.size() << " faculty from " << filename << std::endl;
    return faculty;
}

std::vector<Room> FileHandler::loadRooms(const std::string& filename) {
    std::vector<Room> rooms;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "ERROR: Cannot open rooms file: " << filename << std::endl;
        std::cout << "Please make sure 'rooms.txt' exists in your project directory." << std::endl;
        return rooms; // Return empty vector instead of creating demo data
    }

    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            try {
                std::string roomId = tokens[0];
                std::string type = tokens[1];
                int capacity = std::stoi(tokens[2]);
                std::string status = tokens[3];

                Room room(roomId, type, capacity, status);
                rooms.push_back(room);
            }
            catch (const std::exception& e) {
                std::cout << "WARNING: Invalid room data at line " << lineNum << ": " << line << std::endl;
            }
        }
        else {
            std::cout << "WARNING: Invalid room format at line " << lineNum << ": " << line << std::endl;
        }
    }

    file.close();
    std::cout << "Loaded " << rooms.size() << " rooms from " << filename << std::endl;
    return rooms;
}

void FileHandler::saveCourses(const std::string& filename, const std::vector<Course>& courses) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "ERROR: Cannot save courses to " << filename << std::endl;
        return;
    }

    for (const auto& course : courses) {
        file << course.getCode() << "," << course.getName() << "," << course.getCreditHours() << ","
            << course.getType() << "," << course.getSemester() << "," << course.getPrerequisite() << "\n";
    }
    file.close();
    std::cout << "Saved " << courses.size() << " courses to " << filename << std::endl;
}

void FileHandler::saveStudents(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "ERROR: Cannot save students to " << filename << std::endl;
        return;
    }

    for (const auto& student : students) {
        file << student.getRollNumber() << "," << student.getName() << "," << student.getCurrentSemester() << ",";
        auto courses = student.getEnrolledCourses();
        for (size_t i = 0; i < courses.size(); ++i) {
            file << courses[i];
            if (i < courses.size() - 1) file << ";";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Saved " << students.size() << " students to " << filename << std::endl;
}

void FileHandler::saveFaculty(const std::string& filename, const std::vector<Faculty>& faculty) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "ERROR: Cannot save faculty to " << filename << std::endl;
        return;
    }

    for (const auto& fac : faculty) {
        file << fac.getFacultyId() << "," << fac.getName() << "," << fac.getDesignation() << ",";
        auto courses = fac.getAssignedCourses();
        for (size_t i = 0; i < courses.size(); ++i) {
            file << courses[i];
            if (i < courses.size() - 1) file << ";";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Saved " << faculty.size() << " faculty to " << filename << std::endl;
}

void FileHandler::saveRooms(const std::string& filename, const std::vector<Room>& rooms) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "ERROR: Cannot save rooms to " << filename << std::endl;
        return;
    }

    for (const auto& room : rooms) {
        file << room.getRoomId() << "," << room.getType() << "," << room.getCapacity() << "," << room.getStatus() << "\n";
    }
    file.close();
    std::cout << "Saved " << rooms.size() << " rooms to " << filename << std::endl;
}

std::vector<std::string> FileHandler::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    return tokens;
}