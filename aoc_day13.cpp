//https://adventofcode.com/2022/day/13
#include <fstream>
#include <iostream>
using namespace std;

int getNum(const string& s, size_t& pos) {
    //Only deal with 2 digit numbers, with a look ahead for the second digit
    bool two_digit = isdigit(s[pos]+1);
    int i = stoi(s.substr(pos, (two_digit?2:1)));
    if (two_digit) ++pos; //adjust the pos if we found a double digit
    return i;
}

//expensive, inplace conversion, so we can continue string scan seemlessly
void covertIntToList(string& s, int pos) {
    int offset = (isdigit(s.at(pos+1)) ? 3 : 2);
    s.insert(pos,"[");  
    s.insert(pos+offset,"]");
    cout << " converted " << s << ",";
}

int process(ifstream&& f) { 
    string lft,rgt,blank;
    int index = 0;
    int total = 0;
    while(getline(f,lft) && getline(f,rgt)) {
        index++;
        getline(f, blank);
        bool ooo = false;
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
                    ooo = true;
                    break;
                }
                else if (lft_char == ']') { //LEFT List runs out = IN ORDER
                    break;
                }
                else if(isdigit(lft_char) && isdigit(rgt_char)) { //number compare
                    
                    int li = getNum(lft, l_pos);
                    int ri = getNum(rgt, r_pos);
                    if (li != ri) { 
                        ooo = li>ri;
                        break;  //if different we must exit 
                    }
                }
            }
        }
        cout << "\n---" << lft << endl;
        cout << "---" << rgt << endl;
        cout << "---" << string(l_pos, '*') << "^" << endl;
        cout << "---" << string(r_pos, '*') << "^" << endl;
        cout << "Result: " << (ooo ? "OO" : "IO")  << endl;
        if (!ooo)
            total += index;
    }
 
    return total; 
}

int main() {
    cout << process(ifstream("AOC13_example.txt")) << endl;
    cout << process(ifstream("AOC13.txt")) << endl;
    return 0;
}