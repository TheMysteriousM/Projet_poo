#ifndef SIMULATION_H
#define SIMULATION_H

#include "board.h"
#include <unordered_map>

class Simulation {
private:
    Table table;
    int cellSize;
    element currentElement;
    int brushSize;
    std::unordered_map<sf::Keyboard::Key, bool> keyStates; // Track key states

public:
    Simulation(int width, int height, int cellSize)
        : table(height / cellSize, width / cellSize), cellSize(cellSize), currentElement(sand), brushSize(1) {}

    void handleInput(sf::RenderWindow &window);

    void update();

    void draw(sf::RenderWindow &window);
};

#endif // SIMULATION_H