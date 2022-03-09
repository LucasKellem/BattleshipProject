//
// Created by lucas on 11/12/2020.
//

#ifndef FINAL_GAME_H
#define FINAL_GAME_H

#include "Game.h"
#include "Ship.h"
#include "Board.h"
#include "Coordinate.h"
#include "User.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameStates.h"
#include <string>
#include <fstream>
#include <ostream>
#include <string>
#include "RectangularButton.h"
#include "CircularButton.h"

class Game {
public:
    struct highScoreForm{ //Struct used for high score formatting
        string hsName; //Name of user
        int hsScore; //Score of user
    };

    //Title Screen
    sf::Texture titleTex;
    sf::Sprite titleSprite;

    //Exit Button Sprite
    sf::Texture exitTex;
    sf::Sprite exitSprite;

    //Highscore Screen
    sf::Texture highscoreTex;
    sf::Sprite highscoreSprite;

    //Full Screen art vector
    sf::Texture backPatternTex;
    sf::Sprite backPatternSprite;

    //Gameboard Screen
    sf::Texture shotFiredTex;
    sf::Sprite shotFiredSprite;

    //Event Occured, Inform User... Screen
    sf::Texture eventTex;
    sf::Sprite eventSprite;

    //GameOver Screen
    sf::Texture gameoverTex;
    sf::Sprite gameoverSprite;

    //Enter Name Screen
    sf::Texture enterNameText;
    sf::Sprite enterNameSprite;

    //Window Icon Image
    sf::Image windowIcon;

    //Gameboard Currently Selected Coordinate Sprite
    sf::Texture targetTex;
    sf::Sprite targetSprite;
    bool targetVisible; //If TargetSprite Should Be Visible Or Not

    //Game music
    sf::Music mainMenuMusic;
    sf::Music gameMusic;

    //Title Screen interaction
    sf::SoundBuffer interactionBuff;

    //Shot Fired Explosion Sound
    sf::SoundBuffer exploBuff;
    sf::Sound shotSound;

    //Font
    Font myFont;

    //Current gamestate of the applicaton. ie, title screen, name screen, highscore screen, playing, etc
    GameStates gameState;

    //For state_playing user input progression, playstate = 1, ie user selects coord, playstate = 2. user shoots? playstate =...
    int playState;

    //Start Playing Game Button
    RectangularButton playButton;

    //Visit HighScore Screen Button
    RectangularButton highScoreButton;

    //Exit Application Button (Needed For Full Screen Compatibility, Or Else User Has To Press CTRL + ESC)
    RectangularButton exitButton;

    //Music On Button
    RectangularButton musicOnButton;
    sf::Texture musOnTex;
    sf::Sprite musOnSprite;

    //Music Off Button
    RectangularButton musicOffButton;
    sf::Texture musOffTex;
    sf::Sprite musOffSprite;

    //Exit Highscores Button
    RectangularButton exitHighScoreButton;

    //In (Gamestates::State_Playing), The Button To Shoot At Selected Coordinate
    CircularButton fireButton;

    //Our Window
    sf::RenderWindow myWindow;

    //Text For Event Windows, Used To Convey Information To User
    sf::Text whatNow; //text about what to do now
    sf::Text eventHappened; //text about event that happened

    //The Winner of the Game Played...If A Game Is Played
    highScoreForm thisGameWinner;

    //Valid Text Rectangle And Name Of Player Who Lost
    RectangleShape loserBox;
    sf::Text loserName;

    //Valid Text Rectangle And Name Of Player Who Won
    RectangleShape winnerBox;
    Text winnerName;

    //Valid Text Rectangle And Ships Remaining Of Player Who Won (If They Won, Then The Enemy Has Not Sunk All Of Their Ships Yet)
    RectangleShape shipsLeftBox;
    sf::Text shipsRemaining;

    //Valid Text Rectangle And Turns It Took For Winner To Sink All Ships
    RectangleShape turnsBox;
    Text turnsTaken;

    //String Used To Update Window Title
    String titleString;

    //String used for name entering
    String myString;

    //Text used to display name entering
    Text myText;

    int player; //current player

    bool gameOccured;

    int funcMouX; //used to store event mouse coords
    int funcMouY; //used to store event mouse coords
    char funcMouRow; //the converted grid tile storage of funcMouX
    int funcMouCol; //the converted grid tile storage of funcMouY

    //int used to convey information when users shoot
    int funcWasHit; // -9999 is def, 1 is hit and sunk, 2 is hit only, 3 is miss

    //Offsets for fullscreen alignment.
    int xOffset;
    int yOffset;

    Coordinate theShotSelected;

    //Board used to draw user shot textures
    Board board;

