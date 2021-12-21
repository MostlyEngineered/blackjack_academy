#include <iostream>
#include <stdlib.h>

#include "game_classes.hpp"

using std::cout;


int main(){
    Game myGame = Game(1, 500000, 1);
    // Game myGame;
    // Player player = Player('H', 1, 5);
    // Players players = Players(1, 500000);
    // Shoe *_test_shoe = new Shoe(1);
    // cout << "start game" << endl;
    while (true)
    {
        myGame.playRound();
    }
    // cout << "program works" << endl;
    return 0;
}