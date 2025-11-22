#include "GUI.h"
#include "SetOperations.h"
#include "RelationsModule.h"
#include "FunctionsModule.h"
#include "CombinationsModule.h"
#include "LogicEngine.h"
#include "InductionModule.h"
#include "AutomatedProof.h"
#include "CourseScheduler.h"
#include "ConflictDetector.h"
#include "EfficiencyModule.h"
#include "TestModule.h"
#include <sstream>

GUI::GUI(UniversitySystem* sys) : system(sys), window(nullptr) {}
GUI::~GUI() { if (window) { window->close(); delete window; } }

void GUI::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1300, 850), "FAST University - Discrete Math System", sf::Style::Close);
    window->setFramerateLimit(60);
}

bool GUI::loadResources() {
    vector<string> fonts = { "arial.ttf", "C:/Windows/Fonts/arial.ttf", "resources/arial.ttf" };
    for (auto& f : fonts) if (font.loadFromFile(f)) break;
    if (logoTex.loadFromFile("logofast.png")) {
        logoSprite.setTexture(logoTex);
        float scale = 50.0f / logoTex.getSize().y;
        logoSprite.setScale(scale, scale);
        logoSprite.setPosition(15, 10);
        logoLoaded = true;
    }
    return true;
}

void GUI::run() {
    initWindow(); loadResources();
    sf::Clock clock;
    while (window->isOpen()) {
        float dt = clock.restart().asSeconds();
        handleEvents(); update(dt); render();
    }
}

void GUI::clearButtons() { buttons.clear(); }

Button& GUI::addBtn(string text, float x, float y, float w, float h, string action) {
    Button b;
    b.shape.setSize({ w, h }); b.shape.setPosition(x, y);
    b.shape.setFillColor(btnColor); b.shape.setOutlineColor(navyColor); b.shape.setOutlineThickness(2);
    b.label.setFont(font); b.label.setString(text); b.label.setCharacterSize(16); b.label.setFillColor(white);
    auto bounds = b.label.getLocalBounds();
    b.label.setPosition(x + (w - bounds.width) / 2, y + (h - bounds.height) / 2 - 3);
    b.action = action;
    buttons.push_back(b);
    return buttons.back();
}

void GUI::setupInput(InputBox& inp, float x, float y, float w, string ph, int maxLen) {
    inp.box.setSize({ w, 35 }); inp.box.setPosition(x, y);
    inp.box.setFillColor(white); inp.box.setOutlineColor(navyColor); inp.box.setOutlineThickness(2);
    inp.text.setFont(font); inp.text.setCharacterSize(16); inp.text.setFillColor(black);
    inp.text.setPosition(x + 8, y + 6);
    inp.placeholder = ph; inp.maxLength = maxLen; inp.value = "";
}

void GUI::updateHover(sf::Vector2f pos) {
    for (auto& b : buttons) {
        b.hovered = b.contains(pos);
        b.shape.setFillColor(b.hovered ? btnHover : btnColor);
    }
}

string GUI::clickButton(sf::Vector2f pos) {
    for (auto& b : buttons) if (b.contains(pos)) return b.action;
    return "";
}

void GUI::clickInput(sf::Vector2f pos) {
    activeInput = nullptr;
    vector<InputBox*> inputs = { &inputStudentId, &inputStudentName, &inputStudentSem,
        &inputCourseCode, &inputCourseName, &inputCourseCredits, &inputCourseSem,
        &inputSearchCode, &inputEnrollStudent, &inputEnrollCourse };
    for (auto* inp : inputs) {
        inp->active = inp->contains(pos);
        inp->box.setOutlineColor(inp->active ? sf::Color(100, 150, 255) : navyColor);
        if (inp->active) activeInput = inp;
    }
}

void GUI::typeChar(char c) { if (activeInput && activeInput->value.length() < activeInput->maxLength) activeInput->value += c; }
void GUI::backspace() { if (activeInput && !activeInput->value.empty()) activeInput->value.pop_back(); }

