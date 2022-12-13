//https://adventofcode.com/2022/day/10
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
void process(ifstream&& f) {
    string s;    
    int total = 1;
    vector<long> cycles;
    while(getline(f,s)) {
        char cmd = s[0];
        if (cmd == 'n') { //noop
            cycles.push_back(total);
        }
        else { //addx 
            int v = stoi(s.substr(5)); //addx -10
            cycles.push_back(total); //first cycle 
            cycles.push_back(total);
            total += v; //only updates NEXT cycle
        }
    }
    int signal = 0;
    for(size_t x = 20; x<cycles.size(); x+=40)
       signal += (cycles[x-1] * x);

    stringstream ss;
    for(size_t x = 0, px = 1; x<cycles.size(); ++x, ++px) {
        size_t sprite_pos = cycles.at(x);    
        ss << ((px == sprite_pos || px == sprite_pos+1 || px == sprite_pos+2) ? "#" : ".");
   
        if ((px) % 40 == 0) { //each CRT row offset
            px -= 40; 
            ss << endl;    
        }
    }
    cout << signal << endl << ss.str() << endl;
}
int main() {
    process(std::ifstream{"AOC10_example.txt"});
    process(std::ifstream{"AOC10.txt"});
}