#pragma once
#include <string>
#include <vector>

class Faculty {
private:
    std::string facultyId;
    std::string name;
    std::string designation;
    std::vector<std::string> assignedCourses;

public:
    Faculty(const std::string& facultyId, const std::string& name,
        const std::string& designation, const std::vector<std::string>& assignedCourses);

    // Getters
    std::string getFacultyId() const;
    std::string getName() const;
    std::string getDesignation() const;
    std::vector<std::string> getAssignedCourses() const;

    // Setters
    void setFacultyId(const std::string& facultyId);
    void setName(const std::string& name);
    void setDesignation(const std::string& designation);
    void setAssignedCourses(const std::vector<std::string>& courses);

    void assignCourse(const std::string& courseCode);
    void removeCourse(const std::string& courseCode);
    bool teachesCourse(const std::string& courseCode) const;

    std::string toString() const;
};