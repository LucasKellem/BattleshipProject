//
// Created by lucas on 11/12/2020.
//

#include "Board.h"

void Board::initializeTextures(const int xOffset, const int yOffset){
    this->setWindowOffset(xOffset, yOffset);

    //load textures
    if(!waterTex.loadFromFile("resources/ShipTextures/water.png"))
        cerr << "Error Loading Texture File." << endl;
    if(!waterMissTex.loadFromFile("resources/ShipTextures/waterMiss.png"))
        cerr << "Error Loading Texture File." << endl;
    if(!shipBodySunkTex.loadFromFile("resources/ShipTextures/midShipSunk.png"))
        cerr << "Error Loading Texture File." << endl;
    if(!shipBeginSunkTex.loadFromFile("resources/ShipTextures/shipBeginSunk.png"))
        cerr << "Error Loading Texture File." << endl;
    if(!shipEndSunkTex.loadFromFile("resources/ShipTextures/endShipSunk.png"))
        cerr << "Error Loading Texture File." << endl;
    if(!shipHorizBodySunkTex.loadFromFile("resources/ShipTextures/midShipHSunk.png"))
        cerr << "Error Loading Texture File." << endl;
    if(!shipHorizBeginSunkTex.loadFromFile("resources/ShipTextures/shipBeginHSunk.png"))
        cerr << "Error Loading Texture File." << endl;
    if(!shipHorizEndSunkTex.loadFromFile("resources/ShipTextures/endShipHSunk.png"))
        cerr << "Error Loading Texture File." << endl;

    grid.setSize(Vector2f(1000, 1000));
    //grid.setPosition(200, 200); Pre-full screen
    grid.setPosition(xOffset + 200, yOffset + 200);
}
void Board::drawBoard(RenderWindow &myWindow, const User &userOne, const User &userTwo, const int currentPlayer, Sprite &backPattern) {
    vector<Coordinate> currentPlayerShots; //The shots of the current user. We use these shots to draw textures at already attempted shots. Each shot has a boardstate stored, we just need to access it and draw (or not draw) accordingly.

    if(currentPlayer == 1){ //If the current player/attacking player is player one...
        currentPlayerShots = userOne.getAttempts(); //We want the attempted shots of the first player
    }else {  //If the current player/attacking player is player two...
        currentPlayerShots = userTwo.getAttempts(); //We want the attempted shots of the second player
    }

    //get grid textures
    for(int i = 0; i < 10; i++){
        //for every row
        int yPos = 200 + (100 * i); //The current yPos. 200 is the initial value if window is 1600x1200. TODO:Investigate what formula would need to be used if I implement the fullscreen changes.
        for(int j = 0; j < 10; j++){
            //for every column
            int xPos = 200 + (100 * j); //The current xPos. 200 is the initial value if window is 1600x1200. TODO:Investigate what formula would need to be used if I implement the fullscreen changes.

            BoardStates boardState; //Temp var for boardstate at certain coordinate.
            char letterSend = 'A' + i; //char to send to function setPosition
            int numberSend = j; //number to send to function setPosition

            boardState = getBoardState(letterSend, numberSend, currentPlayerShots);

            if(boardState != BoardStates::State_Null){
                switch (boardState) {//set the texture based on what the boardState is
                    //we don't use the other enum values as we only care about enum states where a shot was fired
                    case BoardStates::State_beginShipSunk:
                        gameTileLoop.setTexture(shipBeginSunkTex);
                        break;
                    case BoardStates::State_midShipSunk:
                        gameTileLoop.setTexture(shipBodySunkTex);
                        break;
                    case BoardStates::State_endShipSunk:
                        gameTileLoop.setTexture(shipEndSunkTex);
                        break;
                    case BoardStates::State_beginHorizShipSunk:
                        gameTileLoop.setTexture(shipHorizBeginSunkTex);
                        break;
                    case BoardStates::State_midHorizShipSunk:
                        gameTileLoop.setTexture(shipHorizBodySunkTex);
                        break;
                    case BoardStates::State_endHorizShipSunk:
                        gameTileLoop.setTexture(shipHorizEndSunkTex);
                        break;
                    case BoardStates::State_WaterMiss:
                        gameTileLoop.setTexture(waterMissTex);
                        break;
                    case BoardStates::State_Water:
                        gameTileLoop.setTexture(waterTex);
                        break;
                }
            }

            gameTileLoop.setPosition(this->getWindowOffsets().x + xPos, this->getWindowOffsets().y + yPos);
            if(boardState == BoardStates::State_Null){

            }else{
                myWindow.draw(gameTileLoop);
            }
        }
    }
}
BoardStates Board::getBoardState(char ro, int col, vector<Coordinate> &shots){
    for(int i = 0; i < shots.size(); i++){
        //for every attempted shot...
        if ((ro == shots.at(i).getRow()) && (col == shots.at(i).getCol())) {//if shot coords are the coord in the shot from attempted shots
            return shots.at(i).getCoordState();

        }
    }
    return BoardStates::State_Null;
}
bool Board::gridPressed(const Event event) {//checks if user click is in the grid.
    if(grid.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
        return true;
    }else{
        return false;
    }
}

void Board::setWindowOffset(int xOff, int yOff) {
    _windXOffset = xOff;
    _windYOffset = yOff;
}

Vector2i Board::getWindowOffsets() const {
    return {_windXOffset, _windYOffset};
}

