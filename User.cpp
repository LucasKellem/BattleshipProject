//
// Created by lucas on 11/12/2020.
//

#include "User.h"

using namespace std;

User::User(){
    myFont.loadFromFile("resources/Misc/Pixel Bug.otf");
    _turns = 0;
}
bool User::GeneratedSuccessfully() {
    int intCounter = 0;
    for(int i = 0; i < 5; i++){
        intCounter += _userShips.at(i).getSize();
    }
    //just makes sure theres 17 coords. If not, lemme know.
    cout << intCounter;
    if(intCounter != 17){
        return false;
    }
    else{
        return true;
    }
}
void User::SetShips() {
    //need to make 5 ships, 2 size 3, 1 size 2, 1 size 4, 1 size 5
    rand() % 100; //throw away

    Ship ship1;
    ship1.setShip(_userShips, 3, (rand() % 4));
    _userShips.push_back(ship1);
    Ship ship2;
    ship2.setShip(_userShips, 3, (rand() % 4));
    _userShips.push_back(ship2);
    Ship ship3;
    ship3.setShip(_userShips, 5, (rand() % 4));
    _userShips.push_back(ship3);
    Ship ship4;
    ship4.setShip(_userShips, 2, (rand() % 4));
    _userShips.push_back(ship4);
    Ship ship5;
    ship5.setShip(_userShips, 4, (rand() % 4));
    _userShips.push_back(ship5);

    _numShips = _userShips.size();

    if (!User::GeneratedSuccessfully()) {
        cout << "Uhoh. Ships Were Not Able To Be Generated." << endl;
    } else {
        cout << "Ships Generated Successfully!" << endl;
    }

}
shotFiredBundle User::shotWasFired(char a, int b) {
    shotFiredBundle theBundle;
    Coordinate shot;
    shot.setCoord(a, b);
    bool wasHit = false;
    for (int j = 0; j < 5; j++) {
        //for every ship
        for (int m = 0; m < _userShips.at(j).getSize(); m++) {
            //for every coordinate at ship
            if((a == _userShips.at(j).getRow(m)) && (b == _userShips.at(j).getColumn(m))){
                cout << "Hit!" << endl;
                wasHit = true;

                _userShips.at(j).wasHit(m); //Update coord state of ships
                theBundle.boardState = _userShips.at(j).getCoord(m).getCoordState(); //Throw boardstate in with bundle
                if (_userShips.at(j).wasSunk()){
                    _numShips = _numShips - 1;
                    cout << "Sunk! Number of Ships Left: " << _numShips << endl;
                    theBundle.hitCondition = 1; //Throw wasHit int in with bundle
                    return theBundle; //hit and sink
                }else{
                    cout << "Not Sunk! Number of Ships Left: " << _numShips << endl;
                    theBundle.hitCondition = 2; //Throw wasHit int in with bundle
                    return theBundle; //hit only
                }
            }
        }
    }
    cout << "Miss!" << endl;
    theBundle.hitCondition = 3; //Throw wasHit int in with bundle
    theBundle.boardState = BoardStates::State_WaterMiss;
    return theBundle; //miss
}
bool User::allShipsSunk() const{//check if ships is 0
    if (_numShips == 0){
        return true;
    }
    else{
        return false;
    }
}
void User::printShips(){//delete once the game is done.
    for (int j = 0; j < 5; j++) {
        //for every ship
        cout << endl;
        for (int m = 0; m < _userShips.at(j).getSize(); m++) {
            //for every coordinate at ship
            cout << _userShips.at(j).getCoord(m).getRow() << _userShips.at(j).getCoord(m).getCol() << " ";
        }

    }
    cout << endl;
}
void User::addNewShot(Coordinate newShot){//add new shot to vector of attempted shots
    this->_attemptedShots.push_back(newShot);
    this->_attemptedShots.at(_attemptedShots.size() - 1).setVisibility(1);
    this->_turns++;
}
bool User::alreadyAttempted(int mouseX, int mouseY, const int xOffset, const int yOffset) {//check if shot has already been attempted
    char mouRow;
    int mouCol;
    //mouRow = 'A' + (int) ((b - 201) / 100); //Convert mouse coordinates to grid tiles
    //mouCol = (int) ((a - 201) / 100); ////Convert mouse coordinates to grid tiles
    mouCol = (int) ((mouseX - 201 - xOffset) / 100); ////Convert mouse coordinates to grid tiles
    mouRow = 'A' + (int) ((mouseY - 201 - yOffset) / 100); //Convert mouse coordinates to grid tiles
    bool alreadyFound = false;
    if(_attemptedShots.empty()){
        return false;
    }
    for(int i = 0; i < _attemptedShots.size(); i++){
        //for all attempted shots...
        if((mouCol == _attemptedShots.at(i).getCol()) && (mouRow == _attemptedShots.at(i).getRow())){
            //if new shot col and row is equal to attempted shot at i
            alreadyFound = true; //is found = true.
        }
    }
    return alreadyFound; //return if it is not found.
}
vector<Coordinate> User::getAttempts() const{//return the attempted shots of the user
    return _attemptedShots;
}
void User::setName(string userInName) {//set the name of the user
    _userName = userInName;
}
string User::getName() const{//return the name of the user
    return _userName;
}
int User::getTurns() const{
    return _turns;
}
int User::getShipsLeft() const{
    return _numShips;
}
