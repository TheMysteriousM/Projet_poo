#include "board.h"

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

void Table::update() {
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
                }
                // Sand slides diagonally if possible
                else if (x > 0 && cells[y + 1][x - 1].getMaterial() == none) {
                    cells[y][x].setMaterial(none);
                    cells[y + 1][x - 1].setMaterial(sand);
                } else if (x < width - 1 && cells[y + 1][x + 1].getMaterial() == none) {
                    cells[y][x].setMaterial(none);
                    cells[y + 1][x + 1].setMaterial(sand);
                }
            } else if (current == water) {
                // Water falls straight down if the cell below is empty
                if (below == none) {
                    cells[y][x].setMaterial(none);
                    cells[y + 1][x].setMaterial(water);
                }
                // Water flows sideways if possible
                else if (x > 0 && cells[y][x - 1].getMaterial() == none) {
                    cells[y][x].setMaterial(none);
                    cells[y][x - 1].setMaterial(water);
                } else if (x < width - 1 && cells[y][x + 1].getMaterial() == none) {
                    cells[y][x].setMaterial(none);
                    cells[y][x + 1].setMaterial(water);
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
                cellShape.setFillColor(sf::Color::White); // Empty cell
            }
            cellShape.setPosition(x * cellSize, y * cellSize);
            window.draw(cellShape);
        }
    }
}