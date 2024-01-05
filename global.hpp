# pragma once
#include <SFML/Graphics.hpp>
#include <map>

namespace global{

    constexpr int RUNNING_SPEED = 50;
    
    namespace DIMENSIONS{
        constexpr short NUM_CELLS = 20;
        constexpr short WINDOW_SIZE = 1500;
        constexpr short GRID_START = 0;
        constexpr short GRID_SIZE = WINDOW_SIZE - (GRID_START * 2);
        constexpr short INITIAL_CELL_SIZE = GRID_SIZE/NUM_CELLS;
        constexpr short RUNNING_CELL_SIZE = INITIAL_CELL_SIZE/2;
    }

    namespace ASTAR{
        constexpr short NON_DIAGONAL_COST = 10;
        constexpr short DIAGONAL_COST = 14;
    }

    enum CELL{
        EMPTY,
        WALL,
        START,
        END,
        VISITED,
        NEIGHBOR,
        PATH
    };

    namespace COLOR{
        const sf::Color BCKGRND(173, 216, 230);
        const sf::Color EMPTY(220,220,220);
        const sf::Color WALL(0,0,0);
        const sf::Color START(255,0,0);
        const sf::Color END(0,255,0);
        const sf::Color NEIGHBOR(255, 244, 79);
        const sf::Color VISITED(0, 0, 255);
        const sf::Color PATH(106, 13, 173);

        inline sf::Color getCellColor(global::CELL cell){
            switch (cell){
                case global::CELL::EMPTY:
                    return EMPTY;
                case global::CELL::WALL:
                    return WALL;
                case global::CELL::START:
                    return START;
                case global::CELL::END:
                    return END;  
                case global::CELL::VISITED:
                    return VISITED;
                case global::CELL::NEIGHBOR:
                    return EMPTY;  
                case global::CELL::PATH:
                    return PATH;              
            }
        }
    }
}