#include <iostream>
// #include "card_classes.hpp"
#include "game_classes.hpp"
using std::cout;

int main(){

    Game myGame = Game(1, 500000, 1);

    myGame.playRound();

    return 0;
}