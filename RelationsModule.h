#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Pair {
    string first;
    string second;
};

class RelationsModule {
private:
    vector<Pair> pairs;

public:
    void addPair(string first, string second);
    bool hasPair(string first, string second) const;

    bool isReflexive(vector<string> domain) const;
    bool isSymmetric() const;
    bool isTransitive() const;
    bool isEquivalence(vector<string> domain) const;
    bool isPartialOrder(vector<string> domain) const;

    void display(string relationName) const;

    static void demonstrateRelations();
};