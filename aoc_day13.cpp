//https://adventofcode.com/2022/day/13
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
using namespace std;

int getNum(const string& s, size_t& pos) {
    //Only deal with 2 digit numbers, with a look ahead for the second digit
    bool two_digit = isdigit(s.at(pos)+1);
    int i = stoi(s.substr(pos, (two_digit?2:1)));
    if (two_digit) ++pos; //adjust the pos if we found a double digit
    return i;
}

//expensive, inplace conversion, so we can continue string scan seemlessly
void covertIntToList(string& s, int pos) {
    int offset = (isdigit(s.at(pos+1)) ? 3 : 2);
    s.insert(pos,"[");  
    s.insert(pos+offset,"]");
    //cout << " converted " << s << ",";
}

bool comp(const string& l, const string& r) {
    auto lft = l;
    auto rgt = r;
    size_t l_pos = 0, r_pos = 0;
    for(; l_pos<lft.size() && r_pos<rgt.size(); ++l_pos, ++r_pos) {
        char lft_char = lft.at(l_pos);
        char rgt_char = rgt.at(r_pos);
        if(lft_char != rgt_char) {
            //one list , ont integer
            if (isdigit(lft_char) && rgt_char == '[') {
                covertIntToList(lft, l_pos);
            }
            //one list , ont integer
            else if (isdigit(rgt_char) && lft_char == '[') {
                covertIntToList(rgt, r_pos);
            }
            else if (rgt_char == ']') { //RIGHT List runs out = OUT OF ORDER
                return false;
            }
            else if (lft_char == ']') { //LEFT List runs out = IN ORDER
                return true;
            }
            else if(isdigit(lft_char) && isdigit(rgt_char)) { //number compare
                
                int li = getNum(lft, l_pos);
                int ri = getNum(rgt, r_pos);
                if (li != ri) { 
                    return li<ri;
                }
            }
        }
    }
    return true;
}

int process(ifstream&& f) { 
    string lft,rgt,blank;
    int index = 0;
    int total = 0;
    while(getline(f,lft) && getline(f,rgt)) {
        getline(f, blank);
        index++;
        if (comp(lft,rgt))
            total += index;
    }
    return total; 
}

int process2(ifstream&& f) { 
    string lft,rgt,blank;
    vector<string> packets;
    while(getline(f,lft) && getline(f,rgt)) {
        getline(f, blank);
        packets.emplace_back(lft);
        packets.emplace_back(rgt);
    }
    packets.push_back("[[2]]");
    packets.push_back("[[6]]");
    sort(packets.begin(), packets.end(), &comp);
    int total = 0;
    for(size_t i = 0; i<packets.size(); ++i) {
        //cout << packets[i]  << endl;
        if (packets[i] == "[[2]]")
            total = i+1;        
        else if (packets[i] == "[[6]]")
            total *= i+1;        
    }
    return total; 
}

int main() {
    cout << "part 1 example: " << process(ifstream("AOC13_example.txt")) << endl;
    cout << "part 1: " << process(ifstream("AOC13.txt")) << endl;
    cout << "part 2 example: " << process2(ifstream("AOC13_example.txt")) << endl;
    cout << "part 2: " << process2(ifstream("AOC13.txt")) << endl;
    return 0;
}