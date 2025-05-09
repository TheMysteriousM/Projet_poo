#include <SFML/Graphics.hpp>
#include "simulation.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int cellSize = 10;

    // Create a simulation object
    Simulation sim(windowWidth, windowHeight, cellSize);

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sand Simulation");
    // window.setFramerateLimit(60); // Limit the frame rate ;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sim.handleInput(window);
        sim.update();

        window.clear();
        sim.draw(window);
        window.display();
    }

    return 0;
}

// to run :  g++ -o sand_simulation main.cpp simulation.cpp board.cpp -lsfml-graphics -lsfml-window -lsfml-system