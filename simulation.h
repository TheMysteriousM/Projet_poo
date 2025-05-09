#ifndef SIMULATION_H
#define SIMULATION_H

#include "board.h"

class Simulation {
private:
    Table table;
    int cellSize;
    element currentElement; // Track the currently selected element

public:
    Simulation(int width, int height, int cellSize)
        : table(height / cellSize, width / cellSize), cellSize(cellSize), currentElement(sand) {}

    void handleInput(sf::RenderWindow &window);

    void update();

    void draw(sf::RenderWindow &window);
};

#endif // SIMULATION_H