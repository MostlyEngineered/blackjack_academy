#include <iostream>
#include "card_classes.hpp"
using std::cout;

int main(){

    Game myGame = Game(1, 500000, 1);
    // Game myGame;
    // Player player = Player('H');
    myGame.playRound();
    cout << "program works" << endl;
    return 0;
}