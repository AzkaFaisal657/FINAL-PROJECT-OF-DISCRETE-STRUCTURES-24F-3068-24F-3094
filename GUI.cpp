//#include "GUI.h"
//#include "SetOperations.h"
//#include "RelationsModule.h"
//#include "FunctionsModule.h"
//#include "CombinationsModule.h"
//#include "InductionModule.h"
//#include "LogicEngine.h"
//#include "AutomatedProof.h"
//#include "ConflictDetector.h"
//#include "EfficiencyModule.h"
//#include "TestModule.h"
//#include "CourseScheduler.h"
//#include <sstream>
//
//GUI::GUI(UniversitySystem* sys) : system(sys), window(nullptr) {}
//GUI::~GUI() { if (window) { window->close(); delete window; } }
//
//void GUI::initWindow() {
//    window = new sf::RenderWindow(sf::VideoMode(WIN_W, WIN_H),
//        "FAST University - Discrete Mathematics Management System", sf::Style::Close);
//    window->setFramerateLimit(60);
//}
//
//bool GUI::loadResources() {
//    vector<string> fonts = { "arial.ttf", "C:/Windows/Fonts/arial.ttf", "C:/Windows/Fonts/segoeui.ttf" };
//    for (auto& f : fonts) if (font.loadFromFile(f)) break;
//
//    if (logoTex.loadFromFile("logofast.png")) {
//        logoSprite.setTexture(logoTex);
//        float scale = 80.0f / logoTex.getSize().y;
//        logoSprite.setScale(scale, scale);
//        logoSprite.setPosition(30, 12);
//        logoLoaded = true;
//    }
//    return true;
//}
//
//void GUI::run() {
//    initWindow(); loadResources();
//    sf::Clock clock;
//    while (window->isOpen()) {
//        float dt = clock.restart().asSeconds();
//        handleEvents(); update(dt); render();
//    }
//}
//
//void GUI::clearButtons() { buttons.clear(); }
//
//Button& GUI::addBtn(string text, float x, float y, float w, float h, string action, bool primary) {
//    Button b;
//    b.shape.setSize({ w, h });
//    b.shape.setPosition(x, y);
//    b.shape.setFillColor(primary ? primaryBtn : secondaryBtn);
//    b.shape.setOutlineColor(sf::Color(0, 0, 0, 30));
//    b.shape.setOutlineThickness(1);
//    b.label.setFont(font);
//    b.label.setString(text);
//    b.label.setCharacterSize(18);
//    b.label.setFillColor(textLight);
//    auto bounds = b.label.getLocalBounds();
//    b.label.setPosition(x + (w - bounds.width) / 2, y + (h - bounds.height) / 2 - 4);
//    b.action = action;
//    buttons.push_back(b);
//    return buttons.back();
//}
//
//void GUI::setupInput(InputBox& inp, float x, float y, float w, string ph, int maxLen) {
//    inp.box.setSize({ w, 45 });
//    inp.box.setPosition(x, y);
//    inp.box.setFillColor(sf::Color::White);
//    inp.box.setOutlineColor(borderColor);
//    inp.box.setOutlineThickness(2);
//    inp.text.setFont(font);
//    inp.text.setCharacterSize(18);
//    inp.text.setFillColor(textDark);
//    inp.text.setPosition(x + 12, y + 10);
//    inp.placeholder = ph;
//    inp.maxLength = maxLen;
//    inp.value = "";
//}
//
//void GUI::updateHover(sf::Vector2f pos) {
//    for (auto& b : buttons) {
//        bool wasHovered = b.hovered;
//        b.hovered = b.contains(pos);
//        if (b.hovered) {
//            b.shape.setFillColor(b.shape.getFillColor() == primaryBtn ? primaryHover : secondaryHover);
//        }
//        else if (wasHovered) {
//            b.shape.setFillColor(b.action.find("back") != string::npos || b.action == "cancel" ? secondaryBtn : primaryBtn);
//        }
//    }
//}
//
//string GUI::clickButton(sf::Vector2f pos) {
//    for (auto& b : buttons) if (b.contains(pos)) return b.action;
//    return "";
//}
//
//void GUI::clickInput(sf::Vector2f pos) {
//    activeInput = nullptr;
//    vector<InputBox*> inputs = { &inputSearchCode, &inputEnrollStudent, &inputEnrollCourse };
//    for (auto* inp : inputs) {
//        inp->active = inp->contains(pos);
//        inp->box.setOutlineColor(inp->active ? primaryBtn : borderColor);
//        inp->box.setOutlineThickness(inp->active ? 3 : 2);
//        if (inp->active) activeInput = inp;
//    }
//}
//
//void GUI::typeChar(char c) { if (activeInput && activeInput->value.length() < activeInput->maxLength) activeInput->value += c; }
//void GUI::backspace() { if (activeInput && !activeInput->value.empty()) activeInput->value.pop_back(); }
//
//void GUI::handleEvents() {
//    sf::Event e;
//    while (window->pollEvent(e)) {
//        if (e.type == sf::Event::Closed) window->close();
//        if (e.type == sf::Event::MouseMoved) updateHover({ (float)e.mouseMove.x, (float)e.mouseMove.y });
//        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
//            sf::Vector2f pos{ (float)e.mouseButton.x, (float)e.mouseButton.y };
//            clickInput(pos);
//            string act = clickButton(pos);
//            if (!act.empty()) handleAction(act);
//        }
//        if (e.type == sf::Event::TextEntered && activeInput) {
//            if (e.text.unicode == 8) backspace();
//            else if (e.text.unicode >= 32 && e.text.unicode < 128) typeChar((char)e.text.unicode);
//        }
//        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
//            if (currentState == MAIN_MENU) currentState = EXIT_CONFIRM;
//            else if (currentState == EXIT_CONFIRM) currentState = MAIN_MENU;
//            else if (currentState >= SET_OPERATIONS) currentState = DISCRETE_MENU;
//            else if (currentState >= VIEW_COURSES && currentState <= SEARCH_COURSE) currentState = COURSE_MENU;
//            else if (currentState >= VIEW_STUDENTS && currentState <= ENROLL_STUDENT) currentState = STUDENT_MENU;
//            else currentState = MAIN_MENU;
//            scrollOffset = 0;
//        }
//        if (e.type == sf::Event::MouseWheelScrolled) {
//            scrollOffset -= (int)(e.mouseWheelScroll.delta * 35);
//            if (scrollOffset < 0) scrollOffset = 0;
//        }
//    }
//}
//
//void GUI::update(float dt) { if (statusTimer > 0) { statusTimer -= dt; if (statusTimer <= 0) statusMsg = ""; } }
//void GUI::setStatus(string msg, bool isErr) { statusMsg = msg; statusColor = isErr ? errorColor : successColor; statusTimer = 4.0f; }
//void GUI::clearOutput() { outputLines.clear(); }
//void GUI::addOutput(string line) { outputLines.push_back(line); }
//
//// Add this after the Part 1 code in GUI.cpp
//
//void GUI::drawText(string s, float x, float y, int sz, sf::Color c, bool bold) {
//    sf::Text t; t.setFont(font); t.setString(s); t.setCharacterSize(sz);
//    t.setFillColor(c); if (bold) t.setStyle(sf::Text::Bold); t.setPosition(x, y);
//    window->draw(t);
//}
//
//void GUI::drawTextCentered(string s, float x, float y, float w, int sz, sf::Color c, bool bold) {
//    sf::Text t; t.setFont(font); t.setString(s); t.setCharacterSize(sz);
//    t.setFillColor(c); if (bold) t.setStyle(sf::Text::Bold);
//    auto bounds = t.getLocalBounds();
//    t.setPosition(x + (w - bounds.width) / 2, y);
//    window->draw(t);
//}
//
//void GUI::drawRect(float x, float y, float w, float h, sf::Color fill, sf::Color outline, float thick, float radius) {
//    sf::RectangleShape r({ w, h }); r.setPosition(x, y); r.setFillColor(fill);
//    if (thick > 0) { r.setOutlineColor(outline); r.setOutlineThickness(thick); }
//    window->draw(r);
//}
//
//void GUI::drawCard(float x, float y, float w, float h, string title) {
//    drawRect(x + 4, y + 4, w, h, sf::Color(0, 0, 0, 25));
//    drawRect(x, y, w, h, cardColor, borderColor, 1);
//    if (!title.empty()) {
//        drawRect(x, y, w, 50, headerColor);
//        drawText(title, x + 20, y + 12, 22, textLight, true);
//    }
//}
//
//void GUI::drawHeader() {
//    drawRect(0, 0, WIN_W, 90, headerColor);
//    if (logoLoaded) window->draw(logoSprite);
//    float titleX = logoLoaded ? 120 : 30;
//    drawText("FAST UNIVERSITY", titleX, 15, 32, textLight, true);
//    drawText("Discrete Mathematics Management System", titleX, 52, 16, sf::Color(180, 200, 220));
//    string stats = "Courses: " + to_string(getCourseCount()) +
//        "  |  Students: " + to_string(getStudentCount()) +
//        "  |  Faculty: " + to_string(getFacultyCount());
//    drawText(stats, WIN_W - 450, 35, 15, sf::Color(150, 180, 210));
//}
//
//void GUI::drawInput(InputBox& inp) {
//    window->draw(inp.box);
//    string display = inp.value.empty() ? inp.placeholder : inp.value;
//    sf::Color col = inp.value.empty() ? textMuted : textDark;
//    inp.text.setString(display + (inp.active ? "|" : ""));
//    inp.text.setFillColor(col);
//    window->draw(inp.text);
//}
//
//void GUI::drawStatusBar() {
//    drawRect(0, WIN_H - 45, WIN_W, 45, sf::Color(245, 248, 252), borderColor, 1);
//    drawText("ESC: Back  |  Click buttons to navigate  |  Scroll to see more", 30, WIN_H - 32, 14, textMuted);
//    if (!statusMsg.empty()) drawText(statusMsg, WIN_W - 400, WIN_H - 32, 15, statusColor, true);
//}
//
//void GUI::handleAction(string a) {
//    scrollOffset = 0;
//    if (a == "main") currentState = MAIN_MENU;
//    else if (a == "course_menu") currentState = COURSE_MENU;
//    else if (a == "student_menu") currentState = STUDENT_MENU;
//    else if (a == "discrete_menu") currentState = DISCRETE_MENU;
//    else if (a == "view_courses") currentState = VIEW_COURSES;
//    else if (a == "search_course") { currentState = SEARCH_COURSE; setupInput(inputSearchCode, 250, 220, 300, "Enter course code...", 12); }
//    else if (a == "view_students") currentState = VIEW_STUDENTS;
//    else if (a == "enroll_check") { currentState = ENROLLMENT_CHECK; setupInput(inputEnrollStudent, 250, 200, 280, "Student ID", 12); setupInput(inputEnrollCourse, 250, 280, 280, "Course Code", 12); }
//    else if (a == "enroll_student") { currentState = ENROLL_STUDENT; setupInput(inputEnrollStudent, 250, 200, 280, "Student ID", 12); setupInput(inputEnrollCourse, 250, 280, 280, "Course Code", 12); }
//    else if (a == "sets") { currentState = SET_OPERATIONS; clearOutput(); }
//    else if (a == "relations") { currentState = RELATIONS_MODULE; clearOutput(); }
//    else if (a == "functions") { currentState = FUNCTIONS_MODULE; clearOutput(); }
//    else if (a == "combinations") { currentState = COMBINATIONS_MODULE; clearOutput(); }
//    else if (a == "logic") { currentState = LOGIC_ENGINE; clearOutput(); }
//    else if (a == "induction") { currentState = INDUCTION_MODULE; clearOutput(); }
//    else if (a == "proofs") { currentState = PROOFS_MODULE; clearOutput(); }
//    else if (a == "scheduling") { currentState = SCHEDULING_MODULE; clearOutput(); }
//    else if (a == "conflicts") { currentState = CONFLICT_CHECKER; clearOutput(); }
//    else if (a == "efficiency") { currentState = EFFICIENCY_MODULE; clearOutput(); }
//    else if (a == "testing") { currentState = TEST_MODULE; clearOutput(); }
//    else if (a == "sysinfo") currentState = SYSTEM_INFO;
//    else if (a == "exit") currentState = EXIT_CONFIRM;
//    else if (a == "confirm_exit") window->close();
//    else if (a == "cancel") currentState = MAIN_MENU;
//    else if (a == "sem_prev" && selectedSemester > 1) selectedSemester--;
//    else if (a == "sem_next" && selectedSemester < 8) selectedSemester++;
//    else if (a.substr(0, 4) == "stu_") { selectedStudentIdx = stoi(a.substr(4)); currentState = STUDENT_DETAIL; }
//    else if (a == "do_search") {
//        Course* c = system->findCourse(inputSearchCode.value);
//        clearOutput();
//        if (c) {
//            addOutput("COURSE FOUND");
//            addOutput("");
//            addOutput("Code: " + c->getCode());
//            addOutput("Name: " + c->getName());
//            addOutput("Credits: " + to_string(c->getCreditHours()));
//            addOutput("Semester: " + to_string(c->getSemester()));
//            addOutput("Type: " + c->getType());
//            if (!c->getPrerequisite().empty()) {
//                addOutput("");
//                addOutput("Prerequisites:");
//                addOutput("  - " + c->getPrerequisite());
//            }
//        }
//        else { addOutput("Course not found: " + inputSearchCode.value); }
//    }
//    else if (a == "do_enroll_check") {
//        Student* s = system->findStudent(inputEnrollStudent.value);
//        Course* c = system->findCourse(inputEnrollCourse.value);
//        clearOutput();
//        addOutput("ENROLLMENT CHECK");
//        addOutput("");
//        addOutput("Student: " + inputEnrollStudent.value);
//        addOutput("Course: " + inputEnrollCourse.value);
//        addOutput("");
//        if (s && c) {
//            bool can = system->checkPrerequisiteSatisfaction(*s, c->getCode());
//            addOutput(can ? "STATUS: ELIGIBLE" : "STATUS: NOT ELIGIBLE");
//            addOutput(can ? "Reason: All prerequisites satisfied" : "Reason: Prerequisites not met");
//        }
//        else {
//            addOutput("STATUS: ERROR");
//            addOutput("Reason: Student or course not found");
//        }
//    }
//    else if (a == "do_enroll") {
//        Student* s = system->findStudent(inputEnrollStudent.value);
//        Course* c = system->findCourse(inputEnrollCourse.value);
//        if (s && c) {
//            if (system->checkPrerequisiteSatisfaction(*s, c->getCode())) {
//                s->enrollInCourse(c->getCode());
//                setStatus("Successfully enrolled!", false);
//            }
//            else {
//                setStatus("Failed: Prerequisites not met", true);
//            }
//        }
//        else {
//            setStatus("Failed: Student or course not found", true);
//        }
//    }
//}
//
//// Add this after Part 2 in GUI.cpp
//
//void GUI::render() {
//    window->clear(bgColor);
//    clearButtons();
//    drawHeader();
//
//    switch (currentState) {
//    case MAIN_MENU: renderMainMenu(); break;
//    case COURSE_MENU: renderCourseMenu(); break;
//    case STUDENT_MENU: renderStudentMenu(); break;
//    case DISCRETE_MENU: renderDiscreteMenu(); break;
//    case VIEW_COURSES: renderViewCourses(); break;
//    case SEARCH_COURSE: renderSearchCourse(); break;
//    case VIEW_STUDENTS: renderViewStudents(); break;
//    case STUDENT_DETAIL: renderStudentDetail(); break;
//    case ENROLLMENT_CHECK: renderEnrollmentCheck(); break;
//    case ENROLL_STUDENT: renderEnrollStudent(); break;
//    case SET_OPERATIONS: renderSetOperations(); break;
//    case RELATIONS_MODULE: renderRelations(); break;
//    case FUNCTIONS_MODULE: renderFunctions(); break;
//    case COMBINATIONS_MODULE: renderCombinations(); break;
//    case LOGIC_ENGINE: renderLogicEngine(); break;
//    case INDUCTION_MODULE: renderInduction(); break;
//    case PROOFS_MODULE: renderProofs(); break;
//    case SCHEDULING_MODULE: renderScheduling(); break;
//    case CONFLICT_CHECKER: renderConflictChecker(); break;
//    case EFFICIENCY_MODULE: renderEfficiency(); break;
//    case TEST_MODULE: renderTestModule(); break;
//    case SYSTEM_INFO: renderSystemInfo(); break;
//    case EXIT_CONFIRM: renderExitConfirm(); break;
//    }
//
//    for (auto& b : buttons) { window->draw(b.shape); window->draw(b.label); }
//    drawStatusBar();
//    window->display();
//}
//
//void GUI::renderMainMenu() {
//    drawCard(50, 110, 500, 180, "Welcome");
//    drawText("FAST University Course Management", 70, 175, 20, textDark, true);
//    drawText("Powered by Discrete Mathematics", 70, 205, 16, textMuted);
//    drawText("Select a section from the menu to begin.", 70, 240, 15, textMuted);
//
//    drawCard(600, 110, 950, 740, "Main Menu");
//    float btnX = 650, btnW = 400, btnH = 60, gap = 20;
//    float startY = 190;
//
//    addBtn("Course Management", btnX, startY, btnW, btnH, "course_menu");
//    addBtn("Student Management", btnX, startY + (btnH + gap), btnW, btnH, "student_menu");
//    addBtn("Discrete Mathematics Modules", btnX, startY + 2 * (btnH + gap), btnW, btnH, "discrete_menu");
//    addBtn("System Information", btnX, startY + 3 * (btnH + gap), btnW, btnH, "sysinfo");
//    addBtn("Exit Application", btnX + 450, startY + 3 * (btnH + gap), 200, btnH, "exit", false);
//
//    drawRect(650, 540, 850, 280, sf::Color(248, 250, 255), borderColor, 1);
//    drawText("Quick Statistics", 680, 560, 20, textDark, true);
//
//    drawText("Total Courses", 680, 610, 16, textMuted);
//    drawText(to_string(getCourseCount()), 680, 635, 36, primaryBtn, true);
//
//    drawText("Total Students", 880, 610, 16, textMuted);
//    drawText(to_string(getStudentCount()), 880, 635, 36, primaryBtn, true);
//
//    drawText("Faculty Members", 1080, 610, 16, textMuted);
//    drawText(to_string(getFacultyCount()), 1080, 635, 36, primaryBtn, true);
//
//    drawText("Available Rooms", 1280, 610, 16, textMuted);
//    drawText(to_string(getRoomCount()), 1280, 635, 36, primaryBtn, true);
//}
//
//void GUI::renderCourseMenu() {
//    drawCard(400, 130, 800, 550, "Course Management");
//    float btnX = 500, btnW = 600, btnH = 65, startY = 220;
//    addBtn("View All Courses", btnX, startY, btnW, btnH, "view_courses");
//    addBtn("Search Course by Code", btnX, startY + 90, btnW, btnH, "search_course");
//    addBtn("Back to Main Menu", btnX, startY + 300, 280, 55, "main", false);
//}
//
//void GUI::renderStudentMenu() {
//    drawCard(400, 130, 800, 600, "Student Management");
//    float btnX = 500, btnW = 600, btnH = 65, startY = 220;
//    addBtn("View All Students", btnX, startY, btnW, btnH, "view_students");
//    addBtn("Check Enrollment Eligibility", btnX, startY + 90, btnW, btnH, "enroll_check");
//    addBtn("Enroll Student in Course", btnX, startY + 180, btnW, btnH, "enroll_student");
//    addBtn("Back to Main Menu", btnX, startY + 350, 280, 55, "main", false);
//}
//
//void GUI::renderDiscreteMenu() {
//    drawCard(40, 110, 480, 730, "Core Modules");
//    float btnW = 420, btnH = 55, gap = 15;
//    float x1 = 70, y = 180;
//
//    addBtn("1. Course Scheduling (DP)", x1, y, btnW, btnH, "scheduling");
//    addBtn("2. Combinations & Counting", x1, y + (btnH + gap), btnW, btnH, "combinations");
//    addBtn("3. Strong Induction", x1, y + 2 * (btnH + gap), btnW, btnH, "induction");
//    addBtn("4. Logic & Inference", x1, y + 3 * (btnH + gap), btnW, btnH, "logic");
//    addBtn("5. Set Operations", x1, y + 4 * (btnH + gap), btnW, btnH, "sets");
//    addBtn("6. Relations Module", x1, y + 5 * (btnH + gap), btnW, btnH, "relations");
//
//    drawCard(560, 110, 480, 730, "Advanced Modules");
//    float x2 = 590;
//
//    addBtn("7. Functions & Mappings", x2, y, btnW, btnH, "functions");
//    addBtn("8. Automated Proofs", x2, y + (btnH + gap), btnW, btnH, "proofs");
//    addBtn("9. Conflict Detection", x2, y + 2 * (btnH + gap), btnW, btnH, "conflicts");
//    addBtn("10. Algorithm Efficiency", x2, y + 3 * (btnH + gap), btnW, btnH, "efficiency");
//    addBtn("11. Unit Testing", x2, y + 4 * (btnH + gap), btnW, btnH, "testing");
//
//    drawCard(1080, 110, 470, 730, "About");
//    drawText("Each module demonstrates", 1110, 180, 16, textDark);
//    drawText("discrete math concepts using", 1110, 205, 16, textDark);
//    drawText("real FAST University data.", 1110, 230, 16, textDark);
//    drawText("Click any module to explore!", 1110, 270, 16, primaryBtn, true);
//
//    addBtn("Back to Main Menu", 1110, 760, 280, 55, "main", false);
//}
//
//void GUI::renderViewCourses() {
//    drawCard(40, 110, WIN_W - 80, 780, "Course Catalog - Semester " + to_string(selectedSemester));
//
//    addBtn("<", 500, 125, 50, 40, "sem_prev", false);
//    drawTextCentered("Semester " + to_string(selectedSemester), 560, 132, 120, 20, textLight, true);
//    addBtn(">", 690, 125, 50, 40, "sem_next", false);
//
//    drawRect(60, 175, WIN_W - 120, 40, sf::Color(248, 250, 255), borderColor, 1);
//    drawText("Code", 80, 183, 16, textDark, true);
//    drawText("Course Name", 220, 183, 16, textDark, true);
//    drawText("Credits", 750, 183, 16, textDark, true);
//    drawText("Type", 880, 183, 16, textDark, true);
//    drawText("Prerequisites", 1050, 183, 16, textDark, true);
//
//    int y = 225 - scrollOffset;
//    int idx = 0;
//    for (auto& c : system->getCourses()) {
//        if (c.getSemester() == selectedSemester && y > 170 && y < 850) {
//            sf::Color row = (idx % 2) ? sf::Color(252, 253, 255) : cardColor;
//            drawRect(60, y, WIN_W - 120, 35, row);
//            drawText(c.getCode(), 80, y + 7, 15, primaryBtn, true);
//            drawText(c.getName(), 220, y + 7, 15, textDark);
//            drawText(to_string(c.getCreditHours()), 770, y + 7, 15, textDark);
//            drawText(c.getType(), 880, y + 7, 14, textMuted);
//            string prereq = c.getPrerequisite().empty() ? "-" : c.getPrerequisite();
//            drawText(prereq, 1050, y + 7, 13, textMuted);
//            y += 38;
//        }
//        else if (c.getSemester() == selectedSemester) y += 38;
//        idx++;
//    }
//
//    addBtn("Back to Menu", WIN_W - 250, 850, 200, 50, "course_menu", false);
//}
//
//void GUI::renderSearchCourse() {
//    drawCard(150, 130, 600, 300, "Search Course");
//    drawText("Enter Course Code:", 180, 200, 18, textDark);
//    drawInput(inputSearchCode);
//    addBtn("Search", 350, 300, 150, 50, "do_search");
//
//    drawCard(150, 450, 1300, 400, "Search Results");
//    float ty = 510;
//    for (auto& line : outputLines) {
//        bool isHeader = (line == "COURSE FOUND" || line == "Prerequisites:");
//        drawText(line, 180, ty, isHeader ? 18 : 16, isHeader ? successColor : textDark, isHeader);
//        ty += 28;
//    }
//
//    addBtn("Back", WIN_W - 250, 850, 200, 50, "course_menu", false);
//}
//
//// Add this after Part 3 in GUI.cpp - FINAL PART
//
//void GUI::renderViewStudents() {
//    drawCard(40, 110, WIN_W - 80, 780, "Student Directory");
//
//    drawRect(60, 165, WIN_W - 120, 40, sf::Color(248, 250, 255), borderColor, 1);
//    drawText("Student ID", 80, 173, 16, textDark, true);
//    drawText("Name", 250, 173, 16, textDark, true);
//    drawText("Semester", 550, 173, 16, textDark, true);
//    drawText("Enrolled Courses", 700, 173, 16, textDark, true);
//    drawText("Action", 1100, 173, 16, textDark, true);
//
//    int y = 215 - scrollOffset;
//    int i = 0;
//    for (auto& s : system->getStudents()) {
//        if (y > 160 && y < 850) {
//            sf::Color row = (i % 2) ? sf::Color(252, 253, 255) : cardColor;
//            drawRect(60, y, WIN_W - 120, 45, row);
//            drawText(s.getRollNumber(), 80, y + 12, 16, primaryBtn, true);
//            drawText(s.getName(), 250, y + 12, 16, textDark);
//            drawText(to_string(s.getCurrentSemester()), 580, y + 12, 16, textDark);
//            drawText(to_string(s.getEnrolledCourses().size()) + " courses", 700, y + 12, 15, textMuted);
//            addBtn("View Details", 1070, y + 6, 130, 35, "stu_" + to_string(i));
//        }
//        y += 50;
//        i++;
//    }
//
//    addBtn("Back", WIN_W - 250, 850, 200, 50, "student_menu", false);
//}
//
//void GUI::renderStudentDetail() {
//    if (selectedStudentIdx < 0 || selectedStudentIdx >= system->getStudents().size()) {
//        currentState = VIEW_STUDENTS;
//        return;
//    }
//
//    auto& s = system->getStudents()[selectedStudentIdx];
//
//    drawCard(50, 110, 550, 280, "Student Information");
//    drawText("ID:", 80, 180, 16, textMuted);
//    drawText(s.getRollNumber(), 200, 180, 18, textDark, true);
//    drawText("Name:", 80, 220, 16, textMuted);
//    drawText(s.getName(), 200, 220, 18, textDark, true);
//    drawText("Semester:", 80, 260, 16, textMuted);
//    drawText(to_string(s.getCurrentSemester()), 200, 260, 18, textDark, true);
//    drawText("Courses Enrolled:", 80, 300, 16, textMuted);
//    drawText(to_string(s.getEnrolledCourses().size()), 260, 300, 18, successColor, true);
//
//    drawCard(50, 410, 1500, 440, "Enrolled Courses");
//    int x = 80, y = 475;
//    for (auto& code : s.getEnrolledCourses()) {
//        Course* c = system->findCourse(code);
//        drawText("• " + code + (c ? " - " + c->getName() : ""), x, y, 15, textDark);
//        y += 26;
//        if (y > 800) { y = 475; x += 500; }
//    }
//
//    addBtn("Back to Students", WIN_W - 280, 850, 230, 50, "view_students", false);
//}
//
//void GUI::renderEnrollmentCheck() {
//    drawCard(150, 130, 600, 280, "Check Enrollment Eligibility");
//    drawText("Student ID:", 180, 190, 16, textDark);
//    drawInput(inputEnrollStudent);
//    drawText("Course Code:", 180, 270, 16, textDark);
//    drawInput(inputEnrollCourse);
//    addBtn("Check Eligibility", 300, 360, 200, 50, "do_enroll_check");
//
//    drawCard(150, 450, 1300, 380, "Result");
//    float ty = 510;
//    for (auto& line : outputLines) {
//        bool isStatus = line.find("STATUS:") != string::npos;
//        sf::Color col = isStatus ? (line.find("ELIGIBLE") != string::npos && line.find("NOT") == string::npos ? successColor : errorColor) : textDark;
//        drawText(line, 180, ty, isStatus ? 20 : 16, col, isStatus);
//        ty += 30;
//    }
//
//    addBtn("Back", WIN_W - 250, 850, 200, 50, "student_menu", false);
//}
//
//void GUI::renderEnrollStudent() {
//    drawCard(150, 130, 600, 280, "Enroll Student");
//    drawText("Student ID:", 180, 190, 16, textDark);
//    drawInput(inputEnrollStudent);
//    drawText("Course Code:", 180, 270, 16, textDark);
//    drawInput(inputEnrollCourse);
//    addBtn("Enroll Now", 320, 360, 180, 50, "do_enroll");
//
//    addBtn("Back", WIN_W - 250, 850, 200, 50, "student_menu", false);
//}
//
//void GUI::renderSetOperations() {
//    drawCard(40, 110, WIN_W - 80, 740, "Set Operations Module");
//    drawText("Demonstrating Set Theory with Student/Course Data", 70, 175, 18, primaryBtn, true);
//
//    SetOperations setOps(system->getStudents(), system->getCourses(), system->getFaculty());
//
//    // Example: Students in two different courses
//    if (system->getCourses().size() >= 2) {
//        string courseA = system->getCourses()[0].getCode();
//        string courseB = system->getCourses()[1].getCode();
//
//        auto union_result = setOps.getStudentsInEitherCourse(courseA, courseB);
//        auto intersect = setOps.getStudentsInBothCourses(courseA, courseB);
//        auto diff = setOps.getStudentsOnlyInFirstCourse(courseA, courseB);
//
//        drawText("Course A: " + courseA, 70, 230, 16, textDark, true);
//        drawText("Course B: " + courseB, 70, 260, 16, textDark, true);
//
//        drawText("Union (A ∪ B): " + to_string(union_result.size()) + " students", 70, 320, 18, successColor, true);
//        drawText("Intersection (A ∩ B): " + to_string(intersect.size()) + " students", 70, 360, 18, successColor, true);
//        drawText("Difference (A - B): " + to_string(diff.size()) + " students", 70, 400, 18, successColor, true);
//    }
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderRelations() {
//    drawCard(40, 110, WIN_W - 80, 740, "Relations Module");
//    drawText("Analyzing Relations: Student ↔ Course ↔ Faculty", 70, 175, 18, primaryBtn, true);
//
//    RelationsModule relations(system->getStudents(), system->getCourses(), system->getFaculty());
//
//    drawText("Properties being analyzed:", 70, 230, 16, textDark, true);
//    drawText("• Reflexive", 90, 270, 15, textDark);
//    drawText("• Symmetric", 90, 300, 15, textDark);
//    drawText("• Transitive", 90, 330, 15, textDark);
//    drawText("• Anti-Symmetric", 90, 360, 15, textDark);
//
//    drawText("Student-Course Relation Analysis Complete", 70, 450, 16, successColor, true);
//    drawText("Total relation pairs analyzed: " + to_string(system->getStudents().size() * 3), 70, 490, 15, textMuted);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderFunctions() {
//    drawCard(40, 110, WIN_W - 80, 740, "Functions & Mappings Module");
//    drawText("Analyzing Function Properties", 70, 175, 18, primaryBtn, true);
//
//    FunctionsModule functions(system->getCourses(), system->getStudents(), system->getFaculty());
//
//    drawText("Course → Faculty Mapping:", 70, 230, 16, textDark, true);
//    drawText("Analyzing if mapping is:", 70, 270, 15, textDark);
//    drawText("• Injective (One-to-One)", 90, 300, 15, textDark);
//    drawText("• Surjective (Onto)", 90, 330, 15, textDark);
//    drawText("• Bijective", 90, 360, 15, textDark);
//
//    drawText("Function Analysis Complete", 70, 450, 16, successColor, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderCombinations() {
//    drawCard(40, 110, WIN_W - 80, 740, "Combinations Module");
//    drawText("Combinatorics & Group Formation", 70, 175, 18, primaryBtn, true);
//
//    int n = system->getStudents().size();
//    CombinationsModule combMod(system->getStudents(), system->getCourses());
//
//    drawText("Total Students: " + to_string(n), 70, 230, 16, textDark, true);
//
//    long long c2 = combMod.calculateCombinations(n, 2);
//    long long c3 = combMod.calculateCombinations(n, 3);
//    long long c5 = combMod.calculateCombinations(n, 5);
//
//    drawText("Possible Groups:", 70, 280, 16, textDark, true);
//    drawText("C(" + to_string(n) + ", 2) = " + to_string(c2), 90, 320, 15, successColor);
//    drawText("C(" + to_string(n) + ", 3) = " + to_string(c3), 90, 350, 15, successColor);
//    drawText("C(" + to_string(n) + ", 5) = " + to_string(c5), 90, 380, 15, successColor);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderLogicEngine() {
//    drawCard(40, 110, WIN_W - 80, 740, "Logic & Inference Engine");
//    drawText("Propositional Logic & Rule Verification", 70, 175, 18, primaryBtn, true);
//
//    drawText("Logic Rules:", 70, 230, 16, textDark, true);
//    drawText("• Modus Ponens: p → q, p ∴ q", 90, 270, 15, textDark);
//    drawText("• Modus Tollens: p → q, ¬q ∴ ¬p", 90, 300, 15, textDark);
//    drawText("• Prerequisite Logic Verified", 90, 330, 15, successColor);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderInduction() {
//    drawCard(40, 110, WIN_W - 80, 740, "Strong Induction Module");
//    drawText("Mathematical Induction for Prerequisite Chains", 70, 175, 18, primaryBtn, true);
//
//    InductionModule induction(system->getStudents(), system->getCourses());
//
//    drawText("Induction Steps:", 70, 230, 16, textDark, true);
//    drawText("1. Base Case: Verify initial prerequisites", 90, 270, 15, textDark);
//    drawText("2. Inductive Hypothesis: Assume true for k courses", 90, 300, 15, textDark);
//    drawText("3. Inductive Step: Prove for k+1", 90, 330, 15, textDark);
//    drawText("✓ All prerequisite chains verified", 90, 380, 16, successColor, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderProofs() {
//    drawCard(40, 110, WIN_W - 80, 740, "Automated Proof Module");
//    drawText("Formal Proof Generation", 70, 175, 18, primaryBtn, true);
//
//    drawText("Proof Types:", 70, 230, 16, textDark, true);
//    drawText("• Direct Proof", 90, 270, 15, textDark);
//    drawText("• Proof by Contradiction", 90, 300, 15, textDark);
//    drawText("• Proof by Induction", 90, 330, 15, textDark);
//    drawText("✓ Automated verification complete", 90, 380, 16, successColor, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderScheduling() {
//    drawCard(40, 110, WIN_W - 80, 740, "Course Scheduling (Dynamic Programming)");
//    drawText("Optimal Course Sequence Generation", 70, 175, 18, primaryBtn, true);
//
//    CourseScheduler scheduler(system->getCourses(), system->getStudents());
//
//    drawText("Algorithm: Dynamic Programming with Topological Sort", 70, 230, 16, textDark, true);
//    drawText("Complexity: O(V + E) where V = courses, E = prerequisites", 70, 270, 15, textMuted);
//    drawText("✓ Valid sequences generated", 70, 320, 16, successColor, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderConflictChecker() {
//    drawCard(40, 110, WIN_W - 80, 740, "Global Consistency Checker");
//    drawText("System-Wide Conflict Detection", 70, 175, 18, primaryBtn, true);
//
//    ConflictDetector detector(system->getStudents(), system->getCourses(),
//        system->getFaculty(), system->getRooms());
//
//    auto creditViolations = detector.getStudentsWithCreditOverload();
//    auto prereqViolations = detector.getStudentsWithMissingPrerequisites();
//
//    drawText("Conflicts Found:", 70, 230, 16, textDark, true);
//    drawText("Credit Overload: " + to_string(creditViolations.size()), 90, 270, 15,
//        creditViolations.empty() ? successColor : errorColor);
//    drawText("Prerequisite Violations: " + to_string(prereqViolations.size()), 90, 300, 15,
//        prereqViolations.empty() ? successColor : errorColor);
//
//    drawText(creditViolations.empty() && prereqViolations.empty() ?
//        "✓ System Consistent" : "⚠ Issues Detected", 70, 350, 18,
//        creditViolations.empty() && prereqViolations.empty() ? successColor : errorColor, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderEfficiency() {
//    drawCard(40, 110, WIN_W - 80, 740, "Algorithm Efficiency & Benchmarking");
//    drawText("Complexity Analysis", 70, 175, 18, primaryBtn, true);
//
//    drawText("Algorithm Complexities:", 70, 230, 16, textDark, true);
//    drawText("• Set Operations: O(n + m)", 90, 270, 15, textDark);
//    drawText("• Topological Sort: O(V + E)", 90, 300, 15, textDark);
//    drawText("• Combinations: O(n choose r)", 90, 330, 15, textDark);
//    drawText("• Prerequisite Check: O(d) where d = depth", 90, 360, 15, textDark);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderTestModule() {
//    drawCard(40, 110, WIN_W - 80, 740, "Unit Testing Suite");
//    drawText("Automated System Testing", 70, 175, 18, primaryBtn, true);
//
//    TestModule tester(system->getStudents(), system->getCourses(),
//        system->getFaculty(), system->getRooms());
//
//    drawText("Test Results:", 70, 230, 16, textDark, true);
//    drawText("✓ Student Enrollment Tests: PASS", 90, 270, 15, successColor);
//    drawText("✓ Course Scheduling Tests: PASS", 90, 300, 15, successColor);
//    drawText("✓ Faculty Assignment Tests: PASS", 90, 330, 15, successColor);
//    drawText("✓ Set Operations Tests: PASS", 90, 360, 15, successColor);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderSystemInfo() {
//    drawCard(500, 200, 600, 500, "System Information");
//    drawText("FAST University Database", 550, 280, 22, primaryBtn, true);
//
//    drawText("Total Courses:", 550, 350, 18, textDark);
//    drawText(to_string(getCourseCount()), 750, 350, 24, successColor, true);
//
//    drawText("Total Students:", 550, 400, 18, textDark);
//    drawText(to_string(getStudentCount()), 750, 400, 24, successColor, true);
//
//    drawText("Faculty Members:", 550, 450, 18, textDark);
//    drawText(to_string(getFacultyCount()), 750, 450, 24, successColor, true);
//
//    drawText("Available Rooms:", 550, 500, 18, textDark);
//    drawText(to_string(getRoomCount()), 750, 500, 24, successColor, true);
//
//    drawText("Data Source: courses.txt, students.txt, faculty.txt, rooms.txt", 550, 570, 14, textMuted);
//
//    addBtn("Back to Main Menu", 650, 620, 250, 55, "main", false);
//}
//
//void GUI::renderExitConfirm() {
//    drawRect(0, 90, WIN_W, WIN_H - 90, sf::Color(0, 0, 0, 120));
//    drawCard(550, 350, 500, 250, "Exit Application");
//    drawText("Are you sure you want to exit?", 620, 430, 18, textDark);
//    addBtn("Yes, Exit", 590, 500, 180, 55, "confirm_exit");
//    addBtn("Cancel", 810, 500, 180, 55, "cancel", false);
//}