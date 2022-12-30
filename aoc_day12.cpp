//https://adventofcode.com/2022/day/12
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <ranges>
#include <queue>
#include <map>
#include <set>
using namespace std;
using location = pair<int, int>;


struct Grid
{
    vector<string> grid;
    int max_x, max_y;
    location start;
    location end;

    set<location> visited;
    multimap<int, location> tovisit;
        
    void print(location n) const {
        cout << "   0,1,2,3,4,5,6,7" << endl;
        for(int y = 0; y< max_y; ++y) {
            cout << y << ": ";
            for (int x = 0; x < max_x; ++x) {
                bool viz = visited.contains({x, y});
                cout << grid[y][x] << ((x == n.first && y==n.second) ? "*" : (viz ? "~" : " "));

            }
            cout << endl;
        }
    }
    void enqueue(const location l, const location n, int steps) {
        int x = n.first, y = n.second;
        if (x<0 || y<0 ||  y >= max_y || x >= max_x)
            return;
        const char cc = grid[y][x];
        int diff = ((cc == 'E' ? 'z' : cc) - grid[l.second][l.first]);
        if(diff>1)
            return;
        //cout << "(push c=" << x << "," << y << " steps= " << steps+1 << ") ";
        tovisit.emplace(++steps, n);
    }

    int bfs(location last) {
        enqueue(last, last, 0);
        while (!tovisit.empty()) {
            location n =tovisit.begin()->second;
            int steps = tovisit.begin()->first;
            tovisit.erase(tovisit.begin());
            int x = n.first, y = n.second;
            if (visited.find(n)!=visited.end()) {
                //cout << "SKIP " <<  x << ","<< y << " VISITED" <<endl;
                continue;
            }
            //grid[y][x] = '~';
            visited.insert(n);
            print(n);
            for (auto& e : tovisit)
                cout << "(steps=" << e.first << " l=" << e.second.first << "," << e.second.second << ")";
            cout << endl;
            if (n == end) {
                cout << "END FOUND"<< endl;
                return steps;
            }
            enqueue(last, {x, y-1}, steps);
            enqueue(last, {x, y+1}, steps);
            enqueue(last, {x-1, y}, steps);
            enqueue(last, {x+1, y}, steps);
            last = n;
        }
        return -1;
    }

    Grid(ifstream&& f) {
        while(true) { //each line is is e.g. "A Z"
            string s;
            if (!getline(f,s)) break;
            auto x = s.find('S'); //find start (before moving string)
            auto y = s.find('E'); //find start (before moving string)
            grid.emplace_back(std::move(s));
            if (x != string::npos)
                start = { x, grid.size()-1 };
            if (y != string::npos)
                end = { y, grid.size()-1 };
        }
        max_y = (int)grid.size();
        max_x = (int)grid[0].size();
        
        grid[start.second][start.first] = 'a';
        cout << "steps=" << bfs(start) << endl;
    }
};

int main() {
    Grid g1(ifstream{"AOC12_example.txt"});
    //Grid g2(ifstream{"AOC12.txt"}); 
}








        //out of bounds base case
        /*if (loc.second<0 || loc.first<0 || 
            loc.second >= max_y || loc.first >= max_x)
            return numeric_limits<int>::max();

        visited.emplace(x,y);    
        const char c = grid[y][x];
        const char l = grid[last.second][last.first];

        //cout << "GOT " << c << " " << c - last << endl;
        //ALready visited OR too high to step up
        int st = ((c == 'E' ? 'z' : c) - l);
        if ( st > 1)
            return numeric_limits<int>::max();

        //cout << "Step: curr=" << c << "(" << x << "," << y  << ") last=" << l << " ("  << last.first << "," << last.second << ") steps=" << steps << endl;

        if (c == 'E') {
            //print(grid);
            //cout << "FOUND!" << steps << endl;
            return steps;
        }
        
        steps+=1; 
        //const auto& i = cache.find({last,loc});
        //if(i != cache.end())
        //    return i->second;
        return ranges::min({step(visited, loc, {x-1, y}, steps),
            step(visited, loc, {x, y-1}, steps),
            step(visited, loc, {x+1, y}, steps),
            step(visited, loc, {x, y+1}, steps)});
            
        //return min(min(min(step(visited, loc, {x-1, y}, steps),  step(visited,loc, {x, y-1}, steps)),
        //    step(visited,loc, {x+1, y}, steps)),step(visited,loc, {x, y+1}, steps));
*/