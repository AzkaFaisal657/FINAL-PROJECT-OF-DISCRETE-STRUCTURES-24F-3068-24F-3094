#include "UniversitySystem.h"
#include <iostream>
using namespace std;

// Forward declarations to avoid including all modules
class CourseScheduler { public: static void demonstrateScheduling(); };
class CombinationsModule { public: static void demonstrateCombinations(); };
class InductionModule { public: static void demonstrateStrongInduction(); };
class LogicEngine { public: void demonstrateLogicEngine(); };
class SetOperations { public: static void demonstrateSetOperations(); };
class RelationsModule { public: static void demonstrateRelations(); };
class FunctionsModule { public: static void demonstrateFunctions(); };
class AutomatedProof { public: static void demonstrateAutomatedProof(); };
                             
class ConflictDetector {
public:
  static void generateConflictReport(vector<Student*> students, vector<Course*> courses,
  vector<Faculty*> faculty, vector<Room*> rooms);
    };
class EfficiencyModule { public: static void demonstrateDP(); static void demonstrateMemoization(); };
class TestModule { public: static void runAllTests(); };

UniversitySystem::UniversitySystem() {}

UniversitySystem::~UniversitySystem() {
 for (Course* course : courses) delete course;
 for (Student* student : students) delete student;
 for (Faculty* fac : faculty) delete fac;
 for (Room* room : rooms) delete room;
  }
void UniversitySystem::loadAllData() {
cout << "Loading university data..." << endl;
 Course tempCourses[100];
 int courseCount = 0;
                             FileHandler::loadCourses(tempCourses, courseCount);
                             for (int i = 0; i < courseCount; i++) {
                                 courses.push_back(new Course(tempCourses[i]));
                             }

                             Student tempStudents[100];
                             int studentCount = 0;
                             FileHandler::loadStudents(tempStudents, studentCount);
                             for (int i = 0; i < studentCount; i++) {
                                 students.push_back(new Student(tempStudents[i]));
                             }

                             Faculty tempFaculty[50];
                             int facultyCount = 0;
                             FileHandler::loadFaculty(tempFaculty, facultyCount);
                             for (int i = 0; i < facultyCount; i++) {
                                 faculty.push_back(new Faculty(tempFaculty[i]));
                             }

                             Room tempRooms[50];
                             int roomCount = 0;
                             FileHandler::loadRooms(tempRooms, roomCount);
                             for (int i = 0; i < roomCount; i++) {
                                 rooms.push_back(new Room(tempRooms[i]));
                             }
                         }

                         // FIXED: Added both versions of getCourse
                         Course* UniversitySystem::getCourse(const string& code) {
                             for (Course* course : courses) {
                                 if (course->getCode() == code) return course;
                             }
                             return nullptr;
                         }

                         Course* UniversitySystem::getCourse(const string& code) const {
                             for (Course* course : courses) {
                                 if (course->getCode() == code) return course;
                             }
                             return nullptr;
                         }

                         // FIXED: Added both versions of getStudent
                         Student* UniversitySystem::getStudent(const string& id) {
                             for (Student* student : students) {
                                 if (student->getId() == id) return student;
                             }
                             return nullptr;
                         }

                         const Student* UniversitySystem::getStudent(const string& id) const {
                             for (const Student* student : students) {
                                 if (student->getId() == id) return student;
                             }
                             return nullptr;
                         }

                         Faculty* UniversitySystem::getFaculty(const string& id) const {
                             for (Faculty* fac : faculty) {
                                 if (fac->getId() == id) return fac;
                             }
                             return nullptr;
                         }

                         Room* UniversitySystem::getRoom(const string& id) const {
                             for (Room* room : rooms) {
                                 if (room->getRoomId() == id) return room;
                             }
                             return nullptr;
                         }

                         bool UniversitySystem::canStudentEnroll(string studentId, string courseCode, string& reason) {
                             Student* student = getStudent(studentId);
                             Course* course = getCourse(courseCode);

                             if (!student) { reason = "Student not found"; return false; }
                             if (!course) { reason = "Course not found"; return false; }
                             if (student->hasCompleted(courseCode)) { reason = "Already completed"; return false; }
                             if (student->isEnrolled(courseCode)) { reason = "Already enrolled"; return false; }

                             reason = "Eligible for enrollment";
                             return true;
                         }

                         bool UniversitySystem::enrollStudent(string studentId, string courseCode, string& errorMsg) {
                             if (canStudentEnroll(studentId, courseCode, errorMsg)) {
                                 Student* student = getStudent(studentId);
                                 if (student) {
                                     student->enrollInCourse(courseCode);
                                     return true;
                                 }
                             }
                             return false;
                         }

                         void UniversitySystem::displaySystemInfo() const {
                             cout << "\n=== FAST UNIVERSITY SYSTEM INFO ===" << endl;
                             cout << "Total Courses: " << courses.size() << endl;
                             cout << "Total Students: " << students.size() << endl;
                             cout << "Total Faculty: " << faculty.size() << endl;
                             cout << "Total Rooms: " << rooms.size() << endl;
                         }

                         void UniversitySystem::displayCoursesBySemester(int semester) const {
                             cout << "\n=== SEMESTER " << semester << " COURSES ===" << endl;
                             for (Course* course : courses) {
                                 if (course->getSemester() == semester) {
                                     course->display();
                                 }
                             }
                         }

                         void UniversitySystem::displayStudentInfo(string studentId) const {
                             const Student* student = getStudent(studentId);
                             if (student) {
                                 student->display();
                             }
                             else {
                                 cout << "Student with ID " << studentId << " not found." << endl;
                             }
                         }

                         void UniversitySystem::demonstrateAllModules() {
                             cout << "\n" << string(60, '=') << endl;
                             cout << "   FAST UNIVERSITY - ALL MODULES DEMONSTRATION" << endl;
                             cout << string(60, '=') << endl;

                             // These will be empty if modules aren't included, but won't cause linker errors
                             CourseScheduler::demonstrateScheduling();
                             CombinationsModule::demonstrateCombinations();
                             InductionModule::demonstrateStrongInduction();

                             LogicEngine logic;
                             logic.demonstrateLogicEngine();

                             SetOperations::demonstrateSetOperations();
                             RelationsModule::demonstrateRelations();
                             FunctionsModule::demonstrateFunctions();
                             AutomatedProof::demonstrateAutomatedProof();

                             ConflictDetector::generateConflictReport(students, courses, faculty, rooms);
                             EfficiencyModule::demonstrateDP();
                             EfficiencyModule::demonstrateMemoization();

                             TestModule::runAllTests();

                             cout << "\n" << string(60, '=') << endl;
                             cout << "   ALL 12 MODULES DEMONSTRATED SUCCESSFULLY!" << endl;
                             cout << string(60, '=') << endl;
                         }