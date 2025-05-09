#include "simulation.h"
#include <iostream>

using namespace std;

void Simulation::handleInput(sf::RenderWindow &window) {
    // Handle keyboard input to change the current element
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        currentElement = water;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        currentElement = rock;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        currentElement = sand;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        if (!keyStates[sf::Keyboard::F]) { // Only toggle if the key was not already pressed
            table.setFloor(!table.getFloor());
            cout << "Floor toggled: " << (table.getFloor() ? "ON" : "OFF") << endl;
            keyStates[sf::Keyboard::F] = true; // Mark the key as pressed
        }
    } else {
        keyStates[sf::Keyboard::F] = false; // Reset the key state when the key is released
    }

    // Handle toggling the borders with the B key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        if (!keyStates[sf::Keyboard::B]) {
            table.setBorders(!table.getBorders());
            cout << "Borders toggled: " << (table.getBorders() ? "ON" : "OFF") << endl;
            keyStates[sf::Keyboard::B] = true;
        }
    } else {
        keyStates[sf::Keyboard::B] = false;
    }

    // Adjust brush size with arrow keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!keyStates[sf::Keyboard::Up]) {
            brushSize = std::min(brushSize + 1, 10); // Limit max brush size to 10
            cout << "Brush size increased: " << brushSize << endl;
            keyStates[sf::Keyboard::Up] = true;
        }
    } else {
        keyStates[sf::Keyboard::Up] = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (!keyStates[sf::Keyboard::Down]) {
            brushSize = std::max(brushSize - 1, 1); // Limit min brush size to 1
            cout << "Brush size decreased: " << brushSize << endl;
            keyStates[sf::Keyboard::Down] = true;
        }
    } else {
        keyStates[sf::Keyboard::Down] = false;
    }

    // Handle mouse input to place the current element
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int centerX = mousePos.x / cellSize;
        int centerY = mousePos.y / cellSize;

         // Apply the brush
        for (int y = -brushSize; y <= brushSize; ++y) {
            for (int x = -brushSize; x <= brushSize; ++x) {
                if (currentElement == sand) {
                    table.addSand(centerX + x, centerY + y);
                } else if (currentElement == water) {
                    table.addWater(centerX + x, centerY + y);
                } else if (currentElement == rock) {
                    table.addRock(centerX + x, centerY + y);
                }
            }
        }
    }
    // Handle right mouse button to erase the element
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int centerX = mousePos.x / cellSize;
        int centerY = mousePos.y / cellSize;

        // Apply the brush
        for (int y = -brushSize; y <= brushSize; ++y) {
            for (int x = -brushSize; x <= brushSize; ++x) {
                table.erase(centerX + x, centerY + y);
            }
        }
    }
}

void Simulation::update() {
    table.update();
}

void Simulation::draw(sf::RenderWindow &window) {
    table.draw(window, cellSize);
}