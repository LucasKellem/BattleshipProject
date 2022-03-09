//
// Created by lucas on 11/13/2020.
//

#include "Coordinate.h"

Coordinate::Coordinate(){ //Default constructor
    _coordRow = 'Z';
    _coordNum = -9999;
    _direction = 0;
    _coordState = BoardStates::State_Water;
    _visibility = 0;
}

void Coordinate::setCoord(Coordinate coord) { //TODO:Figure out why I had this and what it is for. Possibly Delete.
    _coordRow = coord._coordRow;
    _coordNum = coord._coordNum;
    _direction = coord._direction;
    _coordState = coord._coordState;
}

void Coordinate::setVisibility(const int a){
    _visibility = a;
}

void Coordinate::setCoord(const char row, const int col) { //Set coordinate given a char and an int as params. Make sure the params don't change.
    _coordRow = row;
    _coordNum = col;
}

char Coordinate::getRow() const{ //Return the row (char) of the coordinate. Const.
    return _coordRow;
}

int Coordinate::getCol() const{ //Return the column (int) of the coordinate. Const.
    return _coordNum;
}

void Coordinate::setDirection(const int directionIn){ //Set the direction of the coordinate.
    _direction = directionIn;
}

BoardStates Coordinate::getCoordState() const{ //Return the coord state of coordinate. Const.
    if(_visibility == 0){
        //IF the visibility is 0 (visibility gets changed when a coordinate is shot by enemy)
        return BoardStates::State_Water; //then return BoardStates::State_Water.
    }else{
        //visibility is true or 1
        return _coordState; //return the real coordstate
    }
}

int Coordinate::getDirection() const{ //Getter for direction. Not used.
    return _direction;
}

void Coordinate::setCoordState(const BoardStates boardstate) { //Set boardstate of a coordinate with param of BoardStates
    _coordState = boardstate;
}

void Coordinate::setCoordState(const int shot) { //This function is used to set the coord state when a shot hits the referenced coordinate. Param is an int.
    if (shot == 1) {
        switch (_coordState) {
            case BoardStates::State_Water:{ //If the coordinate is water...
                _coordState = BoardStates::State_WaterMiss; //Set the new coordstate to WATER & MISS
                break;
            }
            case BoardStates::State_beginShip:{ //If the coordinate is a vertical beginning of ship...
                _coordState = BoardStates::State_beginShipSunk; //Set the new coordstate to VERTICAL BEGINNING SHIP & HIT
                break;
            }
            case BoardStates::State_midShip:{ //If the coordinate is a vertical midship piece...
                _coordState = BoardStates::State_midShipSunk; //Set the new coordstate to VERTICAL MIDSHIP & HIT
                break;
            }
            case BoardStates::State_endShip:{ //If the coordinate is a vertical end of ship...
                _coordState = BoardStates::State_endShipSunk; //Set the new coordstate to VERTICAL ENDSHIP & HIT
                break;
            }
            case BoardStates::State_beginHorizShip:{ //If the coordinate is a horizontal beginning of ship...
                _coordState = BoardStates::State_beginHorizShipSunk; //Set the new coordstate to HORIZONTAL BEGINNING SHIP & HIT
                break;
            }
            case BoardStates::State_midHorizShip:{ //If the coordinate is a horizontal midship piece...
                _coordState = BoardStates::State_midHorizShipSunk; //Set the new coordstate to HORIZONTAL MIDSHIP & HIT
                break;
            }
            case BoardStates::State_endHorizShip:{ //If the coordinate is a horizontal end of ship...
                _coordState = BoardStates::State_endHorizShipSunk; //Set the new coordstate to HORIZONTAL ENDSHIP & HIT
                break;
            }
        }
    }
}

int Coordinate::getVisibility() const{ //Get the visibility of the coordinate.
    return _visibility;
}