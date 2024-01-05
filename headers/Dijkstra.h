#pragma once
#include "Pathfinder.h"
#include <queue>
#include <vector>

class Dijkstra:public Pathfinder{
    public:
        std::vector<Cell*> neighbors;

        Dijkstra(bool _eightDirectional): Pathfinder(_eightDirectional,false,false){};
        void checkAdj(int x, int y,int cost); 
        void findNeighbors() override;
        void findPath() override;

        int getMinIndex();
};
