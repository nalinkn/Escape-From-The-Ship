// 950181F63D0A883F183EC0A5CC67B19928FE896A
//  router.cpp
//  p1-ship
//
//  Created by Nalin Krishnan on 9/10/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <getopt.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "xcode_redirect.hpp"

using namespace std;

class Map {
public:
    void get_options(int argc, char * argv[]);
    //void readMap();
    //void readList();
    
    
private:
    struct Tile {
        char symbol;
        bool isDiscovered;
        char direction;
    };
    struct Coordinate {
     u_int32_t level;
     unsigned int row, col;
    
    };

public:
    int levels;
    int size;
    vector< vector< vector<Tile> > > map;
    string outputMode = "M";
    char routingMode;



    void readMap() {
        //cin >> output;
        //cin >> levels;
        //cin >> size;
        
        //for (int i = 0; i < (size * size * levels); ++i) {
            //cin >> map[floor(i/(size*size))][floor((i % (size*size)) / size)][i % size];
        //}
        string l;
        string z;
        cin >> l;
        cin >> z;
        
        levels = std::stoi(l);
        size = std::stoi(z);
        //Tile tile;
        
        map.resize(size_t(levels), vector<vector<Tile>>(size_t(size), vector<Tile>(size_t(size))));
        
        unsigned int currRow = 0;
        unsigned int currLevel = 0;
        string s;
        while (getline(cin, s)) {
            
            
            if (s[0] == '/') {
                continue;
            }
            if (s.empty()) {
                continue;
            }
            else {
                //if (currLevel == levels) {
                   // break;
                //}
                for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
                    Tile tile = {s[i], false, '-'};
                    
                    //cout << s[i];
                    //cout << currRow << currLevel;
                    if (s[i] != 'H' && s[i] != 'S' && s[i] != 'E' && s[i] != '.' && s[i] != '#') {
                        cerr << "Invalid map character" << endl;
                        exit(1);
                    }
                    

                    map[currLevel][currRow][static_cast<unsigned int>(i)] = tile;
                                        
                }//for
                currRow++;
                if (currRow == static_cast<unsigned int>(size)) {
                    currRow = 0;
                    currLevel++;
                }
            }//else
        }//while
        
        
    }
    
    void readList() {
        string l;
        string z;
        cin >> l;
        cin >> z;
        
        levels = std::stoi(l);
        size = std::stoi(z);
        
        
        
        map.resize(size_t(levels), vector<vector<Tile>>(size_t(size), vector<Tile>(size_t(size))));
        
        unsigned int floorRow  = 0;
        unsigned int floorCol = 0;
        unsigned int floorLevel = 0;
        char floorSymbol = '.';
        for (size_t i = 0; i < static_cast<size_t>(size * size * levels); ++i) {
            Tile floor = {floorSymbol, false, '-'};
            map[floorLevel][floorRow][floorCol] = floor;
            //cout << floorSymbol;
            if (floorCol != static_cast<unsigned int>(size - 1)) {
                floorCol++;
            }
            else {
                if (floorRow != static_cast<unsigned int>(size - 1)) {
                    floorRow++;
                    floorCol = 0;
                }
                else {
                    floorLevel++;
                    floorRow = 0;
                    floorCol = 0;
                }
            }
            
        }
        
        unsigned int currRow = 0;
        unsigned int currCol = 0;
        u_int32_t currLevel = 0;
        char currSymbol;
        char par;
        char c;;
        string comment;
        char comma;
        while (cin >> c){
            if (c != '(') {
                getline(cin, comment);
            }
            else {
                cin >> currLevel >> comma >> currRow >> comma >> currCol >> comma >> currSymbol >> par;
                Tile tile = {currSymbol, false, '-'};
                if (currSymbol != 'H' && currSymbol != 'S' && currSymbol != 'E' && currSymbol != '.' && currSymbol != '#') {
                    cerr << "Invalid map character" << endl;
                    exit(1);
                }
                if (currLevel > static_cast<u_int32_t>(levels - 1)) {
                    cerr << "Invalid map level" << endl;
                    exit(1);
                }
                if (currRow > static_cast<unsigned int>(size - 1)) {
                    cerr << "Invalid map row" << endl;
                    exit(1);
                }
                if (currCol > static_cast<unsigned int>(size - 1)) {
                    cerr << "Invalid map column" << endl;
                    exit(1);
                }
                map[currLevel][currRow][currCol] = tile;
                //cout << currLevel << currRow << currCol << currSymbol;
                
            }
        }
        
        
    }
    
    void search() {
        deque<Coordinate> discovered;
        deque<Coordinate> route;
        Coordinate start;
        Coordinate hanger = {0, 0, 0};
        for (size_t i = 0; i < static_cast<size_t>(levels); ++i) {
            for (size_t j = 0.; j < static_cast<size_t>(size); ++j) {
                for (size_t k = 0; k < static_cast<size_t>(size); ++k) {
                    if (map[static_cast<u_int32_t>(i)][static_cast<unsigned int>(j)][static_cast<unsigned int>(k)].symbol == 'S') {
                        start = {static_cast<u_int32_t>(i), static_cast<unsigned int>(j), static_cast<unsigned int>(k)};
                    }
                    if (map[i][j][k].symbol == 'H') {
                        hanger = {static_cast<u_int32_t>(i), static_cast<unsigned int>(j), static_cast<unsigned int>(k)};
                    }
                }
            }
        }
        discovered.push_back(start);
        map[start.level][start.row][start.col].isDiscovered = true;
        Coordinate curr = start;
        bool hangerFound = false;
        while (!hangerFound) {
            //calling front(), initializing direction, and adding that tile to a new deque
            if (routingMode == 'q') {
                //cout << curr.direction;
                discovered.pop_front();
                
            }
            else {
                //cout << curr.direction;
                discovered.pop_back();
            }
            
            if (curr.row != 0 && !map[curr.level][curr.row - 1][curr.col].isDiscovered && map[curr.level][curr.row - 1][curr.col].symbol != '#') {
                map[curr.level][curr.row - 1][curr.col].isDiscovered = true;
                map[curr.level][curr.row - 1][curr.col].direction = 'n';
                Coordinate c = {curr.level, curr.row - 1, curr.col};
                discovered.push_back(c);
                if (map[c.level][c.row][c.col].symbol == 'H') {
                    hangerFound = true;
                    break;
                }
            }
            if (curr.col != static_cast<unsigned int>(size - 1) && !map[curr.level][curr.row][curr.col + 1].isDiscovered && map[curr.level][curr.row][curr.col + 1].symbol != '#') {
                map[curr.level][curr.row][curr.col + 1].isDiscovered = true;
                map[curr.level][curr.row][curr.col + 1].direction = 'e';
                Coordinate c = {curr.level, curr.row, curr.col + 1};
                discovered.push_back(c);
                if (map[c.level][c.row][c.col].symbol == 'H') {
                    hangerFound = true;
                    break;
                }
            }
            if (curr.row != static_cast<unsigned int>(size -  1) && !map[curr.level][curr.row + 1][curr.col].isDiscovered && map[curr.level][curr.row + 1][curr.col].symbol != '#') {
                map[curr.level][curr.row + 1][curr.col].isDiscovered = true;
                map[curr.level][curr.row + 1][curr.col].direction = 's';
                Coordinate c = {curr.level, curr.row + 1, curr.col};
                discovered.push_back(c);
                if (map[c.level][c.row][c.col].symbol == 'H') {
                    hangerFound = true;
                    break;
                }
            }
            if (curr.col != 0 && !map[curr.level][curr.row][curr.col - 1].isDiscovered && map[curr.level][curr.row][curr.col - 1].symbol != '#') {
                map[curr.level][curr.row][curr.col - 1].isDiscovered = true;
                map[curr.level][curr.row][curr.col - 1].direction = 'w';
                Coordinate c = {curr.level, curr.row, curr.col - 1};
                discovered.push_back(c);
                if (map[c.level][c.row][c.col].symbol == 'H') {
                    hangerFound = true;
                    break;
                }
            }
            if (map[curr.level][curr.row][curr.col].symbol == 'E') {
                for (size_t i = 0; i < static_cast<size_t>(levels); ++i) {
                    
                    if (map[static_cast<u_int32_t>(i)][curr.row][curr.col].symbol == 'E' && !map[static_cast<u_int32_t>(i)][curr.row][curr.col].isDiscovered) {
                        map[static_cast<u_int32_t>(i)][curr.row][curr.col].isDiscovered = true;
                        map[static_cast<u_int32_t>(i)][curr.row][curr.col].direction = static_cast<char>(curr.level + 48);
                        Coordinate c = {static_cast<u_int32_t>(i), curr.row, curr.col};
                        discovered.push_back(c);
                    }
                }
            }
            if (routingMode == 'q') {
                //curr.direction = discovered.front().direction;
                //map[curr.level][curr.row][curr.col].isDiscovered = true;
                //map[curr.level][curr.row][curr.col].symbol = curr.direction;
                //cout << curr.direction;
                //route.push_back(curr);
                if (discovered.size() == 0) {
                    break;
                }
                curr = discovered.front();
            }
            else {
                //curr.direction = discovered.back().direction;
                //map[curr.level][curr.row][curr.col].isDiscovered = true;
                //map[curr.level][curr.row][curr.col].symbol = curr.direction;
                //cout << curr.symbol;
                //route.push_back(curr);
                if (discovered.size() == 0) {
                    break;
                }
                curr = discovered.back();
            }
        }
        
        if (!hangerFound) {
            if (outputMode == "M") {
                cout << "Start in level " << start.level << ", row " << start.row << ", column " << start.col << endl;
                for (size_t i = 0; i < static_cast<size_t>(levels); ++i) {
                    cout << "//level " << i << endl;
                    for (size_t j = 0; j < static_cast<size_t>(size); ++j) {
                        for (size_t k = 0; k < static_cast<size_t>(size); ++k) {
                            cout << map[i][j][k].symbol;
                            if (k == static_cast<size_t>(size - 1)) {
                                cout << endl;
                            }
                        }
                    }
                }
            }
            else {
                cout << "//path taken" << "\n";
            }
            return;
        }
        /*
        for (size_t i = 0; i < route.size(); ++i) {
            route[i].symbol = route[i].direction;
        }
         */
        
    
        Coordinate b = hanger;
        while ((b.level != start.level) || (b.row != start.row) || (b.col != start.col)) {
            if (map[b.level][b.row][b.col].direction == 'n') {
                map[b.level][b.row + 1][b.col].symbol = 'n';
                Coordinate c = {b.level, b.row + 1, b.col};
                route.push_back(c);
            }
            else if (map[b.level][b.row][b.col].direction == 'e') {
                map[b.level][b.row][b.col - 1].symbol = 'e';
                Coordinate c = {b.level, b.row, b.col - 1};
                route.push_back(c);
            }
            else if (map[b.level][b.row][b.col].direction == 's') {
                map[b.level][b.row - 1][b.col].symbol = 's';
                Coordinate c = {b.level, b.row - 1, b.col};
                route.push_back(c);
            }
            else if (map[b.level][b.row][b.col].direction == 'w') {
                map[b.level][b.row][b.col + 1].symbol = 'w';
                Coordinate c = {b.level, b.row, b.col + 1};
                route.push_back(c);
            }
            else {
                map[static_cast<u_int32_t>(map[b.level][b.row][b.col].direction - '0')][b.row][b.col].symbol = static_cast<char>(b.level + '0');
                Coordinate c = {static_cast<u_int32_t>(map[b.level][b.row][b.col].direction - '0'), b.row, b.col};
                route.push_back(c);
            }
            b = route.back();
        }
        
        
        
        
        //char startLevel = static_cast<char>(start.level + '0');
        //char startRow = static_cast<char>(start.row + '0');
        //char startCol = static_cast<char>(start.col + '0');
        
        if (outputMode == "M") {
            cout << "Start in level " << start.level << ", row " << start.row << ", column " << start.col << endl;
            for (size_t i = 0; i < static_cast<size_t>(levels); ++i) {
                cout << "//level " << i << endl;
                for (size_t j = 0; j < static_cast<size_t>(size); ++j) {
                    for (size_t k = 0; k < static_cast<size_t>(size); ++k) {
                        cout << map[i][j][k].symbol;
                        if (k == static_cast<size_t>(size - 1)) {
                            cout << endl;
                        }
                    }
                }
            }
        }
        else {
            cout << "//path taken" << "\n";
            for (int i = static_cast<int>(route.size()) - 1; i >= 0; i--) {
                cout << "(" << route[static_cast<u_int32_t>(i)].level << "," << route[static_cast<unsigned int>(i)].row << "," << route[static_cast<unsigned int>(i)].col << "," << map[route[static_cast<u_int32_t>(i)].level][route[static_cast<unsigned int>(i)].row][route[static_cast<unsigned int>(i)].col].symbol << ")" << "\n";
                //if (i == 0) {
                    //break;
                //}
            }
        }
    }
    
        
        
    
};




