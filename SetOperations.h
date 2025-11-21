#pragma once
#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class SetOperations {
private:
    vector<string> elements;

public:
    void add(string element);
    bool contains(string element) const;
    int size() const;
    string getElement(int index) const;

    SetOperations unionWith(const SetOperations& other) const;
    SetOperations intersectionWith(const SetOperations& other) const;
    SetOperations differenceWith(const SetOperations& other) const;
    bool isSubsetOf(const SetOperations& other) const;
    bool equals(const SetOperations& other) const;

    void display(string setName) const;

    static void demonstrateSetOperations();
};

#endif