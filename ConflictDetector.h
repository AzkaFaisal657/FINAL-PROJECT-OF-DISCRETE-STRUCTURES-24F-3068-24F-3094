#pragma once
#include "Course.h"
#include "Student.h"
#include "Faculty.h"
#include "Room.h"
#include <string>
#include <vector>
using namespace std;

class ConflictDetector {
public:
    static bool checkRoomCapacity(Room& room, int enrolledStudents);
    static bool checkCreditLimit(Student& student, vector<Course*> courses, int maxCredits);
    static bool detectPrerequisiteViolation(Student& student, Course& course, vector<Course*> allCourses);
    static bool detectTeachingOverload(Faculty& faculty, int maxCourses);
    static bool hasTimeConflict(string time1, string time2);
    static void generateConflictReport(vector<Student*> students, vector<Course*> courses,
        vector<Faculty*> faculty, vector<Room*> rooms);

private:
    static const int MAX_CREDITS_PER_SEMESTER = 18;
    static const int MAX_COURSES_PER_FACULTY = 4;
};