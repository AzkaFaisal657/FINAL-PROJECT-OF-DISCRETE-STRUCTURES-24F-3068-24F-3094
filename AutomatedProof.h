#pragma once
#include <string>
#include <iostream>
using namespace std;

struct ProofStep {
    int stepNumber;
    string statement;
    string justification;
};

class AutomatedProof {
private:
    ProofStep steps[50];
    int stepCount;

public:
    AutomatedProof();
    void addStep(string statement, string justification);
    void displayProof(string theoremName);
    void clearProof();

    static void demonstrateAutomatedProof();
    static void proveByInduction(string theorem);
    static void proveByContradiction(string assumption, string contradiction);
};