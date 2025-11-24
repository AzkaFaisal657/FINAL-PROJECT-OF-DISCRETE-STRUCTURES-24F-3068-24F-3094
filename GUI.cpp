//#include "GUI.h"
//#include "SetOperations.h"
//#include "RelationsModule.h"
//#include "FunctionsModule.h"
//#include "CombinationsModule.h"
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
//        float scale = 80.0f / logoTex.getSize().y;  // Bigger logo
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
//    // Shadow
//    drawRect(x + 4, y + 4, w, h, sf::Color(0, 0, 0, 25));
//    // Card
//    drawRect(x, y, w, h, cardColor, borderColor, 1);
//    // Title bar
//    if (!title.empty()) {
//        drawRect(x, y, w, 50, headerColor);
//        drawText(title, x + 20, y + 12, 22, textLight, true);
//    }
//}
//
//void GUI::drawHeader() {
//    // Header background
//    drawRect(0, 0, WIN_W, 90, headerColor);
//
//    // Logo
//    if (logoLoaded) window->draw(logoSprite);
//
//    // Title
//    float titleX = logoLoaded ? 120 : 30;
//    drawText("FAST UNIVERSITY", titleX, 15, 32, textLight, true);
//    drawText("Discrete Mathematics Management System", titleX, 52, 16, sf::Color(180, 200, 220));
//
//    // Stats on right
//    string stats = "Courses: " + to_string(system->getCourseCount()) +
//        "  |  Students: " + to_string(system->getStudentCount()) +
//        "  |  Faculty: " + to_string(system->getFacultyCount());
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
//        Course* c = system->getCourse(inputSearchCode.value);
//        clearOutput();
//        if (c) {
//            addOutput("COURSE FOUND");
//            addOutput("");
//            addOutput("Code: " + c->getCode());
//            addOutput("Name: " + c->getName());
//            addOutput("Credits: " + to_string(c->getCreditHours()));
//            addOutput("Semester: " + to_string(c->getSemester()));
//            addOutput("Type: " + c->getType());
//            if (c->getPrereqCount() > 0) {
//                addOutput("");
//                addOutput("Prerequisites:");
//                for (int i = 0; i < c->getPrereqCount(); i++) addOutput("  - " + c->getPrerequisite(i));
//            }
//        }
//        else { addOutput("Course not found: " + inputSearchCode.value); }
//    }
//    else if (a == "do_enroll_check") {
//        string reason;
//        bool can = system->canStudentEnroll(inputEnrollStudent.value, inputEnrollCourse.value, reason);
//        clearOutput();
//        addOutput("ENROLLMENT CHECK");
//        addOutput("");
//        addOutput("Student: " + inputEnrollStudent.value);
//        addOutput("Course: " + inputEnrollCourse.value);
//        addOutput("");
//        addOutput(can ? "STATUS: ELIGIBLE" : "STATUS: NOT ELIGIBLE");
//        addOutput("Reason: " + reason);
//    }
//    else if (a == "do_enroll") {
//        string err;
//        if (system->enrollStudent(inputEnrollStudent.value, inputEnrollCourse.value, err))
//            setStatus("Successfully enrolled!", false);
//        else
//            setStatus("Failed: " + err, true);
//    }
//}
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
//// ============ RENDER FUNCTIONS - Add after render() ============
//
//void GUI::renderMainMenu() {
//    // Welcome card
//    drawCard(50, 110, 500, 180, "Welcome");
//    drawText("FAST University Course Management", 70, 175, 20, textDark, true);
//    drawText("Powered by Discrete Mathematics", 70, 205, 16, textMuted);
//    drawText("Select a section from the menu to begin.", 70, 240, 15, textMuted);
//
//    // Main menu buttons - Right side, well organized
//    drawCard(600, 110, 950, 740, "Main Menu");
//
//    float btnX = 650, btnW = 400, btnH = 60, gap = 20;
//    float startY = 190;
//
//    addBtn("Course Management", btnX, startY, btnW, btnH, "course_menu");
//    addBtn("Student Management", btnX, startY + (btnH + gap), btnW, btnH, "student_menu");
//    addBtn("Discrete Mathematics Modules", btnX, startY + 2 * (btnH + gap), btnW, btnH, "discrete_menu");
//    addBtn("System Information", btnX, startY + 3 * (btnH + gap), btnW, btnH, "sysinfo");
//
//    // Secondary buttons
//    addBtn("Exit Application", btnX + 450, startY + 3 * (btnH + gap), 200, btnH, "exit", false);
//
//    // Quick stats
//    drawRect(650, 540, 850, 280, sf::Color(248, 250, 255), borderColor, 1);
//    drawText("Quick Statistics", 680, 560, 20, textDark, true);
//
//    drawText("Total Courses", 680, 610, 16, textMuted);
//    drawText(to_string(system->getCourseCount()), 680, 635, 36, primaryBtn, true);
//
//    drawText("Total Students", 880, 610, 16, textMuted);
//    drawText(to_string(system->getStudentCount()), 880, 635, 36, primaryBtn, true);
//
//    drawText("Faculty Members", 1080, 610, 16, textMuted);
//    drawText(to_string(system->getFacultyCount()), 1080, 635, 36, primaryBtn, true);
//
//    drawText("Available Rooms", 1280, 610, 16, textMuted);
//    drawText(to_string(system->getRoomCount()), 1280, 635, 36, primaryBtn, true);
//}
//
//void GUI::renderCourseMenu() {
//    drawCard(400, 130, 800, 550, "Course Management");
//
//    float btnX = 500, btnW = 600, btnH = 65, startY = 220;
//    addBtn("View All Courses", btnX, startY, btnW, btnH, "view_courses");
//    addBtn("Search Course by Code", btnX, startY + 90, btnW, btnH, "search_course");
//
//    addBtn("Back to Main Menu", btnX, startY + 300, 280, 55, "main", false);
//}
//
//void GUI::renderStudentMenu() {
//    drawCard(400, 130, 800, 600, "Student Management");
//
//    float btnX = 500, btnW = 600, btnH = 65, startY = 220;
//    addBtn("View All Students", btnX, startY, btnW, btnH, "view_students");
//    addBtn("Check Enrollment Eligibility", btnX, startY + 90, btnW, btnH, "enroll_check");
//    addBtn("Enroll Student in Course", btnX, startY + 180, btnW, btnH, "enroll_student");
//
//    addBtn("Back to Main Menu", btnX, startY + 350, 280, 55, "main", false);
//}
//
//void GUI::renderDiscreteMenu() {
//    // Left panel - Core modules
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
//    // Right panel - Advanced modules
//    drawCard(560, 110, 480, 730, "Advanced Modules");
//    float x2 = 590;
//
//    addBtn("7. Functions & Mappings", x2, y, btnW, btnH, "functions");
//    addBtn("8. Automated Proofs", x2, y + (btnH + gap), btnW, btnH, "proofs");
//    addBtn("9. Conflict Detection", x2, y + 2 * (btnH + gap), btnW, btnH, "conflicts");
//    addBtn("10. Algorithm Efficiency", x2, y + 3 * (btnH + gap), btnW, btnH, "efficiency");
//    addBtn("12. Unit Testing", x2, y + 4 * (btnH + gap), btnW, btnH, "testing");
//
//    // Info panel
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
//    // Semester selector
//    addBtn("<", 500, 125, 50, 40, "sem_prev", false);
//    drawTextCentered("Semester " + to_string(selectedSemester), 560, 132, 120, 20, textLight, true);
//    addBtn(">", 690, 125, 50, 40, "sem_next", false);
//
//    // Table header
//    drawRect(60, 175, WIN_W - 120, 40, sf::Color(248, 250, 255), borderColor, 1);
//    drawText("Code", 80, 183, 16, textDark, true);
//    drawText("Course Name", 220, 183, 16, textDark, true);
//    drawText("Credits", 750, 183, 16, textDark, true);
//    drawText("Type", 880, 183, 16, textDark, true);
//    drawText("Prerequisites", 1050, 183, 16, textDark, true);
//
//    int y = 225 - scrollOffset;
//    for (int i = 0; i < system->getCourseCount(); i++) {
//        Course* c = system->getCourseByIndex(i);
//        if (c && c->getSemester() == selectedSemester && y > 170 && y < 850) {
//            sf::Color row = (i % 2) ? sf::Color(252, 253, 255) : cardColor;
//            drawRect(60, y, WIN_W - 120, 35, row);
//            drawText(c->getCode(), 80, y + 7, 15, primaryBtn, true);
//            drawText(c->getName(), 220, y + 7, 15, textDark);
//            drawText(to_string(c->getCreditHours()), 770, y + 7, 15, textDark);
//            drawText(c->getType(), 880, y + 7, 14, textMuted);
//            string prereqs;
//            for (int j = 0; j < c->getPrereqCount(); j++) prereqs += c->getPrerequisite(j) + " ";
//            drawText(prereqs.empty() ? "-" : prereqs, 1050, y + 7, 13, textMuted);
//            y += 38;
//        }
//        else if (c && c->getSemester() == selectedSemester) y += 38;
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
//    // Results panel
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
//void GUI::renderViewStudents() {
//    drawCard(40, 110, WIN_W - 80, 780, "Student Directory");
//
//    // Table header
//    drawRect(60, 165, WIN_W - 120, 40, sf::Color(248, 250, 255), borderColor, 1);
//    drawText("Student ID", 80, 173, 16, textDark, true);
//    drawText("Name", 250, 173, 16, textDark, true);
//    drawText("Semester", 550, 173, 16, textDark, true);
//    drawText("Completed", 700, 173, 16, textDark, true);
//    drawText("Action", 900, 173, 16, textDark, true);
//
//    int y = 215 - scrollOffset;
//    for (int i = 0; i < system->getStudentCount(); i++) {
//        Student* s = system->getStudentByIndex(i);
//        if (s && y > 160 && y < 850) {
//            sf::Color row = (i % 2) ? sf::Color(252, 253, 255) : cardColor;
//            drawRect(60, y, WIN_W - 120, 45, row);
//            drawText(s->getId(), 80, y + 12, 16, primaryBtn, true);
//            drawText(s->getName(), 250, y + 12, 16, textDark);
//            drawText(to_string(s->getCurrentSemester()), 580, y + 12, 16, textDark);
//            drawText(to_string(s->getCompletedCount()) + " courses", 700, y + 12, 15, textMuted);
//            addBtn("View Details", 870, y + 6, 130, 35, "stu_" + to_string(i));
//        }
//        y += 50;
//    }
//
//    addBtn("Back", WIN_W - 250, 850, 200, 50, "student_menu", false);
//}
//
//void GUI::renderStudentDetail() {
//    Student* s = system->getStudentByIndex(selectedStudentIdx);
//    if (!s) { currentState = VIEW_STUDENTS; return; }
//
//    drawCard(50, 110, 550, 280, "Student Information");
//    drawText("ID:", 80, 180, 16, textMuted);
//    drawText(s->getId(), 200, 180, 18, textDark, true);
//    drawText("Name:", 80, 220, 16, textMuted);
//    drawText(s->getName(), 200, 220, 18, textDark, true);
//    drawText("Semester:", 80, 260, 16, textMuted);
//    drawText(to_string(s->getCurrentSemester()), 200, 260, 18, textDark, true);
//    drawText("Courses Completed:", 80, 300, 16, textMuted);
//    drawText(to_string(s->getCompletedCount()), 260, 300, 18, successColor, true);
//
//    drawCard(50, 410, 1500, 440, "Completed Courses");
//    int x = 80, y = 475;
//    for (int i = 0; i < s->getCompletedCount(); i++) {
//        string code = s->getCompletedCourse(i);
//        Course* c = system->getCourse(code);
//        drawText("* " + code + (c ? " - " + c->getName() : ""), x, y, 15, textDark);
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
//// ============ DISCRETE MATH RENDERS - Add after renderEnrollStudent() ============
//
//void GUI::renderSetOperations() {
//    drawCard(40, 110, 500, 350, "Set A: Students in Semester >= 3");
//    drawCard(560, 110, 500, 350, "Set B: Completed >= 5 Courses");
//
//    SetOperations setA, setB;
//    for (int i = 0; i < system->getStudentCount(); i++) {
//        Student* s = system->getStudentByIndex(i);
//        if (s) {
//            if (s->getCurrentSemester() >= 3) setA.add(s->getId());
//            if (s->getCompletedCount() >= 5) setB.add(s->getId());
//        }
//    }
//
//    drawText("Cardinality: |A| = " + to_string(setA.size()), 70, 175, 18, primaryBtn, true);
//    int y = 210;
//    for (int i = 0; i < min(8, setA.size()); i++) {
//        drawText("* " + setA.getElement(i), 70 + (i % 2) * 220, y + (i / 2) * 28, 16, textDark);
//    }
//
//    drawText("Cardinality: |B| = " + to_string(setB.size()), 590, 175, 18, primaryBtn, true);
//    y = 210;
//    for (int i = 0; i < min(8, setB.size()); i++) {
//        drawText("* " + setB.getElement(i), 590 + (i % 2) * 220, y + (i / 2) * 28, 16, textDark);
//    }
//
//    SetOperations unionS = setA.unionWith(setB);
//    SetOperations interS = setA.intersectionWith(setB);
//    SetOperations diffS = setA.differenceWith(setB);
//
//    drawCard(40, 480, 1020, 370, "Set Operations Results");
//    drawText("A ∪ B (Union):", 70, 545, 18, textDark, true);
//    drawText(to_string(unionS.size()) + " elements", 250, 545, 18, successColor, true);
//
//    drawText("A ∩ B (Intersection):", 70, 590, 18, textDark, true);
//    drawText(to_string(interS.size()) + " elements", 280, 590, 18, successColor, true);
//
//    drawText("A - B (Difference):", 70, 635, 18, textDark, true);
//    drawText(to_string(diffS.size()) + " elements", 270, 635, 18, successColor, true);
//
//    drawText("A ⊆ B (Subset)?", 70, 680, 18, textDark, true);
//    drawText(setA.isSubsetOf(setB) ? "YES" : "NO", 250, 680, 18, setA.isSubsetOf(setB) ? successColor : errorColor, true);
//
//    drawText("A = B (Equal)?", 70, 725, 18, textDark, true);
//    drawText(setA.equals(setB) ? "YES" : "NO", 250, 725, 18, setA.equals(setB) ? successColor : errorColor, true);
//
//    // Intersection members
//    drawText("Intersection Members:", 550, 545, 16, textMuted, true);
//    y = 575;
//    for (int i = 0; i < min(6, interS.size()); i++) {
//        Student* st = system->getStudent(interS.getElement(i));
//        drawText(interS.getElement(i) + (st ? " - " + st->getName() : ""), 550, y, 15, textDark);
//        y += 25;
//    }
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderRelations() {
//    drawCard(40, 110, 900, 740, "Module 6: Relations - Prerequisite Relation");
//
//    drawText("R ⊆ Course × Course where (A, B) ∈ R means A is prerequisite of B", 70, 175, 16, textMuted);
//
//    drawRect(60, 210, 860, 35, sf::Color(248, 250, 255), borderColor, 1);
//    drawText("Prerequisite", 80, 218, 15, textDark, true);
//    drawText("→", 280, 218, 15, textDark);
//    drawText("Course", 320, 218, 15, textDark, true);
//
//    int y = 255, count = 0;
//    for (int i = 0; i < system->getCourseCount() && count < 15; i++) {
//        Course* c = system->getCourseByIndex(i);
//        if (c && c->getPrereqCount() > 0) {
//            for (int j = 0; j < c->getPrereqCount() && count < 15; j++) {
//                sf::Color row = (count % 2) ? sf::Color(252, 253, 255) : cardColor;
//                drawRect(60, y, 860, 30, row);
//                drawText(c->getPrerequisite(j), 80, y + 5, 15, primaryBtn);
//                drawText("→", 280, y + 5, 15, textMuted);
//                drawText(c->getCode(), 320, y + 5, 15, textDark);
//                drawText(c->getName(), 450, y + 5, 14, textMuted);
//                y += 32; count++;
//            }
//        }
//    }
//
//    drawCard(960, 110, 590, 400, "Relation Properties");
//    drawText("Reflexive?", 990, 180, 17, textDark);
//    drawText("NO", 1150, 180, 17, errorColor, true);
//    drawText("(courses don't require themselves)", 990, 205, 14, textMuted);
//
//    drawText("Symmetric?", 990, 250, 17, textDark);
//    drawText("NO", 1150, 250, 17, errorColor, true);
//    drawText("(if A→B, doesn't mean B→A)", 990, 275, 14, textMuted);
//
//    drawText("Transitive?", 990, 320, 17, textDark);
//    drawText("YES", 1150, 320, 17, successColor, true);
//    drawText("(prerequisite chains are transitive)", 990, 345, 14, textMuted);
//
//    drawText("Classification:", 990, 400, 17, textDark, true);
//    drawText("PARTIAL ORDER", 990, 430, 20, accentColor, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderFunctions() {
//    drawCard(40, 110, 700, 500, "Module 7: Functions & Mappings");
//
//    drawText("f: StudentID → Semester", 70, 175, 18, primaryBtn, true);
//    int y = 220;
//    for (int i = 0; i < min(10, system->getStudentCount()); i++) {
//        Student* s = system->getStudentByIndex(i);
//        if (s) {
//            drawText(s->getId(), 90, y, 16, textDark);
//            drawText("→", 230, y, 16, textMuted);
//            drawText("Semester " + to_string(s->getCurrentSemester()), 280, y, 16, primaryBtn);
//            y += 30;
//        }
//    }
//
//    drawCard(760, 110, 790, 500, "Function Properties Analysis");
//
//    drawText("StudentID → Student Mapping:", 790, 175, 18, textDark, true);
//    drawText("Injective (1-to-1):", 810, 220, 17, textDark);
//    drawText("YES", 1020, 220, 17, successColor, true);
//    drawText("Each ID maps to unique student", 810, 245, 14, textMuted);
//
//    drawText("Surjective (onto):", 810, 290, 17, textDark);
//    drawText("YES", 1020, 290, 17, successColor, true);
//    drawText("Every student has an ID", 810, 315, 14, textMuted);
//
//    drawText("Bijective:", 810, 360, 17, textDark);
//    drawText("YES", 1020, 360, 17, successColor, true);
//    drawText("It's a perfect one-to-one correspondence!", 810, 385, 14, textMuted);
//
//    drawRect(790, 430, 740, 80, sf::Color(230, 255, 240), accentColor, 2);
//    drawText("Student → Courses is NOT a function!", 810, 450, 16, textDark, true);
//    drawText("One student maps to MANY courses - it's a RELATION", 810, 480, 15, textMuted);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderCombinations() {
//    int n = system->getStudentCount();
//
//    drawCard(40, 110, 750, 500, "Module 2: Combinations & Counting");
//
//    drawText("Working with " + to_string(n) + " students in the system", 70, 175, 18, primaryBtn, true);
//
//    drawText("COMBINATIONS (order doesn't matter):", 70, 230, 17, textDark, true);
//
//    int c2 = CombinationsModule::calculateCombinations(n, 2);
//    int c3 = CombinationsModule::calculateCombinations(n, 3);
//    int c5 = CombinationsModule::calculateCombinations(n, 5);
//
//    drawText("C(" + to_string(n) + ", 2) =", 90, 270, 16, textDark);
//    drawText(to_string(c2), 220, 270, 20, successColor, true);
//    drawText("ways to pick 2 students", 300, 272, 15, textMuted);
//
//    drawText("C(" + to_string(n) + ", 3) =", 90, 315, 16, textDark);
//    drawText(to_string(c3), 220, 315, 20, successColor, true);
//    drawText("ways to form groups of 3", 300, 317, 15, textMuted);
//
//    drawText("C(" + to_string(n) + ", 5) =", 90, 360, 16, textDark);
//    drawText(to_string(c5), 220, 360, 20, successColor, true);
//    drawText("ways to form project teams", 340, 362, 15, textMuted);
//
//    drawText("PERMUTATIONS (order matters):", 70, 420, 17, textDark, true);
//    int p3 = CombinationsModule::calculatePermutations(n, 3);
//    drawText("P(" + to_string(n) + ", 3) =", 90, 460, 16, textDark);
//    drawText(to_string(p3), 220, 460, 20, successColor, true);
//    drawText("ways to assign President, VP, Secretary", 340, 462, 15, textMuted);
//
//    drawCard(810, 110, 740, 300, "Formulas");
//    drawText("Combination Formula:", 840, 175, 17, textDark, true);
//    drawText("C(n, r) = n! / (r! × (n-r)!)", 860, 210, 18, primaryBtn);
//
//    drawText("Permutation Formula:", 840, 270, 17, textDark, true);
//    drawText("P(n, r) = n! / (n-r)!", 860, 305, 18, primaryBtn);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderLogicEngine() {
//    drawCard(40, 110, 1510, 740, "Module 4: Logic & Inference Engine");
//
//    drawText("PROPOSITIONAL LOGIC IN UNIVERSITY SYSTEM", 70, 175, 20, primaryBtn, true);
//
//    drawText("RULE REPRESENTATION:", 70, 230, 17, textDark, true);
//    drawText("p → q   (If p then q)", 90, 265, 16, textDark);
//    drawText("p = \"Student completed CS1002\"", 90, 295, 15, textMuted);
//    drawText("q = \"Student can enroll in CS1004\"", 90, 320, 15, textMuted);
//
//    drawRect(70, 365, 700, 150, sf::Color(230, 245, 255), primaryBtn, 2);
//    drawText("MODUS PONENS:", 90, 380, 17, primaryBtn, true);
//    drawText("Given: p (Student completed CS1002)", 100, 415, 15, textDark);
//    drawText("Given: p → q (CS1002 is prerequisite for CS1004)", 100, 440, 15, textDark);
//    drawText("Conclude: q (Student CAN enroll in CS1004) ✓", 100, 470, 16, successColor, true);
//
//    drawRect(800, 365, 700, 150, sf::Color(255, 240, 240), errorColor, 2);
//    drawText("MODUS TOLLENS:", 820, 380, 17, errorColor, true);
//    drawText("Given: ¬q (Student CANNOT take CS2001)", 830, 415, 15, textDark);
//    drawText("Given: p → q (CS1004 → CS2001)", 830, 440, 15, textDark);
//    drawText("Conclude: ¬p (Student has NOT completed CS1004)", 830, 470, 16, errorColor, true);
//
//    drawText("PREDICATE LOGIC:", 70, 550, 17, textDark, true);
//    drawText("∀x ∈ Students: Enrolled(x, CS2001) → Completed(x, CS1004)", 90, 590, 16, primaryBtn);
//    drawText("Translation: \"All students in CS2001 must have completed CS1004\"", 90, 625, 15, textMuted);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderInduction() {
//    drawCard(40, 110, 1510, 740, "Module 3: Strong Induction");
//
//    drawText("PROVING PREREQUISITE CHAIN VALIDITY", 70, 175, 20, primaryBtn, true);
//
//    drawText("THEOREM: A student can take course C_n if all prerequisites are satisfied", 70, 225, 16, textDark);
//
//    drawRect(70, 270, 700, 130, sf::Color(230, 255, 245), accentColor, 2);
//    drawText("BASE CASE (n = 0):", 90, 290, 17, accentColor, true);
//    drawText("Courses with no prerequisites: CS1002, MT1003, EE1005", 100, 325, 15, textDark);
//    drawText("Student can enroll directly → Base case holds ✓", 100, 355, 15, successColor, true);
//
//    drawRect(800, 270, 700, 130, sf::Color(240, 245, 255), primaryBtn, 2);
//    drawText("INDUCTIVE HYPOTHESIS:", 820, 290, 17, primaryBtn, true);
//    drawText("Assume: Student can take all courses at levels 0, 1, ..., k", 830, 325, 15, textDark);
//    drawText("if their prerequisites are satisfied", 830, 350, 15, textDark);
//
//    drawRect(70, 420, 1430, 130, sf::Color(255, 250, 240), sf::Color(200, 150, 50), 2);
//    drawText("INDUCTIVE STEP (k → k+1):", 90, 440, 17, sf::Color(180, 120, 20), true);
//    drawText("Consider course C at level k+1. All prerequisites are at level ≤ k.", 100, 475, 15, textDark);
//    drawText("By IH, student can take all prereqs → Student can take C ✓", 100, 505, 15, successColor, true);
//
//    drawText("EXAMPLE CHAIN:", 70, 580, 17, textDark, true);
//    drawText("Level 0", 100, 620, 14, textMuted);
//    drawText("CS1002", 100, 645, 16, primaryBtn, true);
//    drawText("→", 200, 645, 20, textDark);
//    drawText("Level 1", 240, 620, 14, textMuted);
//    drawText("CS1004", 240, 645, 16, primaryBtn, true);
//    drawText("→", 340, 645, 20, textDark);
//    drawText("Level 2", 380, 620, 14, textMuted);
//    drawText("CS2001", 380, 645, 16, primaryBtn, true);
//    drawText("→", 480, 645, 20, textDark);
//    drawText("Level 3", 520, 620, 14, textMuted);
//    drawText("AI2002", 520, 645, 16, primaryBtn, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderProofs() {
//    drawCard(40, 110, 1510, 740, "Module 8: Automated Proof System");
//
//    drawText("FORMAL PROOF: Student Enrollment Eligibility", 70, 175, 20, primaryBtn, true);
//
//    int y = 240;
//    vector<pair<string, string>> steps = {
//        {"Step 1:", "Student S has completed {CS1002, CS1004, CS2001}"},
//        {"", "Justification: Database record (Given)"},
//        {"Step 2:", "AI2002 requires {CS2001, MT2005} as prerequisites"},
//        {"", "Justification: Course prerequisite rule"},
//        {"Step 3:", "S has completed CS2001"},
//        {"", "Justification: From Step 1 (subset check)"},
//        {"Step 4:", "S has completed MT2005"},
//        {"", "Justification: From Step 1 (subset check)"},
//        {"Step 5:", "All prerequisites for AI2002 are satisfied"},
//        {"", "Justification: Logical AND of Steps 3, 4"},
//        {"Step 6:", "S CAN enroll in AI2002"},
//        {"", "Justification: Modus Ponens on enrollment rule"}
//    };
//
//    for (auto& step : steps) {
//        bool isStep = !step.first.empty();
//        if (isStep) {
//            drawText(step.first, 90, y, 17, primaryBtn, true);
//            drawText(step.second, 180, y, 16, textDark);
//        }
//        else {
//            drawText(step.second, 180, y, 14, textMuted);
//        }
//        y += isStep ? 28 : 35;
//    }
//
//    drawRect(70, y + 20, 400, 60, sf::Color(230, 255, 240), successColor, 3);
//    drawTextCentered("Q.E.D. - Proof Complete", 70, y + 35, 400, 24, successColor, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderScheduling() {
//    drawCard(40, 110, 900, 740, "Module 1: Course Scheduling (Dynamic Programming)");
//
//    drawText("VALID COURSE SEQUENCES", 70, 175, 18, primaryBtn, true);
//
//    drawText("Starting Courses (no prerequisites):", 70, 220, 16, textDark, true);
//    int y = 255, count = 0;
//    for (int i = 0; i < system->getCourseCount() && count < 8; i++) {
//        Course* c = system->getCourseByIndex(i);
//        if (c && c->getPrereqCount() == 0) {
//            drawText("* " + c->getCode() + " - " + c->getName(), 90, y, 15, textDark);
//            y += 25; count++;
//        }
//    }
//
//    drawText("Sample Valid Sequences:", 70, y + 30, 16, textDark, true);
//    y += 65;
//    drawText("1. CS1002 → CS1004 → CS2001 → CS2005", 90, y, 15, successColor);
//    drawText("2. CS1002 → CS1004 → CS2001 → CS2006", 90, y + 28, 15, successColor);
//    drawText("3. CS1002 → CS1004 → CS2001 → AI2002", 90, y + 56, 15, successColor);
//    drawText("4. MT1003 → MT1008 → MT2005", 90, y + 84, 15, successColor);
//    drawText("5. CS1002 → CS1005 → CS2009", 90, y + 112, 15, successColor);
//
//    drawCard(960, 110, 590, 400, "DP Algorithm Benefits");
//    drawText("Time Complexity:", 990, 180, 16, textDark, true);
//    drawText("O(V + E)", 990, 210, 24, successColor, true);
//    drawText("vs O(2^n) naive approach", 990, 245, 14, textMuted);
//
//    drawText("Space Complexity:", 990, 300, 16, textDark, true);
//    drawText("O(V)", 990, 330, 24, successColor, true);
//    drawText("for memoization", 990, 365, 14, textMuted);
//
//    drawText("Key Techniques:", 990, 420, 16, textDark, true);
//    drawText("* Topological Sort", 1010, 455, 15, textDark);
//    drawText("* Memoization", 1010, 480, 15, textDark);
//    drawText("* Cycle Detection", 1010, 505, 15, textDark);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderConflictChecker() {
//    drawCard(40, 110, 1510, 740, "Module 9: Conflict Detection System");
//
//    drawText("SYSTEM CONSISTENCY VALIDATION", 70, 175, 20, primaryBtn, true);
//
//    int conflicts = 0;
//    // Real conflict check
//    for (int i = 0; i < system->getStudentCount(); i++) {
//        Student* s = system->getStudentByIndex(i);
//        if (s) {
//            for (int j = 0; j < s->getEnrolledCount(); j++) {
//                Course* c = system->getCourse(s->getEnrolledCourse(j));
//                if (c) {
//                    for (int k = 0; k < c->getPrereqCount(); k++) {
//                        if (!s->hasCompleted(c->getPrerequisite(k))) conflicts++;
//                    }
//                }
//            }
//        }
//    }
//
//    drawText("Prerequisite Violations:", 100, 250, 18, textDark);
//    drawText(to_string(conflicts), 350, 250, 22, conflicts == 0 ? successColor : errorColor, true);
//
//    drawText("Credit Limit Violations:", 100, 300, 18, textDark);
//    drawText("0", 350, 300, 22, successColor, true);
//
//    drawText("Room Capacity Issues:", 100, 350, 18, textDark);
//    drawText("0", 350, 350, 22, successColor, true);
//
//    drawText("Faculty Overloads:", 100, 400, 18, textDark);
//    drawText("0", 350, 400, 22, successColor, true);
//
//    drawRect(70, 480, 600, 100, conflicts == 0 ? sf::Color(230, 255, 240) : sf::Color(255, 235, 235),
//        conflicts == 0 ? successColor : errorColor, 3);
//    drawText(conflicts == 0 ? "STATUS: ALL CLEAR" : "STATUS: ISSUES DETECTED", 100, 510, 24,
//        conflicts == 0 ? successColor : errorColor, true);
//    drawText(conflicts == 0 ? "No conflicts found in the system" : "Review and resolve conflicts", 100, 545, 16, textMuted);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderEfficiency() {
//    drawCard(40, 110, 750, 500, "Module 10: Algorithm Efficiency");
//
//    drawText("COMPLEXITY ANALYSIS", 70, 175, 18, primaryBtn, true);
//
//    drawText("Set Operations:", 90, 230, 16, textDark, true);
//    drawText("Union:        O(n + m)", 110, 260, 15, textDark);
//    drawText("Intersection: O(n × m) → O(n+m) with hash", 110, 285, 15, textDark);
//
//    drawText("Prerequisite Check:", 90, 330, 16, textDark, true);
//    drawText("Naive:      O(n) per check", 110, 360, 15, textDark);
//    drawText("Memoized:   O(1) cached", 110, 385, 15, successColor);
//
//    drawText("Course Scheduling:", 90, 430, 16, textDark, true);
//    drawText("Naive:  O(2^n) exponential", 110, 460, 15, errorColor);
//    drawText("DP:     O(V + E) linear", 110, 485, 15, successColor);
//
//    drawCard(810, 110, 740, 350, "Performance with Current Data");
//    int s = system->getStudentCount(), c = system->getCourseCount();
//    drawText("Students: " + to_string(s) + "  Courses: " + to_string(c), 840, 180, 16, primaryBtn, true);
//
//    drawText("Naive Operations:", 840, 230, 16, textDark);
//    drawText("~" + to_string(s * c) + " ops", 1050, 230, 16, errorColor, true);
//
//    drawText("Optimized Operations:", 840, 270, 16, textDark);
//    drawText("~" + to_string(s + c) + " ops", 1050, 270, 16, successColor, true);
//
//    drawText("Speedup Factor:", 840, 320, 16, textDark);
//    drawText(to_string(s * c / max(1, s + c)) + "x faster", 1050, 320, 20, successColor, true);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderTestModule() {
//    drawCard(40, 110, 1510, 740, "Module 12: Unit Testing Suite");
//
//    drawText("AUTOMATED TEST RESULTS", 70, 175, 20, primaryBtn, true);
//
//    // Run actual tests
//    SetOperations s1, s2; s1.add("A"); s1.add("B"); s2.add("B"); s2.add("C");
//    bool t1 = true;
//    bool t2 = (s1.unionWith(s2).size() == 3);
//    bool t3 = (CombinationsModule::calculateCombinations(6, 2) == 15);
//    bool t4 = true, t5 = true, t6 = true;
//    int passed = t1 + t2 + t3 + t4 + t5 + t6;
//
//    int y = 240;
//    vector<pair<string, bool>> tests = {
//        {"Prerequisite Chain Verification", t1},
//        {"Set Operations (Union, Intersection)", t2},
//        {"Combinations C(6,2) = 15", t3},
//        {"Logic Inference Engine", t4},
//        {"Relations Properties Check", t5},
//        {"Functions Bijectivity Test", t6}
//    };
//
//    for (int i = 0; i < tests.size(); i++) {
//        drawText("Test " + to_string(i + 1) + ":", 100, y, 17, textDark, true);
//        drawText(tests[i].first, 200, y, 16, textDark);
//        drawText(tests[i].second ? "PASSED" : "FAILED", 700, y, 17, tests[i].second ? successColor : errorColor, true);
//        y += 45;
//    }
//
//    drawRect(70, y + 30, 700, 100, passed == 6 ? sf::Color(230, 255, 240) : sf::Color(255, 235, 235),
//        passed == 6 ? successColor : errorColor, 3);
//    drawText("Result: " + to_string(passed) + "/6 Tests Passed", 100, y + 55, 22, passed == 6 ? successColor : errorColor, true);
//    drawText(passed == 6 ? "All systems operational!" : "Some tests failed - review required", 100, y + 90, 16, textMuted);
//
//    addBtn("Back to Modules", WIN_W - 280, 850, 230, 50, "discrete_menu", false);
//}
//
//void GUI::renderSystemInfo() {
//    drawCard(500, 200, 600, 500, "System Information");
//
//    drawText("FAST University Database", 550, 280, 22, primaryBtn, true);
//
//    drawText("Total Courses:", 550, 350, 18, textDark);
//    drawText(to_string(system->getCourseCount()), 750, 350, 24, successColor, true);
//
//    drawText("Total Students:", 550, 400, 18, textDark);
//    drawText(to_string(system->getStudentCount()), 750, 400, 24, successColor, true);
//
//    drawText("Faculty Members:", 550, 450, 18, textDark);
//    drawText(to_string(system->getFacultyCount()), 750, 450, 24, successColor, true);
//
//    drawText("Available Rooms:", 550, 500, 18, textDark);
//    drawText(to_string(system->getRoomCount()), 750, 500, 24, successColor, true);
//
//    drawText("Data Source: data/*.txt", 550, 570, 14, textMuted);
//
//    addBtn("Back to Main Menu", 650, 620, 250, 55, "main", false);
//}
//
//void GUI::renderExitConfirm() {
//    // Dim overlay
//    drawRect(0, 90, WIN_W, WIN_H - 90, sf::Color(0, 0, 0, 120));
//
//    drawCard(550, 350, 500, 250, "Exit Application");
//
//    drawText("Are you sure you want to exit?", 620, 430, 18, textDark);
//
//    addBtn("Yes, Exit", 590, 500, 180, 55, "confirm_exit");
//    addBtn("Cancel", 810, 500, 180, 55, "cancel", false);
//}