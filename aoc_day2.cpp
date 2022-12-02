#include <fstream>
#include <iostream>
#include <map>
#include <array>
static constexpr std::array<long, 3> score {{ 1,2, 3}}; //score per shape
static constexpr std::array<std::pair<char,char>, 3> choiceWL {{ {'B','C'},  {'C','A'}, {'A','B'} }}; 
int main() {
    std::ifstream f{"AOC2.txt"};
    std::string s;
    long score1, score2 = 0;
    while(std::getline(f,s)) { //each line is is e.g. "A Z"
        int c2 = s[2] - ('X'); //convert X to 0 etc
        score1 += score.at(c2-'A') + (c2 == s[0] ? /*draw*/ 3 : (choiceWL.at(s[0] - 'A').first == c2  ? /*win*/ 6 : 0 /*loose*/));
        score2 += (c2 == 'A' ? score.at(choiceWL.at(s[0] - 'A').first-'A') : ( c2=='B' ? score.at(s[0]-'A') + 3 : score.at(choiceWL.at(s[0] - 'A').second-'A') + 6));
    }
    std::cout << score1 << "," << score2;
}