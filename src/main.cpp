#include <iostream>
#include "card_classes.hpp"
using std::cout;

int main(){

    Game myGame = Game(1, 500000, 1);
    // Game myGame;
    // Player player = Player('H');
    Players players = Players(1, 500000);
    myGame.playRound();
    cout << "program works" << endl;
    return 0;
}