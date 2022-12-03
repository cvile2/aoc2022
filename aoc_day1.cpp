//https://adventofcode.com/2022/day/1
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

int main() {
    std::ifstream f{"AOC1.txt"}; 
    std::string s;
    long seen = 0; //part1
    priority_queue<long> cals; //part2
    while(std::getline(f,s)) {
        if (s.empty())
        {
            cals.push(seen); //store total for elf in priorty ordered queue
            seen = 0; //reset for next elf
        }
        else
            seen += atol(s.c_str());
    }
    long total, max = cals.top();
    cals.pop();
    total += cals.top();
    cals.pop();
    total += cals.top();

    std::cout << max << "," << total << endl;
    return total;
}