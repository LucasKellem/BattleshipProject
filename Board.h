//
// Created by lucas on 11/12/2020.
//

#ifndef FINAL_BOARD_H
#define FINAL_BOARD_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BoardStates.h"
#include "Coordinate.h"
#include <vector>
#include "User.h"
using namespace std;
using namespace sf;

class Ship;


class Board {
private:
    vector<Coordinate> _boardSprites;
    int _windXOffset; //Window xOffset
    int _windYOffset; //Window yOffset
public:
    sf:: Texture waterTex;
    sf:: Texture waterMissTex;
    sf:: Texture shipBodySunkTex;
    sf:: Texture shipEndSunkTex;
    sf:: Texture shipBeginSunkTex;
    sf:: Texture shipHorizBodySunkTex;
    sf:: Texture shipHorizEndSunkTex;
    sf:: Texture shipHorizBeginSunkTex;
    RectangleShape grid; //The invisible rectangle that represents the valid grid points at which we care about user input. Used in buttonPressed();
    Sprite gameTileLoop; //Variable used for drawing sprites in locations at which the current/attacking user has shot at.


    /** @brief Draw user shots
    * @desc This function takes in users, current player, and the render window. Draws the current users shots on the
    * shotFiredSprite, and if there is no shot at a coordinate on sprite, then leaves it blank (as indicated by
    * Shipstate::State_Null). Make sure function does not change user.
    * @param RenderWindow/Main Window
    * @param User/Player One
    * @param User/Player Two
    * @param Int/Current Player
    * @param Sprite/Backpattern
    */
    void drawBoard(RenderWindow &, const User &, const User &, int, Sprite &);

    /** @brief Validates user click is within grids we care about.
    * @desc Validates user click is within grids we care about. Uses the grid bounds and event to check if grid contains
    * event or not.
    * @param Event/User Click
    * @return Bool/Is within or not
    */
    bool gridPressed(Event event);

    /** @brief Returns the boardstate of a coordinate.
    * @desc Returns the boardstate of a coordinate by checking against the vector of user shots. If no such location is
    * found (in user shots) return Shipstate::State_Null, indicating no shot has happened there...So leave the
    * coordinate untouched
    * @param Char/Row
    * @param Int/Column
    * @param Vector<Coordinate>/User Shots
    * @return BoardStates/The boardstate of the coordinate
    */
    BoardStates getBoardState(char, int, vector<Coordinate>&);

    /** @brief Initialize all of the textures the board uses.
    * @desc Initializes all of the textures the board uses, and stores the window xOffset and yOffset for sprite alignment.
    * @param Int/xOffset
    * @param Int/yOffset
    */
    void initializeTextures(int, int);

    /** @brief Set Offsets
    * @desc Sets the window offsets for proper sprite alignment
    * @param Int/xOffset
    * @param Int/yOffset
    */
    void setWindowOffset(int, int);

    /** @brief Get Offsets
    * @desc Returns the window offsets for proper sprite alignment
    * @return Vector2i/Window Offsets
    */
    Vector2i getWindowOffsets() const;
};


#endif //FINAL_BOARD_H