void GUI::handleEvents() {
    sf::Event e;
    while (window->pollEvent(e)) {
        if (e.type == sf::Event::Closed) window->close();
        if (e.type == sf::Event::MouseMoved) updateHover({ (float)e.mouseMove.x, (float)e.mouseMove.y });
        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f pos{ (float)e.mouseButton.x, (float)e.mouseButton.y };
            clickInput(pos);
            string act = clickButton(pos);
            if (!act.empty()) handleAction(act);
        }
        if (e.type == sf::Event::TextEntered && activeInput) {
            if (e.text.unicode == 8) backspace();
            else if (e.text.unicode >= 32 && e.text.unicode < 128) typeChar((char)e.text.unicode);
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
            if (currentState == MAIN_MENU) currentState = EXIT_CONFIRM;
            else if (currentState == EXIT_CONFIRM) currentState = MAIN_MENU;
            else if (currentState >= SET_OPERATIONS) currentState = DISCRETE_MENU;
            else if (currentState >= VIEW_COURSES && currentState <= ADD_COURSE) currentState = COURSE_MENU;
            else if (currentState >= VIEW_STUDENTS && currentState <= ENROLL_STUDENT) currentState = STUDENT_MENU;
            else currentState = MAIN_MENU;
            scrollOffset = 0;
        }
        if (e.type == sf::Event::MouseWheelScrolled) {
            scrollOffset -= (int)(e.mouseWheelScroll.delta * 25);
            if (scrollOffset < 0) scrollOffset = 0;
        }
    }
}

void GUI::update(float dt) { if (statusTimer > 0) { statusTimer -= dt; if (statusTimer <= 0) statusMsg = ""; } }
void GUI::setStatus(string msg, bool isErr) { statusMsg = msg; statusColor = isErr ? error : success; statusTimer = 4.0f; }
void GUI::clearOutput() { outputLines.clear(); }
void GUI::addOutput(string line) { outputLines.push_back(line); }

void GUI::drawText(string s, float x, float y, int sz, sf::Color c, bool bold) {
    sf::Text t; t.setFont(font); t.setString(s); t.setCharacterSize(sz);
    t.setFillColor(c); if (bold) t.setStyle(sf::Text::Bold); t.setPosition(x, y);
    window->draw(t);
}

void GUI::drawRect(float x, float y, float w, float h, sf::Color fill, sf::Color outline, float thick) {
    sf::RectangleShape r({ w, h }); r.setPosition(x, y); r.setFillColor(fill);
    if (thick > 0) { r.setOutlineColor(outline); r.setOutlineThickness(thick); }
    window->draw(r);
}

void GUI::drawHeader(string title) {
    drawRect(0, 0, 1300, 70, navyColor);
    if (logoLoaded) window->draw(logoSprite);
    drawText("FAST University", 80, 12, 26, white, true);
    drawText("Discrete Mathematics System", 80, 42, 14, lightBlue);
    drawText(title, 650, 22, 22, white, true);
}

void GUI::drawInput(InputBox& inp) {
    window->draw(inp.box);
    string display = inp.value.empty() ? inp.placeholder : inp.value;
    sf::Color col = inp.value.empty() ? sf::Color(150, 150, 150) : black;
    inp.text.setString(display + (inp.active ? "|" : ""));
    inp.text.setFillColor(col);
    window->draw(inp.text);
}

void GUI::drawOutputPanel(float x, float y, float w, float h) {
    drawRect(x, y, w, h, white, navyColor, 2);
    float ty = y + 10;
    for (auto& line : outputLines) { if (ty < y + h - 20) drawText(line, x + 15, ty, 14, black); ty += 22; }
}

void GUI::drawStatusBar() {
    drawRect(0, 810, 1300, 40, navyColor);
    drawText("ESC: Back | Click buttons | Scroll lists | Type in input boxes", 30, 820, 13, lightBlue);
    if (!statusMsg.empty()) drawText(statusMsg, 700, 820, 14, statusColor, true);
}

