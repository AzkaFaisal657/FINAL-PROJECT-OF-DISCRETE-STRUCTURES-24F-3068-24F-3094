#pragma once
#include <string>
#include <iostream>
using namespace std;

class TestModule {
public:
    static void runAllTests();
    static bool testPrerequisiteChain();
    static bool testSetOperations();
    static bool testCombinations();
    static bool testLogicInference();
    static bool testRelations();
    static bool testFunctions();
    static void benchmarkPerformance();
    static void validateSystemConstraints();
};
