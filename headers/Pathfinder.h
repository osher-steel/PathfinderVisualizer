#pragma once

#include "Cell.h"
#include <deque>


class Pathfinder{
    public:
        Cell cells[20][20];

        std::deque<Cell*> neighbors;

        Cell* current;
        Cell* start;
        Cell* end;

        bool bfs;
        bool dfs;

        bool finished;
        bool rewinded;
        bool foundTarget;
        bool eightDirectional;

        short pathLength;

        
        Pathfinder(bool _eightDirectional, bool _bfs, bool _dfs):eightDirectional(_eightDirectional), bfs(_bfs), dfs(_dfs){};
        
        void loadCells(const Cell cells[20][20]);
        void run();
        virtual void findPath();
        void check(int x, int y); 
        virtual void findNeighbors();
        void rewind();
};

class BFS:public Pathfinder{
    public:
        BFS(bool _eightDirectional):Pathfinder(_eightDirectional,true,false){};
};

class DFS:public Pathfinder{
    public:
        DFS(bool _eightDirectional):Pathfinder(_eightDirectional,false,true){};
};