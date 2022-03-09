//
// Created by lucas on 11/12/2020.
//

#include "Game.h"

using namespace std;
using namespace sf;

int Game::run( User &userShips, User &user2Ships ) { //Loop all of it inside here, main game loop
    gameOccured = false;
    //Activating vertical synchronization will limit the number of frames displayed to the refresh rate of the monitor.
    //This can avoid some visual artifacts, and limit the framerate to a good value (but not constant across different computers).
    myWindow.setVerticalSyncEnabled(true);

    int windowX = (int)sf::VideoMode::getDesktopMode().width;
    int windowY = (int)sf::VideoMode::getDesktopMode().height;

    //Offsets for full screen compatibility
    xOffset = (windowX - 1600) / 2;
    yOffset = (windowY - 1200) / 2;
    //I know there is some use of "magic numbers" in there. Oops. My first version of the game used a window locked
    //@ 1600x1200, and thus all graphics are also 1600x1200, so I needed to save these sizes and add with the offset.

    //Used to scale background vector art for full screen.
    Vector2u TextureSize = backPatternTex.getSize(); //Get size of texture.
    Vector2u WindowSize = myWindow.getSize(); //Get size of window.

    //Scales for background vector art
    float ScaleX = (float) WindowSize.x / TextureSize.x; //Calculate scale.
    float ScaleY = (float) WindowSize.y / TextureSize.y; //Calculate scale.

    //For background art to fill full screen.
    backPatternSprite.setTexture(backPatternTex); //Set texture
    backPatternSprite.setScale(ScaleX, ScaleY); //Set scale.

    //The sprite of the background for the phase of the game where users are picking spots on board.
    //shotFiredSprite.setPosition(0, 0); Default Positions of these 3 sprites
    shotFiredSprite.setPosition(xOffset + 0, yOffset + 0);
    enterNameSprite.setPosition(xOffset + 0, yOffset + 0);
    eventSprite.setPosition(xOffset + 0, yOffset + 0);

    //set font for event window texts
    eventHappened.setFont(myFont);
    whatNow.setFont(myFont);

    //set sound for the shot fired action
    shotSound.setBuffer(exploBuff);
    shotSound.setVolume(50.f);

    //Initialize board textures
    board.initializeTextures(xOffset, yOffset);

    //Main menu music
    mainMenuMusic.setVolume(50.f); //I find 50.f to be a fair volume. 100.f is ear shattering. Range is 0(mute)-100(full)
    //Considered adding an interactable volume slide button, but I couldn't get it to look right so I decided against it.
    mainMenuMusic.setLoop(true); //Loop the mainMenuMusic
    mainMenuMusic.play(); //Play that bad boy

    //set icon for main window
    myWindow.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());

    //Exit Button Pos
    exitSprite.setPosition(windowX - (xOffset / 2) -(exitSprite.getGlobalBounds().width / 2), (windowY / 2) - 202); 
    exitButton.setButton(Vector2f(200, 85),exitSprite.getPosition());
    //More magic numbers, sorry. If I was doing this in the future, I would have a const or global size for all buttons to follow.

    //Music Off Button Pos
    musOffSprite.setPosition(windowX - (xOffset / 2) - 101, exitSprite.getPosition().y + 101);
    musicOffButton.setButton(Vector2f(100, 100),musOffSprite.getPosition());

    //Music On Button Pos
    musOnSprite.setPosition(windowX - (xOffset / 2) + 1, exitSprite.getPosition().y + 101);
    musicOnButton.setButton(Vector2f(100, 100),musOnSprite.getPosition());

    //set sizes for gameover window
    Vector2f gameOverSizes(602, 106);
    winnerBox.setSize(gameOverSizes);
    loserBox.setSize(gameOverSizes);
    shipsLeftBox.setSize(gameOverSizes);
    turnsBox.setSize(gameOverSizes);

    //set positions for gameover window
    gameoverSprite.setPosition(xOffset + 0, yOffset + 0);
    winnerBox.setPosition(xOffset + 644, yOffset + 202);
    loserBox.setPosition(xOffset + 630, yOffset + 335);
    shipsLeftBox.setPosition(xOffset + 753, yOffset + 566);
    turnsBox.setPosition(xOffset + 593, yOffset + 698);

    //initialize buttons
    playButton.setButton(Vector2f(770, 100), Vector2f(xOffset + 430, yOffset + 350));
    highScoreButton.setButton(Vector2f(1120, 90), Vector2f(xOffset + 280, yOffset + 485));
    fireButton.setButton(80, Vector2f(xOffset + 1325, yOffset + 696));
    exitHighScoreButton.setButton(Vector2f(242, 148), Vector2f(xOffset + 0, yOffset + 416));

    //Everytime new game starts...
    player = 1; //initialize player to player 1
    gameState = GameStates::State_Title; //initialize gamestate
    playState = 1; //Initialize playState (used in Gamestates::State_Playing) for player event progression
    targetVisible = false; //Initialize targetVisible bool

    //Main Game Loop
    while(myWindow.isOpen()){
        DrawGame(userShips, user2Ships, player); //Draw the game
        HandleEvents(userShips, user2Ships, player); //Update and handle events. Yeah yeah yeah I combined them leave me alone
    }
    return 0;
}
void Game::eventWindow(int wasHit, int currPlayer, User &user1, User &user2){ //Event Window To Convey Information To Player
    //window to display text saying what happened, what to do now
    myWindow.clear(Color::White);
    RectangleShape validTextPos;
    validTextPos.setSize(Vector2f(1084, 223)); //Size of text box (these magic numbers are from the eventwindow image, sorry)
    validTextPos.setPosition(xOffset + 262, yOffset + 176);
    validTextPos.setFillColor(Color(0, 0, 0, 0)); //We want this to be transparent

    //text about event that happened
    eventHappened.setFillColor(Color::Black);
    eventHappened.setCharacterSize(50);

    //text about what to do now
    whatNow.setFillColor(Color::Black);
    eventHappened.setCharacterSize(50);

    if(wasHit == 1){//this indicates a hit AND a sink
        switch(currPlayer){
            case 1:
                eventHappened.setString("Hit! And Sunk!");
                whatNow.setString(user2.getName() + "'s Turn!");
                break;
            case 2:
                eventHappened.setString("Hit! And Sunk!");
                whatNow.setString(user1.getName() + "'s Turn!");
                break;
        }
    }else if(wasHit == 2){//this indicates a hit ONLY, go again.
        eventHappened.setString("Hit! Go Again!");
        switch(currPlayer){
            case 1:{
                whatNow.setString(user1.getName() + "'s Turn!");
                break;
            }
            case 2:{
                whatNow.setString(user2.getName() + "'s Turn!");
                break;
            }
        }
    }else if(wasHit == 5){ //This indicates that a hit and sunk occured, and that a game over conditon was met. Someone won.
        eventHappened.setString("Hit! And Sunk!");
        whatNow.setString("Game Over!");
    }else if(wasHit == 3){//this indicates a miss
        switch(currPlayer){
            case 1:{
                eventHappened.setString("Miss!");
                whatNow.setString(user2.getName() + "'s Turn!");
                break;
            }
            case 2: {
                eventHappened.setString("Miss!");
                whatNow.setString(user1.getName() + "'s Turn!");
                break;
            }
        }
    }

    //position of text
    eventHappened.setOrigin(eventHappened.getLocalBounds().width / 2,eventHappened.getLocalBounds().height / 2);
    eventHappened.setPosition(Vector2f((xOffset + 262 + (validTextPos.getLocalBounds().width / 2)), (yOffset + 176 + (validTextPos.getLocalBounds().height / 3))));
    whatNow.setOrigin(whatNow.getLocalBounds().width / 2,whatNow.getLocalBounds().height / 2);
    whatNow.setPosition(Vector2f((xOffset + 262 + (validTextPos.getLocalBounds().width / 2)), (yOffset + 176 + (validTextPos.getLocalBounds().height / 3) * 2)));

    //draw everything.
    myWindow.draw(backPatternSprite);
    myWindow.draw(exitSprite);
    myWindow.draw(exitButton.getButton());
    myWindow.draw(eventSprite);
    myWindow.draw(musicOffButton.getButton());
    myWindow.draw(musOffSprite);
    myWindow.draw(musicOnButton.getButton());
    myWindow.draw(musOnSprite);
    myWindow.draw(validTextPos);
    myWindow.draw(eventHappened);
    myWindow.draw(whatNow);
    myWindow.display();
    sleep(seconds(2));//have a small sleep so that user can read what happened.
}
void Game::eventWindow(bool wasNewHS) { //Event Window To Inform Player If They Had A New High Score Or Not
    myWindow.clear(Color::White);
    
    RectangleShape validTextPos;
    validTextPos.setSize(Vector2f(1084, 223));
    validTextPos.setPosition(xOffset + 262, yOffset + 176);
    validTextPos.setFillColor(Color(0, 0, 0, 0));

    //text about event that happened
    eventHappened.setFillColor(Color::Black);
    eventHappened.setCharacterSize(50);

    //text about what to do now
    whatNow.setFillColor(Color::Black);
    eventHappened.setCharacterSize(50);

    if(wasNewHS){
        whatNow.setString("Congratulations! New High Score!");
        eventHappened.setString("Great Job, Captain!");
    }else{
        whatNow.setString("Unfortunately, Not A New High Score!");
        eventHappened.setString("Better Luck Next Time, Captain!");
    }
    //position of text
    eventHappened.setOrigin(eventHappened.getLocalBounds().width / 2,eventHappened.getLocalBounds().height / 2);
    eventHappened.setPosition(Vector2f((xOffset + 262 + (validTextPos.getLocalBounds().width / 2)), (yOffset + 176 + (validTextPos.getLocalBounds().height / 3))));
    whatNow.setOrigin(whatNow.getLocalBounds().width / 2,whatNow.getLocalBounds().height / 2);
    whatNow.setPosition(Vector2f((xOffset + 262 + (validTextPos.getLocalBounds().width / 2)), (yOffset + 176 + (validTextPos.getLocalBounds().height / 3) * 2)));

    //draw everything.
    myWindow.draw(backPatternSprite);
    myWindow.draw(exitSprite);
    myWindow.draw(exitButton.getButton());
    myWindow.draw(eventSprite);
    myWindow.draw(musicOffButton.getButton());
    myWindow.draw(musOffSprite);
    myWindow.draw(musicOnButton.getButton());
    myWindow.draw(musOnSprite);
    myWindow.draw(validTextPos);
    myWindow.draw(eventHappened);
    myWindow.draw(whatNow);
    myWindow.display();
    sleep(seconds(2));//have a small sleep so that user can read what happened.
}
void Game::tryNewShotWindow(int currPlayer, User &user1, User &user2){ //Window to let user know that they have already shot at the currently selected location...try a new one.
    //window to display text saying what happened, what to do now
    myWindow.clear(Color::White);
    
    //Rectangle used for valid text placement
    RectangleShape validTextPos;
    validTextPos.setSize(Vector2f(1084, 223));
    validTextPos.setPosition(xOffset + 262, yOffset + 176);
    validTextPos.setFillColor(Color(0, 0, 0, 0));

    //text about event that happened
    eventHappened.setFillColor(Color::Black);
    eventHappened.setCharacterSize(50);

    //text about what to do now
    whatNow.setFillColor(Color::Black);
    eventHappened.setCharacterSize(40);

    eventHappened.setString("Invalid Shot Location! \nTry Picking A New Location!");
    switch(currPlayer){
        case 1: {
            whatNow.setString(user1.getName() + "'s Turn!");
            break;
        }
        case 2: {
            whatNow.setString(user2.getName() + "'s Turn!");
            break;
        }
    }

    //position of text
    eventHappened.setOrigin(eventHappened.getLocalBounds().width / 2,eventHappened.getLocalBounds().height / 2);
    eventHappened.setPosition(Vector2f((xOffset + 262 + (validTextPos.getLocalBounds().width / 2)), (yOffset + 176 + (validTextPos.getLocalBounds().height / 4))));
    whatNow.setOrigin(whatNow.getLocalBounds().width / 2,whatNow.getLocalBounds().height / 2);
    whatNow.setPosition(Vector2f((xOffset + 262 + (validTextPos.getLocalBounds().width / 2)), (yOffset + 176 + (validTextPos.getLocalBounds().height / 4) * 3)));

    //draw everything.
    myWindow.draw(backPatternSprite);
    myWindow.draw(exitSprite);
    myWindow.draw(exitButton.getButton());
    myWindow.draw(eventSprite);
    myWindow.draw(musicOffButton.getButton());
    myWindow.draw(musOffSprite);
    myWindow.draw(musicOnButton.getButton());
    myWindow.draw(musOnSprite);
    myWindow.draw(validTextPos);
    myWindow.draw(eventHappened);
    myWindow.draw(whatNow);
    myWindow.display();
    sleep(seconds(2));//have a small sleep so that user can read what happened.
}
void Game::HandleEvents(User &userShips, User &user2Ships, int currPlayer) {
    switch (gameState) {
        case GameStates::State_Title: { //The user is at the title screen.
            Event titleEvent;
            while (myWindow.pollEvent(titleEvent)) { // ask the window if any events occurred
                if (titleEvent.type == Event::Closed) { // if event type is a closed event
                    // i.e. they clicked the X on the window
                    myWindow.close();// then close our window
                } else if (titleEvent.type == sf::Event::MouseButtonPressed) { //If user clicks...
                    if (titleEvent.mouseButton.button == sf::Mouse::Left) { //If it is a left click
                        //Button interaction sound
                        sf::Sound interactionSound;
                        interactionSound.setBuffer(interactionBuff);
                        interactionSound.setVolume(50.f);
                        
                        if (playButton.isClicked(titleEvent)) { //if the user clicks the play button...
                            //play sound effect
                            interactionSound.play();

                            sleep(seconds(1.5));//have a small sleep for smoother transition

                            //set gamestate to Names to get user input names.
                            gameState = GameStates::State_Names;
                        } else if (highScoreButton.isClicked(titleEvent)) { //if the user clicks highscore button...
                            //play sound effect
                            interactionSound.play();
                            sleep(seconds(1.5));//have a small sleep for smoother transition
                            
                            //set gamestate to high score
                            gameState = GameStates::State_HighScore;
                        } else if (exitButton.isClicked(titleEvent)) { //if the user clicks exit button...
                            myWindow.close();
                            exit(-1);
                            break;
                        }else if (musicOffButton.isClicked(titleEvent)) { //if the user clicks music off button...
                            mainMenuMusic.setVolume(0); //Mute music
                            gameMusic.setVolume(0); //Mute music
                            break;
                        }else if (musicOnButton.isClicked(titleEvent)) { //if the user clicks music on button...
                            mainMenuMusic.setVolume(50); //Set volume to default (50.f)
                            gameMusic.setVolume(50); //Set volume to default (50.f)
                            break;
                        }
                    }
                }
                }
                break;
            }
        case GameStates::State_Names: { //User/s are entering names.
            bool enterPressed = false; //Check if enter has been pressed (thus locking name in)
            std::locale locale; //Used for char converting to name string
            Event stringEvent; //The event to watch for
            while (myWindow.pollEvent(stringEvent) && !enterPressed) { //While the user hasn't pressed enter and window polling event
                if (stringEvent.type == Event::Closed) { //If user closes...
                    myWindow.close();
                    exit(-1);
                }else if(stringEvent.type == Event::MouseButtonPressed){ //If user presses mouse...
                    if(stringEvent.mouseButton.button == Mouse::Left){ //If it is a left click...
                        if (exitButton.isClicked(stringEvent)) { //If exit button is pressed...
                            myWindow.close();
                            exit(-1);
                            break;
                        }else if (musicOffButton.isClicked(stringEvent)){ //If music off button is pressed...
                            mainMenuMusic.setVolume(0); //Mute
                            gameMusic.setVolume(0); //Mute
                            break;
                        }else if (musicOnButton.isClicked(stringEvent)){ //If music on button is pressed...
                            mainMenuMusic.setVolume(50); //Unmute
                            gameMusic.setVolume(50); //Unmute
                            break;
                        }
                    }
                } else if (stringEvent.type == Event::KeyPressed) { //If key is pressed...
                    if (stringEvent.key.code == sf::Keyboard::BackSpace) { //if key pressed is backspace...
                        if (!myString.isEmpty()) { //If the string is not empty
                            myString.erase(myString.getSize() - 1, 1); //Erase the last char in string
                            enterPressed = false; //Enter ain't pressed
                        } else {
                            enterPressed = false; //Enter ain't pressed and string was empty.
                        }
                    } else if (stringEvent.key.code == Keyboard::Enter) { //if key pressed is enter...
                        if (player == 1) { //if player is player 1
                            userShips.setName(myString.toAnsiString(locale)); //set their name with conversion of string
                        } else { //if player is player 2
                            user2Ships.setName(myString.toAnsiString(locale)); //set their name with conversion of string
                        }
                        myWindow.clear(); //TODO:Evaluate if this is needed
                        enterPressed = true; //Enter has been pressed
                    }
                } else if ((stringEvent.type == Event::TextEntered) &&
                           ((stringEvent.text.unicode > 64) && (stringEvent.text.unicode < 128))) { //if text is entered (and is valid text)
                    myString.insert(myString.getSize(), stringEvent.text.unicode); //insert the key into string
                    enterPressed = false; //Enter aint pressed

                }
                myText.setOrigin(myText.getLocalBounds().width / 2, myText.getLocalBounds().height / 2); //Update origin
            }
            if (enterPressed) { //Enter has been pressed
                switch (player) {
                    case 1: { //If player is player one
                        if (!userShips.getName().empty()) { //if their name isn't empty (failsafe)
                            player = 2; //Change player
                            myString.clear(); //Clear myString
                            break;
                        }
                        break;
                    }
                    case 2: { //If player is player two
                        if (!user2Ships.getName().empty()) { //if their name isn't empty (failsafe)
                            player = 1; //set player back to player 1
                            mainMenuMusic.pause(); //pause main menu music
                            gameMusic.play(); //start game-play music
                            //game-playing music looped
                            gameMusic.setLoop(true);
                            myString.clear();
                            gameState = GameStates::State_Playing; //Set gamestate to playing!
                            break;
                        }
                        break;
                    }
                }
            }
            break;
        }
        case GameStates::State_Playing: { //Users are playing battleship now
            bool actionHappened = false; // A check for event progression
            while (!actionHappened) { //while an action has not occurred
                sf::Event nEvent;
                while (myWindow.pollEvent(nEvent)) {
                    bool switchPlayer = false; //a check to switch player
                    if (nEvent.type == Event::Closed) { //if user closes window
                        myWindow.close();
                        exit(-1);
                        break;
                    }else if (nEvent.type == Event::MouseButtonPressed) { //if user clicked mouse...
                        if (nEvent.mouseButton.button == sf::Mouse::Left) { //if it is a left click...
                            if (exitButton.isClicked(nEvent)) { //if exit button is clicked...
                                actionHappened = true;
                                myWindow.close();
                                exit(-1);
                                break;
                            } else if (musicOffButton.isClicked(nEvent)) { //if music off button is clicked...
                                mainMenuMusic.setVolume(0); //mute
                                gameMusic.setVolume(0); //mute
                                break;
                            } else if (musicOnButton.isClicked(nEvent)) { //if music on button is clicked...
                                mainMenuMusic.setVolume(50); //unmute
                                gameMusic.setVolume(50); //unmute
                                break;
                            } else if (player ==
                                       1) { //ok so those buttons were not pressed. lets see what happened. if player is player one
                                switch (playState) { //used for event progression
                                    case 1: { //we need a coordinate locked in.
                                        if (board.gridPressed(nEvent)) { //if user clicks valid tile in grid
                                            funcMouX = nEvent.mouseButton.x; //store event mouse coords
                                            funcMouY = nEvent.mouseButton.y; //store event mouse coords
                                            currentSelectedTile(nEvent); //sets the target sprite location
                                            targetVisible = true; //set the target sprite to visible
                                            funcWasHit = -9999; //default
                                            playState = 2; //advance in chain of events!
                                            actionHappened = true; //action did happen!
                                        } else {
                                            playState = 1; //DO NOT advance in chain of events
                                            targetVisible = false; //target ain't visible
                                        }
                                        break;
                                    }
                                    case 2: { //we want user to either pick new location or shoot with locked in location
                                        if ((!userShips.alreadyAttempted(funcMouX, funcMouY, xOffset, yOffset) &&
                                             (fireButton.isClicked(
                                                     nEvent)))) { //if the coordinates selected have not already been attempted AND the fire button is clicked...
                                            funcMouRow = 'A' + (int) ((funcMouY - 201 - yOffset) /
                                                                      100); //Convert mouse coordinates to grid tiles
                                            funcMouCol = (int) ((funcMouX - 201 - xOffset) /
                                                                100); //Convert mouse coordinates to grid tiles
                                            //This is -201 because 200 is the position where the grid starts, and 1 is for the width of the lines.

                                            theShotSelected.setCoord(funcMouRow,
                                                                     funcMouCol); //member function of shot, sets coord
                                            Coordinate shot; //new shot
                                            shot.setCoord(funcMouRow, funcMouCol); //set shot info
                                            shotSound.play(); //play "shot fired" sound

                                            shotFiredBundle shotBundle; //new object of "shot fired bundle", which was made as a unique way for me to return multiple things from one function
                                            shotBundle = user2Ships.shotWasFired(funcMouRow,
                                                                                 funcMouCol); //gets information. user2ships was attacked, see what happened.
                                            funcWasHit = shotBundle.hitCondition; //for event window, checks if it was a hit
                                            shot.setCoordState(
                                                    shotBundle.boardState); //set the boardstate of "shot" for sprite drawing
                                            userShips.addNewShot(
                                                    shot); //The user vector of shots holds boardstates for drawing, and coordinates of already attempted shots.
                                            targetVisible = false; //Target should no longer be visible.
                                            switchPlayer = true; //We can switch player
                                            actionHappened = true; //An action did happen
                                        } else if ((userShips.alreadyAttempted(funcMouX, funcMouY, xOffset, yOffset)) &&
                                                   (fireButton.isClicked(
                                                           nEvent))) { //The shot location has already been attempted.
                                            tryNewShotWindow(currPlayer, userShips,
                                                             user2Ships); //Let them know to pick new location.
                                            actionHappened = true; //an action did happen
                                            playState = 1; //go back to first playstate. we need a new coordinate
                                        } else if (board.gridPressed(nEvent)) { //If they click a new point
                                            funcMouX = nEvent.mouseButton.x; //store event coords
                                            funcMouY = nEvent.mouseButton.y; //store event coords
                                            currentSelectedTile(nEvent); //set target sprite position
                                            targetVisible = true; //target should be visible
                                            funcWasHit = -9999; //default
                                            playState = 2; //loop back to this playstate
                                            actionHappened = true; //an action happened
                                        } else { //button was not clicked
                                            playState = 2; //loop back to here again.
                                        }
                                        break;
                                    }
                                }
                            } else { //player is player two
                                switch (playState) { //used for event progression
                                    case 1: { //we need a coordinate locked in.
                                        if (board.gridPressed(nEvent)) { //if user clicks valid tile in grid
                                            funcMouX = nEvent.mouseButton.x; //store event mouse coords
                                            funcMouY = nEvent.mouseButton.y; //store event mouse coords
                                            currentSelectedTile(nEvent); //sets the target sprite location
                                            targetVisible = true; //set the target sprite to visible
                                            funcWasHit = -9999; //default
                                            playState = 2; //advance in chain of events!
                                            actionHappened = true; //action did happen!
                                        } else {
                                            playState = 1; //DO NOT advance in chain of events
                                            targetVisible = false; //target ain't visible
                                        }
                                        break;
                                    }
                                    case 2: { //we want user to either pick new location or shoot with locked in location
                                        if ((!user2Ships.alreadyAttempted(funcMouX, funcMouY, xOffset, yOffset) &&
                                             (fireButton.isClicked(
                                                     nEvent)))) { //if the coordinates selected have not already been attempted AND the fire button is clicked...
                                            funcMouRow = 'A' + (int) ((funcMouY - 201 - yOffset) /
                                                                      100); //Convert mouse coordinates to grid tiles
                                            funcMouCol = (int) ((funcMouX - 201 - xOffset) /
                                                                100); ////Convert mouse coordinates to grid tiles
                                            //This is -201 because 200 is the position where the grid starts, and 1 is for the width of the lines.

                                            theShotSelected.setCoord(funcMouRow,
                                                                     funcMouCol); //member function of shot, sets coord
                                            Coordinate shot; //new shot
                                            shot.setCoord(funcMouRow, funcMouCol); //set shot info
                                            shotSound.play(); //play "shot fired" sound

                                            shotFiredBundle shotBundle; //new object of "shot fired bundle", which was made as a unique way for me to return multiple things from one function
                                            shotBundle = userShips.shotWasFired(funcMouRow,
                                                                                funcMouCol); //for event window, checks if it was a hit
                                            funcWasHit = shotBundle.hitCondition; //for event window, checks if it was a hit
                                            shot.setCoordState(
                                                    shotBundle.boardState); //set the boardstate of "shot" for sprite drawing
                                            user2Ships.addNewShot(
                                                    shot); //The user vector of shots holds boardstates for drawing, and coordinates of already attempted shots.
                                            targetVisible = false; //target should not be visible
                                            switchPlayer = true; //we can switch player
                                            actionHappened = true; //action did happen
                                        } else if (
                                                (user2Ships.alreadyAttempted(funcMouX, funcMouY, xOffset, yOffset)) &&
                                                (fireButton.isClicked(
                                                        nEvent))) { //The shot location has already been attempted.
                                            tryNewShotWindow(currPlayer, userShips,
                                                             user2Ships); //Let them know to pick new location.
                                            actionHappened = true; //an action did happen
                                            playState = 1; //go back to first playstate. we need a new coordinate
                                        } else if (board.gridPressed(nEvent)) { //If they click new point
                                            funcMouX = nEvent.mouseButton.x; //store event coords
                                            funcMouY = nEvent.mouseButton.y; //store event coords
                                            currentSelectedTile(nEvent); //set target sprite position
                                            targetVisible = true; //target should be visible
                                            funcWasHit = -9999; //default
                                            playState = 2; //loop back to this playstate
                                            actionHappened = true; //an action happened
                                        } else { //button was not clicked
                                            playState = 2; //loop back to here again.
                                        }
                                        break;
                                    }
                                }
                            }
                        }if (switchPlayer) { //If switch player condition was met
                                if (gameOverCheck(userShips, user2Ships, player)) { //check if game is over
                                    //game over condition was met!
                                    gameState = GameStates::State_Finished; //set gamestate to game over.
                                } else{ //game is not over
                                    if (player == 1) { //Current Player is Player 1
                                        if (funcWasHit == 1 || funcWasHit == 3) { //Hit and Sink or a Miss
                                            eventWindow(funcWasHit, currPlayer, userShips, user2Ships); //Event window to inform user
                                            player = 2; //change player
                                            playState = 1; //set playState
                                        } else if (funcWasHit == 2) { //Hit AND continue
                                            eventWindow(funcWasHit, currPlayer, userShips, user2Ships); //Event window to inform user
                                            player = 1; //keep player as player 1
                                            playState = 1; //set playState
                                        }
                                    } else { //Current Player is Player 2
                                        if (funcWasHit == 1 || funcWasHit == 3) { //Hit and Sink or a Miss
                                            eventWindow(funcWasHit, currPlayer, userShips, user2Ships); //Event window to inform user
                                            player = 1; //change player
                                            playState = 1; //set playState
                                        } else if (funcWasHit == 2) { //Hit and continue
                                            eventWindow(funcWasHit, currPlayer, userShips, user2Ships); //Event window to inform user
                                            player = 2; //keep player as player 2
                                            playState = 1; //set playState
                                        }
                                    }
                                }

                            }
                    }
                }
            }
            /*Let me tell you. I spent probably 5 days or 30 hours trying to figure out why my program would infinitely
             * loop between GameStates::State_Name and GameStates::State_Playing, or GameStates::State_Playing and
             * GameStates::State_Finished. The window would rapidly switch between the images of both of the gamestates,
             * at a speed that would give someone a seizure. The culprit? This damn break; statement.
             * Imagine my frustration when several drafts of hundreds of lines of different code combinations were
             * made and then thrown away all because I didn't include the break statement. Yikes. Learned a valuable
             * lesson.
             */
            break; //Annoying break that I have an unhealthy amount of disdain for
        }
        case GameStates::State_Finished: { //Game is over!
            GameOverInitialization(); //Initialize game over screen
            Event newUserEvent; //new event
            while (myWindow.pollEvent(newUserEvent)) { //while polling event
                switch (newUserEvent.type) {
                    case Event::Closed: { //if user closes window...
                        myWindow.close();
                        exit(-1);
                        break;
                    }
                    case Event::MouseButtonPressed: { //if user presses mouse...
                        if (newUserEvent.mouseButton.button == sf::Mouse::Left) { //if it is a left click...
                            if (exitButton.isClicked(newUserEvent)) { //if exit button is clicked...
                                myWindow.close();
                                exit(-1);
                                break;
                            }else if (musicOffButton.isClicked(newUserEvent)) { //if music off button is clicked...
                                mainMenuMusic.setVolume(0); //mute
                                gameMusic.setVolume(0); //mute
                                break;
                            }else if (musicOnButton.isClicked(newUserEvent)) { //if music on button is clicked...
                                mainMenuMusic.setVolume(50); //unmute
                                gameMusic.setVolume(50); //unmute
                                break;
                            }
                            break;
                        }
                    }
                }
            }
            gameOccured = true;
            gameState = GameStates::State_HighScore;
            break;
        }
        case GameStates::State_HighScore: { //User is in highscore screen
            if(gameOccured){
                sleep(seconds(3));
                exit(1);
            }else{
                Event newUserEvent; //new event
                while (myWindow.pollEvent(newUserEvent)) { //while polling event
                    switch (newUserEvent.type) {
                        case Event::Closed: { //if user closes window...
                            myWindow.close();
                            exit(-1); //skidaddle
                            break;
                        }
                        case Event::MouseButtonPressed: { //if user clicks mouse...
                            if (newUserEvent.mouseButton.button == sf::Mouse::Left) { //if user left clicks...
                                if (exitButton.isClicked(newUserEvent)) { //if exit button is clicked...
                                    myWindow.close();
                                    exit(-1);
                                    break;
                                }else if (musicOffButton.isClicked(newUserEvent)) { //if music off button is clicked...
                                    mainMenuMusic.setVolume(0); //mute
                                    gameMusic.setVolume(0); //mute
                                    break;
                                }else if (musicOnButton.isClicked(newUserEvent)) { //if music on button is clicked...
                                    mainMenuMusic.setVolume(50); //unmute
                                    gameMusic.setVolume(50); //unmute
                                    break;
                                }else if(exitHighScoreButton.isClicked(newUserEvent)){ //if exit high score button is clicked...
                                    gameState = GameStates::State_Title; //set gamestate to gamestate State_Title
                                    break;
                                }
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}
void Game::DrawGame(User &userShips, User &user2Ships, int currPlayer) {
    switch (gameState) {
        case GameStates::State_Title: { // Draw the title screen here
            myWindow.clear();

            //Check for hovering over buttons
            Mouse usrMouse;
            playButton.isHovering(usrMouse, myWindow);
            highScoreButton.isHovering(usrMouse, myWindow);
            exitButton.isHovering(usrMouse, myWindow);
            musicOffButton.isHovering(usrMouse, myWindow);
            musicOnButton.isHovering(usrMouse, myWindow);

            myWindow.requestFocus();

            //title screen background
            titleSprite.setTexture(titleTex, true);
            titleSprite.setPosition(xOffset + 0, yOffset + 0);


            //draw everything
            myWindow.draw(backPatternSprite);
            myWindow.draw(titleSprite);
            myWindow.draw(playButton.getButton());
            myWindow.draw(highScoreButton.getButton());
            myWindow.draw(exitSprite);
            myWindow.draw(exitButton.getButton());
            myWindow.draw(musicOffButton.getButton());
            myWindow.draw(musOffSprite);
            myWindow.draw(musicOnButton.getButton());
            myWindow.draw(musOnSprite);

            //Display window
            myWindow.display();
            break;
        }
        case GameStates::State_Names: { //User is entering name
            //Clear window
            myWindow.clear();

            //Check for hovering buttons
            Mouse usrMouse;
            exitButton.isHovering(usrMouse, myWindow);
            musicOffButton.isHovering(usrMouse, myWindow);
            musicOnButton.isHovering(usrMouse, myWindow);

            //Update window title
            if(player == 1){
                //If current player is player one...
                myWindow.setTitle("Player One, Enter Your Name!");
            }else{
                //If current player is player two...
                myWindow.setTitle("Player Two, Enter Your Name!");
            }

            //"Imaginary" rectangle I use to get bounds of valid text positioning.
            RectangleShape textRect;
            textRect.setPosition(xOffset + 470, yOffset + 445);
            textRect.setSize(Vector2f(900, 320));
            textRect.setFillColor(Color::Transparent); //We don't want it to be visible

            //Set characteristics of myText
            myText.setFont(myFont);
            myText.setCharacterSize(50);
            myText.setFillColor(Color::Black);

            //Since text is updated constantly, origin/position will need to update too.
            myText.setOrigin(myText.getLocalBounds().width / 2, myText.getLocalBounds().height / 2);
            myText.setPosition(Vector2f((xOffset + 360 + (textRect.getLocalBounds().width / 2)),(yOffset + 445 + (textRect.getLocalBounds().height / 2))));

            //Update text
            myText.setString(myString);

            //Draw background, text rectangle, and text.
            myWindow.draw(backPatternSprite);
            myWindow.draw(exitSprite);
            myWindow.draw(exitButton.getButton());
            myWindow.draw(enterNameSprite);
            myWindow.draw(musicOffButton.getButton());
            myWindow.draw(musOffSprite);
            myWindow.draw(musicOnButton.getButton());
            myWindow.draw(musOnSprite);
            myWindow.draw(textRect);
            myWindow.draw(myText);

            //Display
            myWindow.display();
            break;
        }
        case GameStates::State_Playing: { //User is playing the game
            //Clear window
            myWindow.clear();

            //Check current player to update window title
            if (player == 1) {
                //Update window title
                titleString = userShips.getName() + "'s Turn";
            } else {
                //Update window title
                titleString = user2Ships.getName() + "'s Turn";
            }

            //Update Window title
            myWindow.setTitle(titleString);

            //draw everything
            myWindow.draw(backPatternSprite);
            //Draw the main image
            myWindow.draw(shotFiredSprite);
            //Member function of board. Draws the sprites for squares that have been shot by the current player.
            board.drawBoard(myWindow, userShips, user2Ships, currPlayer, backPatternSprite);
            //If targetsprite should be visible...
            if(targetVisible){
                //Draw it.
                myWindow.draw(targetSprite);
            }
            myWindow.draw(fireButton.getButton()); //Draw firebutton
            myWindow.draw(exitSprite);
            myWindow.draw(exitButton.getButton());
            myWindow.draw(musicOffButton.getButton());
            myWindow.draw(musOffSprite);
            myWindow.draw(musicOnButton.getButton());
            myWindow.draw(musOnSprite);

            //Display window
            myWindow.display();
            break;
        }
        case GameStates::State_Finished: { //Game is over!
            //Clear window
            myWindow.clear();

            //Check button hovering
            Mouse usrMouse;
            exitButton.isHovering(usrMouse, myWindow);
            musicOffButton.isHovering(usrMouse, myWindow);
            musicOnButton.isHovering(usrMouse, myWindow);

            //winnerBox.setPosition(xOffset + 644, yOffset + 202);
            //loserBox.setPosition(xOffset + 630, yOffset + 335);
            //shipsLeftBox.setPosition(xOffset + 753, yOffset + 566);
            //turnsBox.setPosition(xOffset + 593, yOffset + 698);

            winnerName.setString(thisGameWinner.hsName);
            winnerName.setFont(myFont);
            winnerName.setCharacterSize(100);
            winnerName.setFillColor(Color(255, 167,0));
            winnerName.setOutlineThickness(3);
            winnerName.setOutlineColor(Color::Red);
            //winnerName.setOrigin(winnerName.getLocalBounds().width / 2, winnerName.getLocalBounds().height / 2);
            winnerName.setPosition(Vector2f((xOffset + 644 ),(yOffset + 202 )));

            loserName.setFont(myFont);
            loserName.setCharacterSize(100);
            loserName.setFillColor(Color(255, 167,0));
            loserName.setOutlineThickness(3);
            loserName.setOutlineColor(Color::Red);
            //loserName.setOrigin(loserName.getLocalBounds().width / 2, loserName.getLocalBounds().height / 2);
            loserName.setPosition(Vector2f((xOffset + 630),(yOffset + 335)));

            shipsRemaining.setFont(myFont);
            shipsRemaining.setCharacterSize(100);
            shipsRemaining.setFillColor(Color(255, 167,0));
            shipsRemaining.setOutlineThickness(3);
            shipsRemaining.setOutlineColor(Color::Red);
            //shipsRemaining.setOrigin(shipsRemaining.getLocalBounds().width / 2,shipsRemaining.getLocalBounds().height / 2);
            shipsRemaining.setPosition(Vector2f((xOffset + 760),(yOffset + 566)));

            turnsTaken.setString(to_string(thisGameWinner.hsScore));
            turnsTaken.setFont(myFont);
            turnsTaken.setCharacterSize(100);
            turnsTaken.setFillColor(Color(255, 167,0));
            turnsTaken.setOutlineThickness(3);
            turnsTaken.setOutlineColor(Color::Red);
            //turnsTaken.setOrigin(turnsTaken.getLocalBounds().width / 2, turnsTaken.getLocalBounds().height / 2);
            turnsTaken.setPosition(Vector2f((xOffset + 593 ),(yOffset + 698 )));

            myWindow.setTitle("Game Over!");

            //Draw everything
            myWindow.draw(backPatternSprite);
            myWindow.draw(exitSprite);
            myWindow.draw(exitButton.getButton());
            myWindow.draw(musicOffButton.getButton());
            myWindow.draw(musOffSprite);
            myWindow.draw(musicOnButton.getButton());
            myWindow.draw(musOnSprite);
            myWindow.draw(gameoverSprite);
            myWindow.draw(winnerName);
            myWindow.draw(loserName);
            myWindow.draw(shipsRemaining);
            myWindow.draw(turnsTaken);
            myWindow.display();
            sleep(seconds(5));
            break;
        }
        case GameStates::State_HighScore: { //Highscore screen
            //Clear window
            myWindow.clear();

            vector<highScoreForm> scores = GetHighScores(); //Get the highscores from highscore text file

            myWindow.setTitle("High Scores!");

            //Check mouse hovering
            Mouse usrMouse;
            exitButton.isHovering(usrMouse, myWindow);
            musicOffButton.isHovering(usrMouse, myWindow);
            musicOnButton.isHovering(usrMouse, myWindow);
            exitHighScoreButton.isHovering(usrMouse, myWindow);

            highscoreSprite.setPosition(xOffset + 0, yOffset + 0);

            RectangleShape topScoreRec;
            topScoreRec.setSize(Vector2f(700, 100));
            topScoreRec.setPosition(xOffset + 420, yOffset + 345);

            RectangleShape secondScoreRec;
            secondScoreRec.setSize(Vector2f(700, 100));
            secondScoreRec.setPosition(xOffset + 420, yOffset + 445);

            RectangleShape thirdScoreRec;
            thirdScoreRec.setSize(Vector2f(700, 100));
            thirdScoreRec.setPosition(xOffset + 420, yOffset + 545);

            RectangleShape fourthScoreRec;
            fourthScoreRec.setSize(Vector2f(700, 100));
            fourthScoreRec.setPosition(xOffset + 420, yOffset + 645);

            RectangleShape fifthScoreRec;
            fifthScoreRec.setSize(Vector2f(700, 100));
            fifthScoreRec.setPosition(xOffset + 420, yOffset + 745);

            vector<RectangleShape> textSpaces = {topScoreRec, secondScoreRec, thirdScoreRec, fourthScoreRec, fifthScoreRec};

            //Draw everything
            myWindow.draw(backPatternSprite);
            myWindow.draw(highscoreSprite);
            myWindow.draw(exitHighScoreButton.getButton());
            myWindow.draw(exitSprite);
            myWindow.draw(exitButton.getButton());
            myWindow.draw(musicOffButton.getButton());
            myWindow.draw(musOffSprite);
            myWindow.draw(musicOnButton.getButton());
            myWindow.draw(musOnSprite);

            for (int i = 0; i < scores.size(); i++) {
                Text currentScore; //temp variable to read in text
                currentScore.setFont(myFont); //set font
                int currScore = scores.at(i).hsScore; //get score name
                string currName = scores.at(i).hsName; //get score

                currentScore.setString(currName + ": " + to_string(currScore) + " Turns."); //convert it to specific format
                currentScore.setCharacterSize(50); //set size
                currentScore.setFillColor(Color(255, 253, 145)); //set color

                //winnerName.setOrigin(winnerName.getLocalBounds().width / 2,winnerName.getLocalBounds().height / 2);
                //winnerName.setPosition(Vector2f((875 + (winnerBox.getLocalBounds().width / 2)), (375 + (winnerBox.getLocalBounds().height / 2))));

                currentScore.setOrigin((currentScore.getLocalBounds().width / 2),(currentScore.getLocalBounds().height / 2)); //set origin
                currentScore.setPosition(Vector2f((textSpaces.at(i).getPosition().x + (textSpaces.at(i).getGlobalBounds().width / 2)),(textSpaces.at(i).getPosition().y + (textSpaces.at(i).getGlobalBounds().height / 2)))); //set position
                myWindow.draw(currentScore); //Draw the high score in vector at(i)
            }

            myWindow.display(); //Display window
            break;
        }
    }
}
void Game::GameOverInitialization(){ //initializes things needed for game over condition
    vector<highScoreForm> scores = GetHighScores(); //get high scores

    bool isNewHighScore = false; //Check if game winner score qualifies as a new highscore.

    if(scores.size() < 5){//we have a vector of sorted data. If the size is less than 5, automatically add the score.
        scores.push_back(thisGameWinner); //add this game's winner to vector
        isNewHighScore = true; //it is a new highscore
    }else if(scores.at(scores.size() - 1).hsScore > thisGameWinner.hsScore){ //We have a vector of sorted data. If the bottom value is greater than game's winner user score, we already know it is a new highscore.
        scores.at(scores.size() - 1).hsScore = thisGameWinner.hsScore; //Swap values, sort later.
        scores.at(scores.size() - 1).hsName = thisGameWinner.hsName; //Swap values, sort later.
        isNewHighScore = true; //it is a new highscore
    }

    for(int i = 0; i < scores.size() - 1; i++){ //sort scores.
        //for every score
        if(scores.at(i).hsScore > scores.at(i + 1).hsScore){ //if current score is greater than the score after it...
            highScoreForm temp; //temp variable of struct highscoreform
            temp.hsScore = scores.at(i).hsScore; //hold score
            temp.hsName = scores.at(i).hsName; //hold name

            scores.at(i).hsScore = scores.at(i + 1).hsScore; //swap score
            scores.at(i).hsName = scores.at(i + 1).hsName; //swap name

            scores.at(i + 1).hsScore = temp.hsScore; //finish swapping score
            scores.at(i + 1).hsName = temp.hsName; //finish swapping name
            i = -1; //reset i
        }
    }

    if(isNewHighScore){ //if it was a new highscore...
        //write to highscore file
        ofstream writeToHighscore("Highscores.txt"); //open highscore file

        if(writeToHighscore.fail()){ //if file can't be opened
            cerr << "Error Opening High Score File!" << endl;
            exit (-1);
        }

        writeToHighscore << scores.size() << endl; //write the amount of scores

        for(int i = 0; i < scores.size(); i++){
            //for every score...
            if(scores.at(i).hsName.empty()){ //if the name is empty (this was included when bugfixing highscore operations earlier in development. I figure I'll keep this here, but I haven't had the issue in a long time.
                cerr << "Found Empty String. " << endl;
            }else{
                writeToHighscore << scores.at(i).hsName << " " << scores.at(i).hsScore << endl; //write the scores to file
            }
        }
        writeToHighscore.close(); //close file
    }
    eventWindow(isNewHighScore); //let user know if the score was a high score or not
}
vector<Game::highScoreForm> Game::GetHighScores(){ //function that returns highscores
    vector<highScoreForm> scores; //Vector of highscores
    fstream readHighScore("Highscores.txt"); //File of highscores. We want to read from it.

    if(!readHighScore.is_open()){ //Check for error
        cerr << "Error Opening High Score File!" << endl;
        exit(-1);
    }
    if(readHighScore.peek() == std::ifstream::traits_type::eof() ){ //Check if the file is empty
        cerr << "Empty File." << endl;
    }else{ //If file is not empty...
        int fileSize;
        readHighScore >> fileSize; //read in file size for the for loop.
        for(int i = 0; i < fileSize; i++){
            highScoreForm temp; //Temp object
            readHighScore >> temp.hsName >> temp.hsScore; //Read in data
            if(temp.hsName.empty()){ //fix for bug I had earlier
                cerr << "Found Empty Name. " << endl;
            }else{
                scores.push_back(temp); //Push back current score
            }
        }
    }
    readHighScore.close(); //Close your file ya heathen.
    return scores;
}
void Game::currentSelectedTile(Event usrEvent){ //sets the coordinates of target sprite
    targetVisible = true;
    int mouXCoord, mouYCoord;
    mouXCoord =  (201 + xOffset + (100 * ((int)(usrEvent.mouseButton.x - 201 - xOffset) / 100))); ////Convert mouse coordinates to grid tiles
    mouYCoord =  (201 + yOffset + (100 * ((int)(usrEvent.mouseButton.y - 201 - yOffset) / 100))); //Convert mouse coordinates to grid tiles
    targetSprite.setPosition(Vector2f(mouXCoord , mouYCoord ));
}
bool Game::gameOverCheck(User &userOne, User &userTwo, int currPlayer){ //check if game over condition has been met
    switch(currPlayer){ //check current player
        case 1:{ //if the current player is player one...
            if(userTwo.allShipsSunk()){
                thisGameWinner.hsName = userOne.getName(); //winner name is player 1 name
                thisGameWinner.hsScore = userOne.getTurns(); //winner score is player 1 turns
                loserName.setString(userTwo.getName()); //loser name is player 2 name
                shipsRemaining.setString(to_string(userOne.getShipsLeft())); //see how many ships user 1 had left
                return true;
            }
            break;
        }
        case 2:{ //if the current player is player two...
            if(userOne.allShipsSunk()){
                thisGameWinner.hsName = userTwo.getName(); //winner name is player 2 name
                thisGameWinner.hsScore = userTwo.getTurns(); //winner score is player 2 turns
                loserName.setString(userOne.getName()); //loser name is player 1 name
                shipsRemaining.setString(to_string(userTwo.getShipsLeft())); //see how many ships user 2 had left
                return true;
            }
            break;
        }
    }
    return false;
}

/* RADIO:
    *I would cycle between two songs, one for title screen, one for when the user is playing. Thats why I have two songNums.
    * However, if you wanted a complete radio, would just need a rand num generated each time a song was played, or a predetermined list of ints/songs.
    * Would have a folder of songs and a way to get song information for whatever song is selected.
    */
/*
int songNum = ( rand() % 4 ) + 1;
int secondSongNum;
secondSongNum = ( rand() % 4 ) + 1;
while(secondSongNum == songNum){ //Checks if secondSongNum is equal to first. If it is, keep generating until you get a new song.
secondSongNum = ( rand() % 3 ) + 1;
}
//The filepath formula here works because I had songs saved as "Track1", "Track2", etc. But if you were to include song info, might need to change this system.
string filePath1 = "C:\\Users\\lucas\\Documents\\battleShipExtraSongs\\Track" + to_string( songNum ) + ".ogg";
string filePath2 = "C:\\Users\\lucas\\Documents\\battleShipExtraSongs\\Track" + to_string(secondSongNum) + ".ogg";
if ( !mainMenuMusic.openFromFile( filePath1 ) ){
cerr << "mainMenuMusic File Not Found" << endl;
}
if ( !gameMusic.openFromFile( filePath2 ) ){
cerr << "Music File Not Found" << endl;
}
/*
 * To whoever is grading this: I made a list of absolute bops but unfortunately I don't think getting sued or
 * academic consequences is worth using a good songs in a small battleship game. Sorry :(
 * "Rocket 69"- Connie Allen. "Atom Bomb Baby"- Five Stars. "Uranium Fever"- Elliot Britt. "I Don't Want To Set The World On Fire"- Ink Spots.
 * "A Wonderful Guy"- Tex Beneke. "I'm Movin' Out"- The Rouses Brothers. "Orange Colored Sky"- Nat King Cole.
 *
 * TODO:Change Songs Back To Non-Illegal Ones When Submitting
 */


/*
 *                  Pre-Full Screen positions and adjustments
 *
 * playButton.setButton(Vector2f(770, 100), Vector2f(430, 350)); Pre-full screen
 * highScoreButton.setButton(Vector2f(1120, 70), Vector2f(280, 485)); Pre-full screen
 * fireButton.setButton(80, Vector2f(1325, 696)); Pre-full screen
 * validTextPos.setPosition(262, 176); Pre-fullscreen 
 * eventHappened.setPosition(Vector2f((262 + (validTextPos.getLocalBounds().width / 2)), (176 + (validTextPos.getLocalBounds().height / 3)))); Pre-full screen
 * whatNow.setPosition(Vector2f((262 + (validTextPos.getLocalBounds().width / 2)), (176 + (validTextPos.getLocalBounds().height / 3) * 2))); Pre-full screen
 * validTextPos.setPosition(262, 176);
 * eventHappened.setPosition(Vector2f((262 + (validTextPos.getLocalBounds().width / 2)), (176 + (validTextPos.getLocalBounds().height / 3))));
 * whatNow.setPosition(Vector2f((262 + (validTextPos.getLocalBounds().width / 2)), (176 + (validTextPos.getLocalBounds().height / 3) * 2)));
 * validTextPos.setPosition(262, 176);
 * eventHappened.setPosition(Vector2f((262 + (validTextPos.getLocalBounds().width / 2)), (176 + (validTextPos.getLocalBounds().height / 4)))); This was in "shot already selected" hence difference vertical placement
 * whatNow.setPosition(Vector2f((262 + (validTextPos.getLocalBounds().width / 2)), (176 + (validTextPos.getLocalBounds().height / 4) * 3))); This was in "shot already selected" hence difference vertical placement
 * titleSprite.setPosition(0, 0);
 * textRect.setPosition(470, 445);
 * myText.setPosition(Vector2f((360 + (textRect.getLocalBounds().width / 2)),(445 + (textRect.getLocalBounds().height / 2))));
 * gameoverSprite.setPosition(0, 0);
 * winnerBox.setPosition(875, 375);
 * winnerName.setPosition(Vector2f((875 + (winnerBox.getLocalBounds().width / 2)),(375 + (winnerBox.getLocalBounds().height / 2))));
 * loserBox.setPosition(850, 515);
 * loserName.setPosition(Vector2f((850 + (loserBox.getLocalBounds().width / 2)),(515 + (loserBox.getLocalBounds().height / 2))));
 * shipsLeftBox.setPosition(1085, 630);
 * shipsRemaining.setPosition(Vector2f((1085 + (shipsLeftBox.getLocalBounds().width / 2)),(630 + (shipsLeftBox.getLocalBounds().height / 2))));
 * turnsBox.setPosition(745, 760);
 * turnsTaken.setPosition(Vector2f((745 + (turnsBox.getLocalBounds().width / 2)),(760 + (turnsBox.getLocalBounds().height / 2))));
 * highscoreSprite.setPosition(0, 0);
 * topScoreRec.setPosition(420, 345);
 * secondScoreRec.setPosition(420, 445);
 * thirdScoreRec.setPosition(420, 545);
 * fourthScoreRec.setPosition(420, 645);
 * fifthScoreRec.setPosition(420, 745);
 * mouXCoord = 201 + xOffset + (100 * ((int) ((usrEvent.mouseButton.x - 201) / 100))); ////Convert mouse coordinates to grid tiles
 * mouYCoord = 201 + yOffset + (100 * ((int) ((usrEvent.mouseButton.y - 201) / 100))); //Convert mouse coordinates to grid tiles
 */