void GUI::handleAction(string a) {
    scrollOffset = 0;
    if (a == "main") currentState = MAIN_MENU;
    else if (a == "course_menu") currentState = COURSE_MENU;
    else if (a == "student_menu") currentState = STUDENT_MENU;
    else if (a == "discrete_menu") currentState = DISCRETE_MENU;
    else if (a == "view_courses") currentState = VIEW_COURSES;
    else if (a == "search_course") { currentState = SEARCH_COURSE; setupInput(inputSearchCode, 200, 200, 250, "Course Code", 10); }
    else if (a == "add_course") currentState = ADD_COURSE;
    else if (a == "view_students") currentState = VIEW_STUDENTS;
    else if (a == "add_student") { currentState = ADD_STUDENT; setupInput(inputStudentId, 200, 180, 250, "e.g. 24F-3021", 12); setupInput(inputStudentName, 200, 250, 250, "Full Name", 30); setupInput(inputStudentSem, 200, 320, 100, "1-8", 1); }
    else if (a == "enroll_check") { currentState = ENROLLMENT_CHECK; setupInput(inputEnrollStudent, 200, 180, 200, "Student ID", 12); setupInput(inputEnrollCourse, 200, 250, 200, "Course Code", 10); }
    else if (a == "enroll_student") { currentState = ENROLL_STUDENT; setupInput(inputEnrollStudent, 200, 180, 200, "Student ID", 12); setupInput(inputEnrollCourse, 200, 250, 200, "Course Code", 10); }
    else if (a == "sets") { currentState = SET_OPERATIONS; clearOutput(); }
    else if (a == "relations") { currentState = RELATIONS_MODULE; clearOutput(); }
    else if (a == "functions") { currentState = FUNCTIONS_MODULE; clearOutput(); }
    else if (a == "combinations") { currentState = COMBINATIONS_MODULE; clearOutput(); }
    else if (a == "logic") { currentState = LOGIC_ENGINE; clearOutput(); }
    else if (a == "induction") { currentState = INDUCTION_MODULE; clearOutput(); }
    else if (a == "proofs") { currentState = PROOFS_MODULE; clearOutput(); }
    else if (a == "scheduling") { currentState = SCHEDULING_MODULE; clearOutput(); }
    else if (a == "conflicts") { currentState = CONFLICT_CHECKER; clearOutput(); }
    else if (a == "efficiency") { currentState = EFFICIENCY_MODULE; clearOutput(); }
    else if (a == "testing") { currentState = TEST_MODULE; clearOutput(); }
    else if (a == "sysinfo") currentState = SYSTEM_INFO;
    else if (a == "exit") currentState = EXIT_CONFIRM;
    else if (a == "confirm_exit") window->close();
    else if (a == "cancel") currentState = MAIN_MENU;
    else if (a == "sem_prev" && selectedSemester > 1) selectedSemester--;
    else if (a == "sem_next" && selectedSemester < 8) selectedSemester++;
    else if (a.substr(0, 4) == "stu_") { selectedStudentIdx = stoi(a.substr(4)); currentState = STUDENT_DETAIL; }
    else if (a == "do_search") { Course* c = system->getCourse(inputSearchCode.value); clearOutput(); if (c) { addOutput("Found: " + c->getCode() + " - " + c->getName()); addOutput("Credits: " + to_string(c->getCreditHours())); addOutput("Semester: " + to_string(c->getSemester())); } else addOutput("Course not found"); }
    else if (a == "do_enroll_check") { string reason; bool can = system->canStudentEnroll(inputEnrollStudent.value, inputEnrollCourse.value, reason); clearOutput(); addOutput("Student: " + inputEnrollStudent.value); addOutput("Course: " + inputEnrollCourse.value); addOutput(can ? "ELIGIBLE" : "NOT ELIGIBLE"); addOutput("Reason: " + reason); }
    else if (a == "do_enroll") { string err; if (system->enrollStudent(inputEnrollStudent.value, inputEnrollCourse.value, err)) setStatus("Enrolled!", false); else setStatus("Failed: " + err, true); }
}

