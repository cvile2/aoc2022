//https://adventofcode.com/2022/day/6
#include <fstream>
#include <iostream>
#include <regex>
#include <array>
#include <unordered_map>
using namespace std;

int scan_message(int range_limt)
{
    ifstream f{"AOC6.txt"}; 
    string l;
    std::getline(f,l);
    array<int,27> freq = {0};
    for(auto i = 0; i<range_limt; ++i) //init freq for the first window
        freq[l[i]-'a']++;
    
    int s = 0; int e = range_limt - 1; //sliding window
    
    while (e < l.size())
    {
        if (std::all_of(freq.begin(), freq.end(), [](auto c){return c<=1;}))
            return e+1; //found!

        freq[l[s]-'a']--;
        s++; 
        e++;
        freq[l[e]-'a']++;
    }
    return -1; //not found
}

int main() {
    cout << scan_message(4) << " " << scan_message(14) << endl;
    return 0;
}