void printHelp(char *argv[]) {
    cout << "Usage: " << argv[0] << " -s|-q|[-o M|L]|-h" << endl;
    cout << "This program is to find an escape route out of a spaceship" << endl;
    cout << "using two different search containers (stack and queue)" << endl;
    cout << "and two different input types (map and coordinate list)." << endl;
} // printHelp()


void Map::get_options(int argc, char * argv[]) {
    //bool stackMode = false;
    
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    
    int stackCount = 0;
    int queueCount = 0;
    int choice;
    int option_index = 0;
    struct option long_options[] = {
        { "stack",  no_argument,        nullptr, 's'  },
        { "queue",  no_argument,        nullptr, 'q'  },
        { "output", required_argument,  nullptr, 'o'  },
        { "help",   no_argument,        nullptr, 'h'  },
        { nullptr,  0,                  nullptr, '\0' }
    };
    
    // ask in office hours how to use getopt_long with the routing modes
    // since they don't have required arguments but are rewuired by themselves
    while ((choice = getopt_long(argc, argv, "sqo:h", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            printHelp(argv);
            exit(0);
        
        case 'o':
            outputMode = optarg;
            if (outputMode != "M" && outputMode != "L") {
                cout << "Invalid output mode specified" << endl;
                exit(1);
            }
            break;
                
        case 's':
            //stackMode = true;
                //cout << "Multiple routing modes specified" << endl;
                //exit(1);
            
            routingMode = 's';
            stackCount++;
            break;
            
            
                
        case 'q':
            //stackMode = false;
            /*if (rmodeSpecified) {
                cout << "Multiple routing modes specified" << endl;
                exit(1);
            }*/
            routingMode = 'q';
            queueCount++;
            break;
                
            
            
                
               
    
                
        /*
        default:
            cerr << "Error: invalid option" << endl;
            exit(1);
         */
        }
        
    }
    if (stackCount == 0 && queueCount == 0) {
        cout << "No routing mode specified" << endl;
        exit(1);
    }
    else if (stackCount > 1 || queueCount > 1) {
        cout << "Multiple routing modes specified" << endl;
        exit(1);
    }
    else if (stackCount == 1 && queueCount == 1) {
        cout << "Multiple routing modes specified" << endl;
        exit(1);
    }
    else {
        
    }
    
}
    
    








int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    char inputMode;
    cin >> inputMode;
    
    
    Map map;
    map.get_options(argc, argv);
    
    
    if (inputMode == 'M') {
        map.readMap();
    }
    
    else {
        map.readList();
    }
    map.search();
    

    // All done!
    return 0;
}
