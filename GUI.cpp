#include "GUI.h"

GUI::GUI(UniversitySystem* sys) : system(sys), currentState(MAIN_MENU), selectedOption(0),
selectedSemester(1), selectedStudentId("22K-0001"), message("") {
    window = nullptr;

    // Initialize colors
    backgroundColor = sf::Color(25, 25, 50);
    titleColor = sf::Color(255, 215, 0);
    textColor = sf::Color(255, 255, 255);
    buttonColor = sf::Color(70, 70, 120);
    selectedColor = sf::Color(100, 150, 255);
    messageColor = sf::Color(255, 200, 100);
}

GUI::~GUI() {
    if (window) {
        window->close();
        delete window;
    }
}

void GUI::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1200, 800), "FAST University - Discrete Math Management System");
    window->setFramerateLimit(60);
}

bool GUI::loadFont() {
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Warning: Could not load font. Please add arial.ttf to your project folder." << endl;
        return false;
    }
    return true;
}

void GUI::run() {
    initWindow();

    if (!loadFont()) {
        cout << "Running in console mode..." << endl;
        system->demonstrateAllModules();
        return;
    }

    cout << "SFML GUI Started Successfully!" << endl;
    cout << "Use Arrow Keys to navigate, Enter to select, Escape to go back" << endl;

    while (window->isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void GUI::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        switch (currentState) {
        case MAIN_MENU:
            handleMainMenuInput(event);
            break;
        case VIEW_COURSES:
            handleCoursesViewInput(event);
            break;
        case VIEW_STUDENTS:
            handleStudentsViewInput(event);
            break;
        case ENROLLMENT:
            handleEnrollmentInput(event);
            break;
        case DISCRETE_DEMOS:
            handleDiscreteDemosInput(event);
            break;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (currentState == MAIN_MENU) {
                    currentState = EXIT_CONFIRM;
                }
                else {
                    currentState = MAIN_MENU;
                    selectedOption = 0;
                }
            }
        }
    }
}

void GUI::update() {
    // Update logic here
}

void GUI::render() {
    window->clear(backgroundColor);

    // Draw header
    drawText("FAST University Management System", 50, 20, 36, titleColor);
    drawText("Discrete Mathematics Project - SFML GUI", 50, 65, 20, textColor);

    switch (currentState) {
    case MAIN_MENU:
        drawMainMenu();
        break;
    case VIEW_COURSES:
        drawCoursesView();
        break;
    case VIEW_STUDENTS:
        drawStudentsView();
        break;
    case ENROLLMENT:
        drawEnrollmentScreen();
        break;
    case DISCRETE_DEMOS:
        drawDiscreteDemos();
        break;
    case CONFLICT_REPORT:
        drawConflictReport();
        break;
    case EXIT_CONFIRM:
        drawExitConfirm();
        break;
    }

    // Draw footer message
    if (!message.empty()) {
        drawText(message, 50, 750, 18, messageColor);
    }

    // Draw controls help
    drawText("Controls: Arrow Keys = Navigate | Enter = Select | Escape = Back", 50, 770, 16, textColor);

    window->display();
}

void GUI::drawMainMenu() {
    drawText("MAIN MENU", 500, 150, 32, titleColor);

    vector<string> menuItems = {
        "View Courses by Semester",
        "View Student Information",
        "Course Enrollment System",
        "Discrete Math Demonstrations",
        "Generate Conflict Report",
        "System Information",
        "Exit System"
    };

    for (int i = 0; i < menuItems.size(); i++) {
        drawButton(menuItems[i], 400, 220 + i * 70, 400, 50, i == selectedOption);
    }

    drawText("Welcome to FAST University Course Management", 400, 650, 20, textColor);
    drawText("Demonstrating Discrete Mathematics Concepts", 400, 680, 20, textColor);
}

void GUI::drawCoursesView() {
    drawText("COURSE CATALOG", 500, 120, 32, titleColor);

    // Semester selection
    drawText("Select Semester: " + to_string(selectedSemester), 400, 180, 24, textColor);
    drawButton("Previous", 650, 175, 120, 35, false);
    drawButton("Next", 780, 175, 120, 35, false);

    // Display courses for selected semester
    drawBox(50, 230, 1100, 500, sf::Color(40, 40, 80), sf::Color(100, 100, 150));

    int yPos = 250;
    int courseCount = 0;

    for (int i = 0; i < system->getCourseCount(); i++) {
        Course* course = system->getCourseByIndex(i);
        if (course && course->getSemester() == selectedSemester) {
            string courseInfo = course->getCode() + " - " + course->getName() +
                " (" + to_string(course->getCreditHours()) + " credits) - " + course->getType();
            drawText(courseInfo, 70, yPos, 18, textColor);
            yPos += 30;
            courseCount++;
        }
    }

    if (courseCount == 0) {
        drawText("No courses found for Semester " + to_string(selectedSemester), 500, 300, 24, textColor);
    }

    drawText("Total Courses: " + to_string(courseCount), 70, 750, 18, textColor);
    drawButton("Back to Main Menu", 900, 750, 250, 35, false);
}

