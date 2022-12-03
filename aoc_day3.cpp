//https://adventofcode.com/2022/day/3
#include <fstream>
#include <iostream>
#include <array>
#include <bitset>
#include <numeric> 
#include <cstring> 
using namespace std;

constexpr int calc_priorty(const char x) { return (x<='Z' ? x - 'A' + 26 : x - 'a'); /*/Upper or lowercase*/ };

int part1(ifstream&& f) {
    string s;
    long total = 0; 
    array<std::bitset<2>, 52> found;
    while(getline(f,s)) { 
        for(auto pos = 0; pos < s.size()/2; ++pos) //O(n) scan two halfs of rucksack
        {
            found[calc_priorty(s[pos])][0] = true;        
            found[calc_priorty(s[pos+s.size()/2])][1] = true;
        }
        for(auto pos = 0; pos < 52; ++pos) 
        {
            if (found[pos].count() == 2)
                total += pos+1;
            found[pos].reset(); //avoid needing to create new memory for each line
        }
    }
    return total;
}

int part2(ifstream&& f) {
    string s;
    long total = 0; 
    array<std::bitset<3>, 52> found;
    int i = 0;
    while(getline(f,s)) 
    {
        for(auto c : s)
            found[calc_priorty(c)][i] = true;
        ++i;

        if (i == 3) //process every 3 "rucksacks"
        {
            for(auto pos = 0; pos < 52; ++pos) 
            {
                if (found[pos].count() == 3)
                    total += pos+1;
                found[pos].reset();
            }
            i = 0;
        }
    }
    return total;
}

int main() {
    cout << part1(ifstream{"AOC3.txt"}) << endl;
    cout << part2(ifstream{"AOC3.txt"}) << endl;
}