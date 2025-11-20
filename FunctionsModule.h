#pragma once
#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Mapping {
    string domain;
    string codomain;
};

class FunctionsModule {
private:
    vector<Mapping> mappings;

public:
    void addMapping(string from, string to);
    void clearMappings();
    int getMappingCount() const { return mappings.size(); }
    Mapping getMapping(int index) const;

    bool isInjective();
    bool isSurjective(vector<string> codomain);
    bool isBijective(vector<string> codomain);

    void display(string functionName) const;

    static void demonstrateFunctions();
    static void demonstrateComposition();
};