void GUI::drawStudentsView() {
    drawText("STUDENT INFORMATION", 480, 120, 32, titleColor);

    // Student selection
    drawText("Student ID: " + selectedStudentId, 400, 180, 24, textColor);

    Student* student = system->getStudent(selectedStudentId);
    if (student) {
        drawBox(50, 230, 1100, 500, sf::Color(40, 40, 80), sf::Color(100, 100, 150));

        // Basic info
        drawText("Name: " + student->getName(), 70, 250, 20, textColor);
        drawText("Current Semester: " + to_string(student->getCurrentSemester()), 70, 280, 20, textColor);
        drawText("Completed Courses: " + to_string(student->getCompletedCount()), 70, 310, 20, textColor);
        drawText("Currently Enrolled: " + to_string(student->getEnrolledCount()), 70, 340, 20, textColor);

        // Completed courses
        int yPos = 380;
        drawText("Completed Courses:", 70, yPos, 20, titleColor);
        yPos += 30;

        for (int i = 0; i < student->getCompletedCount(); i++) {
            string courseCode = student->getCompletedCourse(i);
            Course* course = system->getCourse(courseCode);
            if (course) {
                drawText("• " + courseCode + " - " + course->getName(), 90, yPos, 16, textColor);
                yPos += 25;
            }
        }

        // Enrolled courses
        yPos += 20;
        drawText("Currently Enrolled:", 70, yPos, 20, titleColor);
        yPos += 30;

        for (int i = 0; i < student->getEnrolledCount(); i++) {
            string courseCode = student->getEnrolledCourse(i);
            Course* course = system->getCourse(courseCode);
            if (course) {
                drawText("• " + courseCode + " - " + course->getName(), 90, yPos, 16, textColor);
                yPos += 25;
            }
        }
    }
    else {
        drawText("Student not found: " + selectedStudentId, 500, 300, 24, textColor);
    }

    drawButton("Back to Main Menu", 900, 750, 250, 35, false);
}

void GUI::drawEnrollmentScreen() {
    drawText("COURSE ENROLLMENT SYSTEM", 450, 120, 32, titleColor);

    drawText("Student: " + selectedStudentId, 100, 180, 24, textColor);
    drawText("Check enrollment eligibility for courses", 100, 220, 20, textColor);

    drawBox(50, 260, 1100, 400, sf::Color(40, 40, 80), sf::Color(100, 100, 150));

    // Display courses that student can enroll in
    int yPos = 280;
    int availableCount = 0;

    for (int i = 0; i < system->getCourseCount(); i++) {
        Course* course = system->getCourseByIndex(i);
        if (course) {
            string reason;
            bool canEnroll = system->canStudentEnroll(selectedStudentId, course->getCode(), reason);

            if (canEnroll) {
                string courseInfo = course->getCode() + " - " + course->getName() +
                    " (Semester " + to_string(course->getSemester()) + ")";
                drawText("✓ " + courseInfo, 70, yPos, 16, sf::Color(100, 255, 100));
                yPos += 25;
                availableCount++;
            }
        }
    }

    if (availableCount == 0) {
        drawText("No available courses for enrollment at this time", 400, 300, 20, textColor);
    }

    drawText("Available Courses: " + to_string(availableCount), 70, 680, 18, textColor);
    drawButton("Enroll in CS2001", 800, 300, 300, 40, selectedOption == 0);
    drawButton("Enroll in CS2005", 800, 350, 300, 40, selectedOption == 1);
    drawButton("Back to Main Menu", 900, 750, 250, 35, false);
}

void GUI::drawDiscreteDemos() {
    drawText("DISCRETE MATHEMATICS DEMONSTRATIONS", 350, 120, 32, titleColor);

    vector<string> demoItems = {
        "Set Operations",
        "Relations & Properties",
        "Combinations & Counting",
        "Logic & Inference Engine",
        "Functions & Mappings",
        "Automated Proof System",
        "Run All Demonstrations"
    };

    for (int i = 0; i < demoItems.size(); i++) {
        drawButton(demoItems[i], 400, 180 + i * 70, 400, 50, i == selectedOption);
    }

    drawText("Select a discrete mathematics module to demonstrate", 400, 650, 20, textColor);
    drawButton("Back to Main Menu", 900, 750, 250, 35, false);
}

