//https://adventofcode.com/2022/day/14
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

using tPos = pair<size_t,size_t>;

class Mine {
    static int getNum(const string& line, size_t& pos) {
        auto l = line.find_first_of("0123456789", pos);
        auto r = line.find_first_not_of("0123456789", l);
        pos = max(l,r);
        return stoi(line.substr(l, r));
    }

    size_t minx = 500, 
        miny = 0, 
        maxx= 500, 
        maxy= 0;

    void linefill(auto& grid, tPos from, const tPos& to) {
        int xdf = to.first - from.first;
        int ydf = to.second - from.second;         
        bool exit = false;
        while ( !exit ) {
            if ( from == to )
                exit = true;
            grid.at(from.second-miny).at(from.first-minx) = '#';
            from.first += (xdf == 0 ? 0 : xdf > 0 ? 1 : -1);
            from.second += (ydf == 0 ? 0 : ydf > 0 ? 1 : -1);
        };
        //print_grid(grid);
    }

    void print_grid(const auto& grid) const {
        cout << "Grid:\n";
        for( size_t i = 0; i < grid.size(); ++i )
            cout << i << ":" << grid[i] << endl;
    }

    bool can_fall(const auto& grid, const tPos& p ) const{
        if (p.first<0 || p.first>=maxx || p.second>=maxy) {
            return true; //void
        }
        return (grid.at(p.second).at(p.first)  == '.');
    }

    bool fall(auto& grid, const tPos& p ) const {
        if (p.first<0 || p.first>=maxx || p.second>=maxy) {
            //cout << "VOID: " << p.first << "," << p.second << endl;
            return true; //void
        }
        
        if(can_fall(grid, {p.first, p.second+1})) //DOWN
            return fall(grid, {p.first, p.second+1}); 
        else if(can_fall(grid, {p.first-1, p.second+1}))
            return fall(grid, {p.first-1, p.second+1}); //DOWN LEFT
        else if(can_fall(grid, {p.first+1, p.second+1}))
            return fall(grid, {p.first+1, p.second+1}); //DOWN RIGHT
        else
            grid.at(p.second).at(p.first) = 'o'; //ALL blocked - settled

        //print_grid(grid);
        return false; //not void
    };
public:

    int process(ifstream&& f) { 
        string line;
        vector<vector<tPos>> paths;
        
        while(getline(f,line)) {
            paths.push_back(vector<tPos>());
            for (size_t pos = 0; pos < string::npos;) {
                tPos c = tPos{getNum(line, pos),getNum(line, pos)};
                minx = min(minx, c.first);
                miny = min(miny, c.second);
                maxx = max(maxx, c.first);
                maxy = max(maxy, c.second);
                paths.back().emplace_back(std::move(c));
            }
        }
        maxx = maxx-minx+1;
        maxy = maxy-miny+1;
        //cout << "\nLimits: " << minx << "," << miny << " " << maxx << "," << maxy << " | " << endl;
        vector<string> grid(maxy, string(maxx, '.'));
        
        for( size_t i = 0; i < paths.size(); ++i )  {
            auto& from = paths[i][0];
            for( size_t j = 1; j < paths[i].size(); ++j) {
                auto& to = paths[i][j];
                linefill(grid, from, to);
                from = to;
            }
        }
        int sandCount = 0;
        while(!fall(grid, { 500 - minx, 0 })) {
            sandCount++;
        }
        return sandCount; 
    }
};

int main() {
    cout << "part 1 example:" << Mine{}.process(ifstream("AOC14_example.txt")) << endl;
    cout << "part 1:" << Mine{}.process(ifstream("AOC14.txt")) << endl;
    return 0;
}