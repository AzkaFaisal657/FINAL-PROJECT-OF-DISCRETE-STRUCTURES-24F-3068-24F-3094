#pragma once
#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "UniversitySystem.h"
#include <vector>
#include <functional>
using namespace std;

struct Button {
    sf::RectangleShape shape;
    sf::Text label;
    string action;
    bool hovered = false;
    bool contains(sf::Vector2f p) { return shape.getGlobalBounds().contains(p); }
};

struct InputBox {
    sf::RectangleShape box;
    sf::Text text;
    string value;
    string placeholder;
    bool active = false;
    int maxLength = 20;
    bool contains(sf::Vector2f p) { return box.getGlobalBounds().contains(p); }
};

class GUI {
private:
    sf::RenderWindow* window;
    UniversitySystem* system;
    sf::Font font;
    sf::Texture logoTex;
    sf::Sprite logoSprite;
    bool logoLoaded = false;

    enum State {
        MAIN_MENU, COURSE_MENU, STUDENT_MENU, DISCRETE_MENU,
        // Course states
        VIEW_COURSES, SEARCH_COURSE, ADD_COURSE,
        // Student states  
        VIEW_STUDENTS, STUDENT_DETAIL, ADD_STUDENT, ENROLLMENT_CHECK, ENROLL_STUDENT,
        // Discrete Math states
        SET_OPERATIONS, RELATIONS_MODULE, FUNCTIONS_MODULE, COMBINATIONS_MODULE,
        LOGIC_ENGINE, INDUCTION_MODULE, PROOFS_MODULE, SCHEDULING_MODULE,
        CONFLICT_CHECKER, EFFICIENCY_MODULE, TEST_MODULE,
        // Other
        SYSTEM_INFO, EXIT_CONFIRM
    };

    State currentState = MAIN_MENU;
    int selectedSemester = 1;
    int selectedStudentIdx = -1;
    int scrollOffset = 0;

    string statusMsg;
    sf::Color statusColor;
    float statusTimer = 0;

    // Input boxes
    InputBox inputStudentId, inputStudentName, inputStudentSem;
    InputBox inputCourseCode, inputCourseName, inputCourseCredits, inputCourseSem;
    InputBox inputSearchCode, inputEnrollStudent, inputEnrollCourse;
    InputBox* activeInput = nullptr;

    // Colors
    sf::Color bgColor{ 235, 245, 255 };
    sf::Color navyColor{ 25, 50, 95 };
    sf::Color lightBlue{ 180, 210, 245 };
    sf::Color white{ 255, 255, 255 };
    sf::Color black{ 30, 30, 30 };
    sf::Color btnColor{ 55, 90, 140 };
    sf::Color btnHover{ 85, 130, 190 };
    sf::Color success{ 40, 160, 80 };
    sf::Color error{ 200, 60, 60 };

    vector<Button> buttons;
    vector<string> outputLines; // For displaying results

public:
    GUI(UniversitySystem* sys);
    ~GUI();
    void run();

private:
    void initWindow();
    bool loadResources();
    void handleEvents();
    void update(float dt);
    void render();

    // Button/Input helpers
    void clearButtons();
    Button& addBtn(string text, float x, float y, float w, float h, string action);
    void setupInput(InputBox& inp, float x, float y, float w, string placeholder, int maxLen = 20);
    void updateHover(sf::Vector2f pos);
    string clickButton(sf::Vector2f pos);
    void clickInput(sf::Vector2f pos);
    void typeChar(char c);
    void backspace();

    // Drawing
    void drawText(string s, float x, float y, int sz, sf::Color c, bool bold = false);
    void drawRect(float x, float y, float w, float h, sf::Color fill, sf::Color outline = sf::Color::Transparent, float thick = 0);
    void drawHeader(string title);
    void drawInput(InputBox& inp);
    void drawOutputPanel(float x, float y, float w, float h);
    void drawStatusBar();

    // Screens
    void renderMainMenu();
    void renderCourseMenu();
    void renderStudentMenu();
    void renderDiscreteMenu();
    void renderViewCourses();
    void renderSearchCourse();
    void renderAddCourse();
    void renderViewStudents();
    void renderStudentDetail();
    void renderAddStudent();
    void renderEnrollmentCheck();
    void renderEnrollStudent();
    void renderSetOperations();
    void renderRelations();
    void renderFunctions();
    void renderCombinations();
    void renderLogicEngine();
    void renderInduction();
    void renderProofs();
    void renderScheduling();
    void renderConflictChecker();
    void renderEfficiency();
    void renderTestModule();
    void renderSystemInfo();
    void renderExitConfirm();

    // Actions
    void handleAction(string action);
    void setStatus(string msg, bool isError = false);
    void clearOutput();
    void addOutput(string line);
};

#endif