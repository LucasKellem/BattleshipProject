//
// Created by lucas on 11/12/2020.
//

#ifndef FINAL_USER_H
#define FINAL_USER_H

#include "Coordinate.h"
#include "Ship.h"
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;
class Ship;

struct shotFiredBundle{
    BoardStates boardState;
    int hitCondition;
};

class User {
private:
    vector<Ship> _userShips;
    int _numShips;
    vector<Coordinate> _attemptedShots;
    string _userName;
    int _turns;

public:
    Font myFont;

    /** @brief Default Constructor
    * @desc Initializes user to default values
    */
    User();

    /** @brief get attempts
    * @desc returns the vector of coordinates which is user shots
    * @return vector<Coordinate> attempts
    */
    vector<Coordinate> getAttempts() const;

    /** @brief set ships
    * @desc intializes/sets all 5 ships for user
    */
    void SetShips();

    /** @brief generated successfully?
    * @desc checks if all ships were generated successfully
    * @return bool was or wasn't successful
    */
    bool GeneratedSuccessfully();

    /** @brief shot was fired
    * @desc A function that handles when a shot is taken AT the user. If its a hit, changes boardstate and coordstate
    * of the shot coordinate of the ship.
    * @param char row
    * @param int column
    * @return shotFiredBundle with int (was hit code) and boardstate
    */
    shotFiredBundle shotWasFired(char a, int b);

    /** @brief check if all ships sunk
    * @desc checks if all of the user's ships are sunk.
    * @return bool all or not all ships sunk.
    */
    bool allShipsSunk() const;

    /** @brief print ships
    * @desc prints all ships of the user. helpful for debugging
    */
    void printShips();

    /** @brief new shot
    * @desc called by the user when they take a shot. Adds the new shot to the vector of attempts
    * @param Coordinate the shot
    */
    void addNewShot(Coordinate);

    /** @brief was shot already attempted
    * @desc checks if the coordinate selected by user has already been attempted by them.
    * @param int mousex
    * @param int mousey
    * @param int windowXOffset
    * @param int windowYOffset
    * @return bool/already attempted or not
    */
    bool alreadyAttempted(int, int, const int, const int);

    /** @brief set user string name
    * @desc sets the user's name to the parameter string
    * @param name/string
    */
    void setName(string);

    /** @brief Return Name
    * @desc Returns user name
    * @return Name/string
    */
    string getName() const;

    /** @brief Return turns
    * @desc Returns the amount of turns that the user has taken
    * @return Turns/Int
    */
    int getTurns() const;

    /** @brief Return Ships Left
    * @desc Returns the amount of user ships remaining/not sunk
    * @return Ships Remaining/Int
    */
    int getShipsLeft() const;
};


#endif //FINAL_USER_H
