#pragma once
#include "Pathfinder.h"
#include <queue>

class AStar: public Pathfinder{
    public:
        std::vector<Cell*> neighbors;
        
        AStar(bool _eightDirectional):Pathfinder(_eightDirectional,false,false){};

        void findNeighbors() override;
        void calculateCellValue(int x, int y, int cost);
        void findPath() override;

        int getMinIndex();
};
