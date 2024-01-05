#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>
#include "headers/Dijkstra.h"
#include "headers/AStar.h"
#include<map>

sf::Vector2i getCellIndex(sf::Vector2i mouseposition);
bool mouseIsIninital_(sf::Vector2i position);
void settingUpEvent(sf::Event event,sf::Vector2i mousePosition);
void drawGrid( sf::RectangleShape rect, const Cell cells[20][20], sf::RenderWindow &window,short cell_size, sf::Vector2i init_point);

std::map<std::string,Pathfinder* > pathfinders;
Cell initial_cells[20][20];

sf::Clock timer;
sf::Time elapsed;

bool settingUp;

bool clickedStartEnd;
bool firstSquareDrawn;

bool drawingDragged;
bool drawingWalls;
bool drawingStart;
bool drawingTarget;



int main() {
    pathfinders["astar"] = new AStar(false);
    pathfinders["bfs"] = new BFS(false);
    pathfinders["dfs"] = new AStar(true);
    pathfinders["dij"] = new Dijkstra(false);

    clickedStartEnd = false;
    firstSquareDrawn = false;

    settingUp = true;

    drawingDragged = false;
    drawingWalls = true;
    drawingStart = false;
    drawingTarget = false;

    sf::RectangleShape initial_rect(sf::Vector2f(global::DIMENSIONS::INITIAL_CELL_SIZE,global::DIMENSIONS::INITIAL_CELL_SIZE));
    initial_rect.setFillColor(global::COLOR::EMPTY);
    initial_rect.setOutlineThickness(2);
    initial_rect.setOutlineColor(sf::Color(0, 0, 0));

    sf::RectangleShape running_rect = initial_rect;
    running_rect.setSize(sf::Vector2f(global::DIMENSIONS::RUNNING_CELL_SIZE,global::DIMENSIONS::RUNNING_CELL_SIZE));


    bool displayed = false;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(global::DIMENSIONS::WINDOW_SIZE, global::DIMENSIONS::WINDOW_SIZE), "Pathfinding Algorithms");

    initial_cells[0][0].changeType(global::CELL::START);
    initial_cells[19][19].changeType(global::CELL::END);

    while (window.isOpen()) {        
        sf::Event event;

        while (window.pollEvent(event)) {
            if(settingUp)
                settingUpEvent(event,sf::Mouse::getPosition(window));

            if (event.type == sf::Event::Closed)
                window.close();
        }

        // This maintains the running speed of the algorithms
        elapsed = timer.getElapsedTime();

        //Runs each algorithm
        if (!settingUp && elapsed.asMilliseconds() >= global::RUNNING_SPEED){ 
            for (const auto& pathfinder : pathfinders) {
                pathfinder.second->run();
            }

            timer.restart();
        }

        window.clear(global::COLOR::BCKGRND);

        // During setup the grid takes up the entire window
        if(settingUp){
            drawGrid(initial_rect,initial_cells,window,global::DIMENSIONS::INITIAL_CELL_SIZE, sf::Vector2i(0,0));
        }
        else{
            // drawGrid(initial_rect,pathfinders["dfs"]->cells,window,global::DIMENSIONS::INITIAL_CELL_SIZE, sf::Vector2i(0,0));


            // Window is divided into 4 grids to view the 4 pathfinding algorithms simultaneously
            drawGrid(running_rect,pathfinders["astar"]->cells,window,global::DIMENSIONS::RUNNING_CELL_SIZE, sf::Vector2i(0,0));
            drawGrid(running_rect,pathfinders["bfs"]->cells,window,global::DIMENSIONS::RUNNING_CELL_SIZE, sf::Vector2i(global::DIMENSIONS::WINDOW_SIZE/2,0));
            drawGrid(running_rect,pathfinders["dfs"]->cells,window,global::DIMENSIONS::RUNNING_CELL_SIZE, sf::Vector2i(0,global::DIMENSIONS::WINDOW_SIZE/2));
            drawGrid(running_rect,pathfinders["dij"]->cells,window,global::DIMENSIONS::RUNNING_CELL_SIZE, sf::Vector2i(global::DIMENSIONS::WINDOW_SIZE/2,global::DIMENSIONS::WINDOW_SIZE/2));
        }

        window.display();
    }

    return 0;
}

