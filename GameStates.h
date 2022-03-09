//
// Created by lucas on 11/12/2020.
//

#ifndef FINAL_GAMESTATES_H
#define FINAL_GAMESTATES_H

//This enum class is used for "GameStates" in the main game running loop. Allows me to easily sort and write code
//for situations that occur in the game...like being at the title screen, playing the game, getting user names,
//displaying the game over information, highscore information, etc

enum class GameStates {
    State_Title = 0, //Title Screen
    State_HighScore, //High Score Screen
    State_Names, //Getting User Names Screen
    State_Playing, //Playing The Game State
    State_Finished //Game Has Been Ended, Someone Won
};


#endif //FINAL_GAMESTATES_H
