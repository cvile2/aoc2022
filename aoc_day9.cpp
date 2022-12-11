//https://adventofcode.com/2022/day/9
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

const map<char,int> x = { {'U', 0 }, { 'D', 0 }, { 'L', -1}, { 'R', 1 } };
const map<char,int> y = { {'U', -1 }, { 'D', 1}, { 'L', 0 }, { 'R', 0 } };
void process(ifstream& f) {
    std::string s;
    set<pair<int,int>> visited = {{0,0}};
    pair<int,int> head, tail = {0,0}; //x,y
    
    while(std::getline(f,s)) {
        char dir = s[0]; //e.g. R 4
        for(int mv = stoi(s.substr(2)); mv>0; --mv) {
            head.first += x.at(dir);
            head.second += y.at(dir);          
            int xdiff = tail.first - head.first;
            int ydiff = tail.second -head.second;

            //cout << "..HEAD MOVE:" << head.first << "," << head.second  << " diff " << xdiff << ", " << ydiff << endl;
            if (abs(xdiff)>1) {
                tail.first+=(xdiff<0?1:-1);
                 tail.second=head.second;
            }
            else if (abs(ydiff)>1) {
                tail.second+=(ydiff<0?1:-1);
                tail.first=head.first;
            }
            visited.insert(tail);
        }
    }
    std::cout << visited.size() << endl;;
}
int main() {
    
    std::ifstream f1{"AOC9_example.txt"}; 
    process(f1);
    std::ifstream f2{"AOC9.txt"}; 
    process(f2);
}