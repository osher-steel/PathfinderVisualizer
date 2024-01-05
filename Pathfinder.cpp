#include "headers/Pathfinder.h"

void Pathfinder::loadCells(const Cell _cells[20][20]){
    for(int i=0; i<20; i++){
        for(int j =0; j<20; j++){
            cells[i][j].color = _cells[i][j].color;
            cells[i][j].type =  _cells[i][j].type;
            cells[i][j].index = sf::Vector2i(i,j);

            if(cells[i][j].isStart()){
                start = &cells[i][j];
                current = start;
                start->value = 0;
            }

            if(cells[i][j].isEnd()){
                end = &cells[i][j];
            }
        }
    }
}

void Pathfinder::run(){
    if(!finished){
        findPath();
    }
    else if(!rewinded){
        rewind();
        rewinded = true;
    }
}

void Pathfinder::findPath(){
    // Adds valid adjacent cells to the deque
    findNeighbors();

    if(!neighbors.empty() && !finished){
        // BFS follows a FIFO(First In First Out) implementation while DFS follows a LIFO(Last In Last Out) implementation
        if(bfs){
            current = neighbors.front();
            neighbors.pop_front();

            // std::cout<<current.x<<","<<current.y<<std::endl;
        }
        else if(dfs){
            current = neighbors.back();
            neighbors.pop_back();
        }

        if(current->isEnd()){
            end = current;
            finished = true;
        }
        else
            current->changeType(global::CELL::VISITED);
    }
}

void Pathfinder::check(int x, int y){
    if(x>=0 && x<=19 && y>=0 && y<=19){
        Cell * cell = &cells[x][y];

        if(cell->isEmpty() || cell->isEnd()){
            neighbors.push_back(cell);
            cell->parent = current->index;

            if(cell->isEmpty())
                cell->changeType(global::CELL::NEIGHBOR);
        }
    }
}

void Pathfinder::findNeighbors(){
        check(current->index.x-1,current->index.y);
        check(current->index.x,current->index.y-1); 
        check(current->index.x+1,current->index.y);
        check(current->index.x,current->index.y+1);

    // Checks adjacent diagonal cells
    if(eightDirectional){
            check(current->index.x-1,current->index.y-1);
            check(current->index.x+1,current->index.y-1);  
            check(current->index.x-1,current->index.y+1);
            check(current->index.x+1,current->index.y+1);
    }

}

void Pathfinder::rewind(){
    sf::Vector2i parent = end->parent;

    pathLength= 0;

    // The algorithm retraces the path by starting at the ending point and following the parent cells.   
    while(true){
        if(parent == start->index)
            break;
    
        cells[parent.x][parent.y].changeType(global::CELL::PATH);
        parent = cells[parent.x][parent.y].parent;

        pathLength++;
    }

    std::cout<<pathLength<<std::endl;
}

