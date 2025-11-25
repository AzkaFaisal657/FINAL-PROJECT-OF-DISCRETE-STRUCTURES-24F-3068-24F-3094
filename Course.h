#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>

class Course {
private:
    std::string code;
    std::string name;
    int creditHours;
    std::string type;
    int semester;
    std::string prerequisite;
    std::vector<std::string> prerequisites;

public:
    Course();
    Course(std::string code, std::string name, int credits, std::string type, int sem, std::string prereq = "");

    std::string getCode() const;
    std::string getName() const;
    int getCreditHours() const;
    std::string getType() const;
    int getSemester() const;
    std::string getPrerequisite() const;
    std::vector<std::string> getPrerequisites() const;

    void setCode(const std::string& code);
    void setName(const std::string& name);
    void setCreditHours(int credits);
    void setType(const std::string& type);
    void setSemester(int sem);
    void setPrerequisite(const std::string& prereq);

    void addPrerequisite(const std::string& prereqCode);
    bool hasPrerequisite(const std::string& prereqCode) const;
    void display() const;
    std::string toString() const;
};

#endif