#include <fstream>
#include <iostream>
#include <map>
const std::map<char, long> shape = { {'A',1}, {'B',2}, {'C',3} }; //score per shape
std::map<std::pair<char,char>, long> wins = {  {{'A', 'B'}, 6},  {{'B', 'C'}, 6},  {{'C', 'A'}, 6}}; 
const std::map<char,std::pair<char,char>> choiceWL = { {'A', {'B','C'}},  {'B', {'C','A'}},  {'C', {'A','B'}} }; 
int main() {
    std::ifstream f{"AOC2.txt"};
    std::string s;
    long score1, score2 = 0;
    while(std::getline(f,s)) {
        char c2 = (s[2] - ('X'-'A')); //convert X to A etc
        score1 += shape.at(c2) +  (/* draw ? */ c2 == s[0] ? 3 : wins[{s[0],c2}]);
        score2 += (c2 == 'A' ? shape.at(choiceWL.at(s[0]).first) : ( c2=='B' ? shape.at(s[0]) + 3 : shape.at(choiceWL.at(s[0]).second) + 6));
    }
    std::cout << score1 << "," << score2;
}