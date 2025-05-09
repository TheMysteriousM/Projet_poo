#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>

enum element {none, sand, water, rock} ; 
class Cell {
    element material; // get the element on the cell
    bool inertial ;
public:
    Cell() : material(none), inertial(false) {} // default constructor
    void setMaterial(element mat) ;
    element getMaterial() ;

    void setInertial(bool state) ;
    bool isInertial() ;
};

class Table {
private:
    int height;
    int width;
    std::vector<std::vector<Cell>> cells;
    bool floor ;
    bool borders ;

public:
    Table(int height, int width) : height(height), width(width), cells(height, std::vector<Cell>(width)), floor(true), borders(false) {}
    void addSand(int x, int y) ;
    void addWater(int x, int y) ;
    void addRock(int x, int y) ;
    void erase(int x, int y);
    bool getFloor() { return floor; }
    bool getBorders() { return borders; }
    void setFloor(bool value) { floor = value; }
    void setBorders(bool value) { borders = value; }
    void update() ;
    void draw(sf::RenderWindow &window, int cellSize)  ;
};

#endif // BOARD_H