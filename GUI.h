#pragma once
#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "UniversitySystem.h"
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class GUI {
private:
    sf::RenderWindow* window;
    UniversitySystem* system;
    sf::Font font;

    enum State {
        MAIN_MENU,
        VIEW_COURSES,
        VIEW_STUDENTS,
        ENROLLMENT,
        DISCRETE_DEMOS,
        CONFLICT_REPORT,
        EXIT_CONFIRM
    };

    State currentState;
    int selectedOption;
    int selectedSemester;
    string selectedStudentId;
    string message;

    // Colors
    sf::Color backgroundColor;
    sf::Color titleColor;
    sf::Color textColor;
    sf::Color buttonColor;
    sf::Color selectedColor;
    sf::Color messageColor;

public:
    GUI(UniversitySystem* sys);
    ~GUI();

    void run();
    void initWindow();
    bool loadFont();

private:
    void handleEvents();
    void update();
    void render();

    // Drawing functions
    void drawMainMenu();
    void drawCoursesView();
    void drawStudentsView();
    void drawEnrollmentScreen();
    void drawDiscreteDemos();
    void drawConflictReport();
    void drawExitConfirm();

    void drawText(string text, float x, float y, int size, sf::Color color);
    void drawButton(string text, float x, float y, float width, float height, bool selected);
    void drawBox(float x, float y, float width, float height, sf::Color fillColor, sf::Color outlineColor);

    // Input handling
    void handleMainMenuInput(sf::Event& event);
    void handleCoursesViewInput(sf::Event& event);
    void handleStudentsViewInput(sf::Event& event);
    void handleEnrollmentInput(sf::Event& event);
    void handleDiscreteDemosInput(sf::Event& event);

    // Helper functions
    vector<string> wrapText(string text, int lineLength);
};

#endif
