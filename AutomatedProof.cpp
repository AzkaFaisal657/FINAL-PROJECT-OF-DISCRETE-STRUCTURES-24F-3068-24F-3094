#include "AutomatedProof.h"

AutomatedProof::AutomatedProof() : stepCount(0) {}

void AutomatedProof::addStep(string statement, string justification) {
    if (stepCount < 50) {
        steps[stepCount].stepNumber = stepCount + 1;
        steps[stepCount].statement = statement;
        steps[stepCount].justification = justification;
        stepCount++;
    }
}

void AutomatedProof::displayProof(string theoremName) {
    cout << "\n=== FORMAL PROOF: " << theoremName << " ===" << endl;
    for (int i = 0; i < stepCount; i++) {
        cout << "Step " << steps[i].stepNumber << ": " << steps[i].statement << endl;
        cout << "        Justification: " << steps[i].justification << endl;
    }
    cout << "QED (Proof Complete)" << endl;
}

void AutomatedProof::clearProof() {
    stepCount = 0;
}

void AutomatedProof::demonstrateAutomatedProof() {
    cout << "\n=== MODULE 8: AUTOMATED PROOF SYSTEM ===" << endl;

    cout << "\n1. PREREQUISITE CHAIN PROOF:" << endl;
    AutomatedProof proof1;
    proof1.addStep("Student completed CS1002", "Given (premise)");
    proof1.addStep("CS1004 requires CS1002", "Prerequisite rule");
    proof1.addStep("Student completed CS1004", "Modus Ponens");
    proof1.addStep("CS2001 requires CS1004", "Prerequisite rule");
    proof1.addStep("Student can enroll in CS2001", "Modus Ponens");
    proof1.displayProof("Course Enrollment Eligibility");

    cout << "\n2. SET MEMBERSHIP PROOF:" << endl;
    AutomatedProof proof2;
    proof2.addStep("Let S = {students enrolled in CS101}", "Definition");
    proof2.addStep("Ali enrolled in CS101", "Given fact");
    proof2.addStep("Therefore, Ali ? S", "Definition of set membership");
    proof2.addStep("CS101 requires CS1002", "Prerequisite rule");
    proof2.addStep("Ali ? S ? Ali completed CS1002", "Logical implication");
    proof2.addStep("Therefore, Ali completed CS1002", "Modus Ponens");
    proof2.displayProof("Set Membership and Prerequisites");

    cout << "\n3. FUNCTION PROPERTIES PROOF:" << endl;
    AutomatedProof proof3;
    proof3.addStep("Define f: StudentID ? Student", "Function definition");
    proof3.addStep("Each StudentID maps to exactly one Student", "University policy");
    proof3.addStep("No two StudentIDs map to same Student", "Uniqueness constraint");
    proof3.addStep("Therefore, f is injective", "Definition of injection");
    proof3.addStep("Every Student has a StudentID", "Registration requirement");
    proof3.addStep("Therefore, f is surjective", "Definition of surjection");
    proof3.addStep("f is both injective and surjective", "Steps 4 and 6");
    proof3.addStep("Therefore, f is bijective", "Definition of bijection");
    proof3.displayProof("StudentID Function Bijectivity");
}

void AutomatedProof::proveByInduction(string theorem) {
    cout << "\n=== PROOF BY INDUCTION: " << theorem << " ===" << endl;
    cout << "Base Case: Verify for n=1" << endl;
    cout << "Inductive Step: Assume true for n=k, prove for n=k+1" << endl;
    cout << "Conclusion: Theorem holds for all natural numbers n" << endl;
}

void AutomatedProof::proveByContradiction(string assumption, string contradiction) {
    cout << "\n=== PROOF BY CONTRADICTION ===" << endl;
    cout << "Assume: " << assumption << endl;
    cout << "This leads to: " << contradiction << endl;
    cout << "Contradiction! Therefore, assumption is false" << endl;
    cout << "QED" << endl;
}