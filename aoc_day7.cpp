//https://adventofcode.com/2022/day/7
#include <fstream>
#include <iostream>
#include <list>
using namespace std;

struct dir {
    dir(const string& n) : name(n) {};
    string name;
    int size = 0;
    list<dir> sub_dirs;
};
//Parse our file into a tree
int parse(ifstream& f, dir& node) {
    string l;
    while(std::getline(f,l)) {
        if(l[0] == '$' && l[2] == 'c') {
            auto name = l.substr(5);
            if(name == "..")
                break; //exit recursion
            
            node.sub_dirs.push_back(dir{name});
            node.size+=parse(f, node.sub_dirs.back());
        }
        else if (l[0] == '$'|| l[0] == 'd') //ignore other commands and "dir"
        { /*skip*/ }
        else //now assume a filesize!
            node.size+=stoi(l.substr(0, l.find_first_of(" ")));
    }
    return node.size;
}

void find_size_le(const dir& node, const int target, int& total)
{
    for( const auto& n : node.sub_dirs )
        find_size_le(n, target, total);
    if (node.size <= target)
        total+=node.size;
}

int find_smallest_gt(const dir& node, const int target, int bestfit)
{
    if(node.size < target)
        return bestfit;
    for( const auto& n : node.sub_dirs )
        bestfit = min(find_smallest_gt(n, target, bestfit), bestfit);
    return min(bestfit, node.size);
}

int main() {
    ifstream f{"AOC7.txt"}; 
    string l;
    std::getline(f,l); //skip cd / 
    dir root{"/"};
    const auto total_size = parse(f, root);
    //Part1
    int lt_total{0};
    find_size_le(root, 100000, lt_total);
    //Part2
    auto target = /*target*/ 30000000 - /*free space*/ (70000000 - total_size);
    auto closest = find_smallest_gt(root, target, 70000000);
    cout << lt_total << "," << closest << endl;
}