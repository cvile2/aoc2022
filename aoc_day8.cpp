//https://adventofcode.com/2022/day/8
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
using namespace std;

struct Trees
{
    vector<string> grid;
    int max_x, max_y;

    Trees(istream& f)
    {
        string l;
        while (std::getline(f,l)) 
            grid.push_back(l);
        max_x = grid[0].size();
        max_y = grid.size();
    }
    
    bool visibile(int y, int x, int move_x, int move_y) const {
        auto h = grid[y][x];
        y +=move_y;
        x +=move_x;
        for( ;y < max_y && x < max_x && y >= 0 && x >= 0; y += move_y, x += move_x ) {
            if (h <= grid[y][x]) 
                return false;
        }        
        return true;
    }

    int scenic(int y, int x, int move_x, int move_y) const {
        auto h = grid[y][x];
        y +=move_y;
        x +=move_x;
        int count = 0;
        for( ;y < max_y && x < max_x && y >= 0 && x >= 0;  y += move_y, x += move_x ) {
            count++;
            if (grid[y][x] >= h) 
                break;
        }        
        return count;
    }
};

int main() {
    ifstream f{"AOC8.txt"}; 
    Trees t(f);   
    int count = (t.max_x + t.max_y) * 2  - 4; //part 1
    int scenic = 0; //part 2
    for(int y = 1; y < t.max_y-1; ++y ) {
        for(int x = 1; x < t.max_x-1; ++x ) { 
            if (t.visibile(y, x, -1, 0) || t.visibile(y, x, 0,-1 )  || 
                 t.visibile(y, x, 1, 0) || t.visibile(y, x, 0, 1))
                count++;
            scenic = max(scenic, (t.scenic(y, x, -1, 0) * t.scenic(y, x, 0,-1 )  *
                 t.scenic(y, x, 1, 0) * t.scenic(y, x, 0, 1)));
        }
    }
    cout << count << " " << scenic << endl;
    return 0;
}