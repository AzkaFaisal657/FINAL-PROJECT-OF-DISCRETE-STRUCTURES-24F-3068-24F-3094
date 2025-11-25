#include "TestModule.h"
#include <iostream>
#include <algorithm>
#include <map>

TestModule::TestModule(const std::vector<Student>& students, const std::vector<Course>& courses,
    const std::vector<Faculty>& faculty, const std::vector<Room>& rooms)
    : allStudents(students), allCourses(courses), allFaculty(faculty), allRooms(rooms) {}

void TestModule::runAllTests() {
    std::cout << "\n-------------------------------------------------------------" << std::endl;
    std::cout << "          UNIT TESTING & BENCHMARKING MODULE" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    std::cout << "Loading test data from FAST University SE Department..." << std::endl;
    std::cout << "✓ Courses loaded: " << allCourses.size() << std::endl;
    std::cout << "✓ Students loaded: " << allStudents.size() << std::endl;
    std::cout << "✓ Faculty loaded: " << allFaculty.size() << std::endl;
    std::cout << "✓ Rooms loaded: " << allRooms.size() << std::endl;

    // Count prerequisites
    int prerequisiteCount = 0;
    for (const auto& course : allCourses) {
        if (!course.getPrerequisite().empty()) prerequisiteCount++;
    }
    std::cout << "✓ Prerequisites loaded: " << prerequisiteCount << std::endl;

    std::cout << "\nRunning Comprehensive Test Suite..." << std::endl;
    std::cout << "=========================================" << std::endl;

    int totalTests = 0;
    int passedTests = 0;

    // Run individual tests
    if (testStudentEnrollment()) passedTests++; totalTests++;
    if (testCourseScheduling()) passedTests++; totalTests++;
    if (testStudentGroups()) passedTests++; totalTests++;
    if (testFacultyAssignments()) passedTests++; totalTests++;
    if (testRoomAllocations()) passedTests++; totalTests++;
    if (testSetOperations()) passedTests++; totalTests++;
    if (testRelationsFunctions()) passedTests++; totalTests++;
    if (testAutomatedProofs()) passedTests++; totalTests++;
    if (testInductionModule()) passedTests++; totalTests++;
    if (testLogicEngine()) passedTests++; totalTests++;
    if (testConflictDetection()) passedTests++; totalTests++;
    if (testEfficiencyBenchmarks()) passedTests++; totalTests++;

    displayFinalSummary(passedTests, totalTests);
}

bool TestModule::testStudentEnrollment() {
    std::cout << "\n1. STUDENT ENROLLMENT VERIFICATION" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    // Test 1: All students have valid roll numbers
    for (const auto& student : allStudents) {
        if (student.getRollNumber().empty()) {
            std::cout << "✗ FAIL: Student with empty roll number found" << std::endl;
            allTestsPassed = false;
            break;
        }
    }
    if (allTestsPassed) std::cout << "✓ All students have valid roll numbers" << std::endl;

    // Test 2: All students enrolled in courses matching their semester
    bool semesterMatch = true;
    for (const auto& student : allStudents) {
        for (const auto& courseCode : student.getEnrolledCourses()) {
            Course* course = nullptr;
            for (auto& c : allCourses) {
                if (c.getCode() == courseCode) {
                    course = &c;
                    break;
                }
            }
            if (course && course->getSemester() > student.getCurrentSemester()) {
                std::cout << "✗ FAIL: Student " << student.getRollNumber()
                    << " enrolled in future course " << courseCode << std::endl;
                semesterMatch = false;
                allTestsPassed = false;
            }
        }
    }
    if (semesterMatch) std::cout << "✓ All students enrolled in appropriate semester courses" << std::endl;

    // Test 3: Check for duplicate roll numbers
    std::set<std::string> rollNumbers;
    bool uniqueRolls = true;
    for (const auto& student : allStudents) {
        if (rollNumbers.find(student.getRollNumber()) != rollNumbers.end()) {
            std::cout << "✗ FAIL: Duplicate roll number " << student.getRollNumber() << std::endl;
            uniqueRolls = false;
            allTestsPassed = false;
        }
        rollNumbers.insert(student.getRollNumber());
    }
    if (uniqueRolls) std::cout << "✓ All student roll numbers are unique" << std::endl;

    displayTestResults(allTestsPassed, "Student Enrollment");
    return allTestsPassed;
}

