#pragma once
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <fstream>
#include "Course.h"
#include "Faculty.h"
#include "Room.h"
#include "Student.h"
using namespace std;

class FileHandler {
public:
    static void loadCourses(Course courses[], int& count);
    static void loadFaculty(Faculty faculty[], int& count);
    static void loadRooms(Room rooms[], int& count);
    static void loadStudents(Student students[], int& count);
    static void saveCourses(Course courses[], int count);
    static void saveStudentProgress(Student students[], int count);

private:
    static void splitString(string str, string arr[], int& arrSize, char delimiter);

    static const string COURSES_FILE;
    static const string FACULTY_FILE;
    static const string ROOMS_FILE;
    static const string STUDENTS_FILE;
};

#endif