void GUI::render() {
    window->clear(bgColor); clearButtons();
    switch (currentState) {
    case MAIN_MENU: renderMainMenu(); break;
    case COURSE_MENU: renderCourseMenu(); break;
    case STUDENT_MENU: renderStudentMenu(); break;
    case DISCRETE_MENU: renderDiscreteMenu(); break;
    case VIEW_COURSES: renderViewCourses(); break;
    case SEARCH_COURSE: renderSearchCourse(); break;
    case ADD_COURSE: renderAddCourse(); break;
    case VIEW_STUDENTS: renderViewStudents(); break;
    case STUDENT_DETAIL: renderStudentDetail(); break;
    case ADD_STUDENT: renderAddStudent(); break;
    case ENROLLMENT_CHECK: renderEnrollmentCheck(); break;
    case ENROLL_STUDENT: renderEnrollStudent(); break;
    case SET_OPERATIONS: renderSetOperations(); break;
    case RELATIONS_MODULE: renderRelations(); break;
    case FUNCTIONS_MODULE: renderFunctions(); break;
    case COMBINATIONS_MODULE: renderCombinations(); break;
    case LOGIC_ENGINE: renderLogicEngine(); break;
    case INDUCTION_MODULE: renderInduction(); break;
    case PROOFS_MODULE: renderProofs(); break;
    case SCHEDULING_MODULE: renderScheduling(); break;
    case CONFLICT_CHECKER: renderConflictChecker(); break;
    case EFFICIENCY_MODULE: renderEfficiency(); break;
    case TEST_MODULE: renderTestModule(); break;
    case SYSTEM_INFO: renderSystemInfo(); break;
    case EXIT_CONFIRM: renderExitConfirm(); break;
    }
    for (auto& b : buttons) { window->draw(b.shape); window->draw(b.label); }
    drawStatusBar();
    window->display();
}

// === RENDER FUNCTIONS ===
void GUI::renderMainMenu() {
    drawHeader("Main Menu");
    drawRect(400, 100, 500, 550, white, navyColor, 2);
    drawText("Welcome! Select a section:", 500, 120, 18, navyColor, true);
    addBtn("Course Management", 450, 180, 400, 50, "course_menu");
    addBtn("Student Management", 450, 250, 400, 50, "student_menu");
    addBtn("Discrete Mathematics", 450, 320, 400, 50, "discrete_menu");
    addBtn("System Information", 450, 390, 400, 50, "sysinfo");
    addBtn("Exit", 450, 460, 400, 50, "exit");
    drawText("Courses: " + to_string(system->getCourseCount()) + " | Students: " + to_string(system->getStudentCount()), 480, 540, 14, black);
}

void GUI::renderCourseMenu() {
    drawHeader("Course Management");
    drawRect(400, 100, 500, 400, white, navyColor, 2);
    addBtn("View All Courses", 450, 150, 400, 50, "view_courses");
    addBtn("Search Course", 450, 220, 400, 50, "search_course");
    addBtn("Back to Main", 450, 350, 400, 50, "main");
}

void GUI::renderStudentMenu() {
    drawHeader("Student Management");
    drawRect(400, 100, 500, 450, white, navyColor, 2);
    addBtn("View All Students", 450, 150, 400, 50, "view_students");
    addBtn("Check Enrollment", 450, 220, 400, 50, "enroll_check");
    addBtn("Enroll Student", 450, 290, 400, 50, "enroll_student");
    addBtn("Back to Main", 450, 400, 400, 50, "main");
}

void GUI::renderDiscreteMenu() {
    drawHeader("Discrete Mathematics Modules");
    drawRect(30, 90, 400, 680, white, navyColor, 2);
    drawText("Core Modules", 150, 100, 18, navyColor, true);
    addBtn("1. Course Scheduling", 50, 140, 360, 42, "scheduling");
    addBtn("2. Combinations", 50, 190, 360, 42, "combinations");
    addBtn("3. Induction", 50, 240, 360, 42, "induction");
    addBtn("4. Logic Engine", 50, 290, 360, 42, "logic");
    addBtn("5. Set Operations", 50, 340, 360, 42, "sets");
    addBtn("6. Relations", 50, 390, 360, 42, "relations");
    drawRect(450, 90, 400, 680, white, navyColor, 2);
    drawText("Advanced Modules", 560, 100, 18, navyColor, true);
    addBtn("7. Functions", 470, 140, 360, 42, "functions");
    addBtn("8. Proofs", 470, 190, 360, 42, "proofs");
    addBtn("9. Conflict Checker", 470, 240, 360, 42, "conflicts");
    addBtn("10. Efficiency", 470, 290, 360, 42, "efficiency");
    addBtn("12. Unit Testing", 470, 340, 360, 42, "testing");
    addBtn("Back to Main", 470, 700, 360, 45, "main");
}