bool TestModule::testCourseScheduling() {
    std::cout << "\n2. COURSE SCHEDULING MODULE" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    // Test CourseScheduler with actual data
    CourseScheduler scheduler(allCourses, allStudents);

    // Test 1: Generate valid sequences
    try {
        auto sequences = scheduler.generateValidSequences(5);
        if (sequences.empty()) {
            std::cout << "⚠ WARNING: No valid course sequences generated" << std::endl;
        }
        else {
            std::cout << "✓ Generated " << sequences.size() << " valid course sequences" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Course scheduling crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    // Test 2: Check prerequisite validation
    std::vector<std::string> validSequence = { "CS1002", "CS1004", "CS2001", "CS2005" };
    std::vector<std::string> invalidSequence = { "CS2005", "CS1002" }; // Wrong order

    bool validCheck = scheduler.checkPrerequisiteOrder(validSequence);
    bool invalidCheck = scheduler.checkPrerequisiteOrder(invalidSequence);

    if (validCheck && !invalidCheck) {
        std::cout << "✓ Prerequisite validation working correctly" << std::endl;
    }
    else {
        std::cout << "✗ FAIL: Prerequisite validation incorrect" << std::endl;
        allTestsPassed = false;
    }

    // Test 3: Student schedule recommendation
    if (!allStudents.empty()) {
        auto recommended = scheduler.getRecommendedSchedule(allStudents[0], allStudents[0].getCurrentSemester());
        std::cout << "✓ Schedule recommendation generated for " << allStudents[0].getRollNumber() << std::endl;
    }

    displayTestResults(allTestsPassed, "Course Scheduling");
    return allTestsPassed;
}

bool TestModule::testStudentGroups() {
    std::cout << "\n3. STUDENT GROUP COMBINATIONS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    CombinationsModule combModule(allStudents, allCourses);

    // Test 1: Generate groups for a course
    try {
        auto groups = combModule.generateStudentGroups("CS2001", 4);
        if (!groups.empty()) {
            std::cout << "✓ Generated " << groups.size() << " student groups for CS2001" << std::endl;
        }
        else {
            std::cout << "⚠ WARNING: No groups generated for CS2001" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Group generation crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    // Test 2: Combination calculation
    long long comb = combModule.calculateCombinations(10, 3);
    if (comb == 120) {
        std::cout << "✓ Combination calculation correct: C(10,3) = 120" << std::endl;
    }
    else {
        std::cout << "✗ FAIL: Combination calculation wrong: C(10,3) = " << comb << std::endl;
        allTestsPassed = false;
    }

    // Test 3: Large combination handling
    long long largeComb = combModule.calculateCombinations(78, 8);
    if (largeComb > 0) {
        std::cout << "✓ Large combination handled: C(78,8) = " << largeComb << std::endl;
    }
    else {
        std::cout << "✗ FAIL: Large combination calculation failed" << std::endl;
        allTestsPassed = false;
    }

    displayTestResults(allTestsPassed, "Student Groups");
    return allTestsPassed;
}

bool TestModule::testFacultyAssignments() {
    std::cout << "\n4. FACULTY ASSIGNMENTS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    // Test 1: Check if each course has exactly one faculty
    std::map<std::string, int> courseFacultyCount;
    for (const auto& faculty : allFaculty) {
        for (const auto& courseCode : faculty.getAssignedCourses()) {
            courseFacultyCount[courseCode]++;
        }
    }

    bool oneFacultyPerCourse = true;
    for (const auto& pair : courseFacultyCount) {
        if (pair.second != 1) {
            std::cout << "✗ FAIL: Course " << pair.first << " has " << pair.second << " faculty" << std::endl;
            oneFacultyPerCourse = false;
            allTestsPassed = false;
        }
    }
    if (oneFacultyPerCourse) std::cout << "✓ Each course assigned to exactly one faculty" << std::endl;

    // Test 2: Check faculty overload
    int maxCoursesPerFaculty = 4;
    bool facultyOverload = false;
    for (const auto& faculty : allFaculty) {
        if (faculty.getAssignedCourses().size() > maxCoursesPerFaculty) {
            std::cout << "✗ FAIL: Faculty " << faculty.getName() << " overloaded with "
                << faculty.getAssignedCourses().size() << " courses" << std::endl;
            facultyOverload = true;
            allTestsPassed = false;
        }
    }
    if (!facultyOverload) std::cout << "✓ No faculty overload detected" << std::endl;

    displayTestResults(allTestsPassed, "Faculty Assignments");
    return allTestsPassed;
}

bool TestModule::testRoomAllocations() {
    std::cout << "\n5. ROOM ALLOCATIONS & CAPACITY" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    // Test 1: Room capacity validation
    bool validCapacity = true;
    for (const auto& room : allRooms) {
        if (room.getCapacity() <= 0) {
            std::cout << "✗ FAIL: Room " << room.getRoomId() << " has invalid capacity" << std::endl;
            validCapacity = false;
            allTestsPassed = false;
        }
    }
    if (validCapacity) std::cout << "✓ All rooms have valid capacity" << std::endl;

    // Test 2: Room status validation
    bool validStatus = true;
    for (const auto& room : allRooms) {
        if (room.getStatus().empty()) {
            std::cout << "✗ FAIL: Room " << room.getRoomId() << " has empty status" << std::endl;
            validStatus = false;
            allTestsPassed = false;
        }
    }
    if (validStatus) std::cout << "✓ All rooms have valid status" << std::endl;

    // Test 3: Sufficient total capacity
    int totalCapacity = 0;
    for (const auto& room : allRooms) {
        totalCapacity += room.getCapacity();
    }

    if (totalCapacity >= allStudents.size()) {
        std::cout << "✓ Sufficient room capacity: " << totalCapacity << " for " << allStudents.size() << " students" << std::endl;
    }
    else {
        std::cout << "⚠ WARNING: Room capacity (" << totalCapacity << ") may be insufficient for "
            << allStudents.size() << " students" << std::endl;
    }

    displayTestResults(allTestsPassed, "Room Allocations");
    return allTestsPassed;
}

bool TestModule::testSetOperations() {
    std::cout << "\n6. SET OPERATIONS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    SetOperations setOps(allStudents, allCourses, allFaculty);

    // Test 1: Basic set operations
    std::vector<std::string> setA = { "A", "B", "C" };
    std::vector<std::string> setB = { "B", "C", "D" };

    auto unionSet = setOps.setUnion(setA, setB);
    auto intersectionSet = setOps.setIntersection(setA, setB);
    auto differenceSet = setOps.setDifference(setA, setB);

    if (unionSet.size() == 4 && intersectionSet.size() == 2 && differenceSet.size() == 1) {
        std::cout << "✓ Basic set operations working correctly" << std::endl;
    }
    else {
        std::cout << "✗ FAIL: Basic set operations incorrect" << std::endl;
        allTestsPassed = false;
    }

    // Test 2: University-specific set operations
    try {
        auto commonStudents = setOps.getStudentsInBothCourses("CS1002", "CS1004");
        std::cout << "✓ University set operations working: " << commonStudents.size() << " students in both courses" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: University set operations crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    // Test 3: Power set generation
    std::vector<std::string> smallSet = { "A", "B", "C" };
    auto powerSet = setOps.generatePowerSet(smallSet);
    if (powerSet.size() == 8) { // 2^3 = 8
        std::cout << "✓ Power set generation correct: 2^3 = 8 subsets" << std::endl;
    }
    else {
        std::cout << "✗ FAIL: Power set generation wrong: " << powerSet.size() << " subsets" << std::endl;
        allTestsPassed = false;
    }

    displayTestResults(allTestsPassed, "Set Operations");
    return allTestsPassed;
}

bool TestModule::testRelationsFunctions() {
    std::cout << "\n7. RELATIONS & FUNCTIONS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    // Test Relations Module
    RelationsModule relations(allStudents, allCourses, allFaculty);
    try {
        relations.analyzeStudentCourseRelation();
        std::cout << "✓ Relations module working correctly" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Relations module crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    // Test Functions Module
    FunctionsModule functions(allCourses, allStudents, allFaculty);
    try {
        functions.analyzeCourseToFaculty();
        std::cout << "✓ Functions module working correctly" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Functions module crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    displayTestResults(allTestsPassed, "Relations & Functions");
    return allTestsPassed;
}

bool TestModule::testAutomatedProofs() {
    std::cout << "\n8. AUTOMATED PROOFS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    AutomatedProof proof(allStudents, allCourses, allFaculty);

    try {
        proof.generatePrerequisiteProof("Database Systems requires Data Structures");
        std::cout << "✓ Automated proof generation working" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Automated proof crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    try {
        proof.generateCreditLimitProof();
        std::cout << "✓ Credit limit proof working" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Credit limit proof crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    displayTestResults(allTestsPassed, "Automated Proofs");
    return allTestsPassed;
}

bool TestModule::testInductionModule() {
    std::cout << "\n9. INDUCTION MODULE" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    InductionModule induction(allStudents, allCourses);

    try {
        bool chainValid = induction.verifyPrerequisiteChain("CS2005");
        if (chainValid) {
            std::cout << "✓ Prerequisite chain verification working" << std::endl;
        }
        else {
            std::cout << "⚠ WARNING: Prerequisite chain validation failed" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Induction module crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    try {
        auto results = induction.verifyAllStudentsForCourse("CS2001");
        std::cout << "✓ Student eligibility verification working" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Student eligibility check crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    displayTestResults(allTestsPassed, "Induction Module");
    return allTestsPassed;
}

bool TestModule::testLogicEngine() {
    std::cout << "\n10. LOGIC ENGINE" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    LogicEngine logic(allCourses, allStudents, allFaculty);

    // Test propositional logic operations
    if (logic.logicalAND(true, true) == true &&
        logic.logicalAND(true, false) == false &&
        logic.logicalOR(false, true) == true &&
        logic.logicalNOT(true) == false) {
        std::cout << "✓ Propositional logic operations correct" << std::endl;
    }
    else {
        std::cout << "✗ FAIL: Propositional logic operations incorrect" << std::endl;
        allTestsPassed = false;
    }

    // Test rule evaluation
    try {
        bool result = logic.evaluateRule("If Dr. Ahmed teaches CS2001, lab must be L201");
        std::cout << "✓ Rule evaluation working: " << (result ? "VALID" : "INVALID") << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Rule evaluation crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    displayTestResults(allTestsPassed, "Logic Engine");
    return allTestsPassed;
}

bool TestModule::testConflictDetection() {
    std::cout << "\n11. CONFLICT DETECTION" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    ConflictDetector detector(allStudents, allCourses, allFaculty, allRooms);

    try {
        detector.checkAllConflicts();
        std::cout << "✓ Conflict detection working" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Conflict detection crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    // Test specific conflict detection methods
    try {
        auto overloaded = detector.getStudentsWithCreditOverload();
        auto missingPrereqs = detector.getStudentsWithMissingPrerequisites();
        std::cout << "✓ Specific conflict checks working" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Specific conflict checks crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    displayTestResults(allTestsPassed, "Conflict Detection");
    return allTestsPassed;
}

bool TestModule::testEfficiencyBenchmarks() {
    std::cout << "\n12. EFFICIENCY BENCHMARKS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bool allTestsPassed = true;

    EfficiencyModule efficiency(allStudents, allCourses);

    try {
        efficiency.benchmarkAllAlgorithms();
        std::cout << "✓ Efficiency benchmarking working" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "✗ FAIL: Efficiency benchmarking crashed: " << e.what() << std::endl;
        allTestsPassed = false;
    }

    displayTestResults(allTestsPassed, "Efficiency Benchmarks");
    return allTestsPassed;
}

void TestModule::displayTestResults(bool result, const std::string& testName) {
    std::cout << "[" << (result ? "PASS" : "FAIL") << "] " << testName << std::endl;
}

void TestModule::displayFinalSummary(int passed, int total) {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "          TESTING SUMMARY" << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Total Tests Run: " << total << std::endl;
    std::cout << "Tests Passed: " << passed << std::endl;
    std::cout << "Tests Failed: " << (total - passed) << std::endl;

    double successRate = (passed * 100.0) / total;
    std::cout << "Success Rate: " << successRate << "%" << std::endl;

    std::cout << "\nSystem Integrity: "
        << (successRate >= 80 ? "HIGH ✓" :
            successRate >= 60 ? "MEDIUM ⚠" : "LOW ✗") << std::endl;

    if (successRate == 100) {
        std::cout << "🎉 ALL TESTS PASSED! System is fully operational." << std::endl;
    }
    else if (successRate >= 80) {
        std::cout << "✅ System is mostly operational. Minor issues detected." << std::endl;
    }
    else {
        std::cout << "❌ System has significant issues that need attention." << std::endl;
    }

    std::cout << "\nUnit Testing & Benchmarking Completed." << std::endl;
    std::cout << "FAST University SE Department System Validation Complete." << std::endl;
}