#pragma once
#include <vector>
#include <string>
#include "Course.h"
#include "Student.h"
#include "Faculty.h"
#include "Room.h"

class FileHandler {
public:
    static std::vector<Course> loadCourses(const std::string& filename);
    static std::vector<Student> loadStudents(const std::string& filename, const std::vector<Course>& allCourses);
    static std::vector<Faculty> loadFaculty(const std::string& filename);
    static std::vector<Room> loadRooms(const std::string& filename);

    static void saveCourses(const std::string& filename, const std::vector<Course>& courses);
    static void saveStudents(const std::string& filename, const std::vector<Student>& students);
    static void saveFaculty(const std::string& filename, const std::vector<Faculty>& faculty);
    static void saveRooms(const std::string& filename, const std::vector<Room>& rooms);

private:
    static std::vector<std::string> split(const std::string& str, char delimiter);
};