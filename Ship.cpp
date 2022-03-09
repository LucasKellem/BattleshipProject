//
// Created by lucas on 11/12/2020.
//

#include "Ship.h"


using namespace std;

Ship::Ship() { //Default constructor
    _size = 0; //Initialize _size to 0.
    _currSize = 0; //Initialize appendable _currSize to 0.
    _direction = 0; //Initialize ship to vertical
}

void Ship::setShip(vector<Ship> &ships, const int theSize, const int randomDirection) { //Sets ship into the user's vector of ships, using the included ship size and random direction param.
    _currSize = theSize; //Assign current size with designated size of ship. Current size WILL change over the span of gameplay.
    _direction = randomDirection; //Assign direction with the designated param.
    _size = theSize; //Assign current size with designated size of ship. Current size WILL change over the span of gameplay.
    Coordinate coord; //Coord used in generation of ship coords.
    char letter; //Letter used in generation of ship coords. This corresponds with y, or row!.
    int number; //Number used in generation of ship coords. This corresponds with x, or column!.
    bool couldPlace = false; //End condition for while loop. While false...generate new coord location. If this coord location (and the other locations orientated around this coordinate) are valid...set true, and break.
    while(!couldPlace){
        //While the coordinate is not placed...
        //Just a heads up, the math in this section gave me many headaches over the 2 months I have worked on random object generation in a coordinate system. Maybe I am just stupid but it was pretty difficult. Enjoy
        switch(_direction){
            //Check randomly generated direction
            case 0: { //0 Indicates That The Ship Coordinates Will Be Generated Vertically, Going Up. So generate base coord, and then proceeding coords (xPos, xPos, xPos,...) and (yPos + 1, yPos + 2, yPos + 3,...)
                int row; //Temp val used for letter (row...will be char)
                int column; //Temp val used for number (column...will be int)
                row = rand() % (11 - theSize); //Since this is base yPos, yPos + 1, yPos + 2, yPos + n...we want a yPos value from 0 to (11 - size) so we don't leave bounds!
                column = rand() % 10; //This is a vertical ship, so the only constraint on the horizontal alignment is that it is within 0 and 9.
                vector<Coordinate> coords; //temp vector of coords to test with
                for (int i = 0; i < theSize; i++) {
                    //For every coordinate in the (future) ship...
                    letter = 'A' + row + i; //Convert the letter to a char A-J.
                    number = column; //Assign variable number to variable column.
                    coord.setCoord(letter, number); //Set the coordinates of the coord variable used for generation.
                    coords.push_back(coord); //Add the coord to the vector of coords used for testing validity.
                }if(alreadyExists(coords, ships)){
                    //If any of the coordinates in vector coords exists...
                    couldPlace = false; //It is not valid! DO NOT MOVE ON. Regenerate and try again.
                }else{
                    couldPlace = true; //It is valid! We are all good to move on.
                    for(int m = 0; m < theSize; m++) {
                        //Push back the coordinates from the temp vector coords to the real, genuine, member variable of ship.
                        _coordinates.push_back(coords.at(m));
                    }
                }
                break;
            }
            case 1: { //1 Indicates That The Ship Coordinates Will Be Generated Vertically, Going Down. So generate base coord, and then proceeding coords (xPos, xPos, xPos,...) and (yPos - 1, yPos - 2, yPos - 3,...)
                int row; //Temp val used for letter (row...will be char)
                int column; //Temp val used for number (column...will be int)
                row = rand() % (11 - theSize) + (theSize - 1); //Since this is base yPos, yPos - 1, yPos - 2, yPos - n...we want a yPos value from (0 + size) to 9 so we don't leave bounds!
                column = rand() % 10; //This is a vertical ship, so the only constraint on the horizontal alignment is that it is within 0 and 9.
                vector<Coordinate> coords; //temp vector of coords to test with
                for (int i = 0; i < theSize; i++) {
                    //For every coordinate in the (future) ship...
                    letter = 'A' + row - i; //Convert the letter to a char A-J.
                    number = column; //Assign variable number to variable column.
                    coord.setCoord(letter, number); //Set the coordinates of the coord variable used for generation.
                    coords.push_back(coord); //Add the coord to the vector of coords used for testing validity.
                }
                if(alreadyExists(coords, ships)){
                    //If any of the coordinates in vector coords exists...
                    couldPlace = false; //It is not valid! DO NOT MOVE ON. Regenerate and try again.
                }
                else{
                    couldPlace = true; //It is valid! We are all good to move on.
                    for (int m = 0; m < theSize; m++) {
                        //Push back the coordinates from the temp vector coords to the real, genuine, member variable of ship.
                        _coordinates.push_back(coords.at(m));
                    }
                }
                break;
            }
            case 2: { //2 Indicates That The Ship Coordinates Will Be Generated Horizontally, Going Left. So generate base coord, and then proceeding coords (xPos - 1, xPos - 2, xPos - 3,...) and (yPos, yPos, yPos,...)
                int row; //Temp val used for letter (row...will be char)
                int column; //Temp val used for number (column...will be int)
                row = rand() % 10; //This is a horizontal ship, so the only constraint on the vertical alignment is that it is within 0 and 9.
                column = rand() % (11 - theSize) + (theSize - 1); //Since this is base xPos, xPos - 1, xPos - 2, xPos - n...we want a xPos value from (0 + size) to 9 so we don't leave bounds!
                vector<Coordinate> coords; //temp vector of coords to test with
                for (int i = 0; i < theSize; i++) {
                    //For every coordinate in the (future) ship...
                    letter = 'A' + row; //Convert the letter to a char A-J.
                    number = column - i; //Assign variable number to variable column.
                    coord.setCoord(letter, number); //Set the coordinates of the coord variable used for generation.
                    coords.push_back(coord); //Add the coord to the vector of coords used for testing validity.
                }
                if(alreadyExists(coords, ships)){
                    //If any of the coordinates in vector coords exists...
                    couldPlace = false; //It is not valid! DO NOT MOVE ON. Regenerate and try again.
                }else{
                    couldPlace = true; //It is valid! We are all good to move on.
                    for (int m = 0; m < theSize; m++) {
                        //Push back the coordinates from the temp vector coords to the real, genuine, member variable of ship.
                        _coordinates.push_back(coords.at(m));
                    }
                }
                break;
            }
            case 3: { //3 Indicates That The Ship Coordinates Will Be Generated Horizontally, Going Right. So generate base coord, and then proceeding coords (xPos + 1, xPos + 2, xPos + 3,...) and (yPos, yPos, yPos,...)
                int row; //Temp val used for letter (row...will be char)
                int column; //Temp val used for number (column...will be int)
                row = rand() % 10; //This is a horizontal ship, so the only constraint on the vertical alignment is that it is within 0 and 9.
                column = rand() % (11 - theSize); //Since this is base xPos, xPos + 1, xPos + 2, xPos + n...we want a xPos value from 0 to (11 - size) so we don't leave bounds!
                vector<Coordinate> coords; //temp vector of coords to test with
                for (int i = 0; i < theSize; i++) {
                    //For every coordinate in the (future) ship...
                    letter = 'A' + row; //Convert the letter to a char A-J.
                    number = column + i; //Assign variable number to variable column.
                    coord.setCoord(letter, number); //Set the coordinates of the coord variable used for generation.
                    coords.push_back(coord); //Add the coord to the vector of coords used for testing validity.
                }if(alreadyExists(coords, ships)){
                    //If any of the coordinates in vector coords exists...
                    couldPlace = false; //It is not valid! DO NOT MOVE ON. Regenerate and try again.
                }else{
                    couldPlace = true; //It is valid! We are all good to move on.
                    for (int m = 0; m < theSize; m++) {
                        //Push back the coordinates from the temp vector coords to the real, genuine, member variable of ship.
                        _coordinates.push_back(coords.at(m));
                    }
                }
                break;
            }
        }
    }

    //This section is about setting the coord states for the end and beginning pieces of the ship. Then sets the coordstates for the mid pieces with a for loop.
    if(_direction == 0){ //0 Indicates That The Ship Coordinates Will Be Generated Vertically, Going Up. So generate base coord, and then proceeding coords (xPos, xPos, xPos,...) and (yPos + 1, yPos + 2, yPos + 3,...)
        _coordinates.at(0).setCoordState(BoardStates::State_beginShip); //.at(0) will be an end/begin piece.
        _coordinates.at(0).setDirection(_direction); //.at(0) will be an end/begin piece.
        _coordinates.at(theSize - 1).setCoordState(BoardStates::State_endShip); //.at(size() - 1) will be an end/begin piece.
        _coordinates.at(theSize - 1).setDirection(_direction); //.at(size() - 1) will be an end/begin piece.
        for (int i = 1; i < (theSize - 1); i++) {
            //for all midpieces of ship...
            _coordinates.at(i).setDirection(_direction); //Set Direction and coordstate (for texture drawing at a later point in the program)
            _coordinates.at(i).setCoordState(BoardStates::State_midShip);
        }
    }else if(_direction == 1){ //1 Indicates That The Ship Coordinates Will Be Generated Vertically, Going Down. So generate base coord, and then proceeding coords (xPos, xPos, xPos,...) and (yPos - 1, yPos - 2, yPos - 3,...)
        _coordinates.at(0).setCoordState(BoardStates::State_endShip); //.at(0) will be an end/begin piece.
        _coordinates.at(0).setDirection(_direction); //.at(0) will be an end/begin piece.
        _coordinates.at(theSize - 1).setCoordState(BoardStates::State_beginShip); //.at(size() - 1 (don't break the bounds of the object bud)) will be an end/begin piece.
        _coordinates.at(theSize - 1).setDirection(_direction); //.at(size() - 1) will be an end/begin piece.
        for (int i = 1; i < (theSize - 1); i++) {
            //for all midpieces of ship...
            _coordinates.at(i).setDirection(_direction); //Set Direction and coordstate (for texture drawing at a later point in the program)
            _coordinates.at(i).setCoordState(BoardStates::State_midShip);
        }
    }else if(_direction == 2){ //2 Indicates That The Ship Coordinates Will Be Generated Horizontally, Going Left. So generate base coord, and then proceeding coords (xPos - 1, xPos - 2, xPos - 3,...) and (yPos, yPos, yPos,...)
        _coordinates.at(theSize - 1).setCoordState(BoardStates::State_beginHorizShip); //.at(size() - 1) will be an end/begin piece.
        _coordinates.at(theSize - 1).setDirection(_direction); //.at(size() - 1) will be an end/begin piece.
        _coordinates.at(0).setCoordState(BoardStates::State_endHorizShip); //.at(0) will be an end/begin piece.
        _coordinates.at(0).setDirection(_direction); //.at(0) will be an end/begin piece.
        for (int i = 1; i < (theSize - 1); i++) {
            //for all midpieces of ship...
            _coordinates.at(i).setDirection(_direction); //Set Direction and coordstate (for texture drawing at a later point in the program)
            _coordinates.at(i).setCoordState(BoardStates::State_midHorizShip);
        }
    }else{ //3 Indicates That The Ship Coordinates Will Be Generated Horizontally, Going Right. So generate base coord, and then proceeding coords (xPos + 1, xPos + 2, xPos + 3,...) and (yPos, yPos, yPos,...)
        _coordinates.at(0).setCoordState(BoardStates::State_beginHorizShip); //.at(0) will be an end/begin piece.
        _coordinates.at(0).setDirection(_direction); //.at(0) will be an end/begin piece.
        _coordinates.at(theSize - 1).setCoordState(BoardStates::State_endHorizShip); //.at(size() - 1) will be an end/begin piece.
        _coordinates.at(theSize - 1).setDirection(_direction); //.at(size() - 1) will be an end/begin piece.
        for (int i = 1; i < (theSize - 1); i++) {
            //for all midpieces of ship...
            _coordinates.at(i).setDirection(_direction); //Set Direction and coordstate (for texture drawing at a later point in the program)
            _coordinates.at(i).setCoordState(BoardStates::State_midHorizShip);
        }
    }
}
int Ship::getSize() const{
    return _size;
}
Coordinate Ship::getCoord(int a) const{
    if(a >= _coordinates.size()){ //failsafe for bug I used to have
        cout << "found it!" << endl;
        cout << a << endl;
        cout << _coordinates.size() << endl;
    }
    return _coordinates.at(a);
}
bool Ship::alreadyExists(vector<Coordinate> &coordTest, vector<Ship> &ships){
    for(int i = 0; i < ships.size(); i++){
        //for every ship
        for (int j = 0; j < ships.at(i).getSize(); j++){
            //for every coord
            for (int m = 0; m < coordTest.size(); m++){
                if((coordTest.at(m).getRow() == ships.at(i).getCoord(j).getRow()) && (coordTest.at(m).getCol() == ships.at(i).getCoord(j).getCol())){
                    return true;
                }
            }
        }
    }
    return false;
}
char Ship::getRow(int a) const{
    return _coordinates.at(a).getRow();
}
int Ship::getColumn(int a) const{
    return _coordinates.at(a).getCol();
}
void Ship::wasHit(int a){
    _currSize = _currSize - 1; //decrease size
    _coordinates.at(a).setVisibility(1); //set coordinate to visible (was hit)
    _coordinates.at(a).setCoordState(1); //change the board state to "was hit"
}
bool Ship::wasSunk(){
    if (_currSize == 0){ //if the size is 0, ship is sunk
        return true;
    }
    else{
        return false;
    }
}
