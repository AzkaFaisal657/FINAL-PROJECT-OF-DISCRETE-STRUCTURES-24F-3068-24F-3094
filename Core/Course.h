#pragma once
#include <string>
#include <vector>

using namespace std;

class Course {
private:
    string code;
    string name;
    int creditHours;
    string type;
    int semester;
    vector<string> prerequisites;

public:
    Course();
    Course(string code, string name, int credits, string type, int sem);

    void addPrerequisite(string prereqCode);
    bool hasPrerequisite(string prereqCode) const;
    size_t getPrereqCount() const;
    string getPrerequisite(int index) const;

    string getCode() const { return code; }
    string getName() const { return name; }
    int getCreditHours() const { return creditHours; }
    string getType() const { return type; }
    int getSemester() const { return semester; }

    void display() const;
};