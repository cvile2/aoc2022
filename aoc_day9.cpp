//https://adventofcode.com/2022/day/9
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <array>
using namespace std;
const map<char,int> x = { {'U', 0 }, { 'D', 0 }, { 'L', -1}, { 'R', 1 } };
const map<char,int> y = { {'U', -1 }, { 'D', 1}, { 'L', 0 }, { 'R', 0 } };
template<size_t N>
void process(ifstream&& f) {
    string s;
    set<pair<int,int>> visited;
    array<pair<int,int>,N> snake; //x,y
    
    while(getline(f,s)) {
        char dir = s[0]; //e.g. R 4
        for(auto mv = stoi(s.substr(2)); mv>0; --mv) {
            snake[0].first += x.at(dir);
            snake[0].second += y.at(dir);  
            for(size_t t = 1; t < snake.size(); ++t) {
                const auto& hd = snake[t-1];
                auto& tl = snake[t];        
                int xdf = tl.first - hd.first;
                int ydf = tl.second -hd.second;
                //cout << "..HEAD MOVE:" << hd.first << "," << hd.second  << " diff " << xdf << ", " << ydf << endl;
                if (abs(xdf)>1) {
                    tl.first+=(xdf<0?1:-1);
                    tl.second=hd.second;
                }
                else if (abs(ydf)>1) {
                    tl.second+=(ydf<0?1:-1);
                    tl.first=hd.first;
                }
            }
            visited.insert(snake[snake.size()-1]);
        }
    }
    std::cout << visited.size() << endl;
}
int main() {
    process<2>(std::ifstream{"AOC9_example.txt"}); //correct
    process<2>(std::ifstream{"AOC9.txt"}); //correct

    process<10>(std::ifstream{"AOC9_example.txt"}); //correct
    process<10>(std::ifstream{"AOC9p2_example.txt"}); //correct
    process<10>(std::ifstream{"AOC9.txt"}); //incorrect answer! 
}