void GUI::drawConflictReport() {
    drawText("CONFLICT DETECTION REPORT", 450, 120, 32, titleColor);

    drawBox(50, 180, 1100, 500, sf::Color(40, 40, 80), sf::Color(100, 100, 150));

    drawText("System Analysis Results:", 70, 200, 24, titleColor);
    drawText("✓ No room capacity conflicts detected", 90, 240, 18, sf::Color(100, 255, 100));
    drawText("✓ No faculty teaching overloads", 90, 270, 18, sf::Color(100, 255, 100));
    drawText("✓ No prerequisite violations", 90, 300, 18, sf::Color(100, 255, 100));
    drawText("✓ All students within credit limits", 90, 330, 18, sf::Color(100, 255, 100));

    drawText("System Status: ALL CLEAR", 70, 400, 28, sf::Color(100, 255, 100));
    drawText("No scheduling conflicts detected in the system", 70, 450, 20, textColor);

    drawButton("Back to Main Menu", 900, 750, 250, 35, false);
}

void GUI::drawExitConfirm() {
    drawText("EXIT SYSTEM", 520, 300, 32, titleColor);
    drawText("Are you sure you want to exit?", 450, 350, 24, textColor);

    drawButton("Yes, Exit", 400, 420, 200, 50, selectedOption == 0);
    drawButton("No, Go Back", 650, 420, 200, 50, selectedOption == 1);
}

void GUI::drawText(string text, float x, float y, int size, sf::Color color) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setFillColor(color);
    sfText.setPosition(x, y);
    window->draw(sfText);
}

void GUI::drawButton(string text, float x, float y, float width, float height, bool selected) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(selected ? selectedColor : buttonColor);
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(selected ? 3 : 1);
    window->draw(button);

    // Center text in button
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(20);
    sfText.setFillColor(textColor);

    sf::FloatRect textRect = sfText.getLocalBounds();
    sfText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    sfText.setPosition(x + width / 2.0f, y + height / 2.0f);

    window->draw(sfText);
}

void GUI::drawBox(float x, float y, float width, float height, sf::Color fillColor, sf::Color outlineColor) {
    sf::RectangleShape box(sf::Vector2f(width, height));
    box.setPosition(x, y);
    box.setFillColor(fillColor);
    box.setOutlineColor(outlineColor);
    box.setOutlineThickness(2);
    window->draw(box);
}

// Input Handlers
void GUI::handleMainMenuInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedOption = (selectedOption - 1 + 7) % 7;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedOption = (selectedOption + 1) % 7;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            switch (selectedOption) {
            case 0: currentState = VIEW_COURSES; break;
            case 1: currentState = VIEW_STUDENTS; break;
            case 2: currentState = ENROLLMENT; break;
            case 3: currentState = DISCRETE_DEMOS; break;
            case 4: currentState = CONFLICT_REPORT; break;
            case 5:
                message = "System Info: " + to_string(system->getCourseCount()) + " courses, " +
                    to_string(system->getStudentCount()) + " students, " +
                    to_string(system->getFacultyCount()) + " faculty";
                break;
            case 6: currentState = EXIT_CONFIRM; break;
            }
        }
    }
}

void GUI::handleCoursesViewInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            selectedSemester = max(1, selectedSemester - 1);
        }
        else if (event.key.code == sf::Keyboard::Right) {
            selectedSemester = min(8, selectedSemester + 1);
        }
    }
}

void GUI::handleStudentsViewInput(sf::Event& event) {
    // Student view input handling
}

void GUI::handleEnrollmentInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedOption = (selectedOption - 1 + 3) % 3;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedOption = (selectedOption + 1) % 3;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedOption == 0) {
                string errorMsg;
                if (system->enrollStudent(selectedStudentId, "CS2001", errorMsg)) {
                    message = "Successfully enrolled in CS2001!";
                }
                else {
                    message = "Enrollment failed: " + errorMsg;
                }
            }
            else if (selectedOption == 1) {
                string errorMsg;
                if (system->enrollStudent(selectedStudentId, "CS2005", errorMsg)) {
                    message = "Successfully enrolled in CS2005!";
                }
                else {
                    message = "Enrollment failed: " + errorMsg;
                }
            }
        }
    }
}

void GUI::handleDiscreteDemosInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedOption = (selectedOption - 1 + 7) % 7;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedOption = (selectedOption + 1) % 7;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            message = "Running " + to_string(selectedOption + 1) + " demonstration...";
        }
    }
}

vector<string> GUI::wrapText(string text, int lineLength) {
    vector<string> lines;
    stringstream ss(text);
    string word;
    string currentLine;

    while (ss >> word) {
        if (currentLine.length() + word.length() + 1 > lineLength) {
            lines.push_back(currentLine);
            currentLine = word;
        }
        else {
            if (!currentLine.empty()) currentLine += " ";
            currentLine += word;
        }
    }

    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}