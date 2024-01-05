#include "headers/AStar.h"
#include <cmath>
#include <algorithm>

void AStar::findNeighbors(){
    calculateCellValue(current->index.x-1,current->index.y,global::ASTAR::NON_DIAGONAL_COST);
    calculateCellValue(current->index.x,current->index.y-1,global::ASTAR::NON_DIAGONAL_COST);  
    calculateCellValue(current->index.x+1,current->index.y,global::ASTAR::NON_DIAGONAL_COST);
    calculateCellValue(current->index.x,current->index.y+1,global::ASTAR::NON_DIAGONAL_COST);

    if(eightDirectional){
        calculateCellValue(current->index.x-1,current->index.y-1,global::ASTAR::DIAGONAL_COST);
        calculateCellValue(current->index.x+1,current->index.y-1,global::ASTAR::DIAGONAL_COST);  
        calculateCellValue(current->index.x-1,current->index.y+1,global::ASTAR::DIAGONAL_COST);
        calculateCellValue(current->index.x+1,current->index.y+1,global::ASTAR::DIAGONAL_COST);
    }
}

void AStar::calculateCellValue(int x, int y, int cost){
    if(x>=0 && x<=19 && y>=0 && y<=19){    
        Cell * cell = &cells[x][y];
        if(cell->isEmpty() || cell->isEnd() || cell->isNeighbor()){
            if(cell->isEmpty()){
                cell->changeType(global::CELL::NEIGHBOR);
                neighbors.push_back(cell);  
            }

            if(cell->isEnd()){
                neighbors.push_back(cell);  
            }


            int g_cost = current->g_cost + cost;
            int h_cost;

            if(eightDirectional){
                int min = std::min(abs(x-end->index.x), abs(y-end->index.y));
                int max = std::max(abs(x-end->index.x), abs(y-end->index.y));
                h_cost = ((max-min)*global::ASTAR::NON_DIAGONAL_COST) + (min * global::ASTAR::DIAGONAL_COST);
            }
            else{
                h_cost = abs(x-end->index.x) + abs(y-end->index.y);
            }

            int f_cost = g_cost + h_cost;

            if(f_cost < cell->f_cost){
                cell->g_cost = g_cost;
                cell->h_cost = h_cost;
                cell->f_cost = f_cost;

                cell->parent = current->index;
            }

        }
    }
}

void AStar::findPath(){
    findNeighbors();
    
    if(!neighbors.empty() && !finished){
        int currentIndex = getMinIndex();
        current = neighbors[currentIndex];

        if(current->isEnd()){
            end = current;
            finished = true;
        }
        else{
            current->changeType(global::CELL::VISITED);
            neighbors.erase(neighbors.begin()+currentIndex);
        }
    }
}

int AStar::getMinIndex(){
    int min = 0;

    for(int i=1; i<neighbors.size(); i++){
        if(neighbors[i]->f_cost < neighbors[min]->f_cost)
            min = i;
    }

    return min;
}