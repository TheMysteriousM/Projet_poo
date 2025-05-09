#include "simulation.h"

void Simulation::handleInput(sf::RenderWindow &window) {
    // Handle keyboard input to change the current element
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        currentElement = water;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        currentElement = rock;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        currentElement = sand;
    }

    // Handle mouse input to place the current element
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int x = mousePos.x / cellSize;
        int y = mousePos.y / cellSize;

        if (currentElement == sand) {
            table.addSand(x, y);
        } else if (currentElement == water) {
            table.addWater(x, y);
        } else if (currentElement == rock) {
            table.addRock(x, y);
        }
    }
}

void Simulation::update() {
    table.update();
}

void Simulation::draw(sf::RenderWindow &window) {
    table.draw(window, cellSize);
}