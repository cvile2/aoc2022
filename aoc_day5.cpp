//https://adventofcode.com/2022/day/5
#include <fstream>
#include <iostream>
#include <regex>
#include <deque>
#include <array>
#include <cassert>
#include <algorithm>
using namespace std;

void aoc5(ifstream& f) {
    bool done = false;
    string line;
    std::getline(f,line); //get first line for inspection
    vector<deque<char>> stacks((line.size()/4) + 1); //get buckets from formatted size

    do { //Parse stack status - purposely skip the last blank line
        size_t col = 1; //track character we're processing
        while(col < line.size() && !done)
        {
            if (line[col] == '1') //matches the key row
                done = true;
            else if (line[col] != ' ')
                stacks[(col-1)/4].push_front(line[col]);
            col += 4;
        }
    } while (std::getline(f,line) && !done);
    auto stacks9001 = stacks; //copy for part 2

    static const std::regex re("move ([0-9]+) from ([0-9]+) to ([0-9]+)");  
    std::smatch mt; 
    while(std::getline(f,line)) { //now continue to read "move x from y to z" statements
        std::regex_match(line, mt, re);
        auto crate_count = stol(mt[1]);
        auto from = stol(mt[2])-1; //minus index offset
        auto to = stol(mt[3])-1;
        //I want this to be ranges::move and move_backwards - but can't get it to work yet..
        ranges::reverse_copy(stacks[from].end()-crate_count, stacks[from].end(), back_inserter(stacks[to])); 
        ranges::copy(stacks9001[from].end()-crate_count, stacks9001[from].end(), back_inserter(stacks9001[to])); 
        
        for(auto p = crate_count; p>0; p--)
        {
            stacks[from].pop_back();
            stacks9001[from].pop_back();
        }
    }
    std::for_each(stacks.begin(), stacks.end(), [](const auto & x ) { std::cout << (x.empty() ? '?' : x.back()); });
    cout << endl;
    std::for_each(stacks9001.begin(), stacks9001.end(), [](const auto & x ) { std::cout << (x.empty() ? '?' : x.back()); });
}

int main() {
    ifstream f{"AOC5.txt"}; 
    assert(f.is_open());
    aoc5(f);
}