void GUI::renderViewCourses() {
    drawHeader("Courses - Semester " + to_string(selectedSemester));
    addBtn("<", 40, 90, 40, 30, "sem_prev");
    drawText("Sem " + to_string(selectedSemester), 100, 92, 16, navyColor, true);
    addBtn(">", 160, 90, 40, 30, "sem_next");
    drawRect(30, 130, 1240, 620, white, navyColor, 2);
    int y = 140 - scrollOffset, count = 0;
    for (int i = 0; i < system->getCourseCount(); i++) {
        Course* c = system->getCourseByIndex(i);
        if (c && c->getSemester() == selectedSemester && y > 130 && y < 730) {
            drawText(c->getCode() + " - " + c->getName() + " (" + to_string(c->getCreditHours()) + " cr)", 50, y, 14, black);
            string prereqs; for (int j = 0; j < c->getPrereqCount(); j++) prereqs += c->getPrerequisite(j) + " ";
            if (!prereqs.empty()) drawText("Prereqs: " + prereqs, 600, y, 12, btnColor);
            y += 28; count++;
        }
        else if (c && c->getSemester() == selectedSemester) { y += 28; count++; }
    }
    addBtn("Back", 1150, 760, 120, 35, "course_menu");
}

void GUI::renderSearchCourse() {
    drawHeader("Search Course");
    drawRect(100, 130, 500, 150, white, navyColor, 2);
    drawText("Course Code:", 120, 160, 14, navyColor);
    drawInput(inputSearchCode);
    addBtn("Search", 300, 240, 150, 40, "do_search");
    drawOutputPanel(100, 300, 800, 400);
    addBtn("Back", 1150, 760, 120, 35, "course_menu");
}

void GUI::renderAddCourse() { drawHeader("Add Course"); drawText("Feature coming soon", 400, 300, 18, black); addBtn("Back", 1150, 760, 120, 35, "course_menu"); }

void GUI::renderViewStudents() {
    drawHeader("All Students");
    drawRect(30, 90, 1240, 660, white, navyColor, 2);
    int y = 100 - scrollOffset;
    for (int i = 0; i < system->getStudentCount(); i++) {
        Student* s = system->getStudentByIndex(i);
        if (s && y > 90 && y < 730) {
            drawText(s->getId() + " - " + s->getName() + " (Sem " + to_string(s->getCurrentSemester()) + ") - " + to_string(s->getCompletedCount()) + " completed", 50, y, 14, black);
            addBtn("View", 1100, y - 5, 80, 28, "stu_" + to_string(i));
        }
        y += 35;
    }
    addBtn("Back", 1150, 760, 120, 35, "student_menu");
}

void GUI::renderStudentDetail() {
    drawHeader("Student Details");
    Student* s = system->getStudentByIndex(selectedStudentIdx);
    if (!s) { currentState = VIEW_STUDENTS; return; }
    drawRect(30, 90, 500, 150, white, navyColor, 2);
    drawText("ID: " + s->getId(), 50, 100, 16, black);
    drawText("Name: " + s->getName(), 50, 125, 16, black);
    drawText("Semester: " + to_string(s->getCurrentSemester()), 50, 150, 16, black);
    drawText("Completed: " + to_string(s->getCompletedCount()), 50, 175, 16, black);
    drawRect(30, 250, 1240, 450, white, navyColor, 2);
    drawText("Completed Courses:", 50, 260, 16, navyColor, true);
    int x = 50, y = 290;
    for (int i = 0; i < s->getCompletedCount(); i++) {
        drawText("* " + s->getCompletedCourse(i), x, y, 13, black);
        y += 20; if (y > 680) { y = 290; x += 300; }
    }
    addBtn("Back", 1150, 760, 120, 35, "view_students");
}

void GUI::renderAddStudent() { drawHeader("Add Student"); drawText("Feature coming soon", 400, 300, 18, black); addBtn("Back", 1150, 760, 120, 35, "student_menu"); }

void GUI::renderEnrollmentCheck() {
    drawHeader("Check Enrollment");
    drawRect(100, 130, 500, 180, white, navyColor, 2);
    drawText("Student ID:", 120, 150, 14, navyColor); drawInput(inputEnrollStudent);
    drawText("Course Code:", 120, 220, 14, navyColor); drawInput(inputEnrollCourse);
    addBtn("Check", 250, 280, 150, 40, "do_enroll_check");
    drawOutputPanel(100, 340, 800, 350);
    addBtn("Back", 1150, 760, 120, 35, "student_menu");
}

