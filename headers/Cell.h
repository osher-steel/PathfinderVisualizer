#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.hpp"

class Cell{
    public:
        sf::Vector2i parent;
        sf::Vector2i index;
        sf::Color color;

        global::CELL type;

        float value;

        int f_cost;
        int g_cost; 
        int h_cost;
        
        
        Cell():parent(),type(global::CELL::EMPTY),color(global::COLOR::EMPTY),value(100000), f_cost(10000), g_cost(0), h_cost(0){};
        
        void changeType(global::CELL _type);
        void setIndex(sf::Vector2i _index);

        bool isEmpty();
        bool isWall();
        bool isStart();
        bool isEnd();
        bool isVisited();
        bool isNeighbor();
        bool isPath();
};



