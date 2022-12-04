//https://adventofcode.com/2022/day/4
#include <fstream>
#include <iostream>
#include <regex>
#include <array>
using namespace std;
static const std::regex re("([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)");
int main() {
    ifstream f{"AOC4.txt"}; 
    string l;
    int count1, count2 = 0;
    while(std::getline(f,l)) {
        std::smatch mt;
        std::regex_match(l, mt, re);
        array<long, 4> m = { stol(mt[1]), stol(mt[2]), stol(mt[3]), stol(mt[4]) };
        
        if( (m[0] >= m[2] && m[1] <= m[3]) || (m[2] >= m[0] && m[3] <= m[1]))
            ++count1; //part one, fully overlaps?
        if( (m[0] >= m[2] && m[0] <= m[3]) ||   
            (m[1] >= m[2] && m[1] <= m[3]) || 
            (m[2] >= m[0] && m[2] <= m[1]) ||
            (m[3] >= m[0] && m[3] <= m[1]))
            ++count2; //part 2, partial overlap?
    }
    cout << count1 << "," << count2 << endl;
}