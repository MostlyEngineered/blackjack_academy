#include <iostream>
#include "card_classes.hpp"
using std::cout;
#include <stdlib.h>

int main(){
    Game myGame = Game(2, 500000, 1);
    // Game myGame;
    // Player player = Player('H', 1, 5);
    // Players players = Players(1, 500000);
    // Shoe *_test_shoe = new Shoe(1);
    // cout << "start game" << endl;
    myGame.playRound();
    // cout << "program works" << endl;
    return 0;
}