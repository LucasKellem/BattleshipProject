//
// Created by lucas on 11/12/2020.
//

#include "BoardStates.h"

#ifndef FINAL_COORDINATE_H
#define FINAL_COORDINATE_H


class Coordinate {
public:
    /** @brief Default constructor
    * @desc Sets the private member variables to default values.
    */
    Coordinate();

    /** @brief Returns coordstate
    * @desc Returns the coordstate. If it is not visible, returns a default state.
    * @return BoardStates/Coordstate of coordinate
    */
    BoardStates getCoordState() const;

    /** @brief Set coordinate
    * @desc Sets the coordinate to the parameter coordinate
    * @param Current Player/Int
    */
    void setCoord(Coordinate);

    /** @brief Sets the direction
    * @desc Sets the direction of a coordinate to the parameter int
    * @param Direction/Int
    */
    void setDirection(int);

    /** @brief Sets boardstate of coord
    * @desc Sets the coordstate with a Boardstate param. I believe this is used in the original creation of the
     * coordinate in a ship (from vector of ships)/shot (from vector of user attempted shots).
    * @param BoardStates/BoardState of the coordinate
    */
    void setCoordState(BoardStates);

    /** @brief Sets the coordstate when a shot occurs. Has a switch statement altering every situation before and after a "shot" occurs.
    * @desc Called when a shot is taken by a user. This shot will set the boardstate of the coordinate to "hit", whether
    * it is a ship or water.
    * @param Shot/Int
    */
    void setCoordState(int);

    /** @brief Sets the coordinate location with char and int params.
    * @desc Set the grid location of the coordinate with parameter row and column.
    * @param Row/Char
    * @param Column/Int
    */
    void setCoord(char, int);

    /** @brief Returns the row of the coordinate. (Row is char)
    * @desc Returns the row of the coordinate.
    * @return Row/Char
    */
    char getRow() const;

    /** @brief Returns the column of the coordinate. (Col is int).
    * @desc Returns the column of the coordinate.
    * @return Column/Int
    */
    int getCol() const;

    /** @brief Returns the direction of the coordinate.
    * @desc Returns the direction of the coordinate.
    * @return Direction/Int
    */
    int getDirection() const;

    /** @brief Sets the visibility of the coordinate.
    * @desc Sets the visibility of the coordinate. Called when a shot happens.
    * @param Visibility/Int
    */
    void setVisibility(int);

    /** @brief Returns the visibility of the coordinate.
    * @desc Returns the visibility of the coordinate. Used for drawing.
    * @return Visibility/Int
    */
    int getVisibility() const;

private:
    char _coordRow; //A-J. The row of the coordinate.
    int _coordNum; //0-9. The column of the coordinate.
    int _direction; //0 = Vertical, 1 = Down, 2 = Left, 3 = Right. The direction of the coordinate.
    int _visibility;//0 = water, 1 = actual boardstate visible. The visibility of the coordinate.
    BoardStates _coordState; //The boardstate of the coordinate.

};


#endif //FINAL_COORDINATE_H
