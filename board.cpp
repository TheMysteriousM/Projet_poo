#include "board.h"
#include <random>

// Create a random number generator
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dis(-1, 1); // Uniform distribution for random numbers
void Table::addSand(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setMaterial(sand);
    }
}

void Table::addWater(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setMaterial(water);
    }
}

void Table::addRock(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setMaterial(rock);
    }
}

void Table::erase(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setMaterial(none); // Set the cell's material to none
    }
}

void Table::update() {
    // simulating the borders
    if (floor){
        for (int x = 0; x < width; ++x) {
            cells[height - 1][x].setMaterial(rock); // Bottom border
        }
    } ;
    if (borders){
        for (int y = 0; y < height; ++y) {
            cells[y][0].setMaterial(rock); // Left border
            cells[y][width - 1].setMaterial(rock); // Right border
        }
    } ;
    if (!floor){
        for (int x = 0; x < width; ++x) {
            cells[height - 1][x].setMaterial(none); // Bottom border
        }
    } ;
    if (!borders){
        for (int y = 0; y < height; ++y) {
            cells[y][0].setMaterial(none); // Left border
            cells[y][width - 1].setMaterial(none); // Right border
        }
    } ;
    // Simulate falling elements
    for (int y = height - 2; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            element current = cells[y][x].getMaterial();
            element below = cells[y + 1][x].getMaterial();

            if (current == sand) {
                // Sand falls straight down if the cell below is empty
                if (below == none) {
                    cells[y][x].setMaterial(none);
                    cells[y + 1][x].setMaterial(sand);
                } else {
                    // Sand slides diagonally if possible
                    int e = dis(gen);
                    if (x > 0 && cells[y + 1][x - e].getMaterial() == none) {
                        cells[y][x].setMaterial(none);
                        cells[y + 1][x - e].setMaterial(sand);
                    } else if (x < width - 1 && cells[y + 1][x + e].getMaterial() == none) {
                        cells[y][x].setMaterial(none);
                        cells[y + 1][x + e].setMaterial(sand);
                    }
                }
            } else if (current == water) {
                // Water falls straight down if the cell below is empty
                if (below == none) {
                    cells[y][x].setMaterial(none);
                    cells[y + 1][x].setMaterial(water);
                } else {
                    // Water flows sideways if possible
                    int e = dis(gen);
                    if (x > 0 && cells[y][x - e].getMaterial() == none) {
                        cells[y][x].setMaterial(none);
                        cells[y][x - e].setMaterial(water);
                    } else if (x < width - 1 && cells[y][x + e].getMaterial() == none) {
                        cells[y][x].setMaterial(none);
                        cells[y][x + e].setMaterial(water);
                    }
                }
            }
            // Rock does not move
        }
    }
}

void Table::draw(sf::RenderWindow &window, int cellSize) {
    sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            element material = cells[y][x].getMaterial();
            if (material == sand) {
                cellShape.setFillColor(sf::Color::Yellow);
            } else if (material == water) {
                cellShape.setFillColor(sf::Color::Blue);
            } else if (material == rock) {
                cellShape.setFillColor(sf::Color(128, 128, 128)); // Gray for rock
            } else {
                cellShape.setFillColor(sf::Color::Black); // Empty cell
            }
            cellShape.setPosition(x * cellSize, y * cellSize);
            window.draw(cellShape);
        }
    }
}

void Cell::setMaterial(element mat) {
    material = mat;
}
element Cell::getMaterial() {
    return material;
}
void Cell::setInertial(bool state) {
    inertial = state;
}
bool Cell::isInertial() {
    return inertial;
}