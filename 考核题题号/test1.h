#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
struct WordInfo {
    string word;
    int length;
};
bool compareByLength(const WordInfo& a, const WordInfo& b);
