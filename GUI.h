#pragma once
#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "UniversitySystem.h"
#include <vector>
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

    // Window dimensions
    const int WIN_W = 1600;
    const int WIN_H = 950;

    enum State {
        MAIN_MENU, COURSE_MENU, STUDENT_MENU, DISCRETE_MENU,
        VIEW_COURSES, SEARCH_COURSE, VIEW_STUDENTS, STUDENT_DETAIL,
        ENROLLMENT_CHECK, ENROLL_STUDENT,
        SET_OPERATIONS, RELATIONS_MODULE, FUNCTIONS_MODULE, COMBINATIONS_MODULE,
        LOGIC_ENGINE, INDUCTION_MODULE, PROOFS_MODULE, SCHEDULING_MODULE,
        CONFLICT_CHECKER, EFFICIENCY_MODULE, TEST_MODULE,
        SYSTEM_INFO, EXIT_CONFIRM
    };

    State currentState = MAIN_MENU;
    int selectedSemester = 1;
    int selectedStudentIdx = -1;
    int scrollOffset = 0;

    string statusMsg;
    sf::Color statusColor;
    float statusTimer = 0;

    InputBox inputSearchCode, inputEnrollStudent, inputEnrollCourse;
    InputBox* activeInput = nullptr;

    // Professional Color Palette
    sf::Color bgColor{ 240, 248, 255 };         // Alice Blue background
    sf::Color headerColor{ 15, 35, 75 };        // Deep Navy header
    sf::Color cardColor{ 255, 255, 255 };       // White cards
    sf::Color primaryBtn{ 25, 85, 165 };        // Royal Blue buttons
    sf::Color primaryHover{ 35, 115, 205 };     // Lighter blue hover
    sf::Color secondaryBtn{ 70, 85, 105 };      // Slate gray
    sf::Color secondaryHover{ 95, 115, 140 };   // Lighter slate
    sf::Color accentColor{ 0, 150, 136 };       // Teal accent
    sf::Color textDark{ 25, 35, 55 };           // Dark text
    sf::Color textLight{ 255, 255, 255 };       // Light text
    sf::Color textMuted{ 100, 115, 135 };       // Muted text
    sf::Color successColor{ 40, 180, 100 };     // Green
    sf::Color errorColor{ 220, 60, 60 };        // Red
    sf::Color borderColor{ 200, 215, 230 };     // Light border

    vector<Button> buttons;
    vector<string> outputLines;

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

    void clearButtons();
    Button& addBtn(string text, float x, float y, float w, float h, string action, bool primary = true);
    void setupInput(InputBox& inp, float x, float y, float w, string placeholder, int maxLen = 20);
    void updateHover(sf::Vector2f pos);
    string clickButton(sf::Vector2f pos);
    void clickInput(sf::Vector2f pos);
    void typeChar(char c);
    void backspace();

    void drawText(string s, float x, float y, int sz, sf::Color c, bool bold = false);
    void drawTextCentered(string s, float x, float y, float w, int sz, sf::Color c, bool bold = false);
    void drawRect(float x, float y, float w, float h, sf::Color fill, sf::Color outline = sf::Color::Transparent, float thick = 0, float radius = 0);
    void drawCard(float x, float y, float w, float h, string title = "");
    void drawHeader();
    void drawInput(InputBox& inp);
    void drawStatusBar();

    void renderMainMenu();
    void renderCourseMenu();
    void renderStudentMenu();
    void renderDiscreteMenu();
    void renderViewCourses();
    void renderSearchCourse();
    void renderViewStudents();
    void renderStudentDetail();
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

    void handleAction(string action);
    void setStatus(string msg, bool isError = false);
    void clearOutput();
    void addOutput(string line);
};

#endif