    /** @brief initializes game
    * @desc Initializes game by loading textures and sounds
    * @param Player One/User
    * @param Player Two/User
    */
    void startGame(User &, User &){ //Game Initialization

        //Non copyrighted for when I submit.
        if (!mainMenuMusic.openFromFile("resources/Music/menu.wav")){
            cerr << "mainMenuMusic File Not Found" << endl;

            //"Game Menu"
            //Music by Eric Matyas
            //www.soundimage.org
        }
        if (!gameMusic.openFromFile("resources/Music/battleshipMusic.ogg")){
            cerr << "Music File Not Found" << endl;

            //"Battleship"
            //Song by Natalie Kowaliuk
            //love ya kiddo
        }
        //interaction sound
        if (!interactionBuff.loadFromFile("resources/Misc/trans.wav")){
            cerr << "Music File Not Found" << endl;

            //"PowerUp1"
            //Sound by Eric Matyas
            //www.soundimage.org
        }
        //shot fired sound
        if (!exploBuff.loadFromFile("resources/Misc/explosion.ogg")){
            cerr << "Sound File Not Found" << endl;

            //"Explosion 8"
            //Sound Effect by Eric Matyas
            //www.soundimage.org
        }
        if (!windowIcon.loadFromFile("resources/Images/battleship.png")) {
            cerr << "Image Not Found" << endl;
        }
        if( !myFont.loadFromFile("resources/Misc/Pixel Bug.otf")){
            cerr << "Font File Not Found!" << endl;
        }

        //Gamestate Playing Grid Image
        shotFiredTex.loadFromFile("resources/Images/shotPickerScreen.png");
        shotFiredSprite.setTexture(shotFiredTex);

        //event screen texture
        eventTex.loadFromFile("resources/Images/eventScreen.png"); //event screen texture
        eventSprite.setTexture(eventTex); //event screen sprite

        //gameover screen texture
        gameoverTex.loadFromFile("resources/Images/gameover.png"); //gameover screen texture
        gameoverSprite.setTexture(gameoverTex); //gameover screen sprite

        //highscore screen texture
        highscoreTex.loadFromFile("resources/Images/highscoreScreen.png"); //highscore screen texture
        highscoreSprite.setTexture(highscoreTex); //highscore screen sprite

        //entername screen texture
        enterNameText.loadFromFile("resources/Images/entername.png"); //entername screen texture
        enterNameSprite.setTexture(enterNameText); //entername screen sprite

        //target texture
        targetTex.loadFromFile("resources/Images/target.png"); //target texture
        targetSprite.setTexture(targetTex); //target texture

        //exit button texture
        exitTex.loadFromFile("resources/Images/exitButton.png"); //exit button texture
        exitSprite.setTexture(exitTex); //exit button sprite

        //music off button texture
        musOffTex.loadFromFile("resources/Images/mutedButton.png"); //music off button texture
        musOffSprite.setTexture(musOffTex); //music off button sprit

        //music on button texture
        musOnTex.loadFromFile("resources/Images/musicplayButton.png"); //music on button texture
        musOnSprite.setTexture(musOnTex); //music on button sprite

        //Title screen texture
        titleTex.loadFromFile("resources/Images/titlescreen.png");

        //Full Screen Background Art
        backPatternTex.loadFromFile("resources/Images/backgroundpattern.png");

        //myWindow.create(VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),"Welcome To Battleship!");
        myWindow.create(VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),"Welcome To Battleship!", sf::Style::Fullscreen);

        //myWindow.create(VideoMode(1600, 1200),"Welcome To Battleship!"); //Minimum size for images to be to scale

    }

    /** @brief Runs Game
    * @desc Initializes a bunch of variables and contains the main game loop.
    * @param Player One/A user
    * @param Player Two/A user
    * @return returns int exit code
    */
    int run(User &, User &);

    /** @brief Handle Events Based On Gamestate
    * @desc Handles user events/input and updates game
    * @param First Player/User
    * @param Second Player/User
    * @param Current Player/Int
    */
    void HandleEvents(User &, User &, int );

    /** @brief Draws Game Based On GameState
    * @desc Draws game based on events handled by HandleEvents();
    * @param First Player/User
    * @param Second Player/User
    * @param Current Player/Int
    */
    void DrawGame(User &, User &, int );

    /** @brief Event Window That Conveys Information To User
    * @desc Using the parameters, figures out the context of the events that lead up to the function call, then displays
    * information to the user about what they should do.
    * @param WasHit: Int describing what the result of a shot was. 1 = Hit and Sunk. 2 = Hit only. 3 = Miss.
    * @param Current Player/ Int
    * @param First Player/User
    * @param Second Player/User
    */
    void eventWindow(int, int, User &, User &);

    /** @brief Event Window For Game Over
    * @desc Using already stored data in object, describes if the winner had a new highscore or not.
    * @param Bool/Was new highscore.
    */
    void eventWindow(bool);

    /** @brief Informs user to try a new coordinate (shot was already attempted)
    * @desc Informs the current player that they have already tried shooting there, and that they should try a new
    * location.
    * @param Current Player/Int
    * @param First Player/User
    * @param Second Player/User
    */
    void tryNewShotWindow(int, User &, User &);

    /** @brief Checks if any gameover conditions were met
    * @desc Checks if any end game conditions have been met for either player. If not, return false.
    * @param First Player/User
    * @param Second Player/User
    * @param Current Player/Int
    * @return bool (if game is over or not)
    */
    bool gameOverCheck(User &, User &, int );

    /** @brief Initializes gameover information
    * @desc Gets preexisting highscores, then sees if the game winner's score is a new highscore. If it is, it will be
    * written to the highscore file.
    */
    void GameOverInitialization();

    /** @brief Returns a vector of highscores.
    * @desc Reads in all high scores from high score file, then returns vector of these scores.
    * @return vector of high scores
    */
    static vector<highScoreForm> GetHighScores();

    /** @brief Sets target sprite position
    * @desc Converts user click to grid tiles, then places target sprite at currently selected user coordinate.
    * @param Event/User Click
    */
    void currentSelectedTile(Event);

private:

};


#endif //FINAL_GAME_H
