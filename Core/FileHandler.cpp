#include "FileHandler.h"
#include <sstream>
#include <iostream>
using namespace std;

// Define the file paths
const string FileHandler::COURSES_FILE = "data/courses.txt";
const string FileHandler::FACULTY_FILE = "data/teachers.txt";
const string FileHandler::ROOMS_FILE = "data/rooms.txt";
const string FileHandler::STUDENTS_FILE = "data/students.txt";

void FileHandler::splitString(string str, string arr[], int& arrSize, char delimiter) {
    arrSize = 0;
    string token = "";

    for (int i = 0; i < (int)str.length() && arrSize < 50; i++) {
        if (str[i] == delimiter) {
            if (!token.empty()) {
                arr[arrSize++] = token;
                token = "";
            }
        }
        else {
            token += str[i];
        }
    }

    if (!token.empty() && arrSize < 50) {
        arr[arrSize++] = token;
    }
}

void FileHandler::loadCourses(Course courses[], int& count) {
    ifstream file(COURSES_FILE);
    count = 0;

    if (!file.is_open()) {
        cout << "Warning: Could not open " << COURSES_FILE << endl;
        return;
    }

    string line;
    while (getline(file, line) && count < 100) {
        if (line.empty()) continue;

        string tokens[10];
        int tokenCount;
        splitString(line, tokens, tokenCount, ',');

        if (tokenCount >= 5) {
            string code = tokens[0];
            string name = tokens[1];
            int credits = atoi(tokens[2].c_str());
            string type = tokens[3];
            int semester = atoi(tokens[4].c_str());

            courses[count] = Course(code, name, credits, type, semester);

            if (tokenCount > 5 && !tokens[5].empty()) {
                string prereqs[10];
                int prereqCount;
                splitString(tokens[5], prereqs, prereqCount, ';');

                for (int i = 0; i < prereqCount; i++) {
                    courses[count].addPrerequisite(prereqs[i]);
                }
            }

            count++;
        }
    }

    file.close();
    cout << "Loaded " << count << " courses from file." << endl;
}

void FileHandler::loadFaculty(Faculty faculty[], int& count) {
    ifstream file(FACULTY_FILE);
    count = 0;

    if (!file.is_open()) {
        cout << "Warning: Could not open " << FACULTY_FILE << endl;
        return;
    }

    string line;
    while (getline(file, line) && count < 50) {
        if (line.empty()) continue;

        string tokens[10];
        int tokenCount;
        splitString(line, tokens, tokenCount, ',');

        if (tokenCount >= 3) {
            faculty[count] = Faculty(tokens[0], tokens[1], tokens[2]);
            count++;
        }
    }

    file.close();
    cout << "Loaded " << count << " faculty members from file." << endl;
}

void FileHandler::loadRooms(Room rooms[], int& count) {
    ifstream file(ROOMS_FILE);
    count = 0;

    if (!file.is_open()) {
        cout << "Warning: Could not open " << ROOMS_FILE << endl;
        return;
    }

    string line;
    while (getline(file, line) && count < 50) {
        if (line.empty()) continue;

        string tokens[10];
        int tokenCount;
        splitString(line, tokens, tokenCount, ',');

        if (tokenCount >= 4) {
            string id = tokens[0];
            string type = tokens[1];
            int capacity = atoi(tokens[2].c_str());
            string status = tokens[3];

            rooms[count] = Room(id, type, capacity, status);
            count++;
        }
    }

    file.close();
    cout << "Loaded " << count << " rooms from file." << endl;
}

void FileHandler::loadStudents(Student students[], int& count) {
    ifstream file(STUDENTS_FILE);
    count = 0;

    if (!file.is_open()) {
        cout << "Warning: Could not open " << STUDENTS_FILE << endl;
        return;
    }

    string line;
    while (getline(file, line) && count < 200) {
        if (line.empty()) continue;

        string tokens[100];
        int tokenCount;
        splitString(line, tokens, tokenCount, ',');

        if (tokenCount >= 3) {
            string id = tokens[0];
            string name = tokens[1];
            int semester = atoi(tokens[2].c_str());

            students[count] = Student(id, name, semester);

            if (tokenCount > 3 && !tokens[3].empty()) {
                string completed[50];
                int completedCount;
                splitString(tokens[3], completed, completedCount, ';');

                for (int i = 0; i < completedCount; i++) {
                    students[count].completeCourse(completed[i]);
                }
            }

            count++;
        }
    }

    file.close();
    if (count > 0) {
        cout << "Loaded " << count << " students from file." << endl;
    }
}

void FileHandler::saveCourses(Course courses[], int count) {
    ofstream file(COURSES_FILE);

    if (!file.is_open()) {
        cout << "Error: Could not save courses to file." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        file << courses[i].getCode() << ","
            << courses[i].getName() << ","
            << courses[i].getCreditHours() << ","
            << courses[i].getType() << ","
            << courses[i].getSemester();

        if (courses[i].getPrereqCount() > 0) {
            file << ",";
            for (int j = 0; j < courses[i].getPrereqCount(); j++) {
                file << courses[i].getPrerequisite(j);
                if (j < courses[i].getPrereqCount() - 1) {
                    file << ";";
                }
            }
        }

        file << endl;
    }

    file.close();
    cout << "Saved " << count << " courses to file." << endl;
}

void FileHandler::saveStudentProgress(Student students[], int count) {
    ofstream file(STUDENTS_FILE);

    if (!file.is_open()) {
        cout << "Error: Could not save student progress." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        file << students[i].getId() << ","
            << students[i].getName() << ","
            << students[i].getCurrentSemester();

        if (students[i].getCompletedCount() > 0) {
            file << ",";
            for (int j = 0; j < students[i].getCompletedCount(); j++) {
                file << students[i].getCompletedCourse(j);
                if (j < students[i].getCompletedCount() - 1) {
                    file << ";";
                }
            }
        }

        file << endl;
    }

    file.close();
    cout << "Saved " << count << " students to file." << endl;
}