#include <fstream>
#include <iostream>
#include <array>
static constexpr std::array<long, 3> score {{ 1, 2, 3}}; //score per shape
static constexpr std::array<std::pair<long,long>, 3> choiceWL {{ {1,2},  {2,0}, {0,1} }}; 
int main() {
    std::ifstream f{"AOC2.txt"};
    std::string s;
    long score1, score2 = 0;
    while(std::getline(f,s)) { //each line is is e.g. "A Z"
        long c1 = s[0] - ('A'); //convert A to 0 etc
        long c2 = s[2] - ('X'); //convert X to 0 etc
        score1 += score.at(c2) + (c2 == c1 ? /*draw*/ 3 : (choiceWL.at(c1).first == c2  ? /*win*/ 6 : 0 /*loose*/));
        score2 += (c2 == 0 /*WantWin*/ ? score.at(choiceWL.at(c1).first) : ( c2==1 /*WantDraw*/? score.at(c1) + 3 : /*WantLoose*/score.at(choiceWL.at(c1).second) + 6));
    }
    std::cout << score1 << "," << score2;
}