void drawGrid( sf::RectangleShape rect, const Cell cells[20][20], sf::RenderWindow &window, short cell_size,  sf::Vector2i init_point){
    // Draws each individual rectangle based on its color, position and size
    for(int i = 0; i<20;i++){
        for(int j = 0; j<20;j++){
            int x = (i* cell_size)+init_point.x;
            int y = (j* cell_size)+init_point.y;

            rect.setPosition(x, y);
            rect.setFillColor(cells[i][j].color);
            window.draw(rect);
        }
    }
}

void settingUpEvent(sf::Event event,sf::Vector2i mousePosition){

    // If user presses return
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
        //Load cells into pathfinders and start the pathfinding process
        for (const auto& pathfinder : pathfinders) {
            pathfinder.second->loadCells(initial_cells);
        }
        
        settingUp = false;
    }

    // Determine if click was done inside the grid
    if(event.type == sf::Event::MouseButtonPressed && mouseIsIninital_(mousePosition)){
        sf::Vector2i index = getCellIndex(mousePosition);

        if(drawingStart && initial_cells[index.x][index.y].isEmpty()){
            initial_cells[index.x][index.y].changeType(global::CELL::START);
            drawingStart = false;
        }
        else if(drawingTarget  && initial_cells[index.x][index.y].isEmpty()){
            initial_cells[index.x][index.y].changeType(global::CELL::END);
            drawingTarget = false;
        }
        else if(initial_cells[index.x][index.y].isStart() && !drawingTarget){
            initial_cells[index.x][index.y].changeType(global::CELL::EMPTY);
            drawingStart = true;              
        }
        else if(initial_cells[index.x][index.y].isEnd() && !drawingStart){
            initial_cells[index.x][index.y].changeType(global::CELL::EMPTY);
            drawingTarget = true;                 
        }
        else if(!drawingStart && !drawingTarget){
            drawingDragged = true;
        }

    }

    // Draw square that mouse hovers over if it is on drawing mode
    if(mouseIsIninital_(mousePosition) && drawingDragged){
        sf::Vector2i cellIndex= getCellIndex(mousePosition);
        
        if(!initial_cells[cellIndex.x][cellIndex.y].isStart() &&
            !initial_cells[cellIndex.x][cellIndex.y].isEnd()){

            //Figure out if the drag is to draw walls or to erase them
            if(!firstSquareDrawn){
                drawingWalls = !initial_cells[cellIndex.x][cellIndex.y].type ;
                firstSquareDrawn = true;
            }

            if(drawingWalls){
                initial_cells[cellIndex.x][cellIndex.y].changeType(global::CELL::WALL);
            }
            else
                initial_cells[cellIndex.x][cellIndex.y].changeType(global::CELL::EMPTY);
        }
    }

    //Release the drawing drag
    if(event.type == sf::Event::MouseButtonReleased){
        drawingDragged = false;
        firstSquareDrawn = false;
    }

}

bool mouseIsIninital_(sf::Vector2i position){
    // Checks if mouse is inside grid
    if(position.x> global::DIMENSIONS::GRID_START && position.y > global::DIMENSIONS::GRID_START && position.x<(global::DIMENSIONS::GRID_START + (global::DIMENSIONS::INITIAL_CELL_SIZE* global::DIMENSIONS::NUM_CELLS)) && position.y < (global::DIMENSIONS::GRID_START+ (global::DIMENSIONS::INITIAL_CELL_SIZE * global::DIMENSIONS::NUM_CELLS)))
        return true;
    else
        return false;
}

sf::Vector2i getCellIndex(sf::Vector2i mouseposition){
    // Transforms xy coordinates to position in terms of the inital array
    sf::Vector2i position = sf::Vector2i(static_cast<int>((mouseposition.x - global::DIMENSIONS::GRID_START) / global::DIMENSIONS::INITIAL_CELL_SIZE),static_cast<int>((mouseposition.y - global::DIMENSIONS::GRID_START) / global::DIMENSIONS::INITIAL_CELL_SIZE));
    return position;
}