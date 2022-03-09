//
// Created by lucas on 11/12/2020.
//

#ifndef FINAL_SHIP_H
#define FINAL_SHIP_H

#include "Coordinate.h"
#include "User.h"
#include <vector>
#include <iostream>

using namespace std;

class Ship {
private:
    vector<Coordinate> _coordinates; //This is the coordinates of the ship. Ship is basically a vector of coordinates with a size, appending currSize, and direction.
    int _size; //Size of the ship. Will be between 5 and 3.
    int _currSize; //Appending size of ship, when a coordinate of ship is hit, decreases by 1. At 0, the ship is sunk.
    int _direction; //Determines direction of ship in generation.

public:
    /** @brief Default constructor
    * @desc sets private member variables to default values
    */
    Ship();

    /** @brief get coord
    * @desc Returns the coord of a ship at coordinate 'a'. Don't change coord, make sure it is constant.
    * @param int a, a is the position of coordinate on ship
    * @return Coordinate
    */
    Coordinate getCoord(int a) const;

    /** @brief set ship
    * @descUses rand values for direction, given size, and then with the random direction, generates ship with _ coords and sets coordstates accordingly.
    * @param vector<ship> ships
    * @param int size
    * @param int direction
    */
    void setShip(vector<Ship> &ships, const int, const int);

    /** @brief
    * @desc Function to check if a coordinate already exists given vector of ships. If it returns true, then we keep
     * generating until it returns false. Return false? This means coordinate is valid and we are all gucci.
    * @param vector<coordinate> coords to test
    * @param vector<ship> ships to test with
    * @return bool is or isn't valid
    */
    bool alreadyExists(vector<Coordinate> &coordTest, vector<Ship> &ships);

    /** @brief Ship was hit
    * @desc When a ship is hit, this is called. Decreases _currSize by 1, and sets coordstates/coord visibility for drawing purposes.
    * @param int was hit?
    */
    void wasHit(int);

    /** @brief check if ship is sunk
    * @desc Checks if ship is sunk. If _currSize = 0, this returns true (meaning it is sunk). If it returns false, then the ship is not sunk yet.
    * @return bool is or isn't sunk
    */
    bool wasSunk();

    /** @brief get size
    * @desc Return the _size of a ship, NOT the _currSize. Don't change size, make sure it is constant.
    * @return
    */
    int getSize() const;

    /** @brief get row
    * @desc Returns the row of a ship. Don't change row, make sure it is constant.
    * @param int a, which coordinate of ship
    * @return char row
    */
    char getRow(int a) const;

    /** @brief get column
    * @desc Returns the column of a ship. Don't change column, make sure it is constant.
    * @param int a, which coordinate of ship
    * @return int column
    */
    int getColumn(int a) const;
};


#endif //FINAL_SHIP_H
