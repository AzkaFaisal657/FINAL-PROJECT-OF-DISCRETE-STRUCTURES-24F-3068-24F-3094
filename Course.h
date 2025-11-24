#pragma once
#include <string>
#include <vector>

class Course {
private:
    std::string code;
    std::string name;
    int creditHours;
    std::string type;
    int semester;
    std::string prerequisite;

public:
    Course(const std::string& code, const std::string& name, int creditHours,
        const std::string& type, int semester, const std::string& prerequisite = "");

    // Getters
    std::string getCode() const;
    std::string getName() const;
    int getCreditHours() const;
    std::string getType() const;
    int getSemester() const;
    std::string getPrerequisite() const;

    // Setters
    void setCode(const std::string& code);
    void setName(const std::string& name);
    void setCreditHours(int creditHours);
    void setType(const std::string& type);
    void setSemester(int semester);
    void setPrerequisite(const std::string& prerequisite);

    std::string toString() const;
};