#pragma once
#include "Pathfinder.h"
#include <queue>

class AStar: public Pathfinder{
    public:
        // struct Compare {
        //     bool operator()(const std::pair<int, sf::Vector2i>& left, const std::pair<int, sf::Vector2i>& right) const {
        //         return left.first > right.first;  // Use '>' for min heap (lowest value at the top)
        //     }
        // };

        // std::priority_queue<std::pair<int, sf::Vector2i>, std::vector<std::pair<int, sf::Vector2i>>, Compare> neighbors;

        std::vector<Cell*> neighbors;
        
        AStar(bool _eightDirectional):Pathfinder(_eightDirectional,false,false){};

        void findNeighbors() override;
        void calculateCellValue(int x, int y, int cost);
        void findPath() override;

        int getMinIndex();
};