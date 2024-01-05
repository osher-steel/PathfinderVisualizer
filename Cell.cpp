#include "headers/Cell.h"

void Cell::changeType(global::CELL _type){
    type = _type;
    color = global::COLOR::getCellColor(type);
}

void Cell::setIndex(sf::Vector2i _index){
    index = _index;
}

bool Cell::isEmpty(){
    return type == global::CELL::EMPTY;
}

bool Cell::isWall(){
    return type == global::CELL::WALL;
}

bool Cell::isStart(){
    return type == global::CELL::START;
}

bool Cell::isEnd(){
    return type == global::CELL::END;
}

bool Cell::isVisited(){
    return type == global::CELL::VISITED;
}

bool Cell::isNeighbor(){
    return type == global::CELL::NEIGHBOR;
}

bool Cell::isPath(){
    return type == global::CELL::PATH;
}