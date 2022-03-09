//
// Created by lucas on 11/13/2020.
//

#ifndef FINAL_BOARDSTATES_H
#define FINAL_BOARDSTATES_H

//This enum class is used for "BoardStates", which allow me to have a custom setting for coordinate pieces to keep
//track of what texture a tile should be, and if the tile has been hit or not. I found it a convenient method of
//tracking texture use.


enum class BoardStates {
    State_Water = 0, //The tile is water. Or visibility is 0 and is masking a ship. Who knows? Not me.
    State_WaterMiss, //The tile was water, the user shot at it, and missed all ships. Nice shot, rook.
    State_Null, //Used when I don't want to draw a sprite, just leave the tile untouched as the default image from the "shotPicker.png" image for loadtime.
    State_midShip, //The tile is a vertical middle ship piece
    State_midShipSunk, //The vertical middle ship piece was obliterated
    State_beginShip, //The tile is a vertical beginning-of-ship piece
    State_beginShipSunk, //The vertical beginning of ship piece was obliterated
    State_endShip, //The tile is a vertical end-of-ship piece
    State_endShipSunk, //The vertical end of ship piece was obliterated
    State_midHorizShip, //The tile is a horizontal middle-of-ship piece
    State_midHorizShipSunk, //The horizontal middle-of-ship piece was obliterated
    State_beginHorizShip, //The tile is a horizontal beginning-of-ship piece
    State_beginHorizShipSunk, //The horizontal beginning of ship piece was obliterated
    State_endHorizShip, //The tile is a horizontal end-of-ship piece
    State_endHorizShipSunk //The horizontal end of ship piece was obliterated
};


#endif //FINAL_BOARDSTATES_H
