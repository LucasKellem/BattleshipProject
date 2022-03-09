#include "Game.h"
#include <ctime>
#include <string>

using namespace std;
using namespace sf;

int main() {

    srand(time(0)); //Seed your rand or die heathen
    rand() % 100; //Throwaway
    Game game;

    //Player One
    User PlayerOne;
    //Initialize Ships For Player One
    PlayerOne.SetShips();
    //Print The Ships For Player One (REMOVE BEFORE SUBMITTING!!!!!!)
    PlayerOne.printShips();

    rand() % 10;

    //Player Two
    User PlayerTwo;
    //Initialize Ships For Player Two
    PlayerTwo.SetShips();
    //Print The Ships For Player Two (REMOVE BEFORE SUBMITTING!!!!!!)
    PlayerTwo.printShips();

    //Member Function Of Game, Initializes Game
    game.startGame(PlayerOne, PlayerTwo);

    //Run The Game, And Use Return Of Game As Main() Return.
    return game.run(PlayerOne,PlayerTwo);
}

