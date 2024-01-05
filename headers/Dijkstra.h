#pragma once
#include "Pathfinder.h"
#include <queue>
#include <vector>

class Dijkstra:public Pathfinder{
    public:
        // struct Compare {
        // bool operator()(const std::pair<int, sf::Vector2i>& left, const std::pair<int, sf::Vector2i>& right) const {
        //     return left.first > right.first;  // Use '>' for min heap (lowest value at the top)
        // }
        // };

        // std::priority_queue<std::pair<int, sf::Vector2i>, std::vector<std::pair<int, sf::Vector2i>>, Compare> neighbors;

        std::vector<Cell*> neighbors;

        Dijkstra(bool _eightDirectional): Pathfinder(_eightDirectional,false,false){};
        void checkAdj(int x, int y,int cost); 
        void findNeighbors() override;
        void findPath() override;

        int getMinIndex();
};