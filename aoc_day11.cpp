//https://adventofcode.com/2022/day/11
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cassert>
#include <iterator> // for ostream_iterator
using namespace std;

template<typename T>
T delim_to_vector(const string& s) {
    T v;
    for(size_t i = 1; i < s.size(); i+=4) 
        v.emplace_back(stoi(s.substr(i,2)));
    return v;
}

using tNum = unsigned long long; //wow ok
struct Monkey {
    deque<tNum> items;  
    char id;
    char op;
    tNum op_v;
    tNum div; 
    int ttrue; 
    int tfalse;
    void print() const {
        cout << "Monkey " << id << ": ";
        copy(items.begin(), items.end(), ostream_iterator<int>(cout, " "));
        cout << " ("  << " op=" << op << " opv=" << op_v <<
            " div=" << div << " true=" << ttrue << " false=" << tfalse << ")"<< endl;
    }
};

void process(ifstream&& f, const int rounds, const tNum not_interested) {
    string ignorestr, monkeystr, itemstr, opstr, teststr, truestr, falsestr;
    
    vector<Monkey> monkeys;
    while(getline(f,monkeystr)) {
        getline(f, itemstr);
        getline(f, opstr);
        getline(f, teststr);
        getline(f, truestr);
        getline(f, falsestr);
        getline(f, ignorestr); //blank line
    
        Monkey mk;
        mk.id = monkeystr[7];
        mk.items = std::move(delim_to_vector<deque<tNum>>(itemstr.substr(17)));
        bool old = opstr.substr(25) == "old";
        mk.op = (old ? 'o' : opstr[23]); //* or +
        mk.op_v = (old ? 0 : stoi(opstr.substr(25))); //old or number
        mk.div = stoi(teststr.substr(21));
        mk.ttrue = stoi(truestr.substr(29));
        mk.tfalse = stoi(falsestr.substr(30));
        //mk.print();
        monkeys.emplace_back(std::move(mk));
    }
    vector<tNum> inspected(monkeys.size());
    for (int round = 1; round <= rounds; ++round) {
        for(size_t id = 0; id < monkeys.size(); ++id) {
            auto& mk = monkeys.at(id);
            
            while(!mk.items.empty()) {
                tNum wry = mk.items.front();
                wry = ((mk.op == 'o') ? wry * wry :   //old
                    (mk.op == '*' ? wry * mk.op_v : wry + mk.op_v))  //* or +
                    / not_interested; //now not interested
                monkeys[(((wry % mk.div) == 0)? mk.ttrue : mk.tfalse)].items.emplace_back(wry);          
                inspected[id]++;
                mk.items.pop_front();
            }
        }
        if (round % 1000 == 0) {
        cout << "Round " << round << endl;
        for(const auto& mk : monkeys)
            mk.print();
        }
    }
    sort(inspected.begin(), inspected.end(), greater<tNum>());
    /*cout <<"inspected: ";
    for(const auto& i : inspected)
       cout << i << ",";
    cout << endl;*/
    cout << inspected[0] * inspected[1] << endl;
}

int main() {
    process(std::ifstream{"AOC11_example.txt"},20, 3); //passed
    process(std::ifstream{"AOC11.txt"}, 20, 3); //passed
    process(std::ifstream{"AOC11_example.txt"},10000, 1); //not working overflow
    process(std::ifstream{"AOC11.txt"}, 10000, 1); //not working overflow
}