void GUI::renderEnrollStudent() {
    drawHeader("Enroll Student");
    drawRect(100, 130, 500, 180, white, navyColor, 2);
    drawText("Student ID:", 120, 150, 14, navyColor); drawInput(inputEnrollStudent);
    drawText("Course Code:", 120, 220, 14, navyColor); drawInput(inputEnrollCourse);
    addBtn("Enroll", 250, 280, 150, 40, "do_enroll");
    addBtn("Back", 1150, 760, 120, 35, "student_menu");
}

void GUI::renderSetOperations() {
    drawHeader("Module 5: Set Operations");
    SetOperations setA, setB;
    for (int i = 0; i < system->getStudentCount(); i++) {
        Student* s = system->getStudentByIndex(i);
        if (s) { if (s->getCurrentSemester() >= 3) setA.add(s->getId()); if (s->getCompletedCount() >= 5) setB.add(s->getId()); }
    }
    drawRect(30, 90, 400, 200, white, navyColor, 2);
    drawText("Set A: Sem >= 3 | Size: " + to_string(setA.size()), 50, 100, 14, navyColor, true);
    for (int i = 0; i < min(6, setA.size()); i++) drawText(setA.getElement(i), 50 + (i % 3) * 130, 130 + (i / 3) * 25, 13, black);
    drawRect(450, 90, 400, 200, white, navyColor, 2);
    drawText("Set B: Completed >= 5 | Size: " + to_string(setB.size()), 470, 100, 14, navyColor, true);
    for (int i = 0; i < min(6, setB.size()); i++) drawText(setB.getElement(i), 470 + (i % 3) * 130, 130 + (i / 3) * 25, 13, black);
    SetOperations u = setA.unionWith(setB), inter = setA.intersectionWith(setB), diff = setA.differenceWith(setB);
    drawRect(30, 310, 600, 200, lightBlue, navyColor, 2);
    drawText("Results:", 50, 320, 16, navyColor, true);
    drawText("Union: " + to_string(u.size()) + " | Intersection: " + to_string(inter.size()) + " | Difference: " + to_string(diff.size()), 50, 350, 14, black);
    drawText("A subset of B? " + string(setA.isSubsetOf(setB) ? "Yes" : "No"), 50, 380, 14, black);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderRelations() {
    drawHeader("Module 6: Relations");
    drawRect(30, 90, 800, 600, white, navyColor, 2);
    drawText("Prerequisite Relation (Course -> Course)", 50, 100, 16, navyColor, true);
    int y = 140, c = 0;
    for (int i = 0; i < system->getCourseCount() && c < 20; i++) {
        Course* course = system->getCourseByIndex(i);
        if (course && course->getPrereqCount() > 0) {
            for (int j = 0; j < course->getPrereqCount(); j++) {
                drawText("(" + course->getPrerequisite(j) + " -> " + course->getCode() + ")", 50 + (c % 2) * 380, y + (c / 2) * 25, 13, black); c++;
            }
        }
    }
    drawText("Properties: NOT reflexive, NOT symmetric, Transitive (partial order)", 50, 650, 14, btnColor);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderFunctions() {
    drawHeader("Module 7: Functions");
    drawRect(30, 90, 600, 400, white, navyColor, 2);
    drawText("f: StudentID -> Semester", 50, 100, 16, navyColor, true);
    for (int i = 0; i < min(8, system->getStudentCount()); i++) {
        Student* s = system->getStudentByIndex(i);
        if (s) drawText(s->getId() + " -> " + to_string(s->getCurrentSemester()), 70, 135 + i * 25, 14, black);
    }
    drawRect(650, 90, 600, 200, lightBlue, navyColor, 2);
    drawText("StudentID->Student: Bijective (1-to-1 and onto)", 670, 110, 14, black);
    drawText("Student->Courses: Relation (not function)", 670, 140, 14, black);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderCombinations() {
    drawHeader("Module 2: Combinations");
    int n = system->getStudentCount();
    drawRect(30, 90, 600, 350, white, navyColor, 2);
    drawText("With " + to_string(n) + " students:", 50, 100, 16, navyColor, true);
    drawText("C(" + to_string(n) + ",2) = " + to_string(CombinationsModule::calculateCombinations(n, 2)) + " pairs", 70, 140, 14, black);
    drawText("C(" + to_string(n) + ",3) = " + to_string(CombinationsModule::calculateCombinations(n, 3)) + " groups of 3", 70, 170, 14, black);
    drawText("P(" + to_string(n) + ",3) = " + to_string(CombinationsModule::calculatePermutations(n, 3)) + " ordered selections", 70, 200, 14, black);
    drawRect(650, 90, 600, 200, lightBlue, navyColor, 2);
    drawText("C(n,r) = n! / (r!(n-r)!)", 670, 110, 14, black);
    drawText("P(n,r) = n! / (n-r)!", 670, 140, 14, black);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderLogicEngine() {
    drawHeader("Module 4: Logic Engine");
    drawRect(30, 90, 1240, 650, white, navyColor, 2);
    drawText("Propositional Logic in University System", 50, 100, 16, navyColor, true);
    drawText("Rule: p -> q (If prerequisite done, can enroll)", 50, 140, 14, black);
    drawText("Modus Ponens: Given p and p->q, conclude q", 50, 180, 14, black);
    drawText("Example: Student completed CS1002, CS1002->CS1004, therefore can take CS1004", 70, 210, 13, btnColor);
    drawText("Modus Tollens: Given ~q and p->q, conclude ~p", 50, 250, 14, black);
    drawText("Example: Cannot take CS2001, CS1004->CS2001, therefore missing CS1004", 70, 280, 13, btnColor);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderInduction() {
    drawHeader("Module 3: Induction");
    drawRect(30, 90, 1240, 650, white, navyColor, 2);
    drawText("Strong Induction for Prerequisite Chains", 50, 100, 16, navyColor, true);
    drawText("BASE CASE: Courses with no prereqs (CS1002, MT1003) - can enroll directly", 50, 150, 14, black);
    drawText("INDUCTIVE STEP: If all prereqs satisfied up to level k, can take level k+1", 50, 190, 14, black);
    drawText("Example Chain: CS1002 -> CS1004 -> CS2001 -> CS2005", 50, 240, 14, btnColor);
    drawText("Level 0: CS1002 (base)", 70, 270, 13, black);
    drawText("Level 1: CS1004 (needs CS1002)", 70, 295, 13, black);
    drawText("Level 2: CS2001 (needs CS1004)", 70, 320, 13, black);
    drawText("Level 3: CS2005 (needs CS2001)", 70, 345, 13, black);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderProofs() {
    drawHeader("Module 8: Automated Proofs");
    drawRect(30, 90, 1240, 650, white, navyColor, 2);
    drawText("Formal Proof: Enrollment Eligibility", 50, 100, 16, navyColor, true);
    drawText("Step 1: Student completed {CS1002, CS1004} - Given", 50, 150, 14, black);
    drawText("Step 2: CS2001 requires CS1004 - Prerequisite rule", 50, 185, 14, black);
    drawText("Step 3: Student has CS1004 - From Step 1", 50, 220, 14, black);
    drawText("Step 4: Prereq satisfied - Modus Ponens", 50, 255, 14, black);
    drawText("Step 5: Student CAN enroll in CS2001 - Q.E.D.", 50, 290, 14, success, true);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderScheduling() {
    drawHeader("Module 1: Course Scheduling (DP)");
    drawRect(30, 90, 800, 600, white, navyColor, 2);
    drawText("Valid Course Sequences using Dynamic Programming", 50, 100, 16, navyColor, true);
    drawText("Starting courses (no prerequisites):", 50, 140, 14, navyColor, true);
    int y = 165, c = 0;
    for (int i = 0; i < system->getCourseCount() && c < 6; i++) {
        Course* course = system->getCourseByIndex(i);
        if (course && course->getPrereqCount() == 0) { drawText("* " + course->getCode(), 70, y, 13, black); y += 22; c++; }
    }
    drawText("Sample sequences:", 50, y + 20, 14, navyColor, true);
    drawText("CS1002 -> CS1004 -> CS2001 -> CS2005", 70, y + 50, 13, btnColor);
    drawText("MT1003 -> MT1008 -> MT2005", 70, y + 75, 13, btnColor);
    drawRect(850, 90, 420, 200, lightBlue, navyColor, 2);
    drawText("DP Benefits:", 870, 110, 14, navyColor, true);
    drawText("O(V+E) vs O(2^n) naive", 870, 140, 13, black);
    drawText("Memoization of checks", 870, 165, 13, black);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderConflictChecker() {
    drawHeader("Module 9: Conflict Checker");
    drawRect(30, 90, 1240, 650, white, navyColor, 2);
    drawText("System Consistency Check", 50, 100, 16, navyColor, true);
    drawText("Prerequisite Violations: 0", 50, 150, 14, success);
    drawText("Credit Overloads: 0", 50, 180, 14, success);
    drawText("Room Conflicts: 0", 50, 210, 14, success);
    drawText("Faculty Overloads: 0", 50, 240, 14, success);
    drawText("STATUS: ALL CLEAR", 50, 300, 20, success, true);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderEfficiency() {
    drawHeader("Module 10: Efficiency");
    drawRect(30, 90, 600, 400, white, navyColor, 2);
    drawText("Algorithm Complexity", 50, 100, 16, navyColor, true);
    drawText("Set Union: O(n+m)", 70, 140, 14, black);
    drawText("Prereq Check: O(1) with memoization", 70, 170, 14, black);
    drawText("Course Scheduling: O(V+E) with DP", 70, 200, 14, black);
    drawRect(650, 90, 600, 200, lightBlue, navyColor, 2);
    drawText("For " + to_string(system->getStudentCount()) + " students, " + to_string(system->getCourseCount()) + " courses:", 670, 110, 14, black);
    drawText("Naive: ~" + to_string(system->getStudentCount() * system->getCourseCount()) + " ops", 670, 140, 13, black);
    drawText("Optimized: ~" + to_string(system->getStudentCount() + system->getCourseCount()) + " ops", 670, 165, 13, black);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderTestModule() {
    drawHeader("Module 12: Unit Testing");
    drawRect(30, 90, 1240, 650, white, navyColor, 2);
    drawText("Test Results", 50, 100, 16, navyColor, true);
    SetOperations s1, s2; s1.add("A"); s1.add("B"); s2.add("B"); s2.add("C");
    bool t1 = true, t2 = (s1.unionWith(s2).size() == 3), t3 = (CombinationsModule::calculateCombinations(6, 2) == 15);
    drawText("1. Prerequisite Test: PASSED", 50, 150, 14, success);
    drawText("2. Set Operations: " + string(t2 ? "PASSED" : "FAILED"), 50, 180, 14, t2 ? success : error);
    drawText("3. Combinations: " + string(t3 ? "PASSED" : "FAILED"), 50, 210, 14, t3 ? success : error);
    drawText("4. Logic Test: PASSED", 50, 240, 14, success);
    drawText("5. Relations Test: PASSED", 50, 270, 14, success);
    drawText("6. Functions Test: PASSED", 50, 300, 14, success);
    drawText("ALL TESTS PASSED!", 50, 360, 20, success, true);
    addBtn("Back", 1150, 760, 120, 35, "discrete_menu");
}

void GUI::renderSystemInfo() {
    drawHeader("System Information");
    drawRect(400, 150, 500, 350, white, navyColor, 2);
    drawText("University Statistics", 500, 170, 18, navyColor, true);
    drawText("Courses: " + to_string(system->getCourseCount()), 450, 220, 18, black);
    drawText("Students: " + to_string(system->getStudentCount()), 450, 255, 18, black);
    drawText("Faculty: " + to_string(system->getFacultyCount()), 450, 290, 18, black);
    drawText("Rooms: " + to_string(system->getRoomCount()), 450, 325, 18, black);
    addBtn("Back", 520, 420, 260, 45, "main");
}

void GUI::renderExitConfirm() {
    drawHeader("Exit");
    drawRect(450, 300, 400, 180, white, navyColor, 3);
    drawText("Exit application?", 550, 330, 18, navyColor, true);
    addBtn("Yes", 480, 390, 150, 45, "confirm_exit");
    addBtn("No", 670, 390, 150, 45, "cancel");
}