//https://adventofcode.com/2022/day/4
#include <fstream>
#include <iostream>
#include <regex>
#include <array>
using namespace std;

int scan_message(int range_limt)
{
    ifstream f{"AOC6.txt"}; 
    string l;
    std::getline(f,l);
    map<char, int> freq;
    for(auto i = 0; i<range_limt; ++i) //init freq for the first window
        freq[l[i]]++;
    
    int s = 0; int e = range_limt - 1; //sliding window
    
    while (e < l.size())
    {
        if (std::all_of(freq.begin(), freq.end(), [](auto& p){return p.second<=1;}))
            return e+1;

        freq[l[s]]--;
        s++; 
        e++;
        freq[l[e]]++;
    }
    return -1; 
}

int main() {
    cout << scan_message(4) << " " << scan_message(14) << endl;
    return 0;
}