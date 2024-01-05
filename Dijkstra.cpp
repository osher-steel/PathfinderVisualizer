#include "headers/Dijkstra.h"

void Dijkstra::checkAdj(int x, int y,int cost){
    if(x>=0 && x<=19 && y>=0 && y<=19){   
        float current_value = cells[current->index.x][current->index.y].value;

        Cell * cell = &cells[x][y];

        if(cell->isEmpty() || cell->isEnd()|| cell->isNeighbor()){
            float new_value = current_value + cost;

            if(new_value < cell->value){
                cell->value = new_value;
                cell->parent = current->index;
            }

            if(cell->isEmpty()){
                cell->changeType(global::CELL::NEIGHBOR);
                neighbors.push_back(cell);  
            }

            if(cell->isEnd()){
                neighbors.push_back(cell);  
            }
        }
    }
}

void Dijkstra::findNeighbors(){
        checkAdj(current->index.x-1,current->index.y,global::ASTAR::NON_DIAGONAL_COST);
        checkAdj(current->index.x,current->index.y-1,global::ASTAR::NON_DIAGONAL_COST); 
        checkAdj(current->index.x+1,current->index.y,global::ASTAR::NON_DIAGONAL_COST);
        checkAdj(current->index.x,current->index.y+1,global::ASTAR::NON_DIAGONAL_COST);

    if(eightDirectional){
        checkAdj(current->index.x-1,current->index.y-1,global::ASTAR::DIAGONAL_COST);
        checkAdj(current->index.x+1,current->index.y-1,global::ASTAR::DIAGONAL_COST);  
        checkAdj(current->index.x-1,current->index.y+1,global::ASTAR::DIAGONAL_COST);
        checkAdj(current->index.x+1,current->index.y+1,global::ASTAR::DIAGONAL_COST);
    }
}

void Dijkstra::findPath(){
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

int Dijkstra::getMinIndex(){
    int min = 0;

    for(int i=1; i<neighbors.size(); i++){
        if(neighbors[i]->value < neighbors[min]->value)
            min = i;
    }

    return min;
}