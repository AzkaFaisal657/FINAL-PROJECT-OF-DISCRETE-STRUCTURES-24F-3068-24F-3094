#include "FunctionsModule.h"

void FunctionsModule::addMapping(string from, string to) {
    Mapping m;
    m.domain = from;
    m.codomain = to;
    mappings.push_back(m);
}

void FunctionsModule::clearMappings() {
    mappings.clear();
}

Mapping FunctionsModule::getMapping(int index) const {
    if (index >= 0 && index < mappings.size()) {
        return mappings[index];
    }
    Mapping empty = { "", "" };
    return empty;
}

bool FunctionsModule::isInjective() {
    for (int i = 0; i < mappings.size(); i++) {
        for (int j = i + 1; j < mappings.size(); j++) {
            if (mappings[i].codomain == mappings[j].codomain &&
                mappings[i].domain != mappings[j].domain) {
                return false;
            }
        }
    }
    return true;
}

bool FunctionsModule::isSurjective(vector<string> codomain) {
    for (const string& codomainElement : codomain) {
        bool found = false;
        for (const Mapping& m : mappings) {
            if (m.codomain == codomainElement) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool FunctionsModule::isBijective(vector<string> codomain) {
    return isInjective() && isSurjective(codomain);
}

void FunctionsModule::display(string functionName) const {
    cout << functionName << " = { ";
    for (int i = 0; i < mappings.size(); i++) {
        cout << "(" << mappings[i].domain << " → " << mappings[i].codomain << ")";
        if (i < mappings.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void FunctionsModule::demonstrateFunctions() {
    cout << "\n=== MODULE 7: FUNCTIONS & MAPPINGS ===" << endl;

    cout << "\n1. STUDENT → COURSE MAPPING:" << endl;
    FunctionsModule studentCourse;
    studentCourse.addMapping("Ali", "CS101");
    studentCourse.addMapping("Sara", "CS102");
    studentCourse.addMapping("Ahmed", "CS101");

    studentCourse.display("StudentToCourse");
    cout << "Injective (one-to-one)? " << (studentCourse.isInjective() ? "Yes" : "No") << endl;
    cout << "Reason: Multiple students can map to same course" << endl;

    cout << "\n2. COURSE → FACULTY MAPPING:" << endl;
    FunctionsModule courseFaculty;
    courseFaculty.addMapping("CS1002", "Dr_Qamar");
    courseFaculty.addMapping("CS1004", "Dr_Affan");
    courseFaculty.addMapping("CS2001", "Dr_Qamar");

    courseFaculty.display("CourseToFaculty");
    cout << "Injective? " << (courseFaculty.isInjective() ? "Yes" : "No") << endl;
    cout << "Reason: One faculty can teach multiple courses" << endl;

    cout << "\n3. BIJECTION EXAMPLE:" << endl;
    FunctionsModule idToStudent;
    idToStudent.addMapping("22K-0001", "Ali");
    idToStudent.addMapping("22K-0002", "Sara");
    idToStudent.addMapping("22K-0003", "Ahmed");

    vector<string> students = { "Ali", "Sara", "Ahmed" };
    idToStudent.display("IDToStudent");
    cout << "Injective? " << (idToStudent.isInjective() ? "Yes" : "No") << endl;
    cout << "Surjective? " << (idToStudent.isSurjective(students) ? "Yes" : "No") << endl;
    cout << "Bijective? " << (idToStudent.isBijective(students) ? "Yes" : "No") << endl;
    cout << "This is a bijection: each ID maps to exactly one unique student" << endl;
}

void FunctionsModule::demonstrateComposition() {
    cout << "\n4. FUNCTION COMPOSITION:" << endl;
    cout << "f: Student → StudentID" << endl;
    cout << "g: StudentID → Semester" << endl;
    cout << "g ∘ f: Student → Semester" << endl;
    cout << "Example: g(f(Ali)) = g(22K-0001) = 3" << endl;

    cout << "\n5. INVERSE FUNCTION:" << endl;
    cout << "f: StudentID → Student (bijection)" << endl;
    cout << "f⁻¹: Student → StudentID" << endl;
    cout << "Example: f(22K-0001) = Ali, f⁻¹(Ali) = 22K-0